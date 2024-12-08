/*
   graphic.c

   The general graphic routine (the initialization and clear the frame
   buffer) and the definition of the external variable

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.
*/

#include <nusys.h>
#include "graphic.h"
#include "math.h"
#include "common.h"
#include "player.h"
#include "weapon.h"
#include "levels.h"
#include "collision.h"
#include "memory.h"
#include "pathfinding.h"
#include "assets/models/DebugCylinder.h"
#include "assets/models/cyborgwalk.h"
#include "FPGraphics.h"
#include "assets/models/FPHands.h"

extern void DrawPlayers();
extern void DrawBullets();

Gfx gfx_glist[2][GFX_GLIST_LEN];
Gfx gfx_clear_glist[2][GFX_CLEAR_GLIST_LEN];
Dynamic gfx_dynamic[2];
Gfx *glistp;
u32 gfx_gtask_no = 0;

Mtx EntityMap[4096];
short CurrentEntity[4];
int GlobalFrame;
short RenderEnable, GameSequence;

/*----------------------------------------------------------------------------
  gfxRCPIinit

  The initialization of RSP/RDP
----------------------------------------------------------------------------*/
void gfxRCPInit(void)
{
    /* Setting the RSP segment register  */
    gSPSegment(glistp++, 0, 0x0); /* For the CPU virtual address  */

    /* Setting RSP  */
    gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(setup_rspstate));

    /* Setting RDP  */
    gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(setup_rdpstate));
}

/*----------------------------------------------------------------------------
  gfxClearCfb

  Address setting and clearing the frame/Z-buffer

  Use nuGfxZBuffer (the address of the Z-buffer) and nuGfxCfb_ptr (the
  address of the frame buffer) which are global variables of NuSYSTEM.
----------------------------------------------------------------------------*/
void gfxClearCfb(void)
{
    /* Clear the Z-buffer  */
    gDPSetDepthImage(glistp++, OS_K0_TO_PHYSICAL(nuGfxZBuffer));
    gDPSetCycleType(glistp++, G_CYC_FILL);
    gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,
                     OS_K0_TO_PHYSICAL(nuGfxZBuffer));
    gDPSetFillColor(glistp++, (GPACK_ZDZ(G_MAXFBZ, 0) << 16 |
                               GPACK_ZDZ(G_MAXFBZ, 0)));
    gDPFillRectangle(glistp++, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
    gDPPipeSync(glistp++);

    /* Clear the frame buffer  */
    gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,
                     osVirtualToPhysical(nuGfxCfb_ptr));
    gDPSetFillColor(glistp++, (GPACK_RGBA5551(125, 180, 235, 1) << 16 | 
			       GPACK_RGBA5551(115, 175, 215, 1)));
    gDPFillRectangle(glistp++, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
    gDPPipeSync(glistp++);
}

void SetMatrix(int Mode)
{
    if (Mode == 0)
    {
        AffineToMtx((Mtx *)&EntityMap[CurrentEntity[GlobalFrame % 2]], GlobalAffine);
        gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
                  G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        return;
    }

    AffineToMtx((Mtx *)&EntityMap[CurrentEntity[GlobalFrame % 2]], GlobalAffine);
    gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
              G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
}

uint END_DL[] =
    {
        0x0,
        0x0,
        0xB8000000,
        0x0,
        0x0};

Gfx EndDL[] =
    {
        gsSPEndDisplayList(),
};


static Vp VPrime = {
    SCREEN_WD * 2, SCREEN_HT * 2, G_MAXZ / 2, 0, /* The scale factor  */
    SCREEN_WD * 2, SCREEN_HT * 2, G_MAXZ / 2, 0, /* Move  */
};

static Vp P1 = {
    SCREEN_WD * 2, SCREEN_HT, G_MAXZ / 2, 0, /* The scale factor  */
    SCREEN_WD * 2, SCREEN_HT, G_MAXZ / 2, 0, /* Move  */
};
static Vp P2 = {
    SCREEN_WD * 2, SCREEN_HT, G_MAXZ / 2, 0, /* The scale factor  */
    SCREEN_WD * 2, SCREEN_HT, G_MAXZ / 2, 0, /* Move  */
};

static Vp P3 = {
    SCREEN_WD * 2, SCREEN_HT, G_MAXZ / 2, 0, /* The scale factor  */
    SCREEN_WD * 2, SCREEN_HT, G_MAXZ / 2, 0, /* Move  */
};
static Vp P4 = {
    SCREEN_WD * 2, SCREEN_HT, G_MAXZ / 2, 0, /* The scale factor  */
    SCREEN_WD * 2, SCREEN_HT, G_MAXZ / 2, 0, /* Move  */
};



Vp *ViewportArray[] = 
{
    &P1,
    &P2,
    &P3,
    &P4
};

void DrawLevelScene(Dynamic *dynamicp, int PlayerIndex)
{
    
    static u16 LevelNormal[4], FPNormal[4];
    Player *LocalPlayer = (Player *)&GamePlayers[PlayerIndex];

    if (LocalPlayer->IsCPU)
    {
        // Don't draw for CPU bots
        return;
    }
    PGCamera *LocalCamera = (PGCamera *)&GameCameras[PlayerIndex];

    

    ViewportArray[PlayerIndex]->vp.vscale[0] = LocalCamera->Screen.Size[0] * 2;
    ViewportArray[PlayerIndex]->vp.vscale[1] = LocalCamera->Screen.Size[1] * 2;
    ViewportArray[PlayerIndex]->vp.vtrans[0] = LocalCamera->Screen.Position[0] * 4;
    ViewportArray[PlayerIndex]->vp.vtrans[1] = LocalCamera->Screen.Position[1] * 4;


    guPerspective(&dynamicp->LevelMap.Projection[PlayerIndex], &LevelNormal[PlayerIndex],
                  LocalCamera->FOVY, (LocalCamera->Screen.Size[0] / LocalCamera->Screen.Size[1]), LocalCamera->Near, LocalCamera->Far, 1.0);
    gSPPerspNormalize(glistp++, LevelNormal[PlayerIndex]);

    guLookAt(&dynamicp->LevelMap.Viewing[PlayerIndex],
             LocalCamera->Location.Position[0], LocalCamera->Location.Position[1], LocalCamera->Location.Position[2],
             LocalCamera->LookAt[0], LocalCamera->LookAt[1], LocalCamera->LookAt[2],
             LocalCamera->UpVector[0], LocalCamera->UpVector[1], LocalCamera->UpVector[2]);

    guTranslate(&dynamicp->LevelMap.Translation[PlayerIndex], 0.0f, 0.0f, 0.0f);

    gSPMatrix(glistp++, &dynamicp->LevelMap.Projection[PlayerIndex],
              G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &dynamicp->LevelMap.Viewing[PlayerIndex],
              G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &dynamicp->LevelMap.Translation[PlayerIndex],
              G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);


        gDPSetScissor
        (
            glistp++, 
            G_SC_NON_INTERLACE, 
            LocalCamera->Screen.Position[0] - (LocalCamera->Screen.Size[0] * 0.5f), 
            LocalCamera->Screen.Position[1] - (LocalCamera->Screen.Size[1] * 0.5f), 
            LocalCamera->Screen.Position[0] + (LocalCamera->Screen.Size[0] * 0.5f), 
            LocalCamera->Screen.Position[1] + (LocalCamera->Screen.Size[1] * 0.5f)
        );

    gSPViewport(glistp++, ViewportArray[PlayerIndex]);
    

    gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(TableAddress[LevelIndex]));

    DrawPlayers(PlayerIndex);
    DrawBullets(PlayerIndex);
    
    if (LocalPlayer->StatusBits & PLAYERFPS)
    {
        // Clear Z-buffer
        gDPSetRenderMode(glistp++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        gDPSetDepthImage(glistp++, osVirtualToPhysical(nuGfxZBuffer));
        gDPPipeSync(glistp++);
        gDPSetCycleType(glistp++, G_CYC_FILL);
        gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,
                            osVirtualToPhysical(nuGfxZBuffer));
        gDPSetFillColor(glistp++, (GPACK_ZDZ(G_MAXFBZ, 0) << 16 |
                                    GPACK_ZDZ(G_MAXFBZ, 0)));

        gDPFillRectangle(
            glistp++, 
            LocalCamera->Screen.Position[0] - (LocalCamera->Screen.Size[0] * 0.5f), 
            LocalCamera->Screen.Position[1] - (LocalCamera->Screen.Size[1] * 0.5f), 
            LocalCamera->Screen.Position[0] + (LocalCamera->Screen.Size[0] * 0.5f) - 1, 
            LocalCamera->Screen.Position[1] + (LocalCamera->Screen.Size[1] * 0.5f) - 1
        );
        gDPPipeSync(glistp++);

        gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,
                            osVirtualToPhysical(nuGfxCfb_ptr));
        gDPPipeSync(glistp++);
        gDPSetCycleType(glistp++, G_CYC_1CYCLE);
        


        // Setup model matrix
        guPerspective(&dynamicp->FPMap.Projection[PlayerIndex], &FPNormal[PlayerIndex],
                      LocalCamera->FOVY, (LocalCamera->Screen.Size[0] / LocalCamera->Screen.Size[1]), 2.0, 500.0f, 1.0);
        gSPPerspNormalize(glistp++, FPNormal[PlayerIndex]);

        guLookAt(&dynamicp->FPMap.Viewing[PlayerIndex],
                 0, 0, 0,
                 0, 100.0f, 0,
                 0, 0, 1);

        guTranslate(&dynamicp->FPMap.Translation[PlayerIndex], 0.0f, 0.0f, 0.0f);
        guScale(&dynamicp->FPMap.Scale[PlayerIndex], 0.1f, 0.1f, 0.1f);
        guRotate(&dynamicp->FPMap.Rotation[PlayerIndex], (float)(LocalCamera->Impulse / 5.0f), 1.0f, 0.0F, 0.0f);

        
        gSPMatrix(glistp++, &dynamicp->FPMap.Projection[PlayerIndex],
                  G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &dynamicp->FPMap.Viewing[PlayerIndex],
                  G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &dynamicp->FPMap.Translation[PlayerIndex],
                  G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &dynamicp->FPMap.Scale[PlayerIndex],
                  G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &dynamicp->FPMap.Rotation[PlayerIndex],
                  G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        // Draw FP Hands
        if (LocalPlayer->SelectedWeapon == 0)
        {
            LocalPlayer->PrimaryWeapon.Class->DrawCall();
        }
        else
        {
            LocalPlayer->SecondaryWeapon.Class->DrawCall();
        }
    }


    
}

void DrawBullets(int ThisPlayer)
{
    for (int ThisBullet = 0; ThisBullet < MAXBULLETS; ThisBullet++)
    {

        if (ProjectileArray[ThisBullet].Status == BULLET_INACTIVE)
        {
            continue;
        }

        guTranslate(&EntityMap[CurrentEntity[GlobalFrame % 2]],
                    (ProjectileArray[ThisBullet].Location.Position[0]),
                    (ProjectileArray[ThisBullet].Location.Position[1]),
                    (ProjectileArray[ThisBullet].Location.Position[2]));
        gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
                  G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

        guRotate(&EntityMap[CurrentEntity[GlobalFrame % 2]],
                 (float)(ProjectileArray[ThisBullet].Location.Angle[2] / 182.0f),
                 0.0f,
                 0.0f,
                 1.0f);

        gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
                  G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);

        guRotate(&EntityMap[CurrentEntity[GlobalFrame % 2]],
                 (float)(ProjectileArray[ThisBullet].Location.Angle[1] / 182.0f),
                 0.0f,
                 1.0f,
                 0.0f);

        gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
                  G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);

        guRotate(&EntityMap[CurrentEntity[GlobalFrame % 2]],
                 (float)(ProjectileArray[ThisBullet].Location.Angle[0] / 182.0f),
                 1.0f,
                 0.0f,
                 0.0f);

        gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
                  G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);

        gSPDisplayList(glistp++, logo_bulletbox);
        gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
        gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
        gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
    }
}

void DrawPlayers(int PlayerIndex)
{
    // Draw Other Players
    gSPDisplayList(glistp++, Draw_CyborgTP_T);
    for (int ThisPlayer = 0; ThisPlayer < PlayerCount; ThisPlayer++)
    {
        if ((GamePlayers[PlayerIndex].StatusBits & PLAYERFPS) && (ThisPlayer == PlayerIndex))
        {
            // FP mode and not drawing player's own model.
            continue;
        }

        CreateModelMatrix(GlobalAffine, GamePlayers[ThisPlayer].Location.Position, GamePlayers[ThisPlayer].Location.Angle);
        ScalingMatrix(GlobalAffine,0.065f);
        SetMatrix(0);
        //gSPDisplayList(glistp++, Draw_HitBox_M);
        DrawHolster((AnimeHolster*)&CyborgHolster, GamePlayers[ThisPlayer].Location.Position, GamePlayers[ThisPlayer].Location.Angle);
    }
    
    for (int ThisPlayer = PlayerCount; ThisPlayer < PlayerCount + BotCount; ThisPlayer++)
    {
        if (ThisPlayer == PlayerIndex)
        {
            continue;
        }
        guTranslate(&EntityMap[CurrentEntity[GlobalFrame % 2]],
                    (GamePlayers[ThisPlayer].Location.Position[0]),
                    (GamePlayers[ThisPlayer].Location.Position[1]),
                    (GamePlayers[ThisPlayer].Location.Position[2]));
        gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
                  G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

        guRotate(&EntityMap[CurrentEntity[GlobalFrame % 2]],
                 (float)(GamePlayers[ThisPlayer].Location.Angle[2] / 182.0f),
                 0.0f,
                 0.0f,
                 1.0f);

        gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
                  G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gDPPipeSync(glistp++);

        gSPDisplayList(glistp++, Draw_HitBox_M);
    }
}
