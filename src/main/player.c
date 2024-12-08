
#include <nusys.h>
#include <nualsgi_n.h>
#include "graphic.h"
#include "common.h"
#include "main.h"
#include "math.h"
#include "collision.h"
#include "weapon.h"
#include "pathfinding.h"

Player GamePlayers[16];
PGCamera GameCameras[4];
BotStruct GameBots[16];

extern void GetPlayerTargets();

short PlayerCount, BotCount;
float UpDirection[] = { 0.0f, 0.0f, 1.0f};
float LookDirection[] = { 0.0f, 1.0f, 0.0f};



short Spawn[][3] = 
{
    { 658, 291, 30},
    { 658, 291, 30},
    { 658, 341, 30},
    { 598, 341, 30},
};
void initPlayer(int ThisPlayer)
{
    for (int ThisVector = 0; ThisVector < 3; ThisVector++)
    {
        GamePlayers[ThisPlayer].Location.Position[ThisVector] = Spawn[ThisPlayer][ThisVector];
        GamePlayers[ThisPlayer].Location.LastPosition[ThisVector] = Spawn[ThisPlayer][ThisVector];
        GamePlayers[ThisPlayer].Location.Angle[ThisVector] = 0;
        GamePlayers[ThisPlayer].Location.VelocityFront[ThisVector] = 0.0f;
        GamePlayers[ThisPlayer].HitTri[ThisVector] = -1;
    }
    GamePlayers[ThisPlayer].PrimaryWeapon.Class = (WeaponClass*)&AssaultRifle;
    GamePlayers[ThisPlayer].PrimaryWeapon.Ammo = 600;
    GamePlayers[ThisPlayer].PrimaryWeapon.Magazine = 60;
    
    GamePlayers[ThisPlayer].SecondaryWeapon.Class = (WeaponClass*)&Pistol;
    GamePlayers[ThisPlayer].SecondaryWeapon.Ammo = 120;
    GamePlayers[ThisPlayer].SecondaryWeapon.Magazine = 12;
    GamePlayers[ThisPlayer].SelectedWeapon = 0;

    GamePlayers[ThisPlayer].HitTri[3] = -1;
    GamePlayers[ThisPlayer].Location.VelocityFront[0] = 0.01f;
    GamePlayers[ThisPlayer].PlayerIndex = ThisPlayer;
    GamePlayers[ThisPlayer].Location.Radius = 10.0f;
    
    GamePlayers[ThisPlayer].Height = 35.0f;
    GamePlayers[ThisPlayer].HealthData.Shield = 0;
    GamePlayers[ThisPlayer].HealthData.Health = 1;
    if (GamePlayers[ThisPlayer].IsCPU == 1)
    {
        GamePlayers[ThisPlayer].HealthData.Health = GameBots[ThisPlayer].Difficulty;
        GameBots[ThisPlayer].CurrentPathIndex = -1;
        GamePlayers[ThisPlayer].StatusBits |= PLAYERFPS;
    }
    else
    {
        GamePlayers[ThisPlayer].HealthData.Health = 5;
        GamePlayers[ThisPlayer].StatusBits |= PLAYERFPS;
    }
    ResetNavPath(ThisPlayer);
}

void initCamera(int ThisPlayer)
{
    
    for (int ThisVector = 0; ThisVector < 3; ThisVector++)
    {
        GameCameras[ThisPlayer].Location.Position[ThisVector] = 0.0f;
        GameCameras[ThisPlayer].Location.Angle[ThisVector] = 0;
        GameCameras[ThisPlayer].Location.VelocityFront[ThisVector] = 0.0f;

        GameCameras[ThisPlayer].LookAt[ThisVector] = LookDirection[ThisVector];
        GameCameras[ThisPlayer].UpVector[ThisVector] = UpDirection[ThisVector];
    }

    
    GameCameras[ThisPlayer].LookAt[1] = 100.0f;
    GameCameras[ThisPlayer].Location.Radius = 10.0f;
    //GameCameras[ThisPlayer].FOVY = 45;
    GameCameras[ThisPlayer].FOVY = 70;
    GameCameras[ThisPlayer].Near = 2.0f;
    GameCameras[ThisPlayer].Far = 16000.0f;
    GameCameras[ThisPlayer].Screen.Position[0] = 160;
    GameCameras[ThisPlayer].Screen.Position[1] = 120;
    GameCameras[ThisPlayer].Screen.Size[0] = 320;
    GameCameras[ThisPlayer].Screen.Size[1] = 240;
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
        initCamera(ThisPlayer);
    }
}



void DebugControl(int Index)
{
    NUContData* LocalPad = (NUContData*)&contdata[Index];
    //OSContPad* LocalPad = (OSContPad*)&ControllerArray[Index];
    if (LocalPad->trigger & BTN_DDOWN)
    {
        
        
    }

    if (LocalPad->trigger & BTN_DLEFT)
    {
        GamePlayers[Index].StatusBits = ~(GamePlayers[Index].StatusBits & PLAYERFPS);
        //GamePlayers[0].Location.Position[0] += (int)3;
    }

    if (LocalPad->trigger & BTN_DUP)
    {
        
    }
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



        if (LocalPad->button & BTN_Z)
        {
            FireBullet(ThisPlayer);
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
        


        
        //Check R Toggle
        if (LocalPad->button & BTN_R)
        {
            //Check for SwapWeapon
            if (LocalPad->trigger & BTN_A) 
            {
                LocalPlayer->SelectedWeapon ^= 1;
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
                    LocalPlayer->Location.VelocityFront[2] = JUMPHEIGHT;
                    LocalPlayer->ActionBits |= PLAYERJUMP;
                    LocalPlayer->JumpTimer = -1;
                }
            }
            //Check for Melee
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



void UpdateBotControls()
{
    for (int ThisPlayer = PlayerCount; ThisPlayer < PlayerCount + BotCount; ThisPlayer++)
    {
        Player* LocalPlayer =       (Player*)&GamePlayers[ThisPlayer];

        if (!LocalPlayer->IsCPU)
        {
            //Don't run controller for Human Players
            return;
        }


        //No Camera Controls for bots.
        PGCamera* LocalCamera =     (PGCamera*)&GameCameras[ThisPlayer];

        //No Button Inputs for bots.
        //OSContPad* LocalPad = (OSContPad*)&ControllerArray[ThisPlayer];
        //u16 NewButtons = ControllerNewButtons[ThisPlayer];

        float XSpeed = 0.0f;
        float YSpeed = 0.0f;

        /*
        if ((LocalPad->stick_x > 5) || (LocalPad->stick_x < -5))
        {
            XSpeed = (float)LocalPad->stick_x * -0.1f;
        }
        if ((LocalPad->stick_y > 5) || (LocalPad->stick_y < -5))
        {
            YSpeed = (float)LocalPad->stick_y * 0.1f;
        }
        */
        

        //No cameras for bots
        /*
        if (LocalPad->button & BTN_CLEFT)
        {
            LocalCamera->Location.Angle[2] += DEGF * 1.25f;
        }
        if (LocalPad->button & BTN_CRIGHT)
        {
            LocalCamera->Location.Angle[2] -= DEGF * 1.25f;
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
        */


        /*
        if (NewButtons & BTN_Z)
        {
            FireBullet(ThisPlayer);
        }
        */

        
        //The jump timer is a grace-period for jumping
        //Any time the foot comes into contact with the ground, the timer is reset to 15.
        //This gives the player 14 frames after falling off of a cliff to hit the jump button.

        

        if (LocalPlayer->HitTri[FLOORVECTOR] != -1)
        {
            LocalPlayer->JumpTimer = 15; 
            LocalPlayer->IsJump = 0;
        }
        
        LocalPlayer->JumpTimer -= 1;


        /*
        if (LocalPlayer->JumpTimer > 0)
        {
            if (NewButtons & BTN_A) 
            {
                //JUMP
                LocalPlayer->Location.VelocityFront[2] = JUMPHEIGHT;
                LocalPlayer->JumpTimer = -1;
                LocalPlayer->IsJump = 1;
            }
        }
        */
        
        //Apply a new look-at vector infront of the current camera
        //Rotate this vector based on the camera angles.
        //Apply all movement towards this new vector.   
        
        LocalCamera->Location.Position[0] = LocalPlayer->Location.Position[0];
        LocalCamera->Location.Position[1] = LocalPlayer->Location.Position[1];
        LocalCamera->Location.Position[2] = LocalPlayer->Location.Position[2] + LocalPlayer->Height;
    
        
        LocalCamera->LookAt[0] = 0;
        LocalCamera->LookAt[1] = 100;
        LocalCamera->LookAt[2] = 0;

        AlignXVector(LocalCamera->LookAt, LocalPlayer->Location.Angle[0]);
        AlignZVector(LocalCamera->LookAt, LocalPlayer->Location.Angle[2]);

        LocalCamera->LookAt[0] += LocalCamera->Location.Position[0];
        LocalCamera->LookAt[1] += LocalCamera->Location.Position[1];
        LocalCamera->LookAt[2] += LocalCamera->Location.Position[2];
        
        //TransformMatrix(CameraMatrix[ThisPlayer],LocalCamera->Location.Position, LocalCamera->LookAt, LocalCamera->UpVector);
        
        


        

        short CheckAngle, CompareAngle;
        Vector CheckV;
        CheckV[0] = 0;
        CheckV[1] = 0;
        CheckV[2] = 0;


        if (GameBots[ThisPlayer].CurrentPathIndex == -1)
        {
            GamePlayers[ThisPlayer].StatusBits |= PLAYERBSTAR;
            CheckAngle = GetDirection(GamePlayers[ThisPlayer].Location.Position, GamePlayers[0].Location.Position);
            CompareAngle = CheckAngle - ((DEG1 * 180) + GamePlayers[ThisPlayer].Location.Angle[2]);
        }
        
        if (GlobalFrame % ((PlayerCount + BotCount) * 2) == ThisPlayer * 2)
        {
            
            if (GamePlayers[ThisPlayer].StatusBits & PLAYERBSTAR)
            {
                GamePlayers[ThisPlayer].StatusBits &= ~PLAYERBSTAR;
                short Tri = GamePlayers[0].HitTri[FLOORVECTOR];
                if (Tri != -1)
                {
                    BStar(ThisPlayer, Tri);
                }   
            }
        }

        if (GetDistance(GamePlayers[0].Location.Position, GamePlayers[ThisPlayer].Location.Position) < 100.0f)
        {
            CheckAngle = GetDirection(GamePlayers[ThisPlayer].Location.Position, GamePlayers[0].Location.Position);
            CompareAngle = CheckAngle - ((DEG1 * 180) + GamePlayers[ThisPlayer].Location.Angle[2]);
        }
        else
        {
            if (GameBots[ThisPlayer].CurrentPathIndex != -1)
            {   
                //valid path was found, continue.
                if (NavPaths[ThisPlayer][GameBots[ThisPlayer].CurrentPathIndex] == -1)
                {
                    //end of paths, reset.
                    GameBots[ThisPlayer].CurrentPathIndex = -1;
                    CheckAngle = GetDirection(GamePlayers[ThisPlayer].Location.Position, GamePlayers[0].Location.Position);
                    CompareAngle = CheckAngle - ((DEG1 * 180) + GamePlayers[ThisPlayer].Location.Angle[2]);
                }
                else
                {
                    
                    CheckV[0] =  (float)CollisionBuffer[NavPaths[ThisPlayer][GameBots[ThisPlayer].CurrentPathIndex]].Center[0];
                    CheckV[1] =  (float)CollisionBuffer[NavPaths[ThisPlayer][GameBots[ThisPlayer].CurrentPathIndex]].Center[1];
                    CheckV[2] =  (float)CollisionBuffer[NavPaths[ThisPlayer][GameBots[ThisPlayer].CurrentPathIndex]].Center[2];
                    
                    CheckAngle = GetDirection(GamePlayers[ThisPlayer].Location.Position, CheckV);
                    CompareAngle = CheckAngle - ((DEG1 * 180) + GamePlayers[ThisPlayer].Location.Angle[2]);

                    float Dist = GetDistance(LocalPlayer->Location.Position, CheckV);
            
                    if (Dist < 50.0f)
                    {
                        GameBots[ThisPlayer].CurrentPathIndex++;
                        CheckAngle = GetDirection(GamePlayers[ThisPlayer].Location.Position, GamePlayers[0].Location.Position);
                        CompareAngle = CheckAngle - ((DEG1 * 180) + GamePlayers[ThisPlayer].Location.Angle[2]);
                    }
                }
            }
            else
            {
                CheckAngle = GetDirection(GamePlayers[ThisPlayer].Location.Position, GamePlayers[0].Location.Position);
                CompareAngle = CheckAngle - ((DEG1 * 180) + GamePlayers[ThisPlayer].Location.Angle[2]);
            }
        }
        
        if (CompareAngle > (DEG1 * 3))
        {
            LocalPlayer->Location.Angle[2] -= DEG1 * 2;
        }
        if (CompareAngle < (DEG1 * 3))
        {
            LocalPlayer->Location.Angle[2] += DEG1 * 2;
        }
        
       
       

        
        LocalPlayer->Location.VelocityFront[0] = 0.0f;
        LocalPlayer->Location.VelocityFront[1] = -2.25f;
        
        AlignZVector(LocalPlayer->Location.VelocityFront, CheckAngle);

        float X,Y;
        X = MathABS(LocalPlayer->Location.VelocityFront[0]);
        Y = MathABS(LocalPlayer->Location.VelocityFront[0]);

        float TotalSpeed = sqrtf(        
            X * X +
            Y * Y
        );
        

        //If the player has accelerated beyond maximum speed, reduce by the fractional amount.

        if (TotalSpeed > (MAXSPEED))
        {
            Nerf = ((MAXSPEED) / (TotalSpeed));
        
            LocalPlayer->Location.VelocityFront[0] *= Nerf;
            LocalPlayer->Location.VelocityFront[1] *= Nerf;
        }

        /*
        if (TotalSpeed >= 0.1f)
        {
            LocalPlayer->Location.Angle[2] = LocalCamera->Location.Angle[2];
        }
        */




        
        /*
        if (!( (LocalPad->button & BTN_CUP) || (LocalPad->button & BTN_CDOWN) ))
        {
            //LocalCamera->Location.Angle[0] *= 0.95f;
            //SETTINGS TOGGLE
            //Revert the camera to the middle of the screen after releasing CUP/CDOWN.
        }
        */


    }
}


void GetPlayerTargets()
{
    for (int ThisPlayer = 0; ThisPlayer < PlayerCount; ThisPlayer++)
    {
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


        if ((TotalSpeed > MINIMALVELOCITY) || (LocalPlayer->ActionBits & PLAYERJUMP))
        {
            if (!PlayerLevelCollision(ThisPlayer))
            {
                PlayerLevelCollisionB(ThisPlayer);
            }
            else
            {
                LocalPlayer->ActionBits &= ~PLAYERJUMP;
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

        
        if (LocalPlayer->StatusBits & PLAYERFPS)
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
            Target[1] = 40;
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

