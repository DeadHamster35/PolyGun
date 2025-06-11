/*
   stage00.c

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.
*/

#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "graphic.h"
#include "levels.h"
#include "memory.h"
#include "player.h"
#include "weapon.h"
#include "intelligence.h"
#include "assets/assets.h"

static float triPos_x; /* The display position, X */
static float triPos_y; /* The display position, Y */
static float theta;    /* The rotational angle of the square  */

void shadetri(Dynamic *dynamicp);

/* The initialization of stage 0  */
void initStage00(void)
{
    triPos_x = 0.0;
    triPos_y = 0.0;
    theta = 0.0;

}

/* Make the display list and activate the task  */
void makeDL00(void)
{
    Dynamic *dynamicp;
    
    
    CurrentEntity[GlobalFrame % 2] = 0;
    /* Specify the display list buffer  */
    dynamicp = &gfx_dynamic[gfx_gtask_no];
    glistp = &gfx_glist[gfx_gtask_no][0];

    SetSegment(0,0);
    SetSegment(2, osVirtualToPhysical(dynamicp));

    StoreRSPSegments();

    /*  The initialization of RCP  */
    gfxRCPInit();

    /* Clear the frame and Z-buffer  */
    gfxClearCfb();
    
    osViSetSpecialFeatures(OS_VI_GAMMA_OFF);	     
    osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON);

    gDPPipeSync(glistp++);
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    gDPSetRenderMode(glistp++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);


    
    for (int ThisPlayer = 0; ThisPlayer < PlayerCount; ThisPlayer++)
    {
        DrawLevelScene(dynamicp,ThisPlayer);
        
        DrawHUD(ThisPlayer);
        gDPPipeSync(glistp++);
    }
    
    
   
    gDPFullSync(glistp++);
    gSPEndDisplayList(glistp++);

    
    /* Activate the task and
       switch display buffers. */
    
    nuGfxTaskStart(&gfx_glist[gfx_gtask_no][0],
                   (s32)(glistp - gfx_glist[gfx_gtask_no]) * sizeof(Gfx),
                   NU_GFX_UCODE_F3DEX2, NU_SC_NOSWAPBUFFER);

    nuDebTaskPerfBar0(1, 200, NU_SC_NOSWAPBUFFER);
    
    /* Display the drawing state   */
    nuDebConTextPos(0, 3, 2);
    nuDebConCPuts(0, "A30 - Halo");
    nuDebConTextPos(0, 2, 3);
    sprintf(conbuf, "%2d draw/sec", dspcount);
    nuDebConCPuts(0, conbuf);

    /* Draw characters on the frame buffer  */
    nuDebConDisp(NU_SC_SWAPBUFFER);
    /* Switch display list buffers  */
    gfx_gtask_no ^= 1;
}

/* The game progressing process for stage 0 */
void updateGame00(void)
{
    static float vel = 1.0;

    nuContDataGetEx((NUContData*)&contdata[0], 0);
    nuContDataGetEx((NUContData*)&contdata[1], 1);
    nuContDataGetEx((NUContData*)&contdata[2], 2);
    nuContDataGetEx((NUContData*)&contdata[3], 3);
    
    if (contdata[0].trigger & START_BUTTON)
    {
        /* Remove the call-back function.*/
        nuGfxFuncRemove();
        /* Specify next stage to main */
        stage = 1;
    }


    UpdatePlayerControls();
    UpdateBotControls();
    UpdatePlayerResponse();
    CheckProjectiles();

}

/* The vertex coordinate  */
static Vtx shade_vtx[] = {
    {-64, 64, -5, 0, 0, 0, 0, 0xff, 0, 0xff},
    {64, 64, -5, 0, 0, 0, 0, 0, 0, 0xff},
    {64, -64, -5, 0, 0, 0, 0, 0, 0xff, 0xff},
    {-64, -64, -5, 0, 0, 0, 0xff, 0, 0, 0xff},
};

/* Draw a square  */
void shadetri(Dynamic *dynamicp)
{
    int i;

    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->LevelMap.Projection)),
              G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->LevelMap.Translation)),
              G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->LevelMap.Rotation)),
              G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);

    gSPVertex(glistp++, &(shade_vtx[0]), 4, 0);

    gDPPipeSync(glistp++);
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    gDPSetRenderMode(glistp++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
    gSPClearGeometryMode(glistp++, 0xFFFFFFFF);
    gSPSetGeometryMode(glistp++, G_SHADE | G_SHADING_SMOOTH);

    for (i = 0; i < 25; i++)
        gSP2Triangles(glistp++, 0, 1, 2, 0, 0, 2, 3, 0);
}
