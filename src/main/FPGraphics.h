#include <nusys.h>
#include <nualsgi_n.h>
#include "common.h"
#include "graphic.h"

extern short ReticleCoords[4][2];
extern short ShieldCoords[4][2];
extern short RadarCoords[4][2];
extern float ReticleScale[4];
extern void CreateScreenCoords();
extern void DrawHUD(int PlayerIndex);
extern void DrawRadar(int PlayerIndex);
extern Gfx AssaultRifleReticleGFX[];
extern Gfx PistolReticleGFX[];
extern Gfx PlasmaRifleReticleGFX[];
extern Gfx Draw_CyborgTP_T[];