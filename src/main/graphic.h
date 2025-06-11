/*
   graphic.h

   The definition of graphic and around 

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.			
*/

#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_
#include "common.h"
/* The screen size */
#define SCREEN_HT        240
#define SCREEN_WD        320

/* The maximum length of the display list of one task */
#define GFX_GLIST_LEN     2048
/* The length of the display list only for the buffer clear */
#define GFX_CLEAR_GLIST_LEN     512

/*-------------------------- define structure ------------------------------ */
/* The structure of the projection-matrix */

typedef struct {
    Mtx     Projection[4];
    Mtx     Viewing[4];
    Mtx     Translation[4];
    Mtx     Scale[4];
    Mtx     Rotation[4];
    LookAt  Reflection[4];
} MatrixMap;

typedef struct {
    MatrixMap   LevelMap;
    MatrixMap   ModelingMap;
    MatrixMap   FPMap;
} Dynamic;

/*-------------------------------- parameter---------------------------------*/
extern Dynamic gfx_dynamic[];
extern Gfx* glistp;
extern Gfx gfx_glist[][GFX_GLIST_LEN];
extern Gfx gfx_clear_glist[][GFX_CLEAR_GLIST_LEN];
extern u32 gfx_gtask_no;

extern Vp ViewportP1;
extern Vp ViewportP2;
extern Vp ViewportP3;
extern Vp ViewportP4;



extern Mtx EntityMap[4096];
extern short CurrentEntity[4];
extern int GlobalFrame;
extern short RenderEnable, GameSequence;
/*-------------------------------- function ---------------------------------*/
extern void gfxRCPInit(void);
extern void gfxClearCfb(void);
extern void SetMatrix(int Mode);
ushort GetRGBA16(int R, int G, int B, int A);
extern void DrawHUD(int PlayerIndex);
extern void DrawLevelScene(Dynamic *dynamicp, int PlayerIndex);
/*------------------------------- other extern define -----------------------*/
extern Gfx setup_rdpstate[];
extern Gfx setup_rspstate[];
extern void initRDP();
#endif /* _GRAPHIC_H_ */



