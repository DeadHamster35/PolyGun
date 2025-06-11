
#include <nusys.h>
#include <nualsgi_n.h>
#include "common.h"
#include "graphic.h"
#include "HUD.h"




Gfx PistolReticleGFX[] = 
{
    
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0,
                        0, 0, 0, TEXEL0,
                        TEXEL0, 0, PRIMITIVE, 0,
                        0, 0, 0, TEXEL0),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetRenderMode(  G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),


    
    
    gsDPLoadTextureBlock(PistolReticleTex,
                            G_IM_FMT_RGBA,
                            G_IM_SIZ_16b,
                            16, 16,
                            0,
                            G_TX_CLAMP,
                            G_TX_CLAMP,
                            5, 5,
                            G_TX_NOLOD, G_TX_NOLOD),
                            
    gsSPTextureRectangle( ( ((SCREEN_WD * 0.5F) - 8 )  * 4), ( ((SCREEN_HT * 0.5F) - 8) * 4), ( ((SCREEN_WD * 0.5F) + 8) * 4), ( ((SCREEN_HT * 0.5F) + 8) * 4), G_TX_RENDERTILE, 0, 0, 1024, 1024),


    gsDPPipeSync(),


    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx AssaultRifleReticleGFX[] = 
{
    
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0,
                        0, 0, 0, TEXEL0,
                        TEXEL0, 0, PRIMITIVE, 0,
                        0, 0, 0, TEXEL0),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetRenderMode(  G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),


    
    
    gsDPLoadTextureBlock(ARReticleTex,
                            G_IM_FMT_RGBA,
                            G_IM_SIZ_16b,
                            32, 32,
                            0,
                            G_TX_CLAMP,
                            G_TX_CLAMP,
                            5, 5,
                            G_TX_NOLOD, G_TX_NOLOD),
                            
    gsSPTextureRectangle( ( ((SCREEN_WD * 0.5F) - 12 )  * 4), ( ((SCREEN_HT * 0.5F) - 12) * 4), ( ((SCREEN_WD * 0.5F) + 14) * 4), ( ((SCREEN_HT * 0.5F) + 14) * 4), G_TX_RENDERTILE, 0, 0, 1024, 1024),


    gsDPPipeSync(),


    gsDPPipeSync(),
    gsSPEndDisplayList(),
};
void DrawAssaultRifle()
{
    
    return;
    /*
    gSPDisplayList(glistp++, Draw_CyborgLimbs_T);
    gSPDisplayList(glistp++, Draw_ReloadRightArm_M);
    gSPDisplayList(glistp++, Draw_ReloadLeftArm_M);
    gSPDisplayList(glistp++, Draw_ReloadLeftHand_M);
    gSPDisplayList(glistp++, Draw_CyborgHand_M);
    gSPDisplayList(glistp++, Draw_ar_T);
    gSPDisplayList(glistp++, Draw_Assault_Rifle_M);
    */
}


void DrawPistol()
{
    /*
    gSPDisplayList(glistp++, Draw_CyborgFP_T);
    gSPDisplayList(glistp++, Draw_CyborgFP_Elbow_M);
    gSPDisplayList(glistp++, Draw_Pistol_T);
    gSPDisplayList(glistp++, Draw_humanpistol_M);
    */
}
