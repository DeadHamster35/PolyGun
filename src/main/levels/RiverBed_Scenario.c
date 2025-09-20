#include <ultra64.h>
# include "common.h"



extern char _RiverBedSeg4[];
extern char _RiverBedSeg5[];
extern char _RiverBedSeg6[];

StaticPickup RiverBed_PickupList[] = 
{
	{ { -647, -821, -211}, {0, 0, 0}, 1,2,0,0, 0,0,0,0},
};





static char* LevelName = "RiverBed";
static char* SerialNumber = "J5CFD2BAKH-NM3A0C7L";

LevelScenario RiverBed_Scenario = 
{
	(StaticPickup*)&RiverBed_PickupList,
	(char*)&LevelName,
	(uint)&_RiverBedSeg4,
	(uint)&_RiverBedSeg5,
	(uint)&_RiverBedSeg6,
	37188,
	21868,
	108840,
	9752,
	9904,
	162704,
	1910,
    1
};
