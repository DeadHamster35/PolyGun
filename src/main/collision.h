#ifndef CollisionH
#define CollisionH

#include <stdbool.h>
#include <ultra64.h>
#include "common.h"

extern CompactCollision*        CollisionBuffer;
extern CollisionGridHolster*    GridHolster;
extern ushort*                  GridArray;    

extern void BuildCollisionBuffer(uint Address);
extern void VectorCrossProduct(const Vector a, const Vector b, Vector result);
extern void VectorNormalize(Vector v);
extern bool CheckRadius(Vector* Source, Vector* Target, float SourceSize, float TargetSize);
extern void SetSimpleBump(Vector SourcePosition, Vector SourceRadius, Vector TargetPosition, Vector TargetRadius);
extern uint CollisionCount;
extern bool CheckPlayerCollision(int Index);
int CheckViewCone(int PlayerIndex, float Eyesight);
extern void CheckProjectileCollision(int Index);
extern Vector FinalHit;
extern Line BulletRay;
#endif

