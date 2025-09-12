#ifndef MathH
#define MathH

#include <nusys.h>
#include <nualsgi_n.h>
#include "main.h"

extern AffineMtx GlobalAffine;


extern float GetDistance(Vector A, Vector B);
extern short GetDirection(Vector A, Vector B);
extern void NormalizeVector(Vector vector);
extern void CreateMathTables();
extern void AffineToMtx(AffineMtx Affine, Mtx *Matrix);

extern void CreateModelMatrix(AffineMtx Matrix, Vector Position, SVector Angle);
extern void CreatePositionMatrix(AffineMtx Matrix, Vector Position);
extern void ScalingMatrix(AffineMtx matrix , float scale);
extern void ScaleMatrixXYZFixed(AffineMtx Matrix, SVector FScale);
extern void TransformMatrix(AffineMtx InputMatrix, Vector Position, Vector Look, Vector Up);
extern void AlignZVector(Vector Target, short Angle);
extern void AlignXVector(Vector Target, short Angle);
extern void AlignYVector(Vector Target, short Angle);

extern float sint(ushort angle);
extern float cost(ushort angle);
extern float tandy(float Input);
extern ushort atant(float a, float b);
extern ushort atan3(float a, float b);
extern int GetRNG(int Limit);

#endif

