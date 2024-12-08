/*
   gfxinit.c

   The display list for the graphic initialization

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.
*/

#include <nusys.h>
#include "graphic.h"

/*
  The viewport structure
  The conversion from (-1,-1,-1)-(1,1,1).  The decimal part of 2-bit.
 */
static Vp vp = {
    SCREEN_WD * 2, SCREEN_HT * 2, G_MAXZ / 2, 0, /* The scale factor  */
    SCREEN_WD * 2, SCREEN_HT * 2, G_MAXZ / 2, 0, /* Move  */
};



/*
  The initialization of RDP
*/

void initRDP()
{
    gDPSetEnvColor(glistp++, 0, 0, 0, 0);
    gDPSetPrimColor(glistp++, 0, 0, 0, 0, 0, 0);
    gDPSetBlendColor(glistp++, 0, 0, 0, 0);
    gDPSetFogColor(glistp++, 0, 0, 0, 0);
    gDPSetFillColor(glistp++, 0);
    gDPSetPrimDepth(glistp++, 0, 0);
    gDPSetConvert(glistp++, 0, 0, 0, 0, 0, 0);
    gDPSetKeyR(glistp++, 0, 0, 0);
    gDPSetKeyGB(glistp++, 0, 0, 0, 0, 0, 0);

    /* set combine mode */
    gDPSetCombineMode(glistp++, G_CC_SHADE, G_CC_SHADE);

    /* initialize the scissor box */
    gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT);

    /* initialize all the texture tile descriptors to zero */
    gDPSetTile(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    gDPSetTile(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
    gDPSetTile(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0);
    gDPSetTile(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0);
    gDPSetTile(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0);
    gDPSetTile(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0);
    gDPSetTile(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0);
    gDPSetTile(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0);

    gDPSetTileSize(glistp++, 0, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) << G_TEXTURE_IMAGE_FRAC);
    gDPSetTileSize(glistp++, 1, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) << G_TEXTURE_IMAGE_FRAC);
    gDPSetTileSize(glistp++, 2, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) << G_TEXTURE_IMAGE_FRAC);
    gDPSetTileSize(glistp++, 3, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) << G_TEXTURE_IMAGE_FRAC);
    gDPSetTileSize(glistp++, 4, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) << G_TEXTURE_IMAGE_FRAC);
    gDPSetTileSize(glistp++, 5, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) << G_TEXTURE_IMAGE_FRAC);
    gDPSetTileSize(glistp++, 6, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) << G_TEXTURE_IMAGE_FRAC);
    gDPSetTileSize(glistp++, 7, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) << G_TEXTURE_IMAGE_FRAC);
    gDPPipeSync(glistp++);
    gSPEndDisplayList(glistp++);
}

Gfx setup_rdpstate[] = {
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),
    gsDPSetColorDither(G_CD_BAYER),

    
};

/*
  The initialization of RSP
*/
Gfx setup_rspstate[] = {
    gsSPViewport(&vp),
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH | G_CULL_BACK),
    gsSPTexture(0, 0, 0, 0, G_OFF),
    gsSPEndDisplayList(),
};
