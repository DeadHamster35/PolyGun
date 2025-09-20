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
#include "weapon.h"


LevelScenario   LoadedScenario;
PlayerSpawn     SpawnPoints[MAXSPAWNS];
DynamicPickup   DynamicPickArray[MAXDYNAMICPICKS];
StaticPickup    StaticPickArray[MAXSTATICPICKS];

ushort      TotalSpawnPoints, TotalStaticPicks;
int LevelIndex;

/*
uint TableAddress[] =   {0x0600E348, 0x06002618, 0x0600BD78};
uint TableSurface[] =   {0x0600E3B0, 0x060026B0, 0x0600BDB0};
uint TableGrid[] =      {0x0602B3C0, 0x06027B90, 0x0600DBB0};
uint SurfaceCount[] =   {0x05CD, 0x776, 0x60};
*/

void LoadScenario(LevelScenario* Target)
{
    LoadedScenario.ObjectList = Target->ObjectList;
    LoadedScenario.Name = Target->Name;

    LoadedScenario.Segment4Address = Target->Segment4Address;    
    LoadedScenario.Segment5Address = Target->Segment5Address;
    LoadedScenario.Segment6Address = Target->Segment6Address;
    LoadedScenario.Segment4Size = Target->Segment4Size;
    LoadedScenario.Segment5Size = Target->Segment5Size;
    LoadedScenario.Segment6Size = Target->Segment6Size;

    LoadedScenario.DisplayTableAddress = Target->DisplayTableAddress;
    LoadedScenario.SurfaceTableAddress = Target->SurfaceTableAddress;
    LoadedScenario.GridTableAddress = Target->GridTableAddress;
    LoadedScenario.SurfaceCount = Target->SurfaceCount;

    TotalSpawnPoints = 0;
    TotalStaticPicks = 0;
    //Load the pickup/objective arrays from the static lists into the RAM allocations.
    
    for (int Index = 0; Index < Target->ObjectCount; Index++)
    {
        StaticPickup* TargetPick = (StaticPickup*)&Target->ObjectList[Index];

        switch(TargetPick->PickupType)
        {
            case PICKUPTYPE_OBJECTIVE:
            {
                switch (TargetPick->PickupClass)
                {
                    case OBJECTIVECLASS_SPAWN:
                    {
                        SpawnPoints[TotalSpawnPoints].Position[0] = TargetPick->Position[0];
                        SpawnPoints[TotalSpawnPoints].Position[1] = TargetPick->Position[1];
                        SpawnPoints[TotalSpawnPoints].Position[2] = TargetPick->Position[2];

                        SpawnPoints[TotalSpawnPoints].Angle = TargetPick->Angle[2];
                        SpawnPoints[TotalSpawnPoints].Gametype = TargetPick->Magazine;
                        SpawnPoints[TotalSpawnPoints].Team = TargetPick->Ammo;
                        TotalSpawnPoints++;
                        break;
                    }
                }
                break;
            }
            
            case PICKUPTYPE_WEAPON:
            {
                
                StaticPickup* TargetStatic = (StaticPickup*)&StaticPickArray[TotalStaticPicks];

                for (int ThisVec = 0; ThisVec < 3; ThisVec++)
                {
                    TargetStatic->Position[ThisVec] = TargetPick->Position[ThisVec];
                    TargetStatic->Angle[ThisVec] = TargetPick->Angle[ThisVec];
                }

                TargetStatic->PickupType = TargetPick->PickupType;
                TargetStatic->PickupClass = TargetPick->PickupClass;

                
                WeaponClass *LocalClass = (WeaponClass*)WeaponClassArray[TargetPick->PickupClass];
                

                //ammo
                if (TargetPick->Ammo == 0)
                {
                    TargetStatic->Ammo = LocalClass->MaxAmmo;
                }
                else
                {
                    TargetStatic->Ammo = TargetPick->Ammo;
                }

                //age
                if (TargetPick->Age == 0)
                {
                    TargetStatic->Age = LocalClass->MaxAge; 
                }
                else
                {
                    TargetStatic->Age = TargetPick->Age;
                }

                //magazine
                if (TargetPick->Magazine == 0)
                {
                    TargetStatic->Magazine = LocalClass->MagazineSize; 
                }
                else
                {
                    TargetStatic->Magazine = TargetPick->Magazine;
                }
                
                //heat
                TargetStatic->Heat = 0;
                TargetStatic->HeatFrames = 0;

                
                TotalStaticPicks++;
                break;
            }
        }
    }
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
    ReturnAddress = DecompressData(LoadedScenario.Segment4Address, LoadedScenario.Segment4Size);
    SetSegment(4, ReturnAddress);
    ReturnAddress = DecompressData(LoadedScenario.Segment5Address, LoadedScenario.Segment5Size);
    SetSegment(5, ReturnAddress);
    ReturnAddress = DecompressData(LoadedScenario.Segment6Address, LoadedScenario.Segment6Size);
    SetSegment(6, ReturnAddress);
    
    
    
}
