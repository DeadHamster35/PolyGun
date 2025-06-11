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
    gDPSetFillColor(glistp++, (GPACK_RGBA5551(64, 128, 235, 1) << 16 | 
			       GPACK_RGBA5551(128, 128, 215, 1)));
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

void DrawShieldHealth(int PlayerIndex)
{
    Player *LocalPlayer = (Player *)&GamePlayers[PlayerIndex];

    if (LocalPlayer->IsCPU)
    {
        // Don't draw for CPU bots
        return;
    }
    PGCamera *LocalCamera = (PGCamera *)&GameCameras[PlayerIndex];

    int ColorCheck = LocalPlayer->HealthData.Shield;

    
    if (ColorCheck > 75)
    {
        gDPSetPrimColor(glistp++, 0, 0, 32, 208, 255, 192);
    }
    else if (ColorCheck > 40)
    {
        gDPSetPrimColor(glistp++, 0, 0, 255, 255, 0, 192);
    }
    else
    {
        gDPSetPrimColor(glistp++, 0, 0, 255, 0, 0, 192);
    }

    
    gSPSetGeometryMode(glistp++,G_SHADE | G_SHADING_SMOOTH);
    gDPSetCombineLERP(glistp++,TEXEL0, 0, PRIMITIVE, 0,
                        0, 0, 0, TEXEL0,
                        TEXEL0, 0, PRIMITIVE, 0,
                        0, 0, 0, TEXEL0);
    gDPSetTexturePersp(glistp++,G_TP_NONE);
    gDPSetTextureFilter(glistp++,G_TF_BILERP);
    gDPSetTextureConvert(glistp++,G_TC_FILT);
    gDPSetTextureLOD(glistp++,G_TL_TILE);
    gDPSetTextureDetail(glistp++,G_TD_CLAMP);
    gDPSetTextureLUT(glistp++,G_TT_NONE);
    gDPSetRenderMode(glistp++,  G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);

    gDPSetTextureLUT(glistp++, G_TT_RGBA16);
	gSPTexture(glistp++, 65535, 65535, 0, 0, 1);
	gDPLoadTLUT_pal16(glistp++, 0, &ShieldHealthbar_PAL);
	gDPLoadTextureBlock_4b(glistp++, &ShieldHealthbar_T, G_IM_FMT_CI,128,32,0,G_TX_CLAMP,G_TX_CLAMP,7,5,0,0);
    
    gSPTextureRectangle
    (
        glistp++,
        ( (210) <<2), 
        ( (13) <<2), 
        ( (298)<<2), 
        ( (37) <<2), 
        G_TX_RENDERTILE, 
        0, 0, 
        1<<10, 1<<10
    );

    
    ColorCheck = GamePlayers[PlayerIndex].HealthData.Health;

    if (ColorCheck > 75)
    {
        gDPSetPrimColor(glistp++, 0, 0, 25, 192, 255, 192);
        
    }
    else if (ColorCheck > 40)
    {
        gDPSetPrimColor(glistp++, 0, 0, 255, 255, 0, 192);
    }
    else
    {
        gDPSetPrimColor(glistp++, 0, 0, 255, 0, 0, 192);
    }

        
    for (int ThisPass = 0; ThisPass < ColorCheck / 12; ThisPass ++)
    {
        gSPTextureRectangle
        (
            glistp++,
            ( (225 + (ThisPass * 6)) << 2), 
            ( (31) << 2), 
            ( (231 + (ThisPass * 6)) << 2), 
            ( (41) << 2), 
            G_TX_RENDERTILE, 
            3200, 480, 
            1<<10, 1<<10
        );
    }
    

}


void DrawHUD(int PlayerIndex)
{
    Player *LocalPlayer = (Player *)&GamePlayers[PlayerIndex];

    if (LocalPlayer->IsCPU)
    {
        // Don't draw for CPU bots
        return;
    }
    PGCamera *LocalCamera = (PGCamera *)&GameCameras[PlayerIndex];

    gSPClearGeometryMode(glistp++, G_ZBUFFER);



    /*
    //reticle
    if (GamePlayers[PlayerIndex].ZTarget > 0)
    {
        gDPSetPrimColor(glistp++, 0, 0, 255, 0, 0, 192);
    }
    else
    {
        gDPSetPrimColor(glistp++, 0, 0, 25, 192, 255, 192);
    }
    Player* LocalPlayer =       (Player*)&GamePlayers[PlayerIndex];
    WeaponClass* LocalWeapon;
    WeaponEquipment* LocalEquipment;
    if (LocalPlayer->SelectedWeapon == 0)
    {
        LocalEquipment = (WeaponEquipment*)&LocalPlayer->WeaponArray;
        LocalWeapon = (WeaponClass*)LocalPlayer->WeaponArray.Class;
    }
    else
    {
        LocalEquipment = (WeaponEquipment*)&LocalPlayer->SecondaryWeapon;
        LocalWeapon = (WeaponClass*)LocalPlayer->SecondaryWeapon.Class;
    }
    
    
    
   	gSPDisplayList(glistp++, LocalWeapon->Reticle);
    */

    

    
    DrawShieldHealth(PlayerIndex);

    //gDPSetPrimColor(glistp++, 0, 0, 25, 192, 255, 192);
    //DrawARAmmo(LocalEquipment->Magazine);
    //gDPSetTextureLUT(glistp++, G_TT_NONE);


    
}


void DrawLevelScene(Dynamic *dynamicp, int PlayerIndex)
{
    gDPSetTextureFilter(glistp++, G_TF_BILERP)
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

    guLookAtReflect(&dynamicp->LevelMap.Viewing[PlayerIndex], &dynamicp->LevelMap.Reflection[PlayerIndex],
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
    
    gSPLookAt(glistp++, &dynamicp->LevelMap.Reflection[PlayerIndex]);

    gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(TableAddress[LevelIndex]));

    DrawPlayers(PlayerIndex);
    DrawBullets(PlayerIndex);
    
    if (LocalPlayer->StatusBits & STATUSFPS)
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
        

        
        Light_t* Target = (Light_t*)&AR_Lights[0].l[0];

        Vector LightPath;
        LightPath[0] = -0;
        LightPath[1] = -100;
        LightPath[2] = -150;
        //{128,128,128,0,128,128,128,0,LDIRX,LDIRY,LDIRZ,0}
        
        AlignZVector(LightPath, LocalCamera->Location.Angle[2]);
        AlignYVector(LightPath, LocalCamera->Location.Angle[1]);

        Target->dir[0] = LightPath[0];
        Target->dir[1] = LightPath[1];
        

        // Setup model matrix
        guPerspective(&dynamicp->FPMap.Projection[PlayerIndex], &FPNormal[PlayerIndex],
                      LocalCamera->FOVY, (LocalCamera->Screen.Size[0] / LocalCamera->Screen.Size[1]), 2.0, 1500.0f, 1.0);
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
        gSPMatrix(glistp++, &dynamicp->FPMap.Scale[PlayerIndex],
                  G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &dynamicp->FPMap.Rotation[PlayerIndex],
                  G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        // Draw FP Hands

        
        DrawHolster((AnimeHolster*)GamePlayers[PlayerIndex].FPAnime, GamePlayers[PlayerIndex].FPAnimeTimer.CurrentTime);
        
    }


    
}
#define PROJ_COMBINE 1, 0, PRIMITIVE, 0, 1, 0, 1, 0
ushort ProjR, ProjG, ProjB;
void DrawBullets(int ThisPlayer)
{
    for (int ThisBullet = 0; ThisBullet < MAXBULLETS; ThisBullet++)
    {
        
        if (ProjectileArray[ThisBullet].Status == BULLET_INACTIVE)
        {
            continue;
        }

        Projectile* LocalBullet = &ProjectileArray[ThisBullet];

        guTranslate(&EntityMap[CurrentEntity[GlobalFrame % 2]],
                    (LocalBullet->Location.Position[0]),
                    (LocalBullet->Location.Position[1]),
                    (LocalBullet->Location.Position[2]));
        gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
                  G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

        guRotate(&EntityMap[CurrentEntity[GlobalFrame % 2]],
                 (float)(LocalBullet->Location.Angle[2] / 185.0f),
                 0.0f,
                 0.0f,
                 1.0f);

        gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
                  G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);

        guRotate(&EntityMap[CurrentEntity[GlobalFrame % 2]],
                 (float)(LocalBullet->Location.Angle[1] / 185.0f),
                 0.0f,
                 1.0f,
                 0.0f);

        gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
                  G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);

        guRotate(&EntityMap[CurrentEntity[GlobalFrame % 2]],
                 (float)(LocalBullet->Location.Angle[0] / 185.0f),
                 1.0f,
                 0.0f,
                 0.0f);

        gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
                  G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);

        
        ProjR = (LocalBullet->RGB >> 11) & 0x1F;
        ProjG = (LocalBullet->RGB >> 6) & 0x1F;
        ProjB = (LocalBullet->RGB >> 1) & 0x1F;

        gDPSetPrimColor(glistp++, 0, 0, ProjR * 8, ProjG * 8, ProjB * 8, 255);
        gDPSetCombineMode (glistp++, PROJ_COMBINE, PROJ_COMBINE);
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
        if ((GamePlayers[PlayerIndex].StatusBits & STATUSFPS) && (ThisPlayer == PlayerIndex))
        {
            // FP mode and not drawing player's own model.
            continue;
        }
        /*
        CreateModelMatrix(GlobalAffine, GamePlayers[ThisPlayer].Location.Position, GamePlayers[ThisPlayer].Location.Angle);
        ScalingMatrix(GlobalAffine,0.5f);
        SetMatrix(0);
        gSPDisplayList(glistp++, Draw_ar_T);
        gSPDisplayList(glistp++, Draw_Sphere001_M);
        gSPDisplayList(glistp++, Draw_ar_T_Closing);
        */

        guTranslate(&EntityMap[CurrentEntity[GlobalFrame % 2]],
                    (GamePlayers[ThisPlayer].Location.Position[0]),
                    (GamePlayers[ThisPlayer].Location.Position[1]),
                    (GamePlayers[ThisPlayer].Location.Position[2]));
        gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
                  G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

        guRotate(&EntityMap[CurrentEntity[GlobalFrame % 2]],
                 (float)(GamePlayers[ThisPlayer].Location.Angle[2] / 185.0f),
                 0.0f,
                 0.0f,
                 1.0f);

        gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
                  G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gDPPipeSync(glistp++);
        gSPDisplayList(glistp++, Draw_ar_T);
        gSPDisplayList(glistp++, Draw_HitBox_M);
    
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
                 (float)(GamePlayers[ThisPlayer].Location.Angle[2] / 185.0f),
                 0.0f,
                 0.0f,
                 1.0f);

        gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
                  G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gDPPipeSync(glistp++);
        gSPDisplayList(glistp++, Draw_ar_T);
        gSPDisplayList(glistp++, Draw_HitBox_M);
    }
}
