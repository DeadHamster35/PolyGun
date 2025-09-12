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
#include "FPGraphics.h"

static float triPos_x; /* The display position, X */
static float triPos_y; /* The display position, Y */
static float theta;    /* The rotational angle of the square  */



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
    


    
    
    


    for (int ThisPlayer = 0; ThisPlayer < PlayerCount; ThisPlayer++)
    {

        gDPSetTextureFilter(glistp++, G_TF_BILERP)
        gDPPipeSync(glistp++);
        gDPSetCycleType(glistp++, G_CYC_1CYCLE);
        gDPSetRenderMode(glistp++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);


        DrawLevelScene(dynamicp,ThisPlayer);
        DrawBullets(ThisPlayer);
        DrawPlayers(ThisPlayer);                
        DrawPickups(ThisPlayer);
        
    }
    gDPSetRenderMode(glistp++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    //Clear Z-Buffer before drawing FP views.
    gfxClearZfb();
    
    
    
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);

    for (int ThisPlayer = 0; ThisPlayer < PlayerCount; ThisPlayer++)
    {
        gDPPipeSync(glistp++);        
        DrawFirstPerson(dynamicp,ThisPlayer);

        gSPClearGeometryMode(glistp++, G_ZBUFFER);
        DrawHUD(ThisPlayer); 
        gSPSetGeometryMode(glistp++, G_ZBUFFER);     
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
    nuDebConTextPos(0, 2, 12);
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
    CheckPlayerHealth();
    

}

