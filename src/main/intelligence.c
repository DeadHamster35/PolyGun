#include <nusys.h>
#include <nualsgi_n.h>
#include "graphic.h"
#include "common.h"
#include "main.h"
#include "player.h"
#include "pathfinding.h"
#include "math.h"
#include "collision.h"
#include "player.h"




void GetMoveDistance(int ThisPlayer, float Distance)
{
    Player* LocalPlayer = (Player*)(&GamePlayers[ThisPlayer]);
    BotStruct* LocalBot = (BotStruct*)&GameBots[ThisPlayer];
    Player* TargetPlayer = (Player*)(&GamePlayers[LocalBot->TargetPlayer]);

    if (LocalPlayer->StatusBits & STATUSBSTAR)
    {
        return;
    }

    if (TargetPlayer->HitTri[FLOORVECTOR] == -1)
    {
        return;
    }

    short IndexS = BSTARDistance(LocalPlayer->Location.Position, TargetPlayer->HitTri[FLOORVECTOR], Distance);
    BStar(ThisPlayer, IndexS);
    
    if (NavPaths[ThisPlayer][LocalBot->CurrentPathIndex] != -1)
    {
        LocalBot->CurrentTarget[0] = CollisionBuffer[IndexS].Center[0];
        LocalBot->CurrentTarget[1] = CollisionBuffer[IndexS].Center[1];
        LocalBot->CurrentTarget[2] = CollisionBuffer[IndexS].Center[2];
    }
    
    
    
}
void CheckBotMove(int ThisPlayer)
{
    Player* LocalPlayer = (Player*)&GamePlayers[ThisPlayer];
    BotStruct* LocalBot = (BotStruct*)&GameBots[ThisPlayer];
    Actor*  LocalActor = (Actor*)LocalBot->ActorData;
    short CheckAngle, CompareAngle;

    Vector CheckV;
    CheckV[0] = 0;
    CheckV[1] = 0;
    CheckV[2] = 0;
    


    float YSpeed = -2.25f;
    if (GetDistance(GamePlayers[0].Location.Position, LocalPlayer->Location.Position) < LocalActor->FireDistance.Min)
    {
        if (NavPaths[ThisPlayer][LocalBot->CurrentPathIndex] == -1)
        {
            LocalBot->CurrentPathIndex = -1;
            CheckAngle = GetDirection(LocalPlayer->Location.Position, GamePlayers[0].Location.Position);
            CompareAngle = CheckAngle - ((DEG1 * 180) + LocalPlayer->Location.Angle[2]);
            YSpeed = 0.25f;
        }
        else
        {
            CheckV[0] =  (float)CollisionBuffer[NavPaths[ThisPlayer][LocalBot->CurrentPathIndex]].Center[0];
            CheckV[1] =  (float)CollisionBuffer[NavPaths[ThisPlayer][LocalBot->CurrentPathIndex]].Center[1];
            CheckV[2] =  (float)CollisionBuffer[NavPaths[ThisPlayer][LocalBot->CurrentPathIndex]].Center[2];
            
            CheckAngle = GetDirection(LocalPlayer->Location.Position, CheckV);
            CompareAngle = CheckAngle - ((DEG1 * 180) + LocalPlayer->Location.Angle[2]);

            float Dist = GetDistance(LocalPlayer->Location.Position, CheckV);

            if (Dist < 50.0f)
            {
                LocalBot->CurrentPathIndex++;
                CheckAngle = GetDirection(LocalPlayer->Location.Position, GamePlayers[0].Location.Position);
                CompareAngle = CheckAngle - ((DEG1 * 180) + LocalPlayer->Location.Angle[2]);
            }
        }
        
        
        
        
    }
    else
    {
        if (LocalBot->CurrentPathIndex != -1)
        {   
            //valid path was found, continue.
            if (NavPaths[ThisPlayer][LocalBot->CurrentPathIndex] == -1)
            {
                //end of paths, reset.
                LocalBot->CurrentPathIndex = -1;
                CheckAngle = GetDirection(LocalPlayer->Location.Position, GamePlayers[0].Location.Position);
                CompareAngle = CheckAngle - ((DEG1 * 180) + LocalPlayer->Location.Angle[2]);
            }
            else
            {
                CheckV[0] =  (float)CollisionBuffer[NavPaths[ThisPlayer][LocalBot->CurrentPathIndex]].Center[0];
                CheckV[1] =  (float)CollisionBuffer[NavPaths[ThisPlayer][LocalBot->CurrentPathIndex]].Center[1];
                CheckV[2] =  (float)CollisionBuffer[NavPaths[ThisPlayer][LocalBot->CurrentPathIndex]].Center[2];
                
                CheckAngle = GetDirection(LocalPlayer->Location.Position, CheckV);
                CompareAngle = CheckAngle - ((DEG1 * 180) + LocalPlayer->Location.Angle[2]);

                float Dist = GetDistance(LocalPlayer->Location.Position, CheckV);
        
                if (Dist < 50.0f)
                {   
                    LocalBot->CurrentPathIndex++;
                    CheckAngle = GetDirection(LocalPlayer->Location.Position, GamePlayers[0].Location.Position);
                    CompareAngle = CheckAngle - ((DEG1 * 180) + LocalPlayer->Location.Angle[2]);
                }
            }
        }
        else
        {
            CheckAngle = GetDirection(LocalPlayer->Location.Position, GamePlayers[0].Location.Position);
            CompareAngle = CheckAngle - ((DEG1 * 180) + LocalPlayer->Location.Angle[2]);
        }
    }
    
    LocalPlayer->Location.VelocityFront[0] = 0.0f;
    LocalPlayer->Location.VelocityFront[1] = YSpeed;
    
    AlignZVector(LocalPlayer->Location.VelocityFront, CheckAngle);

    float X,Y;
    X = MathABS(LocalPlayer->Location.VelocityFront[0]);
    Y = MathABS(LocalPlayer->Location.VelocityFront[1]);

    float TotalSpeed = sqrtf(        
        X * X +
        Y * Y
    );
    
    float Nerf;
    //If the player has accelerated beyond maximum speed, reduce by the fractional amount.

    if (TotalSpeed > (MAXSPEED))
    {
        Nerf = ((MAXSPEED) / (TotalSpeed));
    
        LocalPlayer->Location.VelocityFront[0] *= Nerf;
        LocalPlayer->Location.VelocityFront[1] *= Nerf;
    }
}

void UpdateBotControls()
{


    for (int ThisPlayer = PlayerCount; ThisPlayer < PlayerCount + BotCount; ThisPlayer++)
    {
        
        Player* LocalPlayer =       (Player*)&GamePlayers[ThisPlayer];
        BotStruct* LocalBot = (BotStruct*)&GameBots[ThisPlayer];
        Actor* LocalActor = (Actor*)LocalBot->ActorData;

        

        if (!LocalPlayer->IsCPU)
        {
            //Don't run controller for Human Players
            continue;
        }
        if (LocalPlayer->StatusBits & STATUSDEAD)
        {
            //Don't run controller for Dead Players
            continue;
        }

        Player* TargetPlayer = (Player*)&GamePlayers[LocalPlayer->PlayerTarget];
        SVector* TargetCenter = (SVector*) &CollisionBuffer[NavPaths[ThisPlayer][LocalBot->CurrentPathIndex]].Center;

        short CheckAngle, CompareAngle;
        float CheckDistance;
        
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
        if (LocalPlayer->FFrames > 0)
        {
            LocalPlayer->FFrames--;
        }
        

        

        //Check if need to update path.

        //CheckAngle = GetDirection(GamePlayers[ThisPlayer].Location.Position, GamePlayers[LocalBot->TargetPlayer].Location.Position);
        //CompareAngle = CheckAngle - ((DEG1 * 180) + GamePlayers[ThisPlayer].Location.Angle[2]);

        
        CheckDistance = GetDistance(LocalBot->CurrentTarget, TargetPlayer->Location.Position);
        if ((CheckDistance > LocalBot->ActorData->FireDistance.Max) || (CheckDistance < LocalBot->ActorData->FireDistance.Min))
        {
            GetMoveDistance(ThisPlayer, LocalActor->OptimalDistance);
        }
        
        
        
        CheckBotMove(ThisPlayer);


        CheckDistance = GetDistance(LocalPlayer->Location.Position, TargetPlayer->Location.Position);

        if ((CheckDistance > LocalBot->ActorData->FireDistance.Min *0.9f) && (CheckDistance < LocalBot->ActorData->FireDistance.Max * 1.1f))
        {

            CheckAngle = GetDirection(LocalPlayer->Location.Position, GamePlayers[LocalBot->TargetPlayer].Location.Position);        
            CompareAngle = LocalPlayer->Location.Angle[2] - CheckAngle;
            if (CompareAngle > (DEG1 * 3))
            {
                LocalPlayer->Location.Angle[2] -= DEG1 * 2;
            }
            if (CompareAngle < (DEG1 * -3))
            {
                LocalPlayer->Location.Angle[2] += DEG1 * 2;
            }


            if (MathABS(CompareAngle) < (DEG1 * 4))
            {
                LocalPlayer->ActionBits |= ACTIONFIRE;
            }
            LocalBot->MovementStress++;
            if (LocalBot->MovementStress > 120)
            {
                LocalBot->MovementStress = 0;
                GetMoveDistance(ThisPlayer, LocalActor->OptimalDistance);
            }
        }
        else
        {
            
            LocalBot->MovementStress++;
            if (LocalBot->MovementStress > 45)
            {
                LocalBot->MovementStress = 0;
                GetMoveDistance(ThisPlayer, LocalActor->OptimalDistance);
            }
        }
        
        



    }
}
