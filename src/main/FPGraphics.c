
#include <nusys.h>
#include <nualsgi_n.h>
#include "main.h"
#include "common.h"
#include "graphic.h"
#include "HUD.h"
#include "player.h"
#include "weapon.h"
#include "levels.h"

short WeaponCoords[4][2];
short ReticleCoords[4][2];
short ShieldCoords[4][2];
short RadarCoords[4][2];
float ReticleScale[4];



void CreateScreenCoords()
{
    
    switch(PlayerCount)
    {
        case 1:
        {
            ReticleScale[0] = 1.0f;

            ReticleCoords[0][0] = 160;
            ReticleCoords[0][1] = 120;

            ShieldCoords[0][0] = 218;
            ShieldCoords[0][1] = 13;

            RadarCoords[0][0] = 42;
            RadarCoords[0][1] = 198;
            
            WeaponCoords[0][0] = 23;
            WeaponCoords[0][1] = 13;
            break;
        }

        case 2:
        {
            ReticleScale[0] = 0.75f;
            ReticleScale[1] = 0.75f;

            ReticleCoords[0][0] = 160;
            ReticleCoords[0][1] = 60;
            ShieldCoords[0][0] = 238;
            ShieldCoords[0][1] = 13;
            RadarCoords[0][0] = 34;
            RadarCoords[0][1] = 91;
            WeaponCoords[0][0] = 23;
            WeaponCoords[0][1] = 13;


            ReticleCoords[1][0] = 160;
            ReticleCoords[1][1] = 180;
            ShieldCoords[1][0] = 238;
            ShieldCoords[1][1] = 130;
            RadarCoords[1][0] = 34;
            RadarCoords[1][1] = 211;
            WeaponCoords[1][0] = 23;
            WeaponCoords[1][1] = 130;
            break;
        }


        case 3:
        {
            ReticleScale[0] = 0.75f;
            ReticleScale[1] = 0.5f;
            ReticleScale[2] = 0.5f;

            ReticleCoords[0][0] = 160;
            ReticleCoords[0][1] = 60;
            ShieldCoords[0][0] = 238;
            ShieldCoords[0][1] = 10;
            RadarCoords[0][0] = 34;
            RadarCoords[0][1] = 91;
            WeaponCoords[0][0] = 23;
            WeaponCoords[0][1] = 10;

            ReticleCoords[1][0] = 80;
            ReticleCoords[1][1] = 180;
            ShieldCoords[1][0] = 115;
            ShieldCoords[1][1] = 128;
            RadarCoords[1][0] = 21;
            RadarCoords[1][1] = 219;
            WeaponCoords[1][0] = 23;
            WeaponCoords[1][1] = 128;

            ReticleCoords[2][0] = 240;
            ReticleCoords[2][1] = 180;
            ShieldCoords[2][0] = 275;
            ShieldCoords[2][1] = 128;
            RadarCoords[2][0] = 181;
            RadarCoords[2][1] = 219;
            WeaponCoords[2][0] = 183;
            WeaponCoords[2][1] = 128;
                    
            
            break;
        }

        case 4:
        {
            ReticleScale[0] = 0.5f;
            ReticleScale[1] = 0.5f;
            ReticleScale[2] = 0.5f;
            ReticleScale[3] = 0.5f;


            ReticleCoords[0][0] = 80;
            ReticleCoords[0][1] = 60;
            ShieldCoords[0][0] = 115;
            ShieldCoords[0][1] = 8;
            RadarCoords[0][0] = 21;
            RadarCoords[0][1] = 99;
            WeaponCoords[0][0] = 23;
            WeaponCoords[0][1] = 8;

            ReticleCoords[1][0] = 240;
            ReticleCoords[1][1] = 60;
            ShieldCoords[1][0] = 275;
            ShieldCoords[1][1] = 8;
            RadarCoords[1][0] = 181;
            RadarCoords[1][1] = 99;
            WeaponCoords[1][0] = 183;
            WeaponCoords[1][1] = 8;

            ReticleCoords[2][0] = 80;
            ReticleCoords[2][1] = 180;
            ShieldCoords[2][0] = 115;
            ShieldCoords[2][1] = 128;
            RadarCoords[2][0] = 21;
            RadarCoords[2][1] = 219;
            WeaponCoords[2][0] = 23;
            WeaponCoords[2][1] = 128;

            ReticleCoords[3][0] = 240;
            ReticleCoords[3][1] = 180;
            ShieldCoords[3][0] = 275;
            ShieldCoords[3][1] = 128;
            RadarCoords[3][0] = 181;
            RadarCoords[3][1] = 219;
            WeaponCoords[3][0] = 183;
            WeaponCoords[3][1] = 128;
                    
            
            break;
        }

    }
}


Gfx ReticleSetup[] = 
{
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0,
                        TEXEL0, 0, PRIMITIVE, 0,
                        TEXEL0, 0, PRIMITIVE, 0,
                        TEXEL0, 0, PRIMITIVE, 0),
    //gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    //gsDPSetTextureConvert(G_TC_FILT),
    //gsDPSetTextureLOD(G_TL_TILE),
    //gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetRenderMode(  G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),
};

Gfx PistolReticleGFX[] = 
{
    
    gsSPDisplayList(&ReticleSetup),


    
    
    gsDPLoadTextureBlock(Reticle_HP_T,
                            G_IM_FMT_RGBA,
                            G_IM_SIZ_16b,
                            16, 16,
                            0,
                            G_TX_CLAMP,
                            G_TX_CLAMP,
                            5, 5,
                            G_TX_NOLOD, G_TX_NOLOD),
                            
    


    


    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx AssaultRifleReticleGFX[] = 
{
    
    

    gsSPDisplayList(&ReticleSetup),
    
    
    gsDPLoadTextureBlock(Reticle_AR_T,
                            G_IM_FMT_RGBA,
                            G_IM_SIZ_16b,
                            32, 32,
                            0,
                            G_TX_CLAMP,
                            G_TX_CLAMP,
                            5, 5,
                            G_TX_NOLOD, G_TX_NOLOD),
                            
    


    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx PlasmaRifleReticleGFX[] = 
{
    
    

    gsSPDisplayList(&ReticleSetup),
    
    
    gsDPLoadTextureBlock(Reticle_PR_T,
                            G_IM_FMT_RGBA,
                            G_IM_SIZ_16b,
                            32, 32,
                            0,
                            G_TX_CLAMP,
                            G_TX_CLAMP,
                            5, 5,
                            G_TX_NOLOD, G_TX_NOLOD),
                            
    


    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

void DrawRadar(int PlayerIndex)
{
    Player *LocalPlayer = (Player *)&GamePlayers[PlayerIndex];
    if (LocalPlayer->IsCPU)
    {
        // Don't draw for CPU bots
        return;
    }

    
    gSPDisplayList(glistp++, &Draw_Radar_T);
    gDPSetRenderMode(glistp++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetCombineLERP(glistp++, 
                        TEXEL0, 0, PRIMITIVE, 0,
                        TEXEL0, 0, PRIMITIVE, 0,
                        TEXEL0, 0, PRIMITIVE, 0,
                        TEXEL0, 0, PRIMITIVE, 0);

    gSPTextureRectangle(glistp++,
         ( ((RadarCoords[PlayerIndex][0]) - (ReticleScale[PlayerIndex] * 32.0f) )  * 4), 
         ( ((RadarCoords[PlayerIndex][1]) - (ReticleScale[PlayerIndex] * 32.0f) ) * 4), 
         ( ((RadarCoords[PlayerIndex][0]) + (ReticleScale[PlayerIndex] * 32.0f) ) * 4), 
         ( ((RadarCoords[PlayerIndex][1]) + (ReticleScale[PlayerIndex] * 32.0f) ) * 4), 
         G_TX_RENDERTILE, 0, 0, 1024 / ReticleScale[PlayerIndex], 1024 / ReticleScale[PlayerIndex]);
}

char NumberStorage[4];
void DrawNumberPlate(int X, int Y, int Number, int ScaleMode)
{
    for (int This = 0; This < 3; This++)
    {
        NumberStorage[This] = Number % 10;
        Number = (int)(Number * 0.1f);
    }
    int Pass = 2;
    bool FirstValue = false;
    while (Pass >= 0)
    {
        if (ScaleMode == 1)
        {
            //small font
            int T = (224 * NumberStorage[Pass]);
            gSPTextureRectangle(glistp++,
                ( X * 4 ), 
                ( Y * 4 ), 
                ((X + 4) * 4), 
                ((Y + 7) * 4), 
                G_TX_RENDERTILE, 
                256, T, 
                1024, 1024
            );
            X += 4;
        }
        else
        {
            if (NumberStorage[Pass] != 0)
            {
                FirstValue = true;
            }
            if (FirstValue)
            {
                //large font
                int T = (384 * NumberStorage[Pass]);
                gSPTextureRectangle(glistp++,
                    ( X * 4 ), 
                    ( Y * 4 ), 
                    ((X + 8) * 4), 
                    ((Y + 12) * 4), 
                    G_TX_RENDERTILE, 
                    0, T, 
                    1024, 1024
                );
                
            }
            X += 8;
        }
        
        Pass--;
    }
    
}

void DrawAmmo(int PlayerIndex)
{
    //simple meter

    Player *LocalPlayer = (Player *)&GamePlayers[PlayerIndex];
    if (LocalPlayer->IsCPU)
    {
        // Don't draw for CPU bots
        return;
    }
    WeaponEquipment* LocalEquip = (WeaponEquipment*)&LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon];
    WeaponClass* LocalClass = (WeaponClass*)LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon].Class;
    
    
    

    gDPSetPrimColor(glistp++, 0, 0, 25, 208, 255, 192);
	//gDPSetCombineMode(glistp++,G_CC_PRIMITIVE, G_CC_PRIMITIVE);

    
    
    
    
    gDPSetRenderMode(glistp++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gSPDisplayList(glistp++, &Draw_AmmoBar_T);
    gDPSetCombineLERP(glistp++, 
                        TEXEL0, 0, PRIMITIVE, 0,
                        TEXEL0, 0, PRIMITIVE, 0,
                        TEXEL0, 0, PRIMITIVE, 0,
                        TEXEL0, 0, PRIMITIVE, 0);


    gDPSetPrimColor(glistp++, 0, 0, 32, 208, 255, 192);
  
    gSPTextureRectangle(glistp++,
         ( ((WeaponCoords[PlayerIndex][0]))  * 4), 
         ( ((WeaponCoords[PlayerIndex][1])) * 4), 
         ( (short)((WeaponCoords[PlayerIndex][0]) + (ReticleScale[PlayerIndex] * 83.0f)) * 4), 
         ( (short)((WeaponCoords[PlayerIndex][1]) + (ReticleScale[PlayerIndex] * 23.0f) ) * 4), 
         G_TX_RENDERTILE, 
         128, 32, 
         1024 / ReticleScale[PlayerIndex], 1024 / ReticleScale[PlayerIndex]);


    gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, 255);
    gSPDisplayList(glistp++, &Draw_NumberPlate_T);

    if (ReticleScale[PlayerIndex] > 0.5f)
    {
        DrawNumberPlate((WeaponCoords[PlayerIndex][0]) + (ReticleScale[PlayerIndex] * 10), 
        (WeaponCoords[PlayerIndex][1]) + (ReticleScale[PlayerIndex] * 3), 
        LocalEquip->Ammo, 0);
    }
    else
    {
        DrawNumberPlate(WeaponCoords[PlayerIndex][0] + 6, 
        WeaponCoords[PlayerIndex][1] + 2, 
        LocalEquip->Ammo, 1);
    }



    
    gDPSetFillColor(glistp++, (GPACK_RGBA5551(64, 128, 235, 1) << 16 | 
			       GPACK_RGBA5551(128, 128, 215, 1)));
    
    float AmmoRatio;
    
    
    if (LocalClass->WeaponFlags & WEAPON_HEAT)
    {
        AmmoRatio = (float)LocalEquip->Heat / 100.0f;
    }
    else
    {
        AmmoRatio = (float)LocalEquip->Magazine / (float)LocalClass->MagazineSize;
    }

    gDPFillRectangle(glistp++,
        (short)( (WeaponCoords[PlayerIndex][0] ) + 4 ), 
        (short)( ((WeaponCoords[PlayerIndex][1] + (ReticleScale[PlayerIndex] * 20.0f)))), 
        (short)( ((WeaponCoords[PlayerIndex][0]) + (AmmoRatio * (ReticleScale[PlayerIndex] * 80.0f)) )), 
        (short)( ((WeaponCoords[PlayerIndex][1]) + (ReticleScale[PlayerIndex] * 28.0f) ))
        );

    
            
    
}




void DrawShieldHealth(int PlayerIndex)
{
    Player *LocalPlayer = (Player *)&GamePlayers[PlayerIndex];

    if (LocalPlayer->IsCPU)
    {
        // Don't draw for CPU bots
        return;
    }
    PGCamera *LocalCamera = (PGCamera *)&GameCameras[PlayerIndex];

    

    
    gSPSetGeometryMode(glistp++,G_SHADE | G_SHADING_SMOOTH);
    gDPSetCombineLERP(glistp++, 
                        TEXEL0, 0, PRIMITIVE, 0,
                        TEXEL0, 0, PRIMITIVE, 0,
                        TEXEL0, 0, PRIMITIVE, 0,
                        TEXEL0, 0, PRIMITIVE, 0);
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


    int ColorCheck, ShieldInverse;
    if (LocalPlayer->HealthData.Shield != 0)
    {
        ColorCheck = LocalPlayer->HealthData.Shield;
        if (ColorCheck > 45)
        {
            gDPSetPrimColor(glistp++, 0, 0, 32, 208, 255, 192);
        }
        else if (ColorCheck > 25)
        {
            gDPSetPrimColor(glistp++, 0, 0, 255, 255, 0, 192);
        }
        else
        {
            gDPSetPrimColor(glistp++, 0, 0, 255, 0, 0, 192);
        }
        ShieldInverse = MAXSHIELD - LocalPlayer->HealthData.Shield;
        gSPTextureRectangle
        (
            glistp++,
            ( (short)(ShieldCoords[PlayerIndex][0] + (ReticleScale[PlayerIndex] * ShieldInverse)) <<2), 
            ( (ShieldCoords[PlayerIndex][1]) <<2), 
            ( (short)(ShieldCoords[PlayerIndex][0] + (ReticleScale[PlayerIndex] * 80))<<2), 
            ( (short)(ShieldCoords[PlayerIndex][1] + (ReticleScale[PlayerIndex] * 24)) <<2), 
            G_TX_RENDERTILE, 
            256 + (32 * ShieldInverse), 0, 
            1024 / ReticleScale[PlayerIndex], 1024 / ReticleScale[PlayerIndex]
        );
    }
    

    if (LocalPlayer->HealthData.Health != 0)
    {
        ColorCheck = GamePlayers[PlayerIndex].HealthData.Health;

        if (ColorCheck > 45)
        {
            gDPSetPrimColor(glistp++, 0, 0, 25, 192, 255, 192);
            
        }
        else if (ColorCheck > 25)
        {
            gDPSetPrimColor(glistp++, 0, 0, 255, 255, 0, 192);
        }
        else
        {
            gDPSetPrimColor(glistp++, 0, 0, 255, 0, 0, 192);
        }

            
        ShieldInverse = (int)((MAXHEALTH - LocalPlayer->HealthData.Health)/8);
        gSPTextureRectangle
        (
            glistp++,
            ( (short)(ShieldCoords[PlayerIndex][0] + (ReticleScale[PlayerIndex] * 6) + (6 * ReticleScale[PlayerIndex] * ShieldInverse)) <<2), 
            ( (short)(ShieldCoords[PlayerIndex][1] + (ReticleScale[PlayerIndex] * 19)) <<2), 
            ( (short)(ShieldCoords[PlayerIndex][0] + (ReticleScale[PlayerIndex] * 56))<<2), 
            ( (short)(ShieldCoords[PlayerIndex][1] + (ReticleScale[PlayerIndex] * 26)) <<2), 
            G_TX_RENDERTILE, 
            480 + (192 * ShieldInverse), 800, 
            1024 / ReticleScale[PlayerIndex], 1024 / ReticleScale[PlayerIndex]
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
    WeaponClass* LocalWeapon = (WeaponClass*)LocalPlayer->WeaponArray[LocalPlayer->SelectedWeapon].Class;

    
    gDPSetDepthSource(glistp++, G_ZS_PRIM);
    gDPSetPrimDepth(glistp++, 0, 0);
    gDPSetTexturePersp(glistp++, G_TP_NONE);
	gDPTileSync(glistp++  );

    DrawAmmo(PlayerIndex);
    
    gDPSetPrimColor(glistp++, 0, 0, 25, 192, 255, 192);
    
    if (LocalPlayer->ClosestPickup != -1)
    {
        StaticPickup *Target = (StaticPickup*)&StaticPickArray[LocalPlayer->ClosestPickup];        
        gSPDisplayList(glistp++, WeaponClassArray[Target->PickupClass]->HUD.PickupIcon);
    }
    
    


    //reticle
    if (GamePlayers[PlayerIndex].ZTarget > 0)
    {
        gDPSetPrimColor(glistp++, 0, 0, 255, 0, 0, 192);
    }
    else
    {
        gDPSetPrimColor(glistp++, 0, 0, 25, 192, 255, 192);
    }
    
    
    
    gSPDisplayList(glistp++, LocalWeapon->HUD.Reticle);
    
    gSPTextureRectangle(glistp++,
         ( ((ReticleCoords[PlayerIndex][0]) - (ReticleScale[PlayerIndex] * LocalWeapon->HUD.ReticleSize) )  * 4), 
         ( ((ReticleCoords[PlayerIndex][1]) - (ReticleScale[PlayerIndex] * LocalWeapon->HUD.ReticleSize) ) * 4), 
         ( ((ReticleCoords[PlayerIndex][0]) + (ReticleScale[PlayerIndex] * LocalWeapon->HUD.ReticleSize) ) * 4), 
         ( ((ReticleCoords[PlayerIndex][1]) + (ReticleScale[PlayerIndex] * LocalWeapon->HUD.ReticleSize) ) * 4), 
         G_TX_RENDERTILE, 0, 0, 1024 / ReticleScale[PlayerIndex], 1024 / ReticleScale[PlayerIndex]);
   	
    
    
    

    
    DrawShieldHealth(PlayerIndex);

    gDPSetPrimColor(glistp++, 0, 0, 25, 192, 255, 192);
    DrawRadar(PlayerIndex);
    


    
    gDPSetTexturePersp(glistp++, G_TP_PERSP);
    
	gDPSetDepthSource(glistp++, G_ZS_PIXEL);
    
    
    
}
