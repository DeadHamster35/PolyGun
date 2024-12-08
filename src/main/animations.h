

#ifndef AnimationsH
#define AnimationsH


#include <nusys.h>
#include <nualsgi_n.h>
#include "common.h"
#include "graphic.h"
#include "main.h"
#include "memory.h"
#include "player.h"
#include "levels.h"
#include "collision.h"



typedef struct PolyAnime
{
    SVector*      PositionData;
    SVector*      AngleData;
    SVector*      ScalingData;
} PolyAnime;


typedef struct PolyNode{
    uint    TextureOffset;	
	uint	MeshCount;
	uint*   MeshOffsets;
} PolyNode;


typedef struct PolyBone{

    float           MeshScale;
	PolyAnime*      AnimationOffset;
    int             NodeCount;
    uint*           NodeOffset;
    int             ChildCount;
    uint*           ChildOffset;
} PolyBone;

typedef struct {
    PolyBone*   RootBone;
    short       FrameCount, CurrentFrame;
} AnimeHolster;


extern void DrawHolster(AnimeHolster* HolsterData, Vector BasePosition, SVector BaseAngle);

#endif