#ifndef PathfindH
#define PathfindH

#include <stdbool.h>
#include <ultra64.h>
#include "common.h"


extern short   NavPaths[16][ASTAR];
extern short   ReversePath[ASTAR];
extern NavNode NavArray[ASTAR];
extern short   NavSize;

extern void ResetNavPath(int Player);
extern void InitNavArray();
extern void BuildNavMesh();
extern void BStar(int PlayerIndex, short TargetTriangle);
extern int BSTARDistance(Vector TargetPosition, short TargetTriangle, float TargetDistance);

#endif

