#include <nusys.h>
#include <nualsgi_n.h>
#include <stdbool.h>
#include <stdio.h>
#include <float.h>
#include "main.h"
#include "math.h"
#include "common.h"
#include "memory.h"
#include "player.h"
#include "weapon.h"

CompactCollision*       CollisionBuffer;
CollisionGridHolster*   GridHolster;
ushort*                 GridArray;
uint CollisionCount;


Vector Intersect, FinalHit;
Vector PlayerIntersect, TriangleIntersect;
float PlayerDistance, TriangleDistance;


typedef struct
{
    uint CodeA;
    uint CodeB;
} F3DCode;

typedef struct
{
    uint    F3DAddress;
    char    Material;
    char    SectionID;
    short   Flag;
} CollisionEntry;


Vector VertexCache[64];



extern void SaveNormal();
extern void SaveAxis();

bool CheckRadius(Vector* Source, Vector* Target, float SourceSize, float TargetSize)
{
	Vector Temp;
    
    float Radius = SourceSize + TargetSize;
	

    //exlcusion math
    //
        Temp[0] = Source[0] - Target[0];
        if ((Temp[0] > Radius) || (Temp[0] < -Radius))
        {
            return false;
        }
        Temp[1] = Source[1] - Target[1];
        if ((Temp[1] > Radius) || (Temp[1] < -Radius))
        {
            return false;
        }
        Temp[2] = Source[2] - Target[2];
        if ((Temp[2] > Radius) || (Temp[2] < -Radius))
        {
            return false;
        }
    //
    //

    Radius *= Radius;

	float Distance=( (Temp[0] * Temp[0]) + (Temp[1] * Temp[1]) + (Temp[2] * Temp[2]) );


	if(Distance<0.01f)
    {
        return(false);
    }
    

	if(Distance>Radius)
    {
        return(false);
    }

	return(true);
}

void SetSimpleBump(Vector SourcePosition, Vector SourceRadius, Vector TargetPosition, Vector TargetRadius)
{
	Vector TempPosition;
    bool NonZero = false;
	for (int CurrentVector = 0; CurrentVector < 3; CurrentVector++)
	{
		TempPosition[CurrentVector] = SourcePosition[CurrentVector] - TargetPosition[CurrentVector];
        if (TempPosition[CurrentVector] != 0)
        {
            NonZero = true;
        }
    }

    if (!NonZero)
    {
        //fix for two players ontop of each other. 
        TempPosition[0] += 0.1f;
        TempPosition[1] += 0.1f;
    }

    
	Vector DScale;
	for (int CurrentVector = 0; CurrentVector < 3; CurrentVector++)
	{
		DScale[CurrentVector] = (float)(TempPosition[CurrentVector] / SourceRadius[CurrentVector]);
	}	
	

    Vector NewPosition;
	NewPosition[0] = SourceRadius[0] * DScale[0] * 1.1f;
	NewPosition[1] = SourceRadius[1] * DScale[1] * 1.1f;
	NewPosition[2] = SourceRadius[2] * DScale[2] * 1.1f;

	for (int CurrentVector = 0; CurrentVector < 3; CurrentVector++)
	{
		TargetPosition[CurrentVector] = SourcePosition[CurrentVector] - NewPosition[CurrentVector];
	}
}

void LoadCache(F3DCode* OpCode)
{
    int Count = ((OpCode->CodeA >> 12) & 0xFF);
    int Index = ((OpCode->CodeA >> 1) & 0x7F);
    Index -= Count;

    for (int Start = 0; Start < Count; Start++)
    {
        Vtx* VTarget = (Vtx*)(GetRealAddress(OpCode->CodeB) + (Start * sizeof(Vtx)));
        VertexCache[Index + Start][0] = VTarget->v.ob[0];
        VertexCache[Index + Start][1] = VTarget->v.ob[1];
        VertexCache[Index + Start][2] = VTarget->v.ob[2];        
    }
}

void Save1Triangle(F3DCode* OpCode)
{
    if (CollisionCount >= MAXTRI)
    {
        return;
    }

    short Index[3];

    Index[2] = (OpCode->CodeA & 0xFF) / 2;
    Index[1] = ((OpCode->CodeA >> 8) & 0xFF) / 2;
    Index[0] = ((OpCode->CodeA >> 16) & 0xFF) / 2;

    for (int ThisVector = 0; ThisVector < 3; ThisVector++)
    {
        CollisionBuffer[CollisionCount].BoundingMax[ThisVector] = -32768;
        CollisionBuffer[CollisionCount].BoundingMin[ThisVector] =  32767;
    }

    for (int ThisVert = 0; ThisVert < 3; ThisVert++)
    {
        for (int ThisVector = 0; ThisVector < 3; ThisVector++)
        {
            CollisionBuffer[CollisionCount].Vertex[ThisVert][ThisVector] = VertexCache[Index[ThisVert]][ThisVector];
            


            if (VertexCache[Index[ThisVert]][ThisVector] < CollisionBuffer[CollisionCount].BoundingMin[ThisVector])
            {
                CollisionBuffer[CollisionCount].BoundingMin[ThisVector] = VertexCache[Index[ThisVert]][ThisVector];
            }

            if (VertexCache[Index[ThisVert]][ThisVector] > CollisionBuffer[CollisionCount].BoundingMax[ThisVector])
            {
                CollisionBuffer[CollisionCount].BoundingMax[ThisVector] = VertexCache[Index[ThisVert]][ThisVector];
            }
        }       

        
        
    }

    SaveNormal();
    SaveAxis();

    
    
    CollisionCount++;

}

void Save2Triangle(F3DCode* OpCode)
{

    
    short Index[3];

    if (CollisionCount >= MAXTRI)
    {
        return;
    }

    Index[2] = (OpCode->CodeA & 0xFF) / 2;
    Index[1] = ((OpCode->CodeA >> 8) & 0xFF)  / 2; 
    Index[0] = ((OpCode->CodeA >> 16) & 0xFF)  / 2;
    

    for (int ThisVector = 0; ThisVector < 3; ThisVector++)
    {
        CollisionBuffer[CollisionCount].BoundingMax[ThisVector] = -32768;
        CollisionBuffer[CollisionCount].BoundingMin[ThisVector] =  32767;
    }

    for (int ThisVert = 0; ThisVert < 3; ThisVert++)
    {
        for (int ThisVector = 0; ThisVector < 3; ThisVector++)
        {
            CollisionBuffer[CollisionCount].Vertex[ThisVert][ThisVector] = VertexCache[Index[ThisVert]][ThisVector];
            

            

            if (VertexCache[Index[ThisVert]][ThisVector] < CollisionBuffer[CollisionCount].BoundingMin[ThisVector])
            {
                CollisionBuffer[CollisionCount].BoundingMin[ThisVector] = VertexCache[Index[ThisVert]][ThisVector];
            }

            if (VertexCache[Index[ThisVert]][ThisVector] > CollisionBuffer[CollisionCount].BoundingMax[ThisVector])
            {
                CollisionBuffer[CollisionCount].BoundingMax[ThisVector] = VertexCache[Index[ThisVert]][ThisVector];
            }
        }       
        
    }
    
    SaveNormal();
    SaveAxis();

    CollisionCount++;

    if (CollisionCount >= MAXTRI)
    {
        return;
    }

    Index[2] = (OpCode->CodeB & 0xFF) / 2;
    Index[1] = ((OpCode->CodeB >> 8) & 0xFF) / 2;
    Index[0] = ((OpCode->CodeB >> 16) & 0xFF) / 2;

    

    for (int ThisVector = 0; ThisVector < 3; ThisVector++)
    {
        CollisionBuffer[CollisionCount].BoundingMax[ThisVector] = -32768;
        CollisionBuffer[CollisionCount].BoundingMin[ThisVector] =  32767;
    }

    for (int ThisVert = 0; ThisVert < 3; ThisVert++)
    {
        for (int ThisVector = 0; ThisVector < 3; ThisVector++)
        {
            CollisionBuffer[CollisionCount].Vertex[ThisVert][ThisVector] = VertexCache[Index[ThisVert]][ThisVector];
            

            if (VertexCache[Index[ThisVert]][ThisVector] < CollisionBuffer[CollisionCount].BoundingMin[ThisVector])
            {
                CollisionBuffer[CollisionCount].BoundingMin[ThisVector] = VertexCache[Index[ThisVert]][ThisVector];
            }

            if (VertexCache[Index[ThisVert]][ThisVector] > CollisionBuffer[CollisionCount].BoundingMax[ThisVector])
            {
                CollisionBuffer[CollisionCount].BoundingMax[ThisVector] = VertexCache[Index[ThisVert]][ThisVector];
            }
        }       
        
    }

    SaveNormal();
    SaveAxis();
    
    CollisionCount++;

}

void BuildCollisionBuffer(uint Address)
{   
    CollisionCount = 0;
    uint LocalCode;
    uint RealAddress = GetRealAddress(Address);
    while(1)
    {
        CollisionEntry* CEntry = (CollisionEntry*)RealAddress;

        if (CEntry->F3DAddress == 0)
        {
            return;
        }

        uint LocalAddress = (GetRealAddress(CEntry->F3DAddress));

        while(1)
        {
            F3DCode* OpCode = (F3DCode*)LocalAddress;
            LocalCode = OpCode->CodeA & 0xFF000000;
            
            if (LocalCode == ((G_VTX)<<24))
            {
                LoadCache(OpCode);
            }

            if (LocalCode == ((G_TRI1)<<24))
            {
                Save1Triangle(OpCode);
            }

            if (LocalCode == ((G_TRI2)<<24))
            {
                Save2Triangle(OpCode);
            }

            if (LocalCode == ((G_DL)<<24))
            {
                //Save2Triangle(OpCode);
            }

            if (LocalCode == ((G_ENDDL)<<24))
            {
                break;
            }

            
            LocalAddress += 8;

        }

        RealAddress += 8;


    };
}
Vector A, B, C;
float LengthA, LengthB;

void SaveNormal() 
{
    


    CompactCollision* LocalTriangle = (CompactCollision*)&CollisionBuffer[CollisionCount];
    
    
    A[0] = LocalTriangle->Vertex[1][0] - LocalTriangle->Vertex[0][0];
    A[1] = LocalTriangle->Vertex[1][1] - LocalTriangle->Vertex[0][1];
    A[2] = LocalTriangle->Vertex[1][2] - LocalTriangle->Vertex[0][2];

    B[0] = LocalTriangle->Vertex[2][0] - LocalTriangle->Vertex[0][0];
    B[1] = LocalTriangle->Vertex[2][1] - LocalTriangle->Vertex[0][1];
    B[2] = LocalTriangle->Vertex[2][2] - LocalTriangle->Vertex[0][2];

    // Calculate the cross product of A and B to get the normal
    C[0] = A[1] * B[2] - A[2] * B[1];
    C[1] = A[2] * B[0] - A[0] * B[2];
    C[2] = A[0] * B[1] - A[1] * B[0];


    LengthA = (float)(C[0] * C[0] + C[1] * C[1] + C[2] * C[2]);
    LengthB = (float)sqrtf(LengthA);
    if (LengthB != 0)
    {
        LocalTriangle->Normal[0] = (float)C[0]/LengthB * 1.0f;
        LocalTriangle->Normal[1] = (float)C[1]/LengthB * 1.0f;
        LocalTriangle->Normal[2] = (float)C[2]/LengthB * 1.0f;
    }

    LocalTriangle->VectorDistance = -1.0f * 
    (
        LocalTriangle->Normal[0] * LocalTriangle->Vertex[0][0] + 
        LocalTriangle->Normal[1] * LocalTriangle->Vertex[0][1] + 
        LocalTriangle->Normal[2] * LocalTriangle->Vertex[0][2]
    ); 

    LocalTriangle->Center[0] = 
    (
        LocalTriangle->Vertex[0][0] +
        LocalTriangle->Vertex[1][0] +
        LocalTriangle->Vertex[2][0] 
    ) / 3.0f;

    LocalTriangle->Center[1] = 
    (
        LocalTriangle->Vertex[0][1] +
        LocalTriangle->Vertex[1][1] +
        LocalTriangle->Vertex[2][1] 
    ) / 3.0f;

    LocalTriangle->Center[2] = 
    (
        LocalTriangle->Vertex[0][2] +
        LocalTriangle->Vertex[1][2] +
        LocalTriangle->Vertex[2][2] 
    ) / 3.0f;

    
    
}

void SaveAxis()
{
    CompactCollision* LocalCollide = (CompactCollision*)&CollisionBuffer[CollisionCount];

    A[0] = LocalCollide->Normal[0] * LocalCollide->Normal[0];
    A[1] = LocalCollide->Normal[1] * LocalCollide->Normal[1];
    A[2] = LocalCollide->Normal[2] * LocalCollide->Normal[2];

    if (A[0] > A[1])
    {
        if (A[0] > A[2])
        {
            LocalCollide->NormalDirection = XAXISVECTOR;
            return;
        }
    }
    
    if (A[1] > A[0])
    {
        if (A[1] > A[2])
        {
            LocalCollide->NormalDirection = YAXISVECTOR;
            return;
        }
    }

    if (A[2] > A[0])
    {
        if (A[2] > A[1])
        {
            if (LocalCollide->Normal[2] > 0)
            {
                LocalCollide->NormalDirection = FLOORVECTOR;
                return;
            }
            LocalCollide->NormalDirection = CEILINGVECTOR;
            return;
            
            return;
        }
    }
    //lol wtf

    LocalCollide->NormalDirection = WTFAXISVECTOR;
}


int CheckXZ(Vector Center, ushort ThisTri)
{
    CompactCollision* Target = (CompactCollision*)(&CollisionBuffer[ThisTri]);

    short HitResult;
    //gaiseki1=(p2z-p1z)*(p3x-p1x)-(p2x-p1x)*(p3z-p1z);
    Vector Product;


    Product[0] = 
    (
        (Target->Vertex[0][2] - Center[2]) *
        (Target->Vertex[1][0] - Center[0]) -
        (Target->Vertex[0][0] - Center[0]) *
        (Target->Vertex[1][2] - Center[2]) 
    );
    Product[1] = 
    (
        (Target->Vertex[1][2] - Center[2]) *
        (Target->Vertex[2][0] - Center[0]) -
        (Target->Vertex[1][0] - Center[0]) *
        (Target->Vertex[2][2] - Center[2]) 
    );
    Product[2] = 
    (
        (Target->Vertex[2][2] - Center[2]) *
        (Target->Vertex[0][0] - Center[0]) -
        (Target->Vertex[2][0] - Center[0]) *
        (Target->Vertex[0][2] - Center[2]) 
    );

    //Initial Check

    if (Product[0] == 0)
    {
        if ((Product[1]*Product[2]) < 0)
        {
            HitResult = 0;
            return 0;
        }
    }
    else
    {
        if (Product[1] == 0)
        {
            if ((Product[0]*Product[2]) < 0)
            {
                HitResult = 0;
                return 0;
            }
        }
        else
        {
            if (Product[0] * Product[1] < 0)
            {
                HitResult = 0;
                return 0;
            }
            else
            {
                if (Product[2] != 0)
                {
                    if (Product[1] * Product[2] < 0)
                    {
                        HitResult = 0;
                        return 0;
                    }
                }
            }
        }
    }

    return 1;
}

int CheckXY(Vector Center, ushort ThisTri)
{
    CompactCollision* Target = (CompactCollision*)(&CollisionBuffer[ThisTri]);

    short HitResult;
    Vector Product;
    

    Product[0] = 
    (
        (Target->Vertex[0][1] - Center[1]) *
        (Target->Vertex[1][0] - Center[0]) -
        (Target->Vertex[0][0] - Center[0]) *
        (Target->Vertex[1][1] - Center[1]) 
    );
    Product[1] = 
    (
        (Target->Vertex[1][1] - Center[1]) *
        (Target->Vertex[2][0] - Center[0]) -
        (Target->Vertex[1][0] - Center[0]) *
        (Target->Vertex[2][1] - Center[1]) 
    );
    Product[2] = 
    (
        (Target->Vertex[2][1] - Center[1]) *
        (Target->Vertex[0][0] - Center[0]) -
        (Target->Vertex[2][0] - Center[0]) *
        (Target->Vertex[0][1] - Center[1]) 
    );

    //Initial Check

    if (Product[0] == 0)
    {
        //Negative Result
        //Secondary Check Alpha
        if ((Product[1]*Product[2]) < 0)
        {
            HitResult = 0;
            return 0;
        }
    }
    else
    {
        if (Product[1] == 0)
        {
            if ((Product[0]*Product[2]) < 0)
            {
                HitResult = 0;
                return 0;
            }
        }
        else
        {
            if (Product[0] * Product[1] < 0)
            {
                HitResult = 0;
                return 0;
            }
            else
            {
                if (Product[2] != 0)
                {
                    if (Product[1] * Product[2] < 0)
                    {
                        HitResult = 0;
                        return 0;
                    }
                }
            }
        }
    }

    return 1;
}

int CheckYZ(Vector Center, ushort ThisTri)
{
    CompactCollision* Target = (CompactCollision*)(&CollisionBuffer[ThisTri]);

    short HitResult;
    
    Vector Product;


    Product[0] = 
    (
        (Target->Vertex[0][1] - Center[1]) *
        (Target->Vertex[1][2] - Center[2]) -
        (Target->Vertex[0][2] - Center[2]) *
        (Target->Vertex[1][1] - Center[1]) 
    );
    Product[1] = 
    (
        (Target->Vertex[1][1] - Center[1]) *
        (Target->Vertex[2][2] - Center[2]) -
        (Target->Vertex[1][2] - Center[2]) *
        (Target->Vertex[2][1] - Center[1]) 
    );
    Product[2] = 
    (
        (Target->Vertex[2][1] - Center[1]) *
        (Target->Vertex[0][2] - Center[2]) -
        (Target->Vertex[2][2] - Center[2]) *
        (Target->Vertex[0][1] - Center[1]) 
    );

    //Initial Check

    if (Product[0] == 0)
    {
        if ((Product[1]*Product[2]) < 0)
        {
            HitResult = 0;
            return 0;
        }
    }
    else
    {
        if (Product[1] == 0)
        {
            if ((Product[0]*Product[2]) < 0)
            {
                HitResult = 0;
                return 0;
            }
        }
        else
        {
            if (Product[0] * Product[1] < 0)
            {
                HitResult = 0;
                return 0;
            }
            else
            {
                if (Product[2] != 0)
                {
                    if (Product[1] * Product[2] < 0)
                    {
                        HitResult = 0;
                        return 0;
                    }
                }
            }
        }
    }

    return 1;
}


int GetGridIndex(Vector Position)
{
    if (Position[0] > GridHolster->GridMax[0])
    {
        return -1;
    }

    if (Position[1] > GridHolster->GridMax[1])
    {
        return -1;
    }

    if (Position[0] < GridHolster->GridMin[0])
    {
        return -1;
    }

    if (Position[1] < GridHolster->GridMin[1])
    {
        return -1;
    }


    int XGrid = ((Position[0] - GridHolster->GridMin[0]) / GridHolster->ChunkWidth);
    int YGrid = ((Position[1] - GridHolster->GridMin[1]) / GridHolster->ChunkLength);
    return ((XGrid * 32) + YGrid);
}

void VectorScale(Vector v, float scalar, Vector result) {
    for (int i = 0; i < 3; ++i) {
        result[i] = v[i] * scalar;
    }
}

void VectorSubtract(const Vector a, const Vector b, Vector result) {
    result[0] = a[0] - b[0];
    result[1] = a[1] - b[1];
    result[2] = a[2] - b[2];
}

void VectorSubtractS(const SVector a, const SVector b, Vector result) {
    result[0] = a[0] - b[0];
    result[1] = a[1] - b[1];
    result[2] = a[2] - b[2];
}

void VectorSubtractFS(const Vector a, const SVector b, Vector result) {
    result[0] = a[0] - b[0];
    result[1] = a[1] - b[1];
    result[2] = a[2] - b[2];
}

void VectorAdd(const Vector a, const Vector b, Vector result) {
    result[0] = a[0] + b[0];
    result[1] = a[1] + b[1];
    result[2] = a[2] + b[2];
}

void VectorCrossProduct(const Vector a, const Vector b, Vector result) {
    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];
}

float VectorDotProduct(const Vector a, const Vector b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

// Helper function to calculate the dot product of two vectors
float InnerProduct(Vector a, Vector b) {
    float result = 0.0;
    for (int i = 0; i < 3; i++)
        result += a[i] * b[i];
    return result;
}


void VectorNormalize(Vector v) {
    float length = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    if (length != 0)
    {
        v[0] /= length;
        v[1] /= length;
        v[2] /= length;
    }
    
}


void CopyVertexArray(VertexArray* SVect, VertexArrayF* FVect)
{
    for (int This = 0; This < 3; This++)
    {
        for (int That = 0; That < 3; That++)
        {
            *FVect[This][That] = (float)*SVect[This][That];
        }
    }
}


float intersectLineTriangle(Vector Start, Vector End, VertexArray Face, Vector Intersect) {
    const float EPSILON = 0.000001;
    
    Vector E1, E2, H, S, Q;
    float a, f, u, v;

    // Calculate vectors
    VectorSubtractS(Face[1], Face[0], E1);
    VectorSubtractS(Face[2], Face[0], E2);
    VectorSubtract(End, Start, S);
    VectorCrossProduct(S, E2, H);
    a = VectorDotProduct(E1, H);

    if (a > -EPSILON && a < EPSILON)
        return 0.0f;

    f = 1.0 / a;
    VectorSubtractFS(Start, Face[0], Q);
    u = f * VectorDotProduct(Q, H);

    if (u < 0.0 || u > 1.0)
        return 0.0f;

    VectorCrossProduct(Q, E1, H);
    v = f * VectorDotProduct(S, H);

    if (v < 0.0 || u + v > 1.0)
        return 0.0f;

    // Calculate the intersection point
    float t = f * VectorDotProduct(E2, H);

    if ((t > EPSILON) && (t <= 1.0f)) {
        Intersect[0] = Start[0] + t * S[0];
        Intersect[1] = Start[1] + t * S[1];
        Intersect[2] = Start[2] + t * S[2];
        return t;
    } else {
        return 0.0f;
    }
    
}


float intersectRayCylinder(Vector start, Vector end, const Cylinder* cylinder, Vector Intersect) 
{
    // Calculate the direction vector of the ray
    Vector dir;
    for (int i = 0; i < 3; ++i) {
        dir[i] = end[i] - start[i];
    }

    // Vector from the start point of the ray to the base of the cylinder
    Vector startToBase;
    for (int i = 0; i < 3; ++i) {
        startToBase[i] = start[i] - cylinder->Base[i];
    }

    // Calculate the components of the direction vector
    float a = dir[0] * dir[0] + dir[1] * dir[1];
    float b = 2 * (dir[0] * startToBase[0] + dir[1] * startToBase[1]);
    float c = startToBase[0] * startToBase[0] + startToBase[1] * startToBase[1] - cylinder->Radius * cylinder->Radius;

    // Calculate the discriminant
    float discriminant = b * b - 4 * a * c;

    // If the discriminant is negative, there is no intersection
    if (discriminant < 0) {
        return -1.0f; // No intersection
    }

    // Calculate the two possible solutions for t
    float t1 = (-b + sqrtf(discriminant)) / (2 * a);
    float t2 = (-b - sqrtf(discriminant)) / (2 * a);

    // Check if the intersection point is within the bounds of the cylinder height
    float z1 = start[2] + t1 * dir[2];
    float z2 = start[2] + t2 * dir[2];

    if (z2 >= cylinder->Base[2] && z2 <= (cylinder->Base[2] + cylinder->Height)){
        // Intersection at t1 is within the cylinder
        Intersect[0] = start[0] + t2 * dir[0];
        Intersect[1] = start[1] + t2 * dir[1];
        Intersect[2] = z2;
        return t2;
    } else if (z1 >= cylinder->Base[2] && z1 <= (cylinder->Base[2] + cylinder->Height)){
        // Intersection at t2 is within the cylinder
        Intersect[0] = start[0] + t1 * dir[0];
        Intersect[1] = start[1] + t1 * dir[1];
        Intersect[2] = z1;
        return t1;
    }

    return -1.0f; // No intersection within the cylinder height
}


short RaycastLevelCollision(Vector Start, Vector End, int GIndex)
{
    
    //Triangle test will return only for triangles inbetween player and target.
    int GArrayPointer, GCount;
    
    float ClosestHit = 1.0f;

    if (GIndex < 0)
    {
        GCount = 0;
    }
    else
    {
        GArrayPointer = GridHolster->GridData[GIndex].ElementIndex;
        GCount = GridHolster->GridData[GIndex].ElementCount;
    }
    

    short LocalHit = -1;
    float Distance;
    for (int ThisElement = 0; ThisElement < GCount; ThisElement++)
    {
        ushort ThisTri = GridArray[GArrayPointer + ThisElement];
        
        Distance = intersectLineTriangle(Start, End, CollisionBuffer[ThisTri].Vertex, Intersect);
        
        if ((Distance > 0) && (Distance < ClosestHit))
        {
            ClosestHit = Distance;
            TriangleDistance = Distance;
            LocalHit = ThisTri;
            FinalHit[0] = Intersect[0];
            FinalHit[1] = Intersect[1];
            FinalHit[2] = Intersect[2];
        }
    }

    return LocalHit;
}


short RaycastPlayerCollision(Vector Start, Vector End, int PlayerIgnore)
{

    //Set PlayerIgnore to -1 to check all players
    Cylinder CheckCylinder;
    short HitPlayer = -1;
    float ClosestHit = 1.0f;
    float Distance;
    for (int ThisPlayer = 0; ThisPlayer < PlayerCount + BotCount; ThisPlayer++)
    {
        if (PlayerIgnore == ThisPlayer)
        {
            //force ignore value
            //set to -1 for bypass
            continue;
        }
        Player *LocalPlayer = (Player*)&GamePlayers[ThisPlayer];
        if (LocalPlayer->StatusBits & STATUSDEAD)
        {
            //Ignore dead players for now.
            continue;            
        }
        
        

        CheckCylinder.Base[0] = LocalPlayer->Location.Position[0];
        CheckCylinder.Base[1] = LocalPlayer->Location.Position[1];
        CheckCylinder.Base[2] = LocalPlayer->Location.Position[2];
        CheckCylinder.Radius = LocalPlayer->Location.Radius;
        CheckCylinder.Height = LocalPlayer->Height;

        Distance = (intersectRayCylinder(Start, End,(Cylinder*)&CheckCylinder, Intersect));
        
        if ((Distance > 0) && (Distance < ClosestHit))
        {
            ClosestHit = Distance;
            PlayerDistance = Distance;
            HitPlayer = ThisPlayer;
            FinalHit[0] = Intersect[0];
            FinalHit[1] = Intersect[1];
            FinalHit[2] = Intersect[2];
        }
    }
    return HitPlayer;
}


short RaycastDDA(Vector start, Vector end) {
    
    int  og  = GetGridIndex(start);
    int  tg  = GetGridIndex(end);
    short hit;

    // Early hit in start‐cell
    if (og >= 0 && (hit = RaycastLevelCollision(start, end, og)) >= 0)
        return hit;

    if (og == tg || (end[0] == start[0] && end[1] == start[1]))
        return -1;

    // Direction & initial cell coords
    float dx    = end[0] - start[0];
    float dy    = end[1] - start[1];
    int   x     = (start[0] - GridHolster->GridMin[0]) / GridHolster->ChunkWidth;
    int   y     = (start[1] - GridHolster->GridMin[1]) / GridHolster->ChunkLength;
    int   sx    = (dx  > 0) - (dx  < 0);
    int   sy    = (dy  > 0) - (dy  < 0);

    // Precompute step increments
    float tDeltaX = dx ? GridHolster->ChunkWidth  / MathABS(dx) : FLT_MAX;
    float tDeltaY = dy ? GridHolster->ChunkLength / MathABS(dy) : FLT_MAX;
    float tMaxX   = dx
                  ? (((sx > 0 ? x + 1 : x) * GridHolster->ChunkWidth  + GridHolster->GridMin[0] - start[0]) / dx)
                  : FLT_MAX;
    float tMaxY   = dy
                  ? (((sy > 0 ? y + 1 : y) * GridHolster->ChunkLength + GridHolster->GridMin[1] - start[1]) / dy)
                  : FLT_MAX;

    // Traverse until out of bounds or we reach target cell
    while (x >= 0 && x < 32 && y >= 0 && y < 32) {
        if (tMaxX < tMaxY) {
            x += sx;
            tMaxX += tDeltaX;
        } else {
            y += sy;
            tMaxY += tDeltaY;
        }

        int idx = (x * 32) + y;
        if (idx == tg) break;
        if ((hit = RaycastLevelCollision(start, end, idx)) >= 0)
            return hit;
    }

    return -1;
}


int CheckViewCone(int PlayerIndex, float Eyesight)
{
    Vector Target;
    Vector Origin;
    Player* LocalPlayer = (Player*)&GamePlayers[PlayerIndex];
    PGCamera* LocalCamera = (PGCamera*)&GameCameras[PlayerIndex];
    short HitPlayer = -1;
    Target[0] = 0;
    Target[1] = Eyesight;
    Target[2] = 0;

    float ClosestHit = 1.0f;
    float Distance;

    
    AlignXVector(Target, LocalCamera->Location.Angle[0]);
    AlignYVector(Target, LocalCamera->Location.Angle[1]);
    AlignZVector(Target, LocalCamera->Location.Angle[2]);

    for (int ThisVec = 0; ThisVec < 3; ThisVec++)
    {
        Origin[ThisVec] = LocalCamera->Location.Position[ThisVec];
        Target[ThisVec] += Origin[ThisVec];
    }
    

    
    HitPlayer = RaycastPlayerCollision(Origin, Target, PlayerIndex);

    if (HitPlayer == -1)
    {
        return HitPlayer;
    }

    short HitTriangle = RaycastDDA(Origin, Target);

    if (HitTriangle >= 0)
    {
        if (TriangleDistance < PlayerDistance)
        {
            return -1;
        }
    }

    
    return HitPlayer;
}


void CheckProjectileCollision(int BulletIndex) 
{
    
    Projectile *LocalBullet = (Projectile*)&ProjectileArray[BulletIndex];
    
    float ClosestHit = 1.00f; //Distance tests use 0->1.0f for return. 

    

    float BulletRadi = (0.5f * LocalBullet->InitialSpeed);
    for (int ThisVector = 0; ThisVector < 2; ThisVector++)
    {
        if (LocalBullet->Location.Position[ThisVector] - BulletRadi > GridHolster->GridMax[ThisVector] + 100.0f )
        {
            LocalBullet->Status = BULLET_INACTIVE;
            return;
        }
        if (LocalBullet->Location.Position[ThisVector] + BulletRadi < GridHolster->GridMin[ThisVector] - 100.0f)
        {
            LocalBullet->Status = BULLET_INACTIVE;
            return;
        }
    }

    if (LocalBullet->Location.Position[2] - BulletRadi > 32000)
    {
        LocalBullet->Status = BULLET_INACTIVE;
        return;
    }
    if (LocalBullet->Location.Position[2] + BulletRadi < -32000)
    {
        LocalBullet->Status = BULLET_INACTIVE;
        return;
    }

    //Player Test
    
    short HitPlayer = RaycastPlayerCollision(LocalBullet->Location.LastPosition, LocalBullet->Location.Position, LocalBullet->Owner);
    

    //Triangle Test
    
    
    //ahhh shit
    short HitTriangle = RaycastDDA(LocalBullet->Location.LastPosition, LocalBullet->Location.Position);


    if (HitTriangle >= 0)
    {
        if (HitPlayer >= 0)
        {
            if (PlayerDistance < TriangleDistance)
            {   
                LocalBullet->Status = BULLET_HIT;
                LocalBullet->Lifespan = 0;
                DamagePlayer(HitPlayer, LocalBullet->Damage);
                return;
            }
        }
        
        LocalBullet->Status = BULLET_HIT;
        LocalBullet->Lifespan = 0;
        LocalBullet->Location.Position[0] = FinalHit[0];
        LocalBullet->Location.Position[1] = FinalHit[1];
        LocalBullet->Location.Position[2] = FinalHit[2];
        return;
    }
    if (HitPlayer >= 0)
    {        
        LocalBullet->Status = BULLET_HIT;
        LocalBullet->Lifespan = 0;
        DamagePlayer(HitPlayer, LocalBullet->Damage);
    }


    
    
}


bool CheckPlayerCollision(int Index)
{
    bool AnyHit = false;
    Vector TestCenter;
    Vector TestSize;
    Vector TotalPush[4];        

    for (int ThisVec = 0; ThisVec < 4; ThisVec++)
    {
        TotalPush[ThisVec][0] = 0.0f;
        TotalPush[ThisVec][1] = 0.0f;
        TotalPush[ThisVec][2] = 0.0f;
    }


    GamePlayers[Index].HitTri[0] = -1;
    GamePlayers[Index].HitTri[1] = -1;
    GamePlayers[Index].HitTri[2] = -1;
    GamePlayers[Index].HitTri[3] = -1;
    
    TestSize[0] = GamePlayers[Index].Location.Radius;
    TestSize[1] = TestSize[0];
    TestSize[2] = (GamePlayers[Index].Height * 0.5f) ;

    // Foot‐sphere center
    TestCenter[0] = GamePlayers[Index].Location.Position[0];
    TestCenter[1] = GamePlayers[Index].Location.Position[1];
    TestCenter[2] = GamePlayers[Index].Location.Position[2] + GamePlayers[Index].Height * 0.5f;


    // fetch grid cell
    int GArrayPointer, GCount;
    int GIndex = GetGridIndex(TestCenter);
    if (GIndex < 0) {
        GCount = 0;
    } else {
        GArrayPointer = GridHolster->GridData[GIndex].ElementIndex;
        GCount        = GridHolster->GridData[GIndex].ElementCount;
    }

    // iterate candidates
    for (int e = 0; e < GCount; e++)
    {
        ushort ThisTri = GridArray[GArrayPointer + e];
        CompactCollision* cc = &CollisionBuffer[ThisTri];


        // narrow‐phase: project & point‐in‐tri
        int HitResult = -1;
        switch (cc->NormalDirection)
        {
            case XAXISVECTOR: HitResult = CheckYZ(TestCenter, ThisTri); break;
            case YAXISVECTOR: HitResult = CheckXZ(TestCenter, ThisTri); break;
            case CEILINGVECTOR:            
                HitResult = CheckXY(TestCenter, ThisTri);
                break;
        }

        if (HitResult > 0)
        {
            
            // signed distance from center to triangle’s plane:
            float planeDist =
                cc->Normal[0]*TestCenter[0] +
                cc->Normal[1]*TestCenter[1] +
                cc->Normal[2]*TestCenter[2] +
                cc->VectorDistance;

            // pick the radius along this face’s axis:
            short Dir = cc->NormalDirection;
            if (Dir > 2)
            {
                Dir = 2;
            }
            float slabRadius = TestSize[Dir];

            // collide as soon as center lies within ±slabRadius of the plane
            if (planeDist >= -slabRadius && planeDist <=  slabRadius)
            {
                int dir = cc->NormalDirection;
                float pen = slabRadius - MathABS(planeDist);

                // record penetration exactly as you do now
                GamePlayers[Index].HitTri[dir] = ThisTri;
                TotalPush[dir][0] += cc->Normal[0] * pen;
                TotalPush[dir][1] += cc->Normal[1] * pen;
                TotalPush[dir][2] += cc->Normal[2] * pen;


                
                if (dir == CEILINGVECTOR)
                {
                    if (GamePlayers[Index].Location.VelocityFront[2] < 0.0f)
                        GamePlayers[Index].Location.VelocityFront[2] = 0.0f;
                    GamePlayers[Index].Location.Position[2] -= 0.1f;
                }

                // skip your old projRadius‐based code entirely
                continue;
            }


            // compute projection of your 3‐axis shape onto this triangle's normal
            float projRadius =
                MathABS(cc->Normal[0]) * TestSize[0] +
                MathABS(cc->Normal[1]) * TestSize[1] +
                MathABS(cc->Normal[2]) * TestSize[2];

            // signed‐distance minus your shape‐radius in that direction
            float pd =
                cc->Normal[0]*TestCenter[0] +
                cc->Normal[1]*TestCenter[1] +
                cc->Normal[2]*TestCenter[2] +
                cc->VectorDistance
                - projRadius;

            // only consider shallow penetrations
            if ((pd < 0.0f) && (pd > -1.001f * projRadius))
            {
                int dir = cc->NormalDirection;
                float pen = -pd;   // positive penetration depth
                GamePlayers[Index].HitTri[dir] = ThisTri;
                
                TotalPush[dir][0] += cc->Normal[0] * pen;
                TotalPush[dir][1] += cc->Normal[1] * pen;
                TotalPush[dir][2] += cc->Normal[2] * pen;

                

                if (dir == CEILINGVECTOR)
                {
                    if (GamePlayers[Index].Location.VelocityFront[2] < 0.0f)
                    {
                        GamePlayers[Index].Location.VelocityFront[2] = 0.0f;
                    }
                        
                    // prevent sphere from sitting in ceiling
                    GamePlayers[Index].Location.Position[2] -= 0.1f;
                }
                
                
            }
        }

    }

    for (int ThisVec = 0; ThisVec < 4; ThisVec++)
    {
        GamePlayers[Index].Location.Position[0] += TotalPush[ThisVec][0];
        GamePlayers[Index].Location.Position[1] += TotalPush[ThisVec][1];
        GamePlayers[Index].Location.Position[2] += TotalPush[ThisVec][2];
    }

    TestCenter[0] = GamePlayers[Index].Location.Position[0];
    TestCenter[1] = GamePlayers[Index].Location.Position[1];
    TestCenter[2] = GamePlayers[Index].Location.Position[2] + GamePlayers[Index].Height * 0.5f;
    for (int e = 0; e < GCount; e++)
    {
        ushort ThisTri = GridArray[GArrayPointer + e];
        CompactCollision* cc = &CollisionBuffer[ThisTri];


        // narrow‐phase: project & point‐in‐tri
        int HitResult = -1;
        switch (cc->NormalDirection)
        {
            case FLOORVECTOR:            
                HitResult = CheckXY(TestCenter, ThisTri);
                break;
        }

        if (HitResult > 0)
        {
            
            // signed distance from center to triangle’s plane:
            float planeDist =
                cc->Normal[0]*TestCenter[0] +
                cc->Normal[1]*TestCenter[1] +
                cc->Normal[2]*TestCenter[2] +
                cc->VectorDistance;

            // pick the radius along this face’s axis:
            short Dir = 2;

            float slabRadius = TestSize[Dir];

            // collide as soon as center lies within ±slabRadius of the plane
            if (planeDist >= -slabRadius && planeDist <=  slabRadius)
            {
                int dir = cc->NormalDirection;
                float pen = slabRadius - MathABS(planeDist);

                // record penetration exactly as you do now
                GamePlayers[Index].HitTri[dir] = ThisTri;
                TotalPush[dir][0] += cc->Normal[0] * pen;
                TotalPush[dir][1] += cc->Normal[1] * pen;
                TotalPush[dir][2] += cc->Normal[2] * pen;


                if (GamePlayers[Index].Location.VelocityFront[2] > 0.0f)
                {
                    GamePlayers[Index].Location.VelocityFront[2] = 0.0f;
                }
                
                AnyHit = true;
                // skip your old projRadius‐based code entirely
                continue;
            }


            // compute projection of your 3‐axis shape onto this triangle's normal
            float projRadius =
                MathABS(cc->Normal[0]) * TestSize[0] +
                MathABS(cc->Normal[1]) * TestSize[1] +
                MathABS(cc->Normal[2]) * TestSize[2];

            // signed‐distance minus your shape‐radius in that direction
            float pd =
                cc->Normal[0]*TestCenter[0] +
                cc->Normal[1]*TestCenter[1] +
                cc->Normal[2]*TestCenter[2] +
                cc->VectorDistance
                - projRadius;

            // only consider shallow penetrations
            if ((pd < 0.0f) && (pd > -1.001f * projRadius))
            {
                int dir = cc->NormalDirection;
                float pen = -pd;   // positive penetration depth
                GamePlayers[Index].HitTri[dir] = ThisTri;
                
                TotalPush[dir][0] += cc->Normal[0] * pen;
                TotalPush[dir][1] += cc->Normal[1] * pen;
                TotalPush[dir][2] += cc->Normal[2] * pen;

                AnyHit = true;
            
            
                if (GamePlayers[Index].Location.VelocityFront[2] > 0.0f)
                {
                    GamePlayers[Index].Location.VelocityFront[2] = 0.0f;
                }
                
                
            }
        }

    }

    GamePlayers[Index].Location.Position[0] += TotalPush[FLOORVECTOR][0];
    GamePlayers[Index].Location.Position[1] += TotalPush[FLOORVECTOR][1];
    GamePlayers[Index].Location.Position[2] += TotalPush[FLOORVECTOR][2];
    
    
    return AnyHit;

}

