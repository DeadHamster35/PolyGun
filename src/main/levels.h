#ifndef LevelH
#define LevelH

#include <nusys.h>
#include <nualsgi_n.h>
#include "common.h"

extern LevelScenario LoadedScenario;
extern PlayerSpawn  SpawnPoints[];
extern DynamicPickup   DynamicPickArray[];
extern StaticPickup    StaticPickArray[];
extern ushort      TotalSpawnPoints, TotalStaticPicks;
extern void LoadLevelData();



extern int LevelIndex;
extern void LoadScenario(LevelScenario* Target);
extern void LoadLevelData();
extern void InitNewLevel();



#endif

