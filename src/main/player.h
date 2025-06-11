#ifndef PlayerH
#define PlayerH

#include <ultra64.h>
#include "common.h"

extern short PlayerCount, BotCount;

extern Player GamePlayers[16];
extern BotStruct GameBots[16];
extern PGCamera GameCameras[4];
extern void initPlayer(int PlayerIndex);
extern void initCamera(int PlayerIndex);
extern void initAllPlayers();
extern void UpdatePlayerControls();
extern void ResetPlayerStatus(int PlayerIndex);
extern void UpdateMenuControls();
extern void UpdatePlayerResponse();
extern AffineMtx CameraMatrix[4];
#endif


