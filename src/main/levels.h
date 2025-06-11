#ifndef LevelH
#define LevelH

#include <nusys.h>
#include <nualsgi_n.h>
#include "common.h"

extern LevelHeaderStruct LevelHeader;
extern void LoadLevelData();



extern int LevelIndex;
extern void LoadHeader();
extern void LoadLevelData();
extern void InitNewLevel();

extern char _A30Seg4[], _A30Seg4END[];
extern char _A30Seg5[], _A30Seg5END[];
extern char _A30Seg6[], _A30Seg6END[];

extern char _RiverBedSeg4[], _RiverBedSeg4END[];
extern char _RiverBedSeg5[], _RiverBedSeg5END[];
extern char _RiverBedSeg6[], _RiverBedSeg6END[];

extern char _sandcastle4[], _sandcastle4END[];
extern char _sandcastle5[], _sandcastle5END[];
extern char _sandcastle6[], _sandcastle6END[];


extern uint Segment4Start[];
extern uint Segment5Start[];
extern uint Segment6Start[];

extern uint Segment4End[];
extern uint Segment5End[];
extern uint Segment6End[];

extern uint TableAddress[];
extern uint TableSurface[];
extern uint TableGrid[];
extern uint SurfaceCount[];

#endif

