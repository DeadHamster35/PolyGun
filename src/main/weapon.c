
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
    

    AssaultRifle.BaseDamage = 1;
    AssaultRifle.BulletLife = 200;
    AssaultRifle.BulletSpeed = 60;
    AssaultRifle.ErrorMax = 800;
    AssaultRifle.FiringRate = 2;
    AssaultRifle.MagazineSize = 60;
    AssaultRifle.MaxAmmo = 600;
    AssaultRifle.ReloadTime = 35;
    AssaultRifle.CameraImpulseY = 3;
    AssaultRifle.MaxImpulseY = 15;
    AssaultRifle.DrawCall = (void*)&DrawAssaultRifle;
    AssaultRifle.Reticle = (Gfx*)&AssaultRifleReticleGFX;
    

    Pistol.BaseDamage = 3;
    Pistol.BulletLife = 250;
    Pistol.BulletSpeed = 70;
    Pistol.ErrorMax = 500;
    Pistol.FiringRate = 6;
    Pistol.MagazineSize = 12;
    Pistol.MaxAmmo = 120;
    Pistol.ReloadTime = 20;
    Pistol.CameraImpulseY = 12;
    Pistol.MaxImpulseY = 30;
    Pistol.DrawCall = (void*)&DrawPistol;
    Pistol.Reticle = (Gfx*)&PistolReticleGFX;
}



void initProjectiles()
{
    for (int ThisBullet = 0; ThisBullet < MAXBULLETS; ThisBullet++)
    {
        Projectile* LocalBullet = (Projectile*)&ProjectileArray[ThisBullet];
        LocalBullet->Status = BULLET_INACTIVE;
    }
}


void FireBullet(int PlayerIndex)
{
    
    Player* LocalPlayer = (Player*)&GamePlayers[PlayerIndex];
    
    //check if fire
    if (LocalPlayer->FFrames > 0)
    {
        return;
    }

    AffineMtx BulletTrajectory;
    Vector BulletOrigin;
    Vector CPUOrigin;
    Vector Error;
    Vector CPUUP;
    CPUUP[0] = 0;
    CPUUP[1] = 0;
    CPUUP[2] = 1;
    WeaponClass* LocalWeapon;
    WeaponEquipment* LocalEquipment;
    if (LocalPlayer->SelectedWeapon == 0)
    {
        LocalEquipment = (WeaponEquipment*)&LocalPlayer->PrimaryWeapon;
        LocalWeapon = (WeaponClass*)LocalPlayer->PrimaryWeapon.Class;
    }
    else
    {
        LocalEquipment = (WeaponEquipment*)&LocalPlayer->SecondaryWeapon;
        LocalWeapon = (WeaponClass*)LocalPlayer->SecondaryWeapon.Class;
    }
    
    if (LocalEquipment->Magazine > 0)
    {
        LocalEquipment->Magazine--;
    }
    else
    {
        //no ammo
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
            
            //Locate Bullet and direct trajectory.
            LocalBullet->Location.Position[0] = GamePlayers[PlayerIndex].Location.Position[0];
            LocalBullet->Location.Position[1] = GamePlayers[PlayerIndex].Location.Position[1];
            LocalBullet->Location.Position[2] = GamePlayers[PlayerIndex].Location.Position[2] + GamePlayers[PlayerIndex].Height;
            
            LocalBullet->Location.Angle[0] = GameCameras[PlayerIndex].Location.Angle[0];
            LocalBullet->Location.Angle[1] = GameCameras[PlayerIndex].Location.Angle[1];
            LocalBullet->Location.Angle[2] = GameCameras[PlayerIndex].Location.Angle[2];

            if (GamePlayers[PlayerIndex].ZTarget > 0)
            {
                BulletOrigin[0] = GamePlayers[GamePlayers[PlayerIndex].ZTarget].Location.Position[0] - GamePlayers[PlayerIndex].Location.Position[0];
                BulletOrigin[1] = GamePlayers[GamePlayers[PlayerIndex].ZTarget].Location.Position[1] - GamePlayers[PlayerIndex].Location.Position[1];
                BulletOrigin[2] = (GamePlayers[GamePlayers[PlayerIndex].ZTarget].Location.Position[2] + GamePlayers[GamePlayers[PlayerIndex].ZTarget].Height * 0.7f) - (GamePlayers[PlayerIndex].Location.Position[2] + GamePlayers[PlayerIndex].Height);

                NormalizeVector(BulletOrigin);
                BulletOrigin[0] *= 100.0f;
                BulletOrigin[1] *= 100.0f;
                BulletOrigin[2] *= 100.0f;
                BulletOrigin[0] += GamePlayers[PlayerIndex].Location.Position[0];
                BulletOrigin[1] += GamePlayers[PlayerIndex].Location.Position[1];
                BulletOrigin[2] += GamePlayers[PlayerIndex].Location.Position[2] + GamePlayers[PlayerIndex].Height;
                

                Error[0] = (BulletOrigin[0]) - ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);
                Error[1] = (BulletOrigin[1]) - ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);
                Error[2] = (BulletOrigin[2]) - ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);
                

                Error[0] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);
                Error[1] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);
                Error[2] += ((float)(GetRNG(LocalWeapon->ErrorMax)) * 0.01f);

                if (GamePlayers[PlayerIndex].IsCPU == 0)
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
                    CPUOrigin[0] = GamePlayers[PlayerIndex].Location.Position[0];
                    CPUOrigin[1] = GamePlayers[PlayerIndex].Location.Position[1];
                    CPUOrigin[2] = GamePlayers[PlayerIndex].Location.Position[2] + GamePlayers[PlayerIndex].Height;
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
                /*
                LocalPlayer->Location.VelocityFront[0] += CameraMatrix[PlayerIndex][0][2] * YSpeed;
                LocalPlayer->Location.VelocityFront[1] += CameraMatrix[PlayerIndex][1][2] * YSpeed;

                LocalPlayer->Location.VelocityFront[0] += CameraMatrix[PlayerIndex][0][0] * XSpeed;
                LocalPlayer->Location.VelocityFront[1] += CameraMatrix[PlayerIndex][1][0] * XSpeed;
                */
                
                
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
	{  1,  8,  1,  0, 0, 0, 255, 255, 0, 255, },
	{  1,  8, -1,  0, 0, 0, 255, 255, 0, 255, },
	{ -1,  8,  1,  0, 0, 0, 255, 255, 0, 255, },
	{ -1,  8, -1,  0, 0, 0, 255, 255, 0, 255, },
	{  1, -8,  1,  0, 0, 0, 255, 255, 0, 255, },
	{  1, -8, -1,  0, 0, 0, 255, 255, 0, 255, },
	{ -1, -8,  1,  0, 0, 0, 255, 255, 0, 255, },
	{ -1, -8, -1,  0, 0, 0, 255, 255, 0, 255, },
};

Gfx logo_bulletbox[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_SHADE | G_ZBUFFER | G_CULL_BACK),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),

    
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

    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

