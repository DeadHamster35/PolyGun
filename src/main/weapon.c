
#include <nusys.h>
#include <nualsgi_n.h>
#include "common.h"
#include "main.h"
#include "math.h"
#include "player.h"
#include "levels.h"
#include "collision.h"
#include "FPGraphics.h"
#include "HUD.h"




Projectile ProjectileArray[MAXBULLETS + 1];


WeaponClass Pistol;
WeaponClass AssaultRifle;
WeaponClass PlasmaRifle;

WeaponClass *WeaponClassArray[WEAPONARRAYCOUNT] = {&AssaultRifle, &Pistol, &PlasmaRifle};

void InitWeaponClasses()
{
    

    AssaultRifle.BaseDamage = 5;
    AssaultRifle.BulletLife = 4000;
    AssaultRifle.BulletSpeed = 400;
    AssaultRifle.ErrorMax = 800;
    AssaultRifle.FiringRate = 3;
    AssaultRifle.MagazineSize = 60;
    AssaultRifle.MaxAmmo = 600;
    AssaultRifle.ReloadTime = 35;
    AssaultRifle.CameraImpulseY = 3;
    AssaultRifle.MaxImpulseY = 15;
    AssaultRifle.ShotsFired = 1;
    AssaultRifle.AmmoPerRound = 1;
    AssaultRifle.HeatPerRound = 0;
    AssaultRifle.AgePerRound = 0;
    AssaultRifle.ZoomLevel[0] = -1;
    AssaultRifle.ZoomLevel[1] = -1;
    AssaultRifle.WeaponFlags = 0;

    AssaultRifle.HUD.Reticle = (Gfx*)&AssaultRifleReticleGFX;
    AssaultRifle.HUD.PickupIcon = (Gfx*)&Draw_IconHUD_AR_T;
    AssaultRifle.HUD.ReticleSize = 14;

    AssaultRifle.Bandolier.Idle =           (AnimeHolster*)&AR_Idle;
    AssaultRifle.Bandolier.Fire =           (AnimeHolster*)&AR_Fire;
    AssaultRifle.Bandolier.ReloadEmpty =    (AnimeHolster*)&AR_Reload_Empty;
    AssaultRifle.Bandolier.ReloadFull =     (AnimeHolster*)&AR_Reload_Full;
    AssaultRifle.Bandolier.Melee =           (AnimeHolster*)&AR_Melee;


    
    

    Pistol.BaseDamage = 25;
    Pistol.BulletLife = 4000;
    Pistol.BulletSpeed = 500;
    Pistol.ErrorMax = 500;
    Pistol.FiringRate = 9;
    Pistol.MagazineSize = 12;
    Pistol.MaxAmmo = 120;
    Pistol.ReloadTime = 20;
    Pistol.CameraImpulseY = 12;
    Pistol.MaxImpulseY = 30;
    Pistol.ShotsFired = 1;
    Pistol.AmmoPerRound = 1;    
    Pistol.HeatPerRound = 0;
    Pistol.AgePerRound = 0;
    Pistol.ZoomLevel[0] = 20;
    Pistol.ZoomLevel[1] = -1;
    Pistol.WeaponFlags = 0;
    
    Pistol.HUD.Reticle = (Gfx*)&PistolReticleGFX;
    Pistol.HUD.PickupIcon = (Gfx*)&Draw_IconHUD_Pistol_T;
    Pistol.HUD.ReticleSize = 8;

    Pistol.Bandolier.Idle =           (AnimeHolster*)&HP_Idle;
    Pistol.Bandolier.Fire =           (AnimeHolster*)&HP_Fire;
    Pistol.Bandolier.ReloadEmpty =    (AnimeHolster*)&HP_Reload_Empty;
    Pistol.Bandolier.ReloadFull =     (AnimeHolster*)&HP_ReloadFull;
    Pistol.Bandolier.Melee =           (AnimeHolster*)&HP_Melee;


    



    PlasmaRifle.BaseDamage = 12;
    PlasmaRifle.BulletLife = 175;
    PlasmaRifle.BulletSpeed = 75;
    PlasmaRifle.ErrorMax = 700;
    PlasmaRifle.FiringRate = 5;
    PlasmaRifle.MagazineSize = 100;  
    PlasmaRifle.MaxAmmo = 100;
    PlasmaRifle.ReloadTime = 20;
    PlasmaRifle.CameraImpulseY = 3;
    PlasmaRifle.MaxImpulseY = 2;
    PlasmaRifle.ShotsFired = 1;
    PlasmaRifle.AmmoPerRound = 1;
    PlasmaRifle.HeatPerRound = 3;
    PlasmaRifle.AgePerRound = 1;
    PlasmaRifle.ZoomLevel[0] = -1;
    PlasmaRifle.ZoomLevel[1] = -1;
    PlasmaRifle.WeaponFlags = 0;
    PlasmaRifle.WeaponFlags |= WEAPON_HEAT;

    PlasmaRifle.HUD.Reticle = (Gfx*)&PlasmaRifleReticleGFX;
    PlasmaRifle.HUD.PickupIcon = (Gfx*)&Draw_IconHUD_PlasmaRifle_T;
    PlasmaRifle.HUD.ReticleSize = 14;
    
    PlasmaRifle.Bandolier.Idle =           (AnimeHolster*)&PlasmaRifle_Idle;
    PlasmaRifle.Bandolier.Fire =           (AnimeHolster*)&PlasmaRifle_Fire;
    PlasmaRifle.Bandolier.ReloadEmpty =    (AnimeHolster*)&PlasmaRifle_Overheat;
    PlasmaRifle.Bandolier.ReloadFull =     (AnimeHolster*)&PlasmaRifle_Overheat;
    PlasmaRifle.Bandolier.Melee =           (AnimeHolster*)&PlasmaRifle_Melee;
    
}



void initProjectiles()
{
    for (int ThisBullet = 0; ThisBullet < MAXBULLETS; ThisBullet++)
    {
        Projectile* LocalBullet = (Projectile*)&ProjectileArray[ThisBullet];
        LocalBullet->Status = BULLET_INACTIVE;
        
    }
}


int CheckPickups(int PlayerIndex)
{
    
    int TargetPickup = -1;
    Vector Source, Target;
    
    Source[0] = GamePlayers[PlayerIndex].Location.Position[0];
    Source[1] = GamePlayers[PlayerIndex].Location.Position[1];
    Source[2] = GamePlayers[PlayerIndex].Location.Position[2];

    float ClosestDistance  = 999999999.0f;

    for (int ThisPick = 0; ThisPick < TotalStaticPicks; ThisPick++)
    {
        StaticPickup* TargetPick = (StaticPickup*)&StaticPickArray[ThisPick];

        Target[0] = TargetPick->Position[0];
        Target[1] = TargetPick->Position[1];
        Target[2] = TargetPick->Position[2];
        float CheckDistance = GetDistance(Target, Source);
        if (CheckDistance < ClosestDistance)
        {
            ClosestDistance = CheckDistance;
            TargetPickup = ThisPick;
        }
    }

    if (ClosestDistance < PICKUPRADIUS)
    {
        return TargetPickup;
    }
    return -1;
}

int GetWeaponIndex(WeaponClass* Class)
{
    for (int ThisWeap = 0; ThisWeap < WEAPONARRAYCOUNT; ThisWeap++)
    {
        if (WeaponClassArray[ThisWeap] == Class)
        {
            return ThisWeap;
        }
    }
    return -1;
}


void PickupObject(int PlayerIndex)
{
    Player* LocalPlayer = (Player*)&GamePlayers[PlayerIndex];

    LocalPlayer->ActionBits &= ~ACTIONPICKUP;
    LocalPlayer->ActionBits &= ~ACTIONRELOAD;

    if (LocalPlayer->ClosestPickup == -1)
    {
        return;
    }
    StaticPickup* LocalPick = (StaticPickup*)&StaticPickArray[LocalPlayer->ClosestPickup];
    WeaponEquipment* LocalWeapon = (WeaponEquipment*)&LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon];

    LocalPlayer->StatusBits &= ~STATUSZOOM;
    LocalPlayer->ZoomFloat = 1.0f;
    LocalPlayer->ZoomLevel = 0;


    switch (LocalPick->PickupType)
    {
        case PICKUPTYPE_WEAPON:
        {
            short HeldData = GetWeaponIndex(LocalWeapon->Class);

            LocalWeapon->Class = WeaponClassArray[LocalPick->PickupClass];
            LocalPick->PickupClass = HeldData;

            if (LocalWeapon->Class->WeaponFlags & WEAPON_HEAT)
            {
                HeldData = LocalWeapon->Heat;
            }
            else
            {
                HeldData = LocalWeapon->Ammo;
            }


            if (LocalPick->Ammo <= 0)
            {
                if (LocalWeapon->Class->WeaponFlags & WEAPON_HEAT)
                {
                    LocalWeapon->Age = 0;
                }
                else
                {
                    LocalWeapon->Ammo = LocalWeapon->Class->MaxAmmo;
                }
                
            }
            else
            {
                if (LocalWeapon->Class->WeaponFlags & WEAPON_HEAT)
                {
                    LocalWeapon->Age = LocalPick->Ammo;
                }
                else
                {
                    LocalWeapon->Ammo = LocalPick->Ammo;
                }
            }

            LocalPick->Ammo = HeldData;




            if (LocalWeapon->Class->WeaponFlags & WEAPON_HEAT)
            {
                HeldData = LocalWeapon->Age;
            }
            else
            {
                HeldData = LocalWeapon->Magazine;
            }
            
            

            if (LocalPick->Magazine <= 0)
            {
                if (LocalWeapon->Class->WeaponFlags & WEAPON_HEAT)
                {
                    LocalWeapon->Age = LocalWeapon->Class->MagazineSize;
                }
                else
                {
                    LocalWeapon->Magazine = LocalWeapon->Class->MagazineSize;
                }
                
            }
            else
            {
                if (LocalWeapon->Class->WeaponFlags & WEAPON_HEAT)
                {
                    LocalWeapon->Age = LocalPick->Magazine;
                }
                else
                {
                    LocalWeapon->Magazine = LocalPick->Magazine;
                }
            }

            LocalPick->Magazine = HeldData;
            
            LocalPlayer->FPAnime = LocalWeapon->Class->Bandolier.Idle;
            LocalPlayer->FPAnimeTimer.MaxTime = LocalWeapon->Class->Bandolier.Idle->FrameCount;
            LocalPlayer->FPAnimeTimer.CurrentTime = 0;
            LocalPlayer->FPAnimeTimer.ActionFrame = LocalWeapon->Class->Bandolier.Idle->ActionFrame;
            break;
        }


        default:
        {
            break;
        }
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
    LocalPlayer->FPAnimeTimer.ActionFrame = LocalClass->Bandolier.Idle->ActionFrame;
    
    LocalPlayer->ActionBits &= ~ACTIONSWAPGUN;
    LocalPlayer->ActionBits &= ~ACTIONRELOAD;
    LocalPlayer->StatusBits &= ~STATUSZOOM;
    LocalPlayer->StatusBits &= ~STATUSRELOADING;
    LocalPlayer->ZoomFloat = 1.0f;
    LocalPlayer->ZoomLevel = 0;
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

    LocalPlayer->StatusBits &= ~STATUSZOOM;
    LocalPlayer->ZoomFloat = 1.0f;
    LocalPlayer->ZoomLevel = 0;

    LocalPlayer->StatusBits |= STATUSMELEE;
    LocalPlayer->FPAnime = LocalClass->Bandolier.Melee;
    LocalPlayer->FPAnimeTimer.MaxTime = LocalClass->Bandolier.Melee->FrameCount;
    LocalPlayer->FPAnimeTimer.CurrentTime = 0;
    LocalPlayer->FPAnimeTimer.ActionFrame = LocalClass->Bandolier.Melee->ActionFrame;
    
}
void ReloadWeapon(int PlayerIndex)
{
    Player* LocalPlayer = (Player*)&GamePlayers[PlayerIndex];

    WeaponEquipment* LocalEquip = (WeaponEquipment*)&LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon];
    WeaponClass* LocalClass = (WeaponClass*)LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon].Class;
    
    LocalPlayer->ActionBits &= ~ACTIONRELOAD;
    
    //Check for existing status preventing a reload.
    
    if (LocalEquip->Magazine >= LocalClass->MagazineSize)
    {
        //cheeky bastard bxr
        LocalPlayer->StatusBits &= ~STATUSMELEE;
        return;
    }
    if (LocalClass->WeaponFlags & WEAPON_HEAT)
    {   
        //battery weapon
        return;
    }
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

    LocalPlayer->StatusBits &= ~STATUSZOOM;
    LocalPlayer->ZoomFloat = 1.0f;
    LocalPlayer->ZoomLevel = 0;

    LocalPlayer->StatusBits |= STATUSRELOADING;
    if (LocalEquip->Ammo == 0)
    {
        LocalPlayer->FPAnime = LocalClass->Bandolier.ReloadEmpty;
        LocalPlayer->FPAnimeTimer.MaxTime = LocalClass->Bandolier.ReloadEmpty->FrameCount;
        LocalPlayer->FPAnimeTimer.CurrentTime = 0;
        LocalPlayer->FPAnimeTimer.ActionFrame = LocalClass->Bandolier.ReloadEmpty->ActionFrame;
    }
    else
    {
        LocalPlayer->FPAnime = LocalClass->Bandolier.ReloadFull;
        LocalPlayer->FPAnimeTimer.MaxTime = LocalClass->Bandolier.ReloadFull->FrameCount;
        LocalPlayer->FPAnimeTimer.CurrentTime = 0;
        LocalPlayer->FPAnimeTimer.ActionFrame = LocalClass->Bandolier.ReloadFull->ActionFrame;
    }
    
    
}

void LoadWeaponAmmo(int PlayerIndex)
{
    Player* LocalPlayer = (Player*)&GamePlayers[PlayerIndex];
    WeaponEquipment* LocalEquip = (WeaponEquipment*)&LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon];
    WeaponClass* LocalClass = (WeaponClass*)LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon].Class;
    int LoadedAmount = LocalClass->MagazineSize;
    int AmmoAmount = LoadedAmount - LocalEquip->Magazine;
    if (AmmoAmount > LocalEquip->Ammo)
    {
        AmmoAmount = LocalEquip->Ammo;
        LoadedAmount = LocalEquip->Ammo;
    }
    LocalEquip->Ammo -= AmmoAmount;
    LocalEquip->Magazine = LoadedAmount;
}

bool CheckMagazine(int PlayerIndex)
{
    Player* LocalPlayer = (Player*)&GamePlayers[PlayerIndex];
    WeaponEquipment *LocalEquipment = (WeaponEquipment*)&LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon];
    WeaponClass *LocalWeapon = (WeaponClass*)LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon].Class;

    if (LocalWeapon->WeaponFlags & WEAPON_HEAT)
    {
        //battery
        if ((LocalEquipment->Heat < 100) && (LocalEquipment->Age >= LocalWeapon->AgePerRound))
        {
            LocalEquipment->Heat += LocalWeapon->HeatPerRound;
            LocalEquipment->Age -= LocalWeapon->AgePerRound;
            return true;
        }
        
        return false;
        
    }


    //ammo
    if (LocalEquipment->Magazine > 0)
    {
        LocalEquipment->Magazine -= LocalWeapon->AmmoPerRound;
        
        return true;
    }
        
    return false;
   
}




void FireBullet(int PlayerIndex)
{
    
    Player* LocalPlayer = (Player*)&GamePlayers[PlayerIndex];

    LocalPlayer->ActionBits &= ~ACTIONFIRE;

    //check if fire
    if (LocalPlayer->FFrames > 0)
    {
        return;
    }
    
    if (LocalPlayer->StatusBits & STATUSRELOADING)
    {
        return;
    }
    if (LocalPlayer->StatusBits & STATUSSWAPGUN)
    {
        return;
    }
    if (LocalPlayer->StatusBits & STATUSMELEE)
    {
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
    bool FirstShot = false;
    for (int ThisShot = 0; ThisShot < LocalWeapon->ShotsFired; ThisShot++)
    {
        
        if (!CheckMagazine(PlayerIndex))
        {
            LocalPlayer->ActionBits |= ACTIONRELOAD;
            return;
        }

        if (!FirstShot)
        {
            FirstShot = true;
            LocalPlayer->StatusBits |= STATUSFIRING;

            LocalPlayer->FPAnime = LocalWeapon->Bandolier.Fire;
            LocalPlayer->FPAnimeTimer.MaxTime = LocalWeapon->Bandolier.Fire->FrameCount;
            LocalPlayer->FPAnimeTimer.CurrentTime = 0;
            LocalPlayer->FPAnimeTimer.ActionFrame = LocalWeapon->Bandolier.Fire->ActionFrame;
            
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
                

                if (LocalPlayer->ZTarget >= 0)
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
                    
                    float Decimator = 0.01f / LocalPlayer->ZoomFloat;
                    Error[0] = (BulletOrigin[0]) - ((float)(GetRNG(LocalWeapon->ErrorMax)) * Decimator);
                    Error[1] = (BulletOrigin[1]) - ((float)(GetRNG(LocalWeapon->ErrorMax)) * Decimator);
                    Error[2] = (BulletOrigin[2]) - ((float)(GetRNG(LocalWeapon->ErrorMax)) * Decimator);
                    

                    Error[0] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * Decimator);
                    Error[1] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * Decimator);
                    Error[2] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * Decimator);

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
                    
                    
                }
                else
                {
                    //no z-target available. fire from camera
                    
                    //apply error
                    if (LocalPlayer->IsCPU == 0)
                    {
                        PGCamera* LocalCamera = (PGCamera*)&GameCameras[PlayerIndex];
                        float Decimator = 0.01f / LocalPlayer->ZoomFloat;
                        Error[0] = LocalCamera->LookAt[0] - ((float)(GetRNG(LocalWeapon->ErrorMax)) * Decimator);
                        Error[1] = LocalCamera->LookAt[1] - ((float)(GetRNG(LocalWeapon->ErrorMax)) * Decimator);
                        Error[2] = LocalCamera->LookAt[2] - ((float)(GetRNG(LocalWeapon->ErrorMax)) * Decimator);

                        Error[0] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * Decimator);
                        Error[1] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * Decimator);
                        Error[2] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * Decimator);

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
                        float Decimator = 0.01f / LocalPlayer->ZoomFloat;
                        CPUDirection[0] = 0;
                        CPUDirection[1] = 100;
                        CPUDirection[2] = 0;
                        AlignZVector(CPUDirection, LocalPlayer->Location.Angle[2]);
                        CPUDirection[0] += LocalPlayer->Location.Position[0];
                        CPUDirection[1] += LocalPlayer->Location.Position[1];
                        CPUDirection[2] += LocalPlayer->Location.Position[2] + LocalPlayer->Height;

                        Error[0] = CPUDirection[0] - ((float)(GetRNG(LocalWeapon->ErrorMax)) * Decimator);
                        Error[1] = CPUDirection[1] - ((float)(GetRNG(LocalWeapon->ErrorMax)) * Decimator);
                        Error[2] = CPUDirection[2] -  ((float)(GetRNG(LocalWeapon->ErrorMax)) * Decimator);

                        Error[0] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * Decimator);
                        Error[1] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * Decimator);
                        Error[2] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * Decimator);

                        TransformMatrix(BulletTrajectory,CPUOrigin, Error, CPUUP);

                        LocalBullet->Location.VelocityFront[0] = BulletTrajectory[0][2] * (LocalBullet->InitialSpeed);
                        LocalBullet->Location.VelocityFront[1] = BulletTrajectory[1][2] * (LocalBullet->InitialSpeed);
                        LocalBullet->Location.VelocityFront[2] = BulletTrajectory[2][2] * (LocalBullet->InitialSpeed);
                    }
                    
                    
                }

                break;
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
        if (ProjectileArray[ThisBullet].Status == BULLET_HIT)
        {
            if (ProjectileArray[ThisBullet].Lifespan > 15)
            {
                ProjectileArray[ThisBullet].Status = BULLET_INACTIVE;
            }
            else
            {
                ProjectileArray[ThisBullet].Lifespan++;
            }
            
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
    
	gsSPVertex(&(BulletBox[0]), 8, 0),
	gsSP1Triangle(0, 1, 2, 0),//1
	gsSP1Triangle(2, 1, 3, 0),//1
	gsSP1Triangle(4, 6, 5, 0),//2
	gsSP1Triangle(5, 6, 7, 0),//2
	gsSP1Triangle(7, 6, 3, 0),//3
	gsSP1Triangle(3, 6, 2, 0),//3
    gsSP1Triangle(0, 4, 1, 0),//4
	gsSP1Triangle(1, 4, 5, 0),//4
	gsSP1Triangle(0, 2, 4, 0),//5
	gsSP1Triangle(4, 2, 6, 0),//5
    gsSP1Triangle(3, 5, 7, 0),//6
	gsSP1Triangle(3, 1, 5, 0),//6

    gsSPEndDisplayList(),
};

