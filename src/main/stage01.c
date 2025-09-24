/*
   stage01.c

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.
*/

#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "graphic.h"
#include "levels.h"
#include "memory.h"
#include "HUD.h"
#include "player.h"
#include "math.h"

short GameFirstStart = 0;
char* PlayerSelectStrings[] = 
{
    "ONE PLAYER",
    "TWO PLAYERS",
    "THREE PLAYERS",
    "FOUR PLAYERS"
    
};


/* Draw a square  */
void PrintMenuText(Dynamic *dynamicp)
{
    int i;

    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->LevelMap.Projection)),
              G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->LevelMap.Translation)),
              G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->LevelMap.Rotation)),
              G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);

    DrawText(80, 180, PlayerSelectStrings[PlayerCount - 1], 1.0f);
}

/* The initialization of stage 1 */
void initStage01(void)
{
    PlayerCount = 1;
}

Gfx DrawMenu[] = 
{
    
    gsDPSetTextureLUT( 0),
	gsSPTexture( 65535, 65535, 0, 0, 1),
	gsDPPipeSync( ),
	gsDPTileSync( ),
	
	gsSPClearGeometryMode(  12518917),
	gsSPSetGeometryMode(  10486789),
    
	gsDPLoadTextureBlock_4b( &ASCII_T, G_IM_FMT_IA,32,256,0,G_TX_CLAMP,G_TX_CLAMP,5,8,0,0),    
    gsSPEndDisplayList(),
};

/* Make the display list for stage 1 and activate the task */
void makeDL01(void)
{
    Dynamic *dynamicp;

    
    glistp = &gfx_clear_glist[gfx_gtask_no][0];

    /* Initialize RCP */
    gfxRCPInit();

  
    /* Clear the frame and Z-buffer */
    gfxClearCfb();
    assert((glistp - gfx_clear_glist[gfx_gtask_no]) < GFX_CLEAR_GLIST_LEN);

    gDPFullSync(glistp++);
    gSPEndDisplayList(glistp++);

    /* Activate the task and
       switch display buffers. */
    nuGfxTaskStart(&gfx_clear_glist[gfx_gtask_no][0],
                   (s32)(glistp - gfx_clear_glist[gfx_gtask_no]) * sizeof(Gfx),
                   NU_GFX_UCODE_F3DEX, NU_SC_NOSWAPBUFFER);

    /* Specify the display list buffer */
    dynamicp = &gfx_dynamic[gfx_gtask_no];
    glistp = &gfx_glist[gfx_gtask_no][0];

    
    

    osViSetSpecialFeatures(OS_VI_GAMMA_OFF);	     
    osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON);

    SetSegment(0,0);
    SetSegment(2, osVirtualToPhysical(dynamicp));

    StoreRSPSegments();

    /* The initialization of RCP */
    gfxRCPInit();

    /* projection,modeling matrix set */
    guOrtho(&dynamicp->LevelMap.Projection[0],
            -(float)SCREEN_WD / 2.0F, (float)SCREEN_WD / 2.0F,
            -(float)SCREEN_HT / 2.0F, (float)SCREEN_HT / 2.0F,
            1.0F, 10.0F, 1.0F);


    
    gDPPipeSync(glistp++);
    
    //gDPSetRenderMode(glistp++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);

    //gDPSetCycleType	(glistp++ ,G_CYC_COPY);
    gSPDisplayList(glistp++, DrawMenu);   
    
    
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    gDPSetCombineMode(glistp++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    //gDPSetRenderMode(glistp++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE);
    gDPSetRenderMode(glistp++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetDepthSource(glistp++, G_ZS_PRIM);
    gDPSetPrimDepth(glistp++, 0, 0);
    gDPSetTexturePersp(glistp++, G_TP_NONE);

    
    PrintMenuText(dynamicp);

    
    gDPFullSync(glistp++);
    gSPEndDisplayList(glistp++);

    assert((glistp - gfx_glist[gfx_gtask_no]) < GFX_GLIST_LEN);

    /* Activate the task and
       switch display buffers. */
    nuGfxTaskStart(&gfx_glist[gfx_gtask_no][0],
                   (s32)(glistp - gfx_glist[gfx_gtask_no]) * sizeof(Gfx),
                   NU_GFX_UCODE_F3DEX, NU_SC_NOSWAPBUFFER);

    nuDebTaskPerfBar0(1, 200, NU_SC_NOSWAPBUFFER);

    /* Display the drawing state  */

    /* Draw characters on the frame buffer */
    nuDebConDisp(NU_SC_SWAPBUFFER);

    /* Switch display list buffers */
    gfx_gtask_no ^= 1;
}


int HeldTimer = 0;
/* The game progressing process for stage 1 */
void updateGame01(void)
{
    /* Data reading of controller 1 */
    nuContDataGetEx((NUContData*)&contdata[0], 0);

    /* Change the display position according to stick data */
    float XPos = contdata[0].stick_x;
    float YPos = contdata[0].stick_y;
    

    //deadstick
    

    if (HeldTimer > 20)
    {
        HeldTimer = 0;
    }

    if (HeldTimer == 0)
    {
        if (XPos > 5)
        {
            if (PlayerCount < 4)
            {
                PlayerCount++;
            }
            
            HeldTimer++;
        }
        else if (XPos < -5)
        {
            if (PlayerCount > 1)
            {
                PlayerCount--;
            }

            
            HeldTimer++;
        }
    }

    if ( ((XPos < 0.20f) && (XPos > -0.20f)) && ((YPos < 0.20f) && (YPos < 0.20f)) )
    {
        HeldTimer = 0;
    }
    else
    {
        HeldTimer++;
    }

    if (contdata[0].trigger & A_BUTTON)
    { 
        
        /* Remove the call-back function.*/
        nuGfxFuncRemove();
        InitNewGame();
        /* Specify next stage to main */
        stage = 0;
        
    }
    /* Move to stage 0 when the start button is pushed */
    if (contdata[0].trigger & START_BUTTON)
    {
            /* Remove the call-back function.*/
            nuGfxFuncRemove();
            InitNewGame();
            /* Specify next stage to main */
            stage = 0;
        
    }

}
