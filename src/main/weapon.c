
#include <nusys.h>
#include <nualsgi_n.h>
#include "common.h"
#include "main.h"
#include "math.h"
#include "player.h"
#include "collision.h"
#include "FPGraphics.h"
#include "HUD.h"




Projectile ProjectileArray[MAXBULLETS];



WeaponClass Pistol;
WeaponClass AssaultRifle;

void InitWeaponClasses()
{
    

    AssaultRifle.BaseDamage = 10;
    AssaultRifle.BulletLife = 200;
    AssaultRifle.BulletSpeed = 60;
    AssaultRifle.ErrorMax = 800;
    AssaultRifle.FiringRate = 2;
    AssaultRifle.MagazineSize = 60;
    AssaultRifle.MaxAmmo = 600;
    AssaultRifle.ReloadTime = 35;
    AssaultRifle.CameraImpulseY = 3;
    AssaultRifle.MaxImpulseY = 15;

    AssaultRifle.Reticle = (Gfx*)&AssaultRifleReticleGFX;

    AssaultRifle.Bandolier.Idle =           (AnimeHolster*)&AR_Idle;
    AssaultRifle.Bandolier.Fire =           (AnimeHolster*)&AR_Fire;
    AssaultRifle.Bandolier.ReloadEmpty =    (AnimeHolster*)&AR_Reload_Empty;
    AssaultRifle.Bandolier.ReloadFull =     (AnimeHolster*)&AR_Reload_Full;
    AssaultRifle.Bandolier.Melee =           (AnimeHolster*)&AR_Melee;


    
    

    Pistol.BaseDamage = 25;
    Pistol.BulletLife = 250;
    Pistol.BulletSpeed = 70;
    Pistol.ErrorMax = 500;
    Pistol.FiringRate = 9;
    Pistol.MagazineSize = 12;
    Pistol.MaxAmmo = 120;
    Pistol.ReloadTime = 20;
    Pistol.CameraImpulseY = 12;
    Pistol.MaxImpulseY = 30;
    
    Pistol.Reticle = (Gfx*)&PistolReticleGFX;


    Pistol.Bandolier.Idle =           (AnimeHolster*)&HP_Idle;
    Pistol.Bandolier.Fire =           (AnimeHolster*)&HP_Fire;
    Pistol.Bandolier.ReloadEmpty =    (AnimeHolster*)&HP_Reload_Empty;
    Pistol.Bandolier.ReloadFull =     (AnimeHolster*)&HP_ReloadFull;
    Pistol.Bandolier.Melee =           (AnimeHolster*)&HP_Melee;
    
}



void initProjectiles()
{
    for (int ThisBullet = 0; ThisBullet < MAXBULLETS; ThisBullet++)
    {
        Projectile* LocalBullet = (Projectile*)&ProjectileArray[ThisBullet];
        LocalBullet->Status = BULLET_INACTIVE;
    }
}

void SwapGun(int PlayerIndex)
{
    Player* LocalPlayer = (Player*)&GamePlayers[PlayerIndex];
    
    LocalPlayer->SelectedWeapon ^= 1;

    WeaponEquipment* LocalEquip = (WeaponEquipment*)&LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon];
    WeaponClass* LocalClass = (WeaponClass*)LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon].Class;

    

    
    LocalPlayer->FPAnime = LocalClass->Bandolier.Idle;
    LocalPlayer->FPAnimeTimer.MaxTime = LocalClass->Bandolier.Idle->FrameCount;
    LocalPlayer->FPAnimeTimer.CurrentTime = 0;
    
    LocalPlayer->ActionBits &= ~ACTIONSWAPGUN;
    LocalPlayer->ActionBits &= ~ACTIONRELOAD;
    //LocalPlayer->StatusBits |= STATUSSWAPGUN;
}

void PlayerMelee(int PlayerIndex)
{
    Player* LocalPlayer = (Player*)&GamePlayers[PlayerIndex];

    WeaponEquipment* LocalEquip = (WeaponEquipment*)&LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon];
    WeaponClass* LocalClass = (WeaponClass*)LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon].Class;
    
    LocalPlayer->ActionBits &= ~ACTIONMELEE;
    
    //Check for existing status preventing a melee.
    if (LocalPlayer->StatusBits & STATUSSWAPGUN)
    {
        return;
    }
    if (LocalPlayer->StatusBits & STATUSMELEE)
    {
        return;
    }

    //Overwrite status that melee priority
    if (LocalPlayer->StatusBits & STATUSRELOADING)
    {
        LocalPlayer->StatusBits &= ~ STATUSRELOADING;
    }

    
    LocalPlayer->StatusBits |= STATUSMELEE;
    LocalPlayer->FPAnime = LocalClass->Bandolier.Melee;
    LocalPlayer->FPAnimeTimer.MaxTime = LocalClass->Bandolier.Melee->FrameCount;
    LocalPlayer->FPAnimeTimer.CurrentTime = 0;
    
}
void ReloadWeapon(int PlayerIndex)
{
    Player* LocalPlayer = (Player*)&GamePlayers[PlayerIndex];

    WeaponEquipment* LocalEquip = (WeaponEquipment*)&LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon];
    WeaponClass* LocalClass = (WeaponClass*)LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon].Class;
    
    LocalPlayer->ActionBits &= ~ACTIONRELOAD;
    
    //Check for existing status preventing a reload.
    if (LocalPlayer->StatusBits & STATUSRELOADING)
    {
        return;
    }
    if (LocalPlayer->StatusBits & STATUSMELEE)
    {
        return;
    }
    if (LocalPlayer->StatusBits & STATUSSWAPGUN)
    {
        return;
    }

    
    LocalPlayer->StatusBits |= STATUSRELOADING;
    LocalPlayer->FPAnime = LocalClass->Bandolier.ReloadEmpty;
    LocalPlayer->FPAnimeTimer.MaxTime = LocalClass->Bandolier.ReloadEmpty->FrameCount;
    LocalPlayer->FPAnimeTimer.CurrentTime = 0;
    
}

void LoadWeaponAmmo(int PlayerIndex)
{
    Player* LocalPlayer = (Player*)&GamePlayers[PlayerIndex];
    WeaponEquipment* LocalEquip = (WeaponEquipment*)&LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon];
    WeaponClass* LocalClass = (WeaponClass*)LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon].Class;

    int AmmoAmount = LocalEquip->Ammo;
    if (AmmoAmount > LocalClass->MagazineSize)
    {
        AmmoAmount = LocalClass->MagazineSize;
    }

    LocalEquip->Ammo -= AmmoAmount;
    LocalEquip->Magazine = AmmoAmount;
}


void FireBullet(int PlayerIndex)
{
    
    Player* LocalPlayer = (Player*)&GamePlayers[PlayerIndex];

    LocalPlayer->ActionBits &= ~ACTIONFIRE;

    //check if fire
    if (LocalPlayer->FFrames > 0)
    {
        //PRINTF("FireBulletCancel - FFrames - %d\n", PlayerIndex);
        return;
    }
    
    if (LocalPlayer->StatusBits & STATUSRELOADING)
    {
        //PRINTF("FireBulletCancel - Reload - %d\n", PlayerIndex);
        return;
    }
    if (LocalPlayer->StatusBits & STATUSSWAPGUN)
    {
        //PRINTF("FireBulletCancel - Swapping - %d\n", PlayerIndex);
        return;
    }
    if (LocalPlayer->StatusBits & STATUSMELEE)
    {
        //PRINTF("FireBulletCancel - Melee - %d\n", PlayerIndex);
        return;
    }

    

    AffineMtx BulletTrajectory;
    Vector BulletOrigin;
    Vector CPUOrigin;
    Vector Error;
    Vector CPUUP;
    Vector CPUDirection;
    CPUUP[0] = 0;
    CPUUP[1] = 0;
    CPUUP[2] = 1;
    WeaponClass* LocalWeapon;
    WeaponEquipment* LocalEquipment;


    LocalEquipment = (WeaponEquipment*)&LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon];
    LocalWeapon = (WeaponClass*)LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon].Class;
    
    if (LocalEquipment->Magazine > 0)
    {
        LocalEquipment->Magazine--;
        LocalPlayer->StatusBits |= STATUSFIRING;

        LocalPlayer->FPAnime = LocalWeapon->Bandolier.Fire;
        LocalPlayer->FPAnimeTimer.CurrentTime = 0;
        LocalPlayer->FPAnimeTimer.MaxTime = LocalWeapon->Bandolier.Fire->FrameCount;
    }
    else
    {   
        //no ammo
        LocalPlayer->ActionBits |= ACTIONRELOAD;
        return;
        
    }

    LocalPlayer->FFrames = LocalWeapon->FiringRate;
    if (LocalPlayer->IsCPU == 0)
    {
        PGCamera* LocalCamera = (PGCamera*)&GameCameras[PlayerIndex];
        //camera impulse
        LocalCamera->Impulse += LocalWeapon->CameraImpulseY;
        if (LocalCamera->Impulse > LocalWeapon->MaxImpulseY)
        {
            LocalCamera->Impulse = LocalWeapon->MaxImpulseY;
        }
    }


    for (int ThisBullet = 0; ThisBullet < MAXBULLETS; ThisBullet++)
    {
        if (ProjectileArray[ThisBullet].Status == BULLET_INACTIVE)
        { 
            Projectile* LocalBullet = (Projectile*)&ProjectileArray[ThisBullet];
            LocalBullet->Status = BULLET_ACTIVE;
            LocalBullet->InitialSpeed = LocalWeapon->BulletSpeed;
            LocalBullet->Damage = LocalWeapon->BaseDamage;
            LocalBullet->Lifespan = LocalWeapon->BulletLife;
            LocalBullet->Distance = 0;
            LocalBullet->Owner = PlayerIndex;
            LocalBullet->RGB = GetRGBA16(255, 255, 0, 255);
            
            
            //Locate Bullet and direct trajectory.
            LocalBullet->Location.Position[0] = LocalPlayer->Location.Position[0];
            LocalBullet->Location.Position[1] = LocalPlayer->Location.Position[1];
            LocalBullet->Location.Position[2] = LocalPlayer->Location.Position[2] + LocalPlayer->Height;

            if (LocalPlayer->IsCPU == 0)
            {
                LocalBullet->Location.Angle[0] = GameCameras[PlayerIndex].Location.Angle[0];
                LocalBullet->Location.Angle[1] = GameCameras[PlayerIndex].Location.Angle[1];
                LocalBullet->Location.Angle[2] = GameCameras[PlayerIndex].Location.Angle[2];
            }
            else
            {
                LocalBullet->Location.Angle[0] = LocalPlayer->Location.Angle[0];
                LocalBullet->Location.Angle[1] = LocalPlayer->Location.Angle[1];
                LocalBullet->Location.Angle[2] = LocalPlayer->Location.Angle[2];
            }
            

            if (LocalPlayer->ZTarget > 0)
            {
                BulletOrigin[0] = GamePlayers[LocalPlayer->ZTarget].Location.Position[0] - LocalPlayer->Location.Position[0];
                BulletOrigin[1] = GamePlayers[LocalPlayer->ZTarget].Location.Position[1] - LocalPlayer->Location.Position[1];
                BulletOrigin[2] = (GamePlayers[LocalPlayer->ZTarget].Location.Position[2] + GamePlayers[LocalPlayer->ZTarget].Height * 0.7f) - (LocalPlayer->Location.Position[2] + LocalPlayer->Height);

                NormalizeVector(BulletOrigin);
                BulletOrigin[0] *= 100.0f;
                BulletOrigin[1] *= 100.0f;
                BulletOrigin[2] *= 100.0f;
                BulletOrigin[0] += LocalPlayer->Location.Position[0];
                BulletOrigin[1] += LocalPlayer->Location.Position[1];
                BulletOrigin[2] += LocalPlayer->Location.Position[2] + LocalPlayer->Height;
                

                Error[0] = (BulletOrigin[0]) - ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);
                Error[1] = (BulletOrigin[1]) - ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);
                Error[2] = (BulletOrigin[2]) - ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);
                

                Error[0] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);
                Error[1] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);
                Error[2] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);

                if (LocalPlayer->IsCPU == 0)
                {
                    TransformMatrix
                    (
                        BulletTrajectory,
                        GameCameras[PlayerIndex].Location.Position, 
                        Error, 
                        GameCameras[PlayerIndex].UpVector
                    );
                }
                else
                {
                    CPUOrigin[0] = LocalPlayer->Location.Position[0];
                    CPUOrigin[1] = LocalPlayer->Location.Position[1];
                    CPUOrigin[2] = LocalPlayer->Location.Position[2] + LocalPlayer->Height;
                    TransformMatrix
                    (
                        BulletTrajectory,
                        CPUOrigin, 
                        Error, 
                        CPUUP
                    );
                }
                

                LocalBullet->Location.VelocityFront[0] = BulletTrajectory[0][2] * LocalBullet->InitialSpeed;
                LocalBullet->Location.VelocityFront[1] = BulletTrajectory[1][2] * LocalBullet->InitialSpeed;
                LocalBullet->Location.VelocityFront[2] = BulletTrajectory[2][2] * LocalBullet->InitialSpeed;
                
                
                return;
            }
            else
            {
                //no z-target available. fire from camera
                
                //apply error
                if (LocalPlayer->IsCPU == 0)
                {
                    PGCamera* LocalCamera = (PGCamera*)&GameCameras[PlayerIndex];
                
                    Error[0] = LocalCamera->LookAt[0] - ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);
                    Error[1] = LocalCamera->LookAt[1] - ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);
                    Error[2] = LocalCamera->LookAt[2] - ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);

                    Error[0] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);
                    Error[1] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);
                    Error[2] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);

                    TransformMatrix(BulletTrajectory,LocalCamera->Location.Position, Error, LocalCamera->UpVector);

                    LocalBullet->Location.VelocityFront[0] = BulletTrajectory[0][2] * (LocalBullet->InitialSpeed);
                    LocalBullet->Location.VelocityFront[1] = BulletTrajectory[1][2] * (LocalBullet->InitialSpeed);
                    LocalBullet->Location.VelocityFront[2] = BulletTrajectory[2][2] * (LocalBullet->InitialSpeed);
                }
                else
                {
                    CPUOrigin[0] = LocalPlayer->Location.Position[0];
                    CPUOrigin[1] = LocalPlayer->Location.Position[1];
                    CPUOrigin[2] = LocalPlayer->Location.Position[2] + LocalPlayer->Height;

                    CPUDirection[0] = 0;
                    CPUDirection[1] = 100;
                    CPUDirection[2] = 0;
                    AlignZVector(CPUDirection, LocalPlayer->Location.Angle[2]);
                    CPUDirection[0] += LocalPlayer->Location.Position[0];
                    CPUDirection[1] += LocalPlayer->Location.Position[1];
                    CPUDirection[2] += LocalPlayer->Location.Position[2] + LocalPlayer->Height;

                    Error[0] = CPUDirection[0] - ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);
                    Error[1] = CPUDirection[1] - ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);
                    Error[2] = CPUDirection[2] -  ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);

                    Error[0] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);
                    Error[1] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);
                    Error[2] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);

                    TransformMatrix(BulletTrajectory,CPUOrigin, Error, CPUUP);

                    LocalBullet->Location.VelocityFront[0] = BulletTrajectory[0][2] * (LocalBullet->InitialSpeed);
                    LocalBullet->Location.VelocityFront[1] = BulletTrajectory[1][2] * (LocalBullet->InitialSpeed);
                    LocalBullet->Location.VelocityFront[2] = BulletTrajectory[2][2] * (LocalBullet->InitialSpeed);
                }
                
                
                
                
                return;
            }

            
        }
    }
}


int MoveProjectile(int BulletIndex) 
{
    
    Projectile *LocalBullet = (Projectile*)&ProjectileArray[BulletIndex];
    LocalBullet->Location.LastPosition[0] = LocalBullet->Location.Position[0];
    LocalBullet->Location.LastPosition[1] = LocalBullet->Location.Position[1];
    LocalBullet->Location.LastPosition[2] = LocalBullet->Location.Position[2];
    
    LocalBullet->Location.Position[0] = LocalBullet->Location.LastPosition[0] - LocalBullet->Location.VelocityFront[0];
    LocalBullet->Location.Position[1] = LocalBullet->Location.LastPosition[1] - LocalBullet->Location.VelocityFront[1];
    LocalBullet->Location.Position[2] = LocalBullet->Location.LastPosition[2] - LocalBullet->Location.VelocityFront[2]; 
    
}

void CheckProjectiles()
{
    for (int ThisBullet = 0; ThisBullet < MAXBULLETS; ThisBullet++)
    {
        if (ProjectileArray[ThisBullet].Status == BULLET_INACTIVE)
        {
            continue;
        }

        MoveProjectile(ThisBullet);
        CheckProjectileCollision(ThisBullet);

    }
}




static Vtx BulletBox[8] = {
	{  1,  8,  1,  0, 0, 0, 255, 255, 255, 255, },
	{  1,  8, -1,  0, 0, 0, 255, 255, 255, 255, },
	{ -1,  8,  1,  0, 0, 0, 255, 255, 255, 255, },
	{ -1,  8, -1,  0, 0, 0, 255, 255, 255, 255, },
	{  1, -8,  1,  0, 0, 0, 255, 255, 255, 255, },
	{  1, -8, -1,  0, 0, 0, 255, 255, 255, 255, },
	{ -1, -8,  1,  0, 0, 0, 255, 255, 255, 255, },
	{ -1, -8, -1,  0, 0, 0, 255, 255, 255, 255, },
};

Gfx logo_bulletbox[] = {
    gsDPPipeSync(),
    //gsSPSetGeometryMode(G_SHADE | G_ZBUFFER | G_CULL_BACK),
    //gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),

    
	gsSPVertex(&(BulletBox[0]), 8, 0),
	gsSP1Triangle(0, 2, 1, 0),//1
	gsSP1Triangle(2, 3, 1, 0),//1
	gsSP1Triangle(4, 5, 6, 0),//2
	gsSP1Triangle(5, 7, 6, 0),//2
	gsSP1Triangle(7, 3, 6, 0),//3
	gsSP1Triangle(3, 2, 6, 0),//3
    gsSP1Triangle(0, 1, 4, 0),//4
	gsSP1Triangle(1, 5, 4, 0),//4
	gsSP1Triangle(0, 4, 2, 0),//5
	gsSP1Triangle(4, 6, 2, 0),//5
    gsSP1Triangle(3, 7, 5, 0),//6
	gsSP1Triangle(3, 5, 1, 0),//6

    gsSPEndDisplayList(),
};

