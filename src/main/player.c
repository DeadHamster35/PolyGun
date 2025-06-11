
#include <nusys.h>
#include <nualsgi_n.h>
#include "graphic.h"
#include "common.h"
#include "main.h"
#include "math.h"
#include "collision.h"
#include "weapon.h"
#include "pathfinding.h"
#include "actors.h"

Player GamePlayers[16];
PGCamera GameCameras[4];
BotStruct GameBots[16];

extern void GetPlayerTargets();

short PlayerCount, BotCount;
float UpDirection[] = { 0.0f, 0.0f, 1.0f};
float LookDirection[] = { 0.0f, 1.0f, 0.0f};



short Spawn[][3] = 
{
    { -1000, -750, -125},
    { 1000, -750, -125},
    { 1035, 2070, 5},
    { 658, 341, 30},
    { 598, 341, 30},
};
void initPlayer(int ThisPlayer)
{
    Player* LocalPlayer = (Player*)&GamePlayers[ThisPlayer];
    BotStruct* LocalBot = (BotStruct*)&GameBots[ThisPlayer];
    for (int ThisVector = 0; ThisVector < 3; ThisVector++)
    {
        LocalPlayer->Location.Position[ThisVector] = Spawn[ThisPlayer][ThisVector];
        LocalPlayer->Location.LastPosition[ThisVector] = Spawn[ThisPlayer][ThisVector];
        LocalPlayer->Location.Angle[ThisVector] = 0;
        LocalPlayer->Location.VelocityFront[ThisVector] = 0.0f;
        LocalPlayer->HitTri[ThisVector] = -1;
    }
    
    LocalPlayer->HitTri[3] = -1;
    LocalPlayer->Location.VelocityFront[0] = 0.01f;
    LocalPlayer->PlayerIndex = ThisPlayer;
    LocalPlayer->Location.Radius = 10.0f;
    
    LocalPlayer->Height = 35.0f;
    LocalPlayer->HealthData.Shield = 100;
    LocalPlayer->HealthData.Health = 100;

    LocalPlayer->StatusBits = 0;
    LocalPlayer->ActionBits = 0;
    LocalPlayer->StatusBits |= STATUSINAIR;
    if (LocalPlayer->IsCPU == 1)
    {
        LocalPlayer->HealthData.Health = LocalBot->Difficulty;
        LocalBot->CurrentPathIndex = -1;        
        LocalBot->TargetPlayer = 0;
        //LocalPlayer->StatusBits |= STATUSFPS;
        LocalBot->ActorData = (Actor*)&Elite;
        
        LocalPlayer->WeaponArray[0].Class = LocalBot->ActorData->PrimaryWeapon;
        LocalPlayer->WeaponArray[1].Class = LocalBot->ActorData->SecondaryWeapon;
        LocalPlayer->SelectedWeapon = 0;
    }
    else
    {
        LocalPlayer->HealthData.Health = 100;
        LocalPlayer->StatusBits |= STATUSFPS;
        LocalPlayer->WeaponArray[0].Class = (WeaponClass*)&AssaultRifle;    
        LocalPlayer->WeaponArray[1].Class = (WeaponClass*)&Pistol;
        LocalPlayer->SelectedWeapon = 0;
    }
    LocalPlayer->WeaponArray[0].Ammo = LocalPlayer->WeaponArray[0].Class->MaxAmmo;
    LocalPlayer->WeaponArray[0].Magazine = LocalPlayer->WeaponArray[0].Class->MagazineSize;
    LocalPlayer->WeaponArray[1].Ammo =  LocalPlayer->WeaponArray[1].Class->MaxAmmo;
    LocalPlayer->WeaponArray[1].Magazine =  LocalPlayer->WeaponArray[1].Class->MagazineSize;
    LocalPlayer->FPAnime = LocalPlayer->WeaponArray[0].Class->Bandolier.Idle;
    LocalPlayer->FPAnimeTimer.MaxTime = LocalPlayer->WeaponArray[0].Class->Bandolier.Idle->FrameCount;
    LocalPlayer->FPAnimeTimer.CurrentTime = 0;
    
    ResetNavPath(ThisPlayer);
}

void initCamera(int ThisPlayer)
{
    PGCamera* LocalCamera = (PGCamera*)&GameCameras[ThisPlayer];

    for (int ThisVector = 0; ThisVector < 3; ThisVector++)
    {
        LocalCamera->Location.Position[ThisVector] = 0.0f;
        LocalCamera->Location.Angle[ThisVector] = 0;
        LocalCamera->Location.VelocityFront[ThisVector] = 0.0f;

        LocalCamera->LookAt[ThisVector] = LookDirection[ThisVector];
        LocalCamera->UpVector[ThisVector] = UpDirection[ThisVector];
    }

    
    LocalCamera->LookAt[1] = 100.0f;
    LocalCamera->Location.Radius = 10.0f;
    //LocalCamera->FOVY = 45;
    LocalCamera->FOVY = 70;
    LocalCamera->Near = 2.0f;
    LocalCamera->Far = 16000.0f;
    LocalCamera->Screen.Position[0] = 160;
    LocalCamera->Screen.Position[1] = 120;
    LocalCamera->Screen.Size[0] = 320;
    LocalCamera->Screen.Size[1] = 240;
}

void initAllPlayers()
{
    for (int ThisPlayer = 0; ThisPlayer < PlayerCount; ThisPlayer++)
    {
        GamePlayers[ThisPlayer].IsCPU = 0;
        initPlayer(ThisPlayer);
        initCamera(ThisPlayer);
        
    }
    for (int ThisPlayer = PlayerCount; ThisPlayer < PlayerCount + BotCount; ThisPlayer++)
    {
        GamePlayers[ThisPlayer].IsCPU = 1;
        GameBots[ThisPlayer].Difficulty = 1;
        initPlayer(ThisPlayer);
        //initCamera(ThisPlayer);
    }
}



void DebugControl(int Index)
{
    NUContData* LocalPad = (NUContData*)&contdata[Index];
    if (LocalPad->trigger & BTN_DDOWN)
    {
        
        
    }

    if (LocalPad->trigger & BTN_DLEFT)
    {
        GamePlayers[Index].StatusBits ^= STATUSFPS;
    }

    if (LocalPad->trigger & BTN_DUP)
    {
        
    }
}

void ResetPlayerStatus(int PlayerIndex)
{
    Player* LocalPlayer = (Player*)&GamePlayers[PlayerIndex];
    WeaponClass* LocalClass = (WeaponClass*)LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon].Class;
    bool StatusReset = false;

    if (LocalPlayer->StatusBits & STATUSRELOADING)
    {
        LocalPlayer->StatusBits &= ~STATUSRELOADING;
        LoadWeaponAmmo(PlayerIndex);
        
        LocalPlayer->FPAnime = LocalClass->Bandolier.Idle;
        LocalPlayer->FPAnimeTimer.CurrentTime = 0;
        LocalPlayer->FPAnimeTimer.MaxTime = LocalClass->Bandolier.Idle->FrameCount;
        StatusReset = true;
    }
    if (LocalPlayer->StatusBits & STATUSMELEE)
    {
        LocalPlayer->StatusBits &= ~STATUSMELEE;
        
        LocalPlayer->FPAnime = LocalClass->Bandolier.Idle;
        LocalPlayer->FPAnimeTimer.CurrentTime = 0;
        LocalPlayer->FPAnimeTimer.MaxTime = LocalClass->Bandolier.Idle->FrameCount;
        StatusReset = true;
    }
    

    if (!StatusReset)
    {
        LocalPlayer->FPAnime = LocalClass->Bandolier.Idle;
        LocalPlayer->FPAnimeTimer.CurrentTime = 0;
        LocalPlayer->FPAnimeTimer.MaxTime = LocalClass->Bandolier.Idle->FrameCount;
    }
    //LocalPlayer->StatusBits &= ~STATUSSWAPGUN;

}


AffineMtx CameraMatrix[4];
float Nerf;
void UpdatePlayerControls()
{
    for (int ThisPlayer = 0; ThisPlayer < PlayerCount; ThisPlayer++)
    {
        DebugControl(ThisPlayer);

        
        Player* LocalPlayer =       (Player*)&GamePlayers[ThisPlayer];

        if (LocalPlayer->IsCPU)
        {
            //Don't run controller for CPU bots
            return;
        }

        //get z-targets
        GetPlayerTargets();

        PGCamera* LocalCamera =     (PGCamera*)&GameCameras[ThisPlayer];

        NUContData* LocalPad = (NUContData*)&contdata[ThisPlayer];
        NUContData* P3 = (NUContData*)&contdata[2];

        float XSpeed = 0.0f;
        float YSpeed = 0.0f;

        if ((LocalPad->stick_x > 5) || (LocalPad->stick_x < -5))
        {
            XSpeed = (float)LocalPad->stick_x * -0.1f;
        }
        if ((LocalPad->stick_y > 5) || (LocalPad->stick_y < -5))
        {
            YSpeed = (float)LocalPad->stick_y * 0.1f;
        }
        
        /* P3 Analog Controlss
        if ((P3->stick_x > 5) || (P3->stick_x < -5))
        {
            if (LocalPlayer->ZTarget > 0)
            {
                float StickSpeed = (float)P3->stick_x * -0.02f;
                LocalCamera->Location.Angle[2] += DEGF * StickSpeed;
            }
            else
            {
                float StickSpeed = (float)P3->stick_x * -0.04f;
                LocalCamera->Location.Angle[2] += DEGF * StickSpeed;
            }
        }

        if ((P3->stick_y > 5) || (P3->stick_y < -5))
        {
            if (LocalPlayer->ZTarget > 0)
            {
                float StickSpeed = (float)P3->stick_y * -0.01f;
                LocalCamera->Location.Angle[0] -= DEGF * StickSpeed;
            }
            else
            {
                float StickSpeed = (float)P3->stick_y * -0.02f;
                LocalCamera->Location.Angle[0] -= DEGF * StickSpeed;
            }
        }
        */

        if (LocalPlayer->ZTarget > 0)
        {
            if (LocalPad->button & BTN_CLEFT)
            {
                LocalCamera->Location.Angle[2] += DEGF * 1.5f;
            }
            if (LocalPad->button & BTN_CRIGHT)
            {
                LocalCamera->Location.Angle[2] -= DEGF * 1.5f;
            }
        }
        else
        {
            if (LocalPad->button & BTN_CLEFT)
            {
                LocalCamera->Location.Angle[2] += DEGF * 2.5f;
            }
            if (LocalPad->button & BTN_CRIGHT)
            {
                LocalCamera->Location.Angle[2] -= DEGF * 2.5f;
            }
        }
        

        if (LocalPad->button & BTN_CUP)
        {
            if (LocalCamera->Location.Angle[0] < MAXLOOK * DEG1)
            {
                LocalCamera->Location.Angle[0] += (short)(DEGF * 1.5f);
            }
        }
        if (LocalPad->button & BTN_CDOWN)
        {
            if (LocalCamera->Location.Angle[0] > -(MAXLOOK * DEG1))
            {
                LocalCamera->Location.Angle[0] -= (short)(DEGF * 1.5f);
            }
        }


        //Firing Impulse, Firing Frames, Invincibility Frames
        if (LocalCamera->Impulse > 0)
        {
            LocalCamera->Impulse--;
        }
        if (LocalPlayer->FFrames > 0)
        {
            LocalPlayer->FFrames--;
        }
        

        
        //The jump timer is a grace-period for jumping
        //Any time the foot comes into contact with the ground, the timer is reset to 15.
        //This gives the player 14 frames after falling off of a cliff to hit the jump button.

        

        if (LocalPlayer->HitTri[FLOORVECTOR] != -1)
        {
            LocalPlayer->JumpTimer = 15; 
        }
        if (LocalPlayer->JumpTimer >= 0)
        {
            LocalPlayer->JumpTimer -= 1;
        }
        

        LocalPlayer->FPAnimeTimer.CurrentTime++;
        if (LocalPlayer->FPAnimeTimer.CurrentTime >= LocalPlayer->FPAnimeTimer.MaxTime)
        {
            ResetPlayerStatus(ThisPlayer);
        }

        
        //Check R Toggle
        if (LocalPad->button & BTN_R)
        {
            //Check for SwapWeapon
            if (LocalPad->trigger & BTN_A) 
            {
                LocalPlayer->ActionBits |= ACTIONSWAPGUN;
            }

            //Check for Reload
            if (LocalPad->trigger & BTN_B) 
            {
                LocalPlayer->ActionBits |= ACTIONRELOAD;
            }
        }
        else
        {
            //Check for Jump
            if (LocalPlayer->JumpTimer > 0)
            {
                if (LocalPad->trigger & BTN_A) 
                {
                    //JUMP
                    LocalPlayer->ActionBits |= ACTIONJUMP;
                    LocalPlayer->JumpTimer = -1;
                }
            }
            //Check for Fire
            if (LocalPad->button & BTN_Z)
            {
                LocalPlayer->ActionBits |= ACTIONFIRE;
            }
            
            //Check for Melee
            if (LocalPad->trigger & BTN_B)
            {
                LocalPlayer->ActionBits |= ACTIONMELEE;
            }
        }
        



        //Apply a new look-at vector infront of the current camera
        //Rotate this vector based on the camera angles.
        //Apply all movement towards this new vector.       
        
        LocalCamera->LookAt[0] = 0;
        LocalCamera->LookAt[1] = 100;
        LocalCamera->LookAt[2] = 0;

        AlignXVector(LocalCamera->LookAt, LocalCamera->Location.Angle[0]);
        AlignZVector(LocalCamera->LookAt, LocalCamera->Location.Angle[2]);

        LocalCamera->LookAt[0] += LocalCamera->Location.Position[0];
        LocalCamera->LookAt[1] += LocalCamera->Location.Position[1];
        LocalCamera->LookAt[2] += LocalCamera->Location.Position[2];
        
        TransformMatrix(CameraMatrix[ThisPlayer],LocalCamera->Location.Position, LocalCamera->LookAt, LocalCamera->UpVector);


        LocalPlayer->Location.VelocityFront[0] += CameraMatrix[ThisPlayer][0][2] * YSpeed;
        LocalPlayer->Location.VelocityFront[1] += CameraMatrix[ThisPlayer][1][2] * YSpeed;

        LocalPlayer->Location.VelocityFront[0] += CameraMatrix[ThisPlayer][0][0] * XSpeed;
        LocalPlayer->Location.VelocityFront[1] += CameraMatrix[ThisPlayer][1][0] * XSpeed;

        

        

        LocalPlayer->Location.VelocityTotal[0] = sqrtf(
            LocalPlayer->Location.VelocityFront[0] * LocalPlayer->Location.VelocityFront[0]
        );

        LocalPlayer->Location.VelocityTotal[1] = sqrtf(            
            LocalPlayer->Location.VelocityFront[1] * LocalPlayer->Location.VelocityFront[1]
        );

        float TotalSpeed = sqrtf(        
            LocalPlayer->Location.VelocityTotal[0] * LocalPlayer->Location.VelocityTotal[0] +
            LocalPlayer->Location.VelocityTotal[1] * LocalPlayer->Location.VelocityTotal[1]
        );
        

        //If the player has accelerated beyond maximum speed, reduce by the fractional amount.

        if (TotalSpeed > (MAXSPEED))
        {
            Nerf = ((MAXSPEED) / (TotalSpeed));
        
            LocalPlayer->Location.VelocityFront[0] *= Nerf;
            LocalPlayer->Location.VelocityFront[1] *= Nerf;
        }

        if (TotalSpeed >= 0.1f)
        {
            LocalPlayer->Location.Angle[2] = LocalCamera->Location.Angle[2];
        }

        LocalCamera->Location.VelocityTotal[2] = sqrtf(            
            LocalPlayer->Location.VelocityFront[2] * LocalPlayer->Location.VelocityFront[2]
        );



        
        
        if (!( (LocalPad->button & BTN_CUP) || (LocalPad->button & BTN_CDOWN) ))
        {
            //LocalCamera->Location.Angle[0] *= 0.95f;
            //SETTINGS TOGGLE
            //Revert the camera to the middle of the screen after releasing CUP/CDOWN.
        }


    }
}




void GetPlayerTargets()
{
    for (int ThisPlayer = 0; ThisPlayer < PlayerCount; ThisPlayer++)
    {
        GamePlayers[ThisPlayer].ZTarget = 0;
        if (GamePlayers[ThisPlayer].IsCPU == 0)
        {
            GamePlayers[ThisPlayer].ZTarget = CheckViewCone(ThisPlayer);
        }
        
    }
}






void UpdatePlayerResponse()
{   
    


    
    for (int ThisPlayer = 0; ThisPlayer < PlayerCount + BotCount; ThisPlayer++)
    {
        Player* LocalPlayer = (Player*)&GamePlayers[ThisPlayer];

        if (LocalPlayer->ActionBits & ACTIONJUMP)
        {
            //player jump
            LocalPlayer->Location.VelocityFront[2] = JUMPHEIGHT;
            LocalPlayer->ActionBits &= ~ACTIONJUMP;
            LocalPlayer->StatusBits |= STATUSINAIR;
        }

        if (LocalPlayer->ActionBits & ACTIONFIRE)
        {
            FireBullet(ThisPlayer);
        }

        if (LocalPlayer->ActionBits & ACTIONMELEE)
        {
            PlayerMelee(ThisPlayer);
        }

        if (LocalPlayer->ActionBits & ACTIONRELOAD)
        {
            ReloadWeapon(ThisPlayer);
        }
        if (LocalPlayer->ActionBits & ACTIONSWAPGUN)
        {
            SwapGun(ThisPlayer);
        }

        for (int ThisVector = 0; ThisVector < 3; ThisVector++)
        {
            LocalPlayer->Location.LastPosition[ThisVector] = LocalPlayer->Location.Position[ThisVector];
            LocalPlayer->Location.Position[ThisVector] -= LocalPlayer->Location.VelocityFront[ThisVector];
            
            if ((LocalPlayer->Location.Position[ThisVector] > 32768) || (LocalPlayer->Location.Position[ThisVector] < -32768))
            {
                initPlayer(ThisPlayer);
            }
        }
        
        
        //Run collision against the level environment.
        float TotalSpeed = (        
            LocalPlayer->Location.VelocityFront[0] * LocalPlayer->Location.VelocityFront[0] +
            LocalPlayer->Location.VelocityFront[1] * LocalPlayer->Location.VelocityFront[1] +
            LocalPlayer->Location.VelocityFront[2] * LocalPlayer->Location.VelocityFront[2]
        );


        if ((TotalSpeed > MINIMALVELOCITY) || (LocalPlayer->StatusBits & STATUSINAIR))
        {
            if (!PlayerLevelCollision(ThisPlayer))
            {
                PlayerLevelCollisionB(ThisPlayer);
            }
            else
            {
                LocalPlayer->StatusBits &= ~STATUSINAIR;
                LocalPlayer->Location.VelocityFront[0] *= 0.85f;
                LocalPlayer->Location.VelocityFront[1] *= 0.85f;
            }
            

            LocalPlayer->Location.VelocityFront[2] += GRAVITY;

            if (LocalPlayer->Location.VelocityFront[2] > TERMINALVELOCITY)
            {
                LocalPlayer->Location.VelocityFront[2] = TERMINALVELOCITY;
            }
        }   
        else
        {
            LocalPlayer->Location.VelocityFront[0] = 0;
            LocalPlayer->Location.VelocityFront[1] = 0;
            LocalPlayer->Location.VelocityFront[2] = 0;
            
        }
        

        
        
        

        //Apply gravity to the player. Cap at terminal velocity.
        


        PGCamera* LocalCamera = (PGCamera*)&GameCameras[ThisPlayer];
        //Player position is assumed to be the feet.


        
        if (LocalPlayer->IsCPU)
        {
            //dont move camera for CPUs
            continue;
        }


        LocalCamera->Location.Position[0] = LocalPlayer->Location.Position[0];
        LocalCamera->Location.Position[1] = LocalPlayer->Location.Position[1];
        LocalCamera->Location.Position[2] = LocalPlayer->Location.Position[2] + LocalPlayer->Height;

        
        if (LocalPlayer->StatusBits & STATUSFPS)
        {
            
            LocalCamera->LookAt[0] = 0;
            LocalCamera->LookAt[1] = 100;
            LocalCamera->LookAt[2] = 0;

            AlignXVector(LocalCamera->LookAt, LocalCamera->Location.Angle[0]);
            AlignZVector(LocalCamera->LookAt, LocalCamera->Location.Angle[2]);

            LocalCamera->LookAt[0] += LocalCamera->Location.Position[0];
            LocalCamera->LookAt[1] += LocalCamera->Location.Position[1];
            LocalCamera->LookAt[2] += LocalCamera->Location.Position[2];
        }
        else
        {
            Vector Target;
            Target[0] = 0;
            Target[1] = 70;
            Target[2] = -5;

            AlignXVector(Target, LocalCamera->Location.Angle[0]);
            AlignZVector(Target, LocalCamera->Location.Angle[2]);

            LocalCamera->LookAt[0] = LocalCamera->Location.Position[0];
            LocalCamera->LookAt[1] = LocalCamera->Location.Position[1];
            LocalCamera->LookAt[2] = LocalCamera->Location.Position[2];

            LocalCamera->Location.Position[0] -= Target[0];
            LocalCamera->Location.Position[1] -= Target[1];
            LocalCamera->Location.Position[2] -= Target[2];

        }
        
    }
    
    return;
    Vector Size;
    Size[0] = GamePlayers[0].Location.Radius;
    Size[1] = GamePlayers[0].Location.Radius;
    Size[2] = GamePlayers[0].Height;
    for (int ThisPlayer = 0; ThisPlayer < PlayerCount + BotCount - 1; ThisPlayer++)
    {
        for (int ThisTarget = ThisPlayer + 1; ThisTarget < PlayerCount + BotCount; ThisTarget++)
        {
            if (GetDistance(GamePlayers[ThisPlayer].Location.Position,GamePlayers[ThisTarget].Location.Position) < (GamePlayers[ThisPlayer].Location.Radius + GamePlayers[ThisTarget].Location.Radius))
            {
                if (GamePlayers[ThisPlayer].IsCPU == 0)
                {
                    GamePlayers[ThisPlayer].HealthData.Health -= 10;
                }
                SetSimpleBump(GamePlayers[ThisTarget].Location.Position, Size, GamePlayers[ThisPlayer].Location.Position, Size);
            }
        }
    }
}


void UpdateMenuControls()
{
    for (int ThisPlayer = 0; ThisPlayer < 1; ThisPlayer++)
    {
        NUContData* LocalPad = (NUContData*)&contdata[ThisPlayer];
        Player* LocalPlayer = (Player*)&GamePlayers[ThisPlayer];
        
        if (LocalPad->trigger &(u16)BTN_START)
        {
            RenderEnable = 0;
            GameSequence = LEVELSEQUENCE;
        }
    }
}

