/*
   main.c

   NuSYSTEM sample nu5

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.
*/
#include <os.h>
#include <stdio.h>
#include <nusys.h>
#include <nualsgi_n.h>
#include "actors.h"
#include "main.h"
#include "segment.h"
#include "levels.h"
#include "player.h"
#include "graphic.h"
#include "collision.h"
#include "pathfinding.h"
#include "memory.h"
#include "weapon.h"
#include "FPGraphics.h"
/* The stage number */
volatile int stage;

/* Declaration of the prototype */
void stage00(int);
void stage01(int);
void setAudioData(void);

/* Declaration of the external function */
void initStage00(void);
void makeDL00(void);
void updateGame00(void);

void initStage01(void);
void makeDL01(void);
void updateGame01(void);
void InitNewGame();

NUContData contdata[4]; /* Read Controller 1 data */
/* Values 0 or 1 used by pending check of the call-back function */
int pendflag = 1;
/* The number of frames displayed in a second */
int dspcount = 0;
/* The buffer for the console display */
char conbuf[40];

/*------------------------
    Main
--------------------------*/
void mainproc(void)
{
    /* The initialization of graphic */
    //nuScCreateScheduler(OS_VI_NTSC_LAN1, 2);
    nuGfxInit();

    /* The initialization of the controller manager */
    nuContInit();

    /* The initialization of audio */
    //SnuAuRetraceCount = 2;
    nuAuInit();
    /* Register audio data on ROM */
    setAudioData();

    
    InitDMA();

    nuAuSeqPlayerSetNo(0, 0);
    nuAuSeqPlayerPlay(0);

    /* Set the stage number to 0 */

    
    
    stage = 1;
    while (1)
    {
        
        switch (stage)
        {
            case 0:
            {
                stage = -1;                
                nuGfxFuncSet((NUGfxFunc)stage00);
                nuGfxDisplayOn();
                break;
            }
                
            case 1:
            {
                stage = -1;
                initStage01();
                nuGfxFuncSet((NUGfxFunc)stage01);
                nuGfxDisplayOn();
                break;
            }
                
            default:
            {
                break;
            }
        }

        /* Wait for that the call-back function switches values (switch the scene) */
        while (stage == -1)
        {

        }
            
        /* Clear the display */
        nuGfxDisplayOff();
    }
}

/* Set audio data */
void setAudioData(void)
{
    /* Register the bank to the sequence player */
    nuAuSeqPlayerBankSet(_midibankSegmentRomStart,
                         _midibankSegmentRomEnd - _midibankSegmentRomStart,
                         _miditableSegmentRomStart);
    /* Register MIDI sequence data to the sequence player */
    nuAuSeqPlayerSeqSet(_seqSegmentRomStart);
    /* Register the bank to the sound player */
    nuAuSndPlayerBankSet(_sfxbankSegmentRomStart,
                         _sfxbankSegmentRomEnd - _sfxbankSegmentRomStart,
                         _sfxtableSegmentRomStart);
}

/*-----------------------------------------------------------------------------
  The call-back function

  pendingGfx which is passed from Nusystem as the argument of the call-back
  function is the total number of RCP tasks that are currently processing
  and waiting for processing.
-----------------------------------------------------------------------------*/

/* The variable for counting how many scenes can be displayed in a second */
#define TARGETFPS 30
int calcFrame(void)
{
    static char frame[60];
    static int ptr = 0;
    static s64 prev = 0, now;
    int i, ctr;

    now = nuScRetraceCounter;
    if (prev >= now)
        now += 0x100000000LL;
    if (now - prev > TARGETFPS)
        prev = now;
    while (prev < now - 1)
    {
        frame[ptr++] = 0;
        ptr = ptr % TARGETFPS;
        prev++;
    }
    frame[ptr++] = 1;
    ptr = ptr % TARGETFPS;
    prev = now & 0xFFFFFFFF;
    ctr = 0;
    for (i = 0; i < TARGETFPS; i++)
        ctr += frame[i];
    return (ctr);
}

/* The stage 0 */
void stage00(int pendingGfx)
{
    /* Displaying process, depending on the number of processing/pending RCP tasks */
    if (pendingGfx < 3 + pendflag)
    {
        if (RenderEnable)
        {
            dspcount = calcFrame();
            GlobalFrame++;
            makeDL00();
        }
        
    }

    /* The game progressing process */
    updateGame00();
}

/* The stage 1 */
void stage01(int pendingGfx)
{
    /* Displaying process, depending on the number of processing/pending RCP tasks */
    if (pendingGfx < 4 + pendflag)
    {
        dspcount = calcFrame();
        makeDL01();
    }

    /* The game progressing process */
    updateGame01();
}

/*


    //outdated code systems. deprecated. 
    //collision data is now precompiled
    
    BuildCollisionBuffer(TableSurface[LevelIndex]);
    SetSegment(8,(uint)&CollisionBuffer);

    //Build Pathfinding Data
    BuildNavMesh();
    
    
*/

extern LevelScenario RiverBed_Scenario;
extern LevelScenario BlockTest_Scenario;
extern LevelScenario BeaverCreek_Scenario;
void InitNewGame()
{
    RenderEnable = 0;
    //PlayerCount = 1;
    BotCount = 0;
    CreateScreenCoords();
    LevelIndex = 1;
    LoadScenario((LevelScenario*)(uint)&RiverBed_Scenario);   

    InitWeaponClasses();
    InitActors();
    initAllPlayers();
    initScreenSystem();
    
    initProjectiles();
 
    LoadLevelData();
    CollisionBuffer = (CompactCollision *)(GetRealAddress(0x06000000 | LoadedScenario.SurfaceTableAddress));
    GridHolster = (CollisionGridHolster *)(GetRealAddress(0x06000000 | LoadedScenario.GridTableAddress));
    GridArray = (ushort *)(GetRealAddress(0x06000000 | LoadedScenario.GridTableAddress) + sizeof(CollisionGridHolster));

    
    
    CollisionCount = LoadedScenario.SurfaceCount;
    InitNavArray();

    GameSequence = LEVELSEQUENCE;
    RenderEnable = 1;
}