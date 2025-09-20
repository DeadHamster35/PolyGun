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
#include "animations.h"

#include "assets/models/DebugCylinder_HitBox_Model.h"
#include "FPGraphics.h"
#include "assets/assets.h"


Gfx gfx_glist[2][GFX_GLIST_LEN];
Gfx gfx_clear_glist[2][GFX_CLEAR_GLIST_LEN];
Dynamic gfx_dynamic[2];
Gfx *glistp;
u32 gfx_gtask_no = 0;


#define	LDIRX	180
#define	LDIRY	0
#define	LDIRZ	32
#define	AMBDIV	1
Lights1 Player_Lights[4]={
	{{128, 128, 128, 0, 128, 128, 128, 0},{240,128,128,0,240,128,128,0,LDIRX,LDIRY,LDIRZ,0}},
    {{128, 128, 128, 0, 128, 128, 128, 0},{240,128,128,0,240,128,128,0,LDIRX,LDIRY,LDIRZ,0}},
    {{128, 128, 128, 0, 128, 128, 128, 0},{240,128,128,0,240,128,128,0,LDIRX,LDIRY,LDIRZ,0}},
    {{128, 128, 128, 0, 128, 128, 128, 0},{240,128,128,0,240,128,128,0,LDIRX,LDIRY,LDIRZ,0}},
};

Mtx EntityMap[512];
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


void gfxClearZfb(void)
{
    /* Clear the Z-buffer  */
    gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT);
    gDPSetDepthImage(glistp++, osVirtualToPhysical(nuGfxZBuffer));
    gDPPipeSync(glistp++);
    gDPSetCycleType(glistp++, G_CYC_FILL);
    gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,
                        osVirtualToPhysical(nuGfxZBuffer));
    gDPSetFillColor(glistp++, (GPACK_ZDZ(G_MAXFBZ, 0) << 16 |
                                GPACK_ZDZ(G_MAXFBZ, 0)));
    
    gDPFillRectangle(glistp++, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
    gDPPipeSync(glistp++);
    gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,
                     osVirtualToPhysical(nuGfxCfb_ptr));

}
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
    gDPSetFillColor(glistp++, (GPACK_RGBA5551(64, 128, 235, 1) << 16 | 
			       GPACK_RGBA5551(128, 128, 215, 1)));
    gDPFillRectangle(glistp++, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
    gDPPipeSync(glistp++);
}

void SetMatrix(int Mode)
{
    return;
    
    if (Mode == 0)
    {
        AffineToMtx(GlobalAffine, (Mtx *)&EntityMap[CurrentEntity[GlobalFrame % 2]]);
        gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
                  G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        return;
    }

    AffineToMtx(GlobalAffine, (Mtx *)&EntityMap[CurrentEntity[GlobalFrame % 2]]);
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



ushort GetRGBA16(int R, int G, int B, int A)
{
	return (R & 0x1F)<<11 | (G & 0x1F)<<6 | (B & 0x1F)<<1 | (A & 0x01);
}


/*
Gfx mat_env_shine[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, ENVIRONMENT),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH),
    gsSPClearGeometryMode(G_CULL_FRONT | G_CULL_BACK | G_FOG | G_TEXTURE_GEN_LINEAR),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 3, G_AC_NONE | G_ZS_PIXEL),
    gsSPTexture(4031, 1983, 0, 0, 1),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cubemap_T),
    gsDPTileSync(),
    gsDPSetTile(0, 0, 0, 256, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadSync(),
    gsDPLoadTLUTCmd(7, 137),
    gsDPPipeSync(),
    gsDPTileSync(),
    gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, FinishLineBanner1_ci8),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_MIRROR, 4, 1, G_TX_WRAP | G_TX_MIRROR, 5, 1),
    gsDPLoadSync(),
    gsDPLoadBlock(7, 0, 0, 1023, 256),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, -5, 0, 0, 0, G_TX_WRAP | G_TX_MIRROR, 4, 1, G_TX_WRAP | G_TX_MIRROR, 5, 1),
    gsDPSetTileSize(0, 291, 48, 124, 124),
    gsSPEndDisplayList(),
};
*/


short LevelNormal[4], FPNormal[4];

void DrawFirstPerson(Dynamic *dynamicp, int PlayerIndex)
{

    
    Player *LocalPlayer = (Player *)&GamePlayers[PlayerIndex];
    if (LocalPlayer->IsCPU)
    {
        return;
    }
    if (LocalPlayer->StatusBits & STATUSZOOM)
    {
        return;
    }
    if (!(LocalPlayer->StatusBits & STATUSFPS))
    {
        return;
    }
    
    Light_t* Target = (Light_t*)&Player_Lights[PlayerIndex].l[0];

    Vector LightPath;
    LightPath[0] = -0;
    LightPath[1] = -96;
    LightPath[2] = -64;
    //{128,128,128,0,128,128,128,0,LDIRX,LDIRY,LDIRZ,0}
    
    PGCamera *LocalCamera = (PGCamera *)&GameCameras[PlayerIndex];
    
    AlignZVector(LightPath, LocalCamera->Location.Angle[2]);
    AlignYVector(LightPath, LocalCamera->Location.Angle[1]);

    Target->dir[0] = LightPath[0];
    Target->dir[1] = LightPath[1];
    
    gSPNumLights(glistp++, 1);
    gSPLight(glistp++, (&Player_Lights[PlayerIndex].l[0]),1);
	gSPLight(glistp++, (&Player_Lights[PlayerIndex].a),2);

    
    
    
    PGScreen *LocalScreen = (PGScreen*)&LocalCamera->Screen;
    LocalScreen->Viewport.vp.vscale[0] = LocalCamera->Screen.Size[0] * 2;
    LocalScreen->Viewport.vp.vscale[1] = LocalCamera->Screen.Size[1] * 2;
    
    LocalScreen->Viewport.vp.vtrans[0] = LocalCamera->Screen.Position[0] * 4;
    LocalScreen->Viewport.vp.vtrans[1] = LocalCamera->Screen.Position[1] * 4;
    
    gSPViewport(glistp++, (Vp*)&LocalScreen->Viewport);


    
    
    
    // Setup model matrix
    guPerspective(&dynamicp->FPMap.Projection[PlayerIndex], &FPNormal[PlayerIndex],
                    LocalCamera->FOVY, (float)(LocalCamera->Screen.Size[0] / LocalCamera->Screen.Size[1]), 2.0, 1500.0f, 1.0);
    gSPPerspNormalize(glistp++, FPNormal[PlayerIndex]);

    guLookAt(&dynamicp->FPMap.Viewing[PlayerIndex],
                0, 0, 0,
                0, 100.0f, 0,
                0, 0, 1);

    guTranslate(&dynamicp->FPMap.Translation[PlayerIndex], 0.0f, 0.0f, 0.0f);
    guScale(&dynamicp->FPMap.Scale[PlayerIndex], 1.0f, 1.0f, 1.0f);
    guRotate(&dynamicp->FPMap.Rotation[PlayerIndex], (float)(LocalCamera->Impulse / 5.0f), 1.0f, 0.0F, 0.0f);

    
    gSPMatrix(glistp++, &dynamicp->FPMap.Projection[PlayerIndex],
                G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &dynamicp->FPMap.Viewing[PlayerIndex],
                G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &dynamicp->FPMap.Translation[PlayerIndex],
                G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &dynamicp->FPMap.Rotation[PlayerIndex],
                G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    // Draw FP Hands
    
    
    gDPSetScissor
    (
        glistp++, 
        G_SC_NON_INTERLACE, 
        LocalCamera->Screen.Position[0] - (LocalCamera->Screen.Size[0] * 0.5f), 
        LocalCamera->Screen.Position[1] - (LocalCamera->Screen.Size[1] * 0.5f), 
        LocalCamera->Screen.Position[0] + (LocalCamera->Screen.Size[0] * 0.5f), 
        LocalCamera->Screen.Position[1] + (LocalCamera->Screen.Size[1] * 0.5f)
    );


    //DrawHolster((AnimeHolster*)GamePlayers[PlayerIndex].FPAnime, GamePlayers[PlayerIndex].FPAnimeTimer.CurrentTime);
    DrawAnime(GamePlayers[PlayerIndex].FPAnime->RootBone, GamePlayers[PlayerIndex].FPAnimeTimer.CurrentTime);
    gDPPipeSync(glistp++);
        
        
    
}
void DrawLevelScene(Dynamic *dynamicp, int PlayerIndex)
{

    

    
    
    Player *LocalPlayer = (Player *)&GamePlayers[PlayerIndex];
    if (LocalPlayer->IsCPU)
    {
        // Don't draw for CPU bots
        return;
    }
    PGCamera *LocalCamera = (PGCamera *)&GameCameras[PlayerIndex];
    PGScreen *LocalScreen = (PGScreen*)&LocalCamera->Screen;
    LocalScreen->Viewport.vp.vscale[0] = 640;
    LocalScreen->Viewport.vp.vscale[1] = 480;
    
    LocalScreen->Viewport.vp.vtrans[0] = 640;
    LocalScreen->Viewport.vp.vtrans[1] = 480;
    
    gSPViewport(glistp++, (Vp*)&LocalScreen->Viewport);
    if (LocalPlayer->StatusBits & STATUSZOOM)
    {
        LocalCamera->FOVY = 70.0f / LocalPlayer->ZoomFloat;
    }
    else
    {
        LocalCamera->FOVY = 70.0f;
    }
    
    guPerspective(&dynamicp->LevelMap.Projection[PlayerIndex], &LevelNormal[PlayerIndex],
                  70.0f, (float)(320.0f/240.0f), 5.0f, 8000.0f, 1.0f);
    gSPPerspNormalize(glistp++, LevelNormal[PlayerIndex]);

    guLookAt(&dynamicp->LevelMap.Viewing[PlayerIndex],
             LocalCamera->Location.Position[0], LocalCamera->Location.Position[1], LocalCamera->Location.Position[2],
             LocalCamera->LookAt[0], LocalCamera->LookAt[1], LocalCamera->LookAt[2],
             0, 0, 1);

    guTranslate(&dynamicp->LevelMap.Translation[PlayerIndex], 100.0f, 150.0f, 0.0f);

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
        0,
        0,
        320,
        240
    );


    //gSPDisplayList(glistp++, (0x06000000 | LoadedScenario.DisplayTableAddress));
    gSPDisplayList(glistp++, &Draw_CyborgTP_T);
    gSPDisplayList(glistp++, &Draw_HitBox_M);
    
    
    gDPSetRenderMode(glistp++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    
    
    


    
}
#define PROJ_COMBINE 1, 0, PRIMITIVE, 0, 1, 0, 1, 0
ushort ProjR, ProjG, ProjB;

void DrawPickups(int ThisPlayer)
{
    float Check = 0;
    Vector Source, Target;
    Source[0] = GamePlayers[ThisPlayer].Location.Position[0];
    Source[1] = GamePlayers[ThisPlayer].Location.Position[1];
    Source[2] = GamePlayers[ThisPlayer].Location.Position[2];

    ProjR = (255 >> 11) & 0x1F;
    ProjG = (255 >> 6) & 0x1F;
    ProjB = (0 >> 1) & 0x1F;

    gDPSetPrimColor(glistp++, 0, 0, ProjR * 8, ProjG * 8, ProjB * 8, 255);
    gDPSetCombineMode (glistp++, PROJ_COMBINE, PROJ_COMBINE);
    gSPSetGeometryMode(glistp++, G_SHADE | G_ZBUFFER | G_CULL_BACK);
    gDPSetRenderMode(glistp++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gDPPipeSync(glistp++);
    

    for (int ThisPick = 0; ThisPick < TotalStaticPicks; ThisPick++)
    {
        Target[0] = StaticPickArray[ThisPick].Position[0];
        Target[1] = StaticPickArray[ThisPick].Position[1];
        Target[2] = StaticPickArray[ThisPick].Position[2];
        

        //Check = GetDistance(Source, Target);
        //if (Check < PICKUPDRAW)
        {
            CreatePositionMatrix(GlobalAffine, Target);
            SetMatrix(0);
            gSPDisplayList(glistp++, logo_bulletbox);
        }
    }
}


void DrawBullets(int ThisPlayer)
{   
    gDPSetCombineMode (glistp++, PROJ_COMBINE, PROJ_COMBINE);
    gSPSetGeometryMode(glistp++, G_SHADE | G_ZBUFFER | G_CULL_BACK);
    gDPSetRenderMode(glistp++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gDPPipeSync(glistp++);
    for (int ThisBullet = 0; ThisBullet < MAXBULLETS; ThisBullet++)
    {
        if (ProjectileArray[ThisBullet].Status == BULLET_INACTIVE)
        {
            continue;
        }

        Projectile* LocalBullet = &ProjectileArray[ThisBullet];
        CreateModelMatrix(GlobalAffine, LocalBullet->Location.Position, LocalBullet->Location.Angle);
        SetMatrix(0);
        ProjR = (LocalBullet->RGB >> 11) & 0x1F;
        ProjG = (LocalBullet->RGB >> 6) & 0x1F;
        ProjB = (LocalBullet->RGB >> 1) & 0x1F;



        gDPSetPrimColor(glistp++, 0, 0, ProjR * 8, ProjG * 8, ProjB * 8, 255);
        gSPDisplayList(glistp++, logo_bulletbox);
    }

    gDPPipeSync(glistp++);

}

void DrawPlayers(int PlayerIndex)
{
    // Draw Other Players
    gSPDisplayList(glistp++, Draw_CyborgTP_T);
    
    for (int ThisPlayer = 0; ThisPlayer < PlayerCount; ThisPlayer++)
    {
        if ((GamePlayers[PlayerIndex].StatusBits & STATUSFPS) && (ThisPlayer == PlayerIndex))
        {
            // FP mode and not drawing player's own model.
            continue;
        }
        
        CreateModelMatrix(GlobalAffine, GamePlayers[ThisPlayer].Location.Position, GamePlayers[ThisPlayer].Location.Angle);
        SetMatrix(0);
        
        gSPDisplayList(glistp++, Draw_HitBox_M);
    }

    for (int ThisPlayer = PlayerCount; ThisPlayer < PlayerCount + BotCount; ThisPlayer++)
    {
        if (ThisPlayer == PlayerIndex)
        {
            continue;
        }
        CreateModelMatrix(GlobalAffine, GamePlayers[ThisPlayer].Location.Position, GamePlayers[ThisPlayer].Location.Angle);
        SetMatrix(0);
        
        
        gSPDisplayList(glistp++, Draw_HitBox_M);
    }


    
    gSPDisplayList(glistp++, Draw_Shield_T);
    short ShieldAlpha, ShieldWork;
    float ShieldRatio;
    for (int ThisPlayer = 0; ThisPlayer < PlayerCount + BotCount; ThisPlayer++)
    {   
        if (GamePlayers[ThisPlayer].HealthData.DisplayStatus == DISPLAY_ON)
        {
            
            ShieldWork = (90 - (RECHARGE_TIME - GamePlayers[ThisPlayer].HealthData.HitFrames));
            ShieldRatio = (ShieldWork * .016f);
            ShieldAlpha = 255;
            
            if (ShieldRatio < 1.0f)
            {
                if (ShieldRatio > 0)
                {
                    ShieldAlpha = (int)(255 * ShieldRatio);
                }
                else
                {
                    ShieldAlpha = 0;
                    GamePlayers[ThisPlayer].HealthData.DisplayStatus = DISPLAY_OFF;
                }
            }

            gDPSetPrimColor(glistp++, 0, 0, 255, 255, 128, ShieldAlpha);
            
            CreateModelMatrix(GlobalAffine, GamePlayers[ThisPlayer].Location.Position, GamePlayers[ThisPlayer].Location.Angle);
            SetMatrix(0);
            gSPDisplayList(glistp++, Draw_ShieldBox_M);
        }
    }
}
