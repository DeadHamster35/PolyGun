#include <ultra64.h>
# include "common.h"



extern char _BlockTestSeg4[];
extern char _BlockTestSeg5[];
extern char _BlockTestSeg6[];
StaticPickup BlockTest_PickupList[] = 
{
	{ { 176, -19, 3}, {0, 0, 0}, 0,0,0,0, 0,0,0,0},
    { { 176, -19, 3}, {0, 0, 0}, 0,0,0,0, 0,0,0,0},
};





char* LevelName = "BlockTest";
char* SerialNumber = "L164F354MK-QP4FEAEN";

LevelScenario BlockTest_Scenario = 
{
	(StaticPickup*)&BlockTest_PickupList,
	(char*)&LevelName,
	(uint)&_BlockTestSeg4,
	(uint)&_BlockTestSeg5,
	(uint)&_BlockTestSeg6,
	7728,
	268,
	16496,
	1864,
	1920,
	30960,
	363,
	1,
};
