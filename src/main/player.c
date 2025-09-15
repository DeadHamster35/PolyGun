
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
#include "levels.h"

Player GamePlayers[16];
PGCamera GameCameras[4];
BotStruct GameBots[16];

extern void GetPlayerTargets();

extern int GetSpawnPoint(int PlayerIndex);

short PlayerCount, BotCount;
float UpDirection[] = { 0.0f, 0.0f, 1.0f};
float LookDirection[] = { 0.0f, 1.0f, 0.0f};


void initPlayer(int ThisPlayer)
{
    Player* LocalPlayer = (Player*)&GamePlayers[ThisPlayer];
    BotStruct* LocalBot = (BotStruct*)&GameBots[ThisPlayer];

    short SpawnIndex = GetSpawnPoint(ThisPlayer);
    for (int ThisVector = 0; ThisVector < 3; ThisVector++)
    {
        LocalPlayer->Location.Position[ThisVector] = SpawnPoints[SpawnIndex].Position[ThisVector];
        LocalPlayer->Location.LastPosition[ThisVector] = SpawnPoints[SpawnIndex].Position[ThisVector];
        LocalPlayer->Location.Angle[ThisVector] = 0;
        LocalPlayer->Location.VelocityFront[ThisVector] = 0.0f;
        LocalPlayer->HitTri[ThisVector] = -1;
    }
    
    LocalPlayer->HitTri[3] = -1;
    LocalPlayer->Location.VelocityFront[0] = 0.01f;
    LocalPlayer->PlayerIndex = ThisPlayer;
    LocalPlayer->Location.Radius = 10.0f;
    
    LocalPlayer->Height = 35.0f;
    LocalPlayer->ZoomFloat = 1.0f;
    LocalPlayer->HealthData.Shield = MAXSHIELD;
    LocalPlayer->HealthData.Health = MAXHEALTH;

    LocalPlayer->StatusBits = 0;
    LocalPlayer->ActionBits = 0;
    LocalPlayer->StatusBits |= STATUSINAIR;
    if (LocalPlayer->IsCPU == 1)
    {
        LocalBot->CurrentPathIndex = -1;        
        LocalBot->TargetPlayer = 0;
        //LocalPlayer->StatusBits |= STATUSFPS;
        LocalBot->ActorData = (Actor*)&MPBot;
        
        LocalPlayer->WeaponArray[0].Class = LocalBot->ActorData->PrimaryWeapon;
        LocalPlayer->WeaponArray[1].Class = LocalBot->ActorData->SecondaryWeapon;
        LocalPlayer->SelectedWeapon = 0;
    }
    else
    {
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
    LocalPlayer->FPAnimeTimer.ActionFrame = 0;
    
    ResetNavPath(ThisPlayer);
}

void DamagePlayer(int PlayerIndex, int Damage)
{
    Player* LocalPlayer = (Player*)&GamePlayers[PlayerIndex];
    
    if (LocalPlayer->StatusBits & STATUSDEAD)
    {
        return;
    }

    //dezoom player when hit
    LocalPlayer->StatusBits &= ~STATUSZOOM;
    LocalPlayer->ZoomLevel = 0;
    LocalPlayer->ZoomFloat = 1.0f;


    //Full bleedthrough; damage falls through shield into health.
    int BleedThrough = Damage - LocalPlayer->HealthData.Shield;
    if (LocalPlayer->HealthData.Shield > 0)
    {
        LocalPlayer->HealthData.Shield -= Damage;
    }
    if (BleedThrough > 0)
    {
        LocalPlayer->HealthData.Health -= BleedThrough;
    }

    LocalPlayer->HealthData.HitFrames = RECHARGE_TIME;
    LocalPlayer->HealthData.RechargeStatus = RECHARGE_OFF;
    

    if (LocalPlayer->HealthData.Health <= 0)
    {
        LocalPlayer->StatusBits |= STATUSDEAD;
        LocalPlayer->RespawnTimer = RESPAWN_TIME;
        LocalPlayer->Location.Angle[0] = DEG1 * 90;
        GameBots[PlayerIndex].Difficulty++;
    }
}

void initScreenSystem()
{
    switch (PlayerCount)
    {
        case 1:
        {
            GameCameras[0].Screen.Size[0] = 320;
            GameCameras[0].Screen.Size[1] = 240;
            GameCameras[0].Screen.Position[0] = 160;
            GameCameras[0].Screen.Position[1] = 120;
            break;
        }
        case 2:
        {
            GameCameras[0].Screen.Size[0] = 320;
            GameCameras[0].Screen.Size[1] = 120;
            GameCameras[1].Screen.Size[0] = 320;
            GameCameras[1].Screen.Size[1] = 120;

            GameCameras[0].Screen.Position[0] = 160;
            GameCameras[0].Screen.Position[1] = 60;
            GameCameras[1].Screen.Position[0] = 160;
            GameCameras[1].Screen.Position[1] = 180;
            break;
        }
        case 3:
        {
            GameCameras[0].Screen.Size[0] = 320;
            GameCameras[0].Screen.Size[1] = 120;
            GameCameras[1].Screen.Size[0] = 160;
            GameCameras[1].Screen.Size[1] = 120;
            GameCameras[2].Screen.Size[0] = 160;
            GameCameras[2].Screen.Size[1] = 120;

            GameCameras[0].Screen.Position[0] = 160;
            GameCameras[0].Screen.Position[1] = 60;
            GameCameras[1].Screen.Position[0] = 80;
            GameCameras[1].Screen.Position[1] = 180;
            GameCameras[2].Screen.Position[0] = 240;
            GameCameras[2].Screen.Position[1] = 180;
            break;
        }
        case 4:
        {
            GameCameras[0].Screen.Size[0] = 160;
            GameCameras[0].Screen.Size[1] = 120;
            GameCameras[1].Screen.Size[0] = 160;
            GameCameras[1].Screen.Size[1] = 120;
            GameCameras[2].Screen.Size[0] = 160;
            GameCameras[2].Screen.Size[1] = 120;
            GameCameras[3].Screen.Size[0] = 160;
            GameCameras[3].Screen.Size[1] = 120;

            GameCameras[0].Screen.Position[0] = 80;
            GameCameras[0].Screen.Position[1] = 60;
            GameCameras[1].Screen.Position[0] = 240;
            GameCameras[1].Screen.Position[1] = 60;
            GameCameras[2].Screen.Position[0] = 80;
            GameCameras[2].Screen.Position[1] = 180;
            GameCameras[3].Screen.Position[0] = 240;
            GameCameras[3].Screen.Position[1] = 180;

            

            
            break;
        }
    }


    for (int ThisPlayer = 0; ThisPlayer < PlayerCount; ThisPlayer++)
    {
        GameCameras[ThisPlayer].Screen.Viewport.vp.vtrans[2] = G_MAXZ / 2;
        GameCameras[ThisPlayer].Screen.Viewport.vp.vscale[2] = G_MAXZ / 2;

        GameCameras[ThisPlayer].Screen.Viewport.vp.vtrans[3] = 0;
        GameCameras[ThisPlayer].Screen.Viewport.vp.vscale[3] = 0;
    }

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
    LocalCamera->FOVY = 70;
    LocalCamera->Near = 2.0f;
    LocalCamera->Far = 16000.0f;
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
    }
}



void DebugControl(int Index)
{
    NUContData* LocalPad = (NUContData*)&contdata[Index];

    if (LocalPad->trigger & BTN_DLEFT)
    {
        GamePlayers[Index].StatusBits ^= STATUSFPS;
    }

}



int GetSpawnPoint(int PlayerIndex)
{
    //Check each spawn point against each enemy player and get furthest distance;

    Vector Source, Target;
    short BestIndex, HitIndex;
    float BestDistance, FarthestDistance;
    
    
    BestDistance = -1.0f;
    BestIndex = -1;
    for (int ThisIndex = 0; ThisIndex < TotalSpawnPoints; ThisIndex++)
    {
        Source[0] = (float)SpawnPoints[ThisIndex].Position[0];
        Source[1] = (float)SpawnPoints[ThisIndex].Position[1];
        Source[2] = (float)SpawnPoints[ThisIndex].Position[2];
        HitIndex = 0;
        FarthestDistance = 9999999999.0f;
        for (int ThisPlayer = 0; ThisPlayer < PlayerCount + BotCount; ThisPlayer++)
        {
            if (ThisPlayer == PlayerIndex)
            {
                continue;
            }
            Target[0] = GamePlayers[ThisPlayer].Location.Position[0];
            Target[1] = GamePlayers[ThisPlayer].Location.Position[1];
            Target[2] = GamePlayers[ThisPlayer].Location.Position[2];
            float CheckDistance = GetDistance(Target, Source);
            if (FarthestDistance > CheckDistance)
            {
                FarthestDistance = CheckDistance;
                HitIndex = 1;
            }

        }
        
        if (HitIndex && (FarthestDistance > BestDistance))
        {
            BestDistance = FarthestDistance;
            BestIndex = ThisIndex;
        }

    }
    if (BestIndex == -1)
    {
        BestIndex = 0;
    }
    return BestIndex;
}
    

void ActionPlayerStatus(int PlayerIndex)
{
    Player* LocalPlayer = (Player*)&GamePlayers[PlayerIndex];
    if (LocalPlayer->StatusBits & STATUSMELEE)
    {
        
        int PlayerHit;
        float Distance;
        PlayerHit = CheckViewCone(PlayerIndex, 50.0f);
        if (PlayerHit != -1)
        {
            DamagePlayer(PlayerHit, 75);            
        }
    }
    if (LocalPlayer->StatusBits & STATUSRELOADING)
    {   
        LoadWeaponAmmo(PlayerIndex);
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

        LocalPlayer->FPAnime = LocalClass->Bandolier.Idle;
        LocalPlayer->FPAnimeTimer.CurrentTime = 0;
        LocalPlayer->FPAnimeTimer.ActionFrame = LocalClass->Bandolier.Idle->ActionFrame;
        LocalPlayer->FPAnimeTimer.MaxTime = LocalClass->Bandolier.Idle->FrameCount;
        StatusReset = true;
    }
    if (LocalPlayer->StatusBits & STATUSMELEE)
    {
        LocalPlayer->StatusBits &= ~STATUSMELEE;
        
        LocalPlayer->FPAnime = LocalClass->Bandolier.Idle;
        LocalPlayer->FPAnimeTimer.CurrentTime = 0;
        LocalPlayer->FPAnimeTimer.ActionFrame = LocalClass->Bandolier.Idle->ActionFrame;
        LocalPlayer->FPAnimeTimer.MaxTime = LocalClass->Bandolier.Idle->FrameCount;
        StatusReset = true;
    }
    

    if (!StatusReset)
    {
        LocalPlayer->FPAnime = LocalClass->Bandolier.Idle;
        LocalPlayer->FPAnimeTimer.CurrentTime = 0;
        LocalPlayer->FPAnimeTimer.ActionFrame = LocalClass->Bandolier.Idle->ActionFrame;
        LocalPlayer->FPAnimeTimer.MaxTime = LocalClass->Bandolier.Idle->FrameCount;
    }
    //LocalPlayer->StatusBits &= ~STATUSSWAPGUN;

}

void GetButtonTimers(int PlayerIndex)
{
    Player* LocalPlayer =       (Player*)&GamePlayers[PlayerIndex];
    NUContData* LocalPad = (NUContData*)&contdata[PlayerIndex];


    if (LocalPlayer->ButtonCooldown.ButtonTimerCL > 0)
    {
        LocalPlayer->ButtonCooldown.ButtonTimerCL--;
    }
    else
    {
        if (LocalPad->button & BTN_CLEFT)
        {
            LocalPlayer->ButtonTimes.ButtonTimerCL++;
        }
        else
        {
            LocalPlayer->ButtonTimes.ButtonTimerCL = 0;
        }
    }


    if (LocalPlayer->ButtonCooldown.ButtonTimerCR > 0)
    {
        LocalPlayer->ButtonCooldown.ButtonTimerCR--;
    }
    else
    {
        if (LocalPad->button & BTN_CRIGHT)
        {
            LocalPlayer->ButtonTimes.ButtonTimerCR++;
        }
        else
        {
            LocalPlayer->ButtonTimes.ButtonTimerCR = 0;
        }
    }
    

    if (LocalPlayer->ButtonCooldown.ButtonTimerCU > 0)
    {
        LocalPlayer->ButtonCooldown.ButtonTimerCU--;
    }
    else
    {
        if (LocalPad->button & BTN_CUP)
        {
            LocalPlayer->ButtonTimes.ButtonTimerCU++;
        }
        else
        {
            LocalPlayer->ButtonTimes.ButtonTimerCU = 0;
        }
    }


    if (LocalPlayer->ButtonCooldown.ButtonTimerCD > 0)
    {
        LocalPlayer->ButtonCooldown.ButtonTimerCD--;
    }
    else
        {
        if (LocalPad->button & BTN_CDOWN)
        {
            LocalPlayer->ButtonTimes.ButtonTimerCD++;
        }
        else
        {
            LocalPlayer->ButtonTimes.ButtonTimerCD = 0;
        }
    }


    if (LocalPlayer->ButtonCooldown.ButtonTimerA > 0)
    {
        LocalPlayer->ButtonCooldown.ButtonTimerA--;
    }
    else
        {
        if (LocalPad->button & BTN_A)
        {
            LocalPlayer->ButtonTimes.ButtonTimerA++;
        }
        else
        {
            LocalPlayer->ButtonTimes.ButtonTimerA = 0;
        }
    }


    if (LocalPlayer->ButtonCooldown.ButtonTimerB > 0)
    {
        LocalPlayer->ButtonCooldown.ButtonTimerB--;
    }
    else
        {
        if (LocalPad->button & BTN_B)
        {
            LocalPlayer->ButtonTimes.ButtonTimerB++;
        }
        else
        {
            LocalPlayer->ButtonTimes.ButtonTimerB = 0;
        }
    }


    if (LocalPlayer->ButtonCooldown.ButtonTimerR > 0)
    {
        LocalPlayer->ButtonCooldown.ButtonTimerR--;
    }
    else
        {
        if (LocalPad->button & BTN_R)
        {
            LocalPlayer->ButtonTimes.ButtonTimerR++;
        }
        else
        {
            LocalPlayer->ButtonTimes.ButtonTimerR = 0;
        }
    }


    if (LocalPlayer->ButtonCooldown.ButtonTimerZ > 0)
    {
        LocalPlayer->ButtonCooldown.ButtonTimerZ--;
    }
    else
    {
        if (LocalPad->button & BTN_Z)
        {
            LocalPlayer->ButtonTimes.ButtonTimerZ++;
        }
        else
        {
            LocalPlayer->ButtonTimes.ButtonTimerZ = 0;
        }
    }

}


AffineMtx CameraMatrix[4];
float Nerf;
void UpdatePlayerControls()
{
    
    GetPlayerTargets();

    for (int ThisPlayer = 0; ThisPlayer < PlayerCount; ThisPlayer++)
    {
        DebugControl(ThisPlayer);

        GetButtonTimers(ThisPlayer);
        Player* LocalPlayer =       (Player*)&GamePlayers[ThisPlayer];
        

        if (LocalPlayer->IsCPU)
        {
            //Don't run controller for CPU bots
            continue;
        }


        WeaponClass* LocalWeapon = LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon].Class;
        PGCamera* LocalCamera =     (PGCamera*)&GameCameras[ThisPlayer];

        

        //get z-targets
        


        NUContData* LocalPad = (NUContData*)&contdata[ThisPlayer];
        NUContData* P3 = (NUContData*)&contdata[2];

        float XSpeed = 0.0f;
        float YSpeed = 0.0f;

        if ((LocalPad->stick_x > 5) || (LocalPad->stick_x < -5))
        {
            XSpeed = (float)LocalPad->stick_x * -0.01f;
        }
        if ((LocalPad->stick_y > 5) || (LocalPad->stick_y < -5))
        {
            YSpeed = (float)LocalPad->stick_y * 0.01f;
        }
        /* P3 Analog Controlss
        if ((P3->stick_x > 5) || (P3->stick_x < -5))
        {
            if (LocalPlayer->ZTarget >= 0)
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
            if (LocalPlayer->ZTarget >= 0)
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
        
        
        if (LocalPlayer->FPAnimeTimer.CurrentTime == LocalPlayer->FPAnimeTimer.ActionFrame)
        {
            ActionPlayerStatus(ThisPlayer);
        }

        LocalPlayer->FPAnimeTimer.CurrentTime++;

        if (LocalPlayer->FPAnimeTimer.CurrentTime >= LocalPlayer->FPAnimeTimer.MaxTime)
        {
            ResetPlayerStatus(ThisPlayer);
        }

        
        if (LocalPlayer->RespawnTimer == -1)
        {
            //Only if Player is Not-Yet-Dead
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
                if (LocalPad->button & BTN_B)
                {
                    if (LocalPlayer->ButtonTimes.ButtonTimerB > 10)
                    {
                        LocalPlayer->ButtonTimes.ButtonTimerB = 0;
                        LocalPlayer->ButtonCooldown.ButtonTimerB = 10;
                        LocalPlayer->ActionBits &= ~ACTIONRELOAD;
                        LocalPlayer->ActionBits |= ACTIONPICKUP;
                    }
                }
                

                
                if (LocalPad->trigger & BTN_CUP)
                {
                    LocalPlayer->ZoomLevel++;
                    if (LocalPlayer->ZoomLevel > 2)
                    {
                        LocalPlayer->ZoomLevel = 0;                        
                        LocalPlayer->ZoomFloat = 1.0f;
                        LocalPlayer->StatusBits &= ~STATUSZOOM;
                    }
                    else
                    {
                        if (LocalWeapon->ZoomLevel[LocalPlayer->ZoomLevel-1] == -1)
                        {
                            LocalPlayer->ZoomLevel = 0;
                            LocalPlayer->ZoomFloat = 1.0f;
                            LocalPlayer->StatusBits &= ~STATUSZOOM;
                        }
                        else
                        {
                            LocalPlayer->ZoomFloat = (float)(LocalWeapon->ZoomLevel[LocalPlayer->ZoomLevel-1] * 0.1f);
                            LocalPlayer->StatusBits |= STATUSZOOM;
                        }
                    }
                    

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



                    
                if (LocalPlayer->ZTarget >= 0)
                {
                    if (LocalPad->button & BTN_CLEFT)
                    {
                        LocalCamera->Location.Angle[2] += DEGF * 1.5f / LocalPlayer->ZoomFloat;
                    }
                    if (LocalPad->button & BTN_CRIGHT)
                    {
                        LocalCamera->Location.Angle[2] -= DEGF * 1.5f / LocalPlayer->ZoomFloat;
                    }
                }
                else
                {
                    if (LocalPad->button & BTN_CLEFT)
                    {
                        LocalCamera->Location.Angle[2] += (short)(DEGF * 2.5f / LocalPlayer->ZoomFloat);
                    }
                    if (LocalPad->button & BTN_CRIGHT)
                    {
                        LocalCamera->Location.Angle[2] -= (short)(DEGF * 2.5f / LocalPlayer->ZoomFloat);
                    }
                }
                

                if (LocalPad->button & BTN_CUP)
                {
                    if (LocalCamera->Location.Angle[0] < MAXLOOK * DEG1)
                    {
                        LocalCamera->Location.Angle[0] += (short)(DEGF * 2.0f / LocalPlayer->ZoomFloat);
                    }
                }
                if (LocalPad->button & BTN_CDOWN)
                {
                    if (LocalCamera->Location.Angle[0] > -(MAXLOOK * DEG1))
                    {
                        LocalCamera->Location.Angle[0] -= (short)(DEGF * 2.0f / LocalPlayer->ZoomFloat);
                    }
                }
            }
            


            //Apply a new look-at vector infront of the current camera
            //Rotate this vector based on the camera angles.
            //Apply all movement towards this new vector.       
            
            LocalCamera->LookAt[0] = 0;
            LocalCamera->LookAt[1] = 100;
            LocalCamera->LookAt[2] = 0;

            AlignXVector(LocalCamera->LookAt, LocalCamera->Location.Angle[0]);
            AlignYVector(LocalCamera->LookAt, LocalCamera->Location.Angle[1]);
            AlignZVector(LocalCamera->LookAt, LocalCamera->Location.Angle[2]);

            LocalCamera->LookAt[0] += LocalCamera->Location.Position[0];
            LocalCamera->LookAt[1] += LocalCamera->Location.Position[1];
            LocalCamera->LookAt[2] += LocalCamera->Location.Position[2];
            
            TransformMatrix(CameraMatrix[ThisPlayer],LocalCamera->Location.Position, LocalCamera->LookAt, LocalCamera->UpVector);


            LocalPlayer->Location.VelocityFront[0] += CameraMatrix[ThisPlayer][0][2] * YSpeed;
            LocalPlayer->Location.VelocityFront[1] += CameraMatrix[ThisPlayer][1][2] * YSpeed;

            LocalPlayer->Location.VelocityFront[0] += CameraMatrix[ThisPlayer][0][0] * XSpeed;
            LocalPlayer->Location.VelocityFront[1] += CameraMatrix[ThisPlayer][1][0] * XSpeed;

            

            


            float TotalSpeed = sqrtf(        
                LocalPlayer->Location.VelocityFront[0] * LocalPlayer->Location.VelocityFront[0] +
                LocalPlayer->Location.VelocityFront[1] * LocalPlayer->Location.VelocityFront[1]
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
        }
        



        



        
        
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
    float TargetCheck;
    for (int ThisPlayer = 0; ThisPlayer < PlayerCount; ThisPlayer++)
    {
        GamePlayers[ThisPlayer].ZTarget = -1;
        if (GamePlayers[ThisPlayer].IsCPU == 0)
        {
            GamePlayers[ThisPlayer].ZTarget = CheckViewCone(ThisPlayer, 2500.0f);
        }
        
    }
}



void CheckPlayerHealth()
{
    for (int ThisPlayer = 0; ThisPlayer < PlayerCount + BotCount; ThisPlayer++)
    {
        Player* LocalPlayer = (Player*)&GamePlayers[ThisPlayer];
        if (LocalPlayer->HealthData.IFrames > 0)
        {
            LocalPlayer->HealthData.IFrames--;
        }
        if (LocalPlayer->HealthData.HitFrames > 0)
        {
            LocalPlayer->HealthData.HitFrames--;

            
            LocalPlayer->HealthData.DisplayStatus = DISPLAY_OFF;
            if (LocalPlayer->HealthData.Shield > 0)
            {
                LocalPlayer->HealthData.DisplayStatus = DISPLAY_ON;
            }
        }


        if (LocalPlayer->HealthData.HitFrames <= 0)
        {
            LocalPlayer->HealthData.HitFrames = 0;
            LocalPlayer->HealthData.RechargeStatus = RECHARGE_ON;
            LocalPlayer->HealthData.DisplayStatus = DISPLAY_OFF;
        }

        if (LocalPlayer->HealthData.RechargeStatus == RECHARGE_ON)
        {
            if (LocalPlayer->HealthData.Health < MAXHEALTH)
            {
                LocalPlayer->HealthData.Health++;
            }
            else
            {
                if (LocalPlayer->HealthData.Shield < MAXSHIELD)
                {
                    LocalPlayer->HealthData.Shield++;
                }
                else
                {
                    LocalPlayer->HealthData.RechargeStatus = RECHARGE_OFF;
                }                
            }
        }
    }
}


void UpdatePlayerResponse()
{   
    


    
    for (int ThisPlayer = 0; ThisPlayer < PlayerCount + BotCount; ThisPlayer++)
    {
        Player* LocalPlayer = (Player*)&GamePlayers[ThisPlayer];

        if (LocalPlayer->RespawnTimer > 0)
        {
            LocalPlayer->RespawnTimer--;
            LocalPlayer->StatusBits &= ~STATUSFPS;
            LocalPlayer->StatusBits &= ~STATUSZOOM;
        }
        if (LocalPlayer->RespawnTimer == 0)
        {
            LocalPlayer->RespawnTimer = -1;
            LocalPlayer->StatusBits |= STATUSFPS;
            initPlayer(ThisPlayer);
            
        }


        if (LocalPlayer->RespawnTimer == -1)
        {
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

            LocalPlayer->ClosestPickup = CheckPickups(ThisPlayer);
            if (LocalPlayer->ActionBits & ACTIONPICKUP)
            {
                PickupObject(ThisPlayer);
            }
            
            
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
        

        //LocalPlayer->Location.VelocityFront[2] += GRAVITY;
        if (LocalPlayer->Location.VelocityFront[2] > TERMINALVELOCITY)
        {
            LocalPlayer->Location.VelocityFront[2] = TERMINALVELOCITY;
        }

        //Run collision against the level environment.
        float TotalSpeed = (        
            LocalPlayer->Location.VelocityFront[0] * LocalPlayer->Location.VelocityFront[0] +
            LocalPlayer->Location.VelocityFront[1] * LocalPlayer->Location.VelocityFront[1] +
            LocalPlayer->Location.VelocityFront[2] * LocalPlayer->Location.VelocityFront[2]
        );

        /*
        if ((TotalSpeed > MINIMALVELOCITY) || (LocalPlayer->StatusBits & STATUSINAIR))
        {
            if (!CheckPlayerCollision(ThisPlayer))
            {
                LocalPlayer->StatusBits |= STATUSINAIR;
            }
            else
            {
                LocalPlayer->StatusBits &= ~STATUSINAIR;
                LocalPlayer->Location.VelocityFront[0] *= 0.85f;
                LocalPlayer->Location.VelocityFront[1] *= 0.85f;
            }
        }   
        else
        {
            LocalPlayer->Location.VelocityFront[0] = 0;
            LocalPlayer->Location.VelocityFront[1] = 0;
            LocalPlayer->Location.VelocityFront[2] = 0;
        }
        */

        
        LocalPlayer->Location.VelocityFront[0] *= 0.85f;
        LocalPlayer->Location.VelocityFront[1] *= 0.85f;

        //Apply gravity to the player. Cap at terminal velocity.
        
        
        if (LocalPlayer->IsCPU)
        {
            //dont move camera for CPUs
            continue;
        }


        


        PGCamera* LocalCamera = (PGCamera*)&GameCameras[ThisPlayer];
        //Player position is assumed to be the feet.


        LocalCamera->Location.Position[0] = LocalPlayer->Location.Position[0];
        LocalCamera->Location.Position[1] = LocalPlayer->Location.Position[1];
        LocalCamera->Location.Position[2] = LocalPlayer->Location.Position[2] + LocalPlayer->Height;

        
        if (LocalPlayer->StatusBits & STATUSFPS)
        {
            
            LocalCamera->LookAt[0] = 0;
            LocalCamera->LookAt[1] = 100;
            LocalCamera->LookAt[2] = 0;

            AlignXVector(LocalCamera->LookAt, LocalCamera->Location.Angle[0]);
            AlignYVector(LocalCamera->LookAt, LocalCamera->Location.Angle[1]);
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
            AlignYVector(Target, LocalCamera->Location.Angle[1]);
            AlignZVector(Target, LocalCamera->Location.Angle[2]);

            LocalCamera->LookAt[0] = LocalCamera->Location.Position[0];
            LocalCamera->LookAt[1] = LocalCamera->Location.Position[1];
            LocalCamera->LookAt[2] = LocalCamera->Location.Position[2];

            LocalCamera->Location.Position[0] -= Target[0];
            LocalCamera->Location.Position[1] -= Target[1];
            LocalCamera->Location.Position[2] -= Target[2];

        }
        
    }
    
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

