#include <nusys.h>
#include <nualsgi_n.h>
#include "graphic.h"
#include "common.h"
#include "main.h"
#include "math.h"
#include "memory.h"
#include "compressionbuffer.h"
#include "levels.h"
#include "collision.h"
#include "player.h"
#include "pathfinding.h"


LevelHeaderStruct LevelHeader;

int LevelIndex;


uint Segment4Start[] = 
{
    (uint)&_A30Seg4,
    (uint)&_RiverBedSeg4,
    (uint)&_sandcastle4
};
uint Segment5Start[] = 
{
    (uint)&_A30Seg5,
    (uint)&_RiverBedSeg5,
    (uint)&_sandcastle5
};
uint Segment6Start[] = 
{
    (uint)&_A30Seg6,
    (uint)&_RiverBedSeg6,
    (uint)&_sandcastle6
};
uint Segment4Ends[] = 
{
    (uint)&_A30Seg4END,
    (uint)&_RiverBedSeg4END,
    (uint)&_sandcastle4END
};
uint Segment5Ends[] = 
{
    (uint)&_A30Seg5END,
    (uint)&_RiverBedSeg5END,
    (uint)&_sandcastle5END
};
uint Segment6Ends[] = 
{
    (uint)&_A30Seg6END,
    (uint)&_RiverBedSeg6END,
    (uint)&_sandcastle6END
};

uint TableAddress[] =   {0x0600E348, 0x06002618, 0x0600BD78};
uint TableSurface[] =   {0x0600E3B0, 0x060026B0, 0x0600BDB0};
uint TableGrid[] =      {0x0602B3C0, 0x06027B90, 0x0600DBB0};
uint SurfaceCount[] =   {0x05CD, 0x776, 0x60};



void LoadHeader()
{
    LevelHeader.Segment4ROM = Segment4Start[LevelIndex];
    LevelHeader.Segment5ROM = Segment5Start[LevelIndex];
    LevelHeader.Segment6ROM = Segment6Start[LevelIndex];

    LevelHeader.Segment4SizeCompressed = Segment4Ends[LevelIndex] - Segment4Start[LevelIndex];
    LevelHeader.Segment5SizeCompressed = Segment5Ends[LevelIndex] - Segment5Start[LevelIndex];
    LevelHeader.Segment6SizeCompressed = Segment6Ends[LevelIndex] - Segment6Start[LevelIndex];
}

void LoadLevelData()
{
    uint ReturnAddress;

    RawBufferPointer = (uint)&RawBuffer;
    if (osGetMemSize() == 0x00800000)
    {
        MemorySize = 8;
        FreeSpaceAddress = 0x80800000;
    }
    else
    {
        MemorySize = 4;
        FreeSpaceAddress = 0x80400000;
    }
    ReturnAddress = DecompressData(LevelHeader.Segment4ROM, LevelHeader.Segment4SizeCompressed);
    SetSegment(4, ReturnAddress);
    ReturnAddress = DecompressData(LevelHeader.Segment5ROM, LevelHeader.Segment5SizeCompressed);
    SetSegment(5, ReturnAddress);
    ReturnAddress = DecompressData(LevelHeader.Segment6ROM, LevelHeader.Segment6SizeCompressed);
    SetSegment(6, ReturnAddress);
    
    
}


void InitNewLevel()
{
    RenderEnable = 0;
    
    //StartMusic//
    nuAuSeqPlayerSetNo(0,0);
    nuAuSeqPlayerPlay(0);


    //LoadHUD();
    

    LoadHeader();
    LoadLevelData();
      

    //outdated code systems. deprecated. 
    //collision data is now precompiled
    /*
    BuildCollisionBuffer(TableSurface[LevelIndex]);
    SetSegment(8,(uint)&CollisionBuffer);

    //Build Pathfinding Data
    BuildNavMesh();
    */
    
    //load collision data from within Segment 6.
    CollisionBuffer = (CompactCollision*)(GetRealAddress(TableSurface[LevelIndex]));
    GridHolster = (CollisionGridHolster*)(GetRealAddress(TableGrid[LevelIndex]));
    GridArray = (ushort*)(GetRealAddress(TableGrid[LevelIndex]) + sizeof(CollisionGridHolster));
    CollisionCount = SurfaceCount[LevelIndex];
    InitNavArray();

    GameSequence = LEVELSEQUENCE;
    RenderEnable = 1;
}