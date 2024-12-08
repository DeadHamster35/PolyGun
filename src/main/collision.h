#ifndef CollisionH
#define CollisionH

#include <stdbool.h>
#include <ultra64.h>
#include "common.h"

extern CompactCollision*        CollisionBuffer;
extern CollisionGridHolster*    GridHolster;
extern ushort*                  GridArray;    

extern void BuildCollisionBuffer(uint Address);
extern bool CheckRadius(Vector* Source, Vector* Target, float SourceSize, float TargetSize);
extern void SetSimpleBump(Vector SourcePosition, Vector SourceRadius, Vector TargetPosition, Vector TargetRadius);
extern uint CollisionCount;
extern bool PlayerLevelCollision(int Index);
extern void PlayerLevelCollisionB(int PlayerIndex);
extern int CheckViewCone(int PlayerIndex);
extern void CheckProjectileCollision(int Index);
extern Vector FinalHit;
extern Line BulletRay;
#endif

