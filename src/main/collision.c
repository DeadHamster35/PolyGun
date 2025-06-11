#include <nusys.h>
#include <nualsgi_n.h>
#include <stdbool.h>
#include <stdio.h>
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
	for (int CurrentVector = 0; CurrentVector < 3; CurrentVector++)
	{
		TempPosition[CurrentVector] = SourcePosition[CurrentVector] - TargetPosition[CurrentVector];
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

bool PlayerLevelCollision(int Index)
{
    
    bool AnyHit = false;
    Vector TestSphere;
    //Foot
    TestSphere[0] = GamePlayers[Index].Location.Position[0];
    TestSphere[1] = GamePlayers[Index].Location.Position[1];
    TestSphere[2] = GamePlayers[Index].Location.Position[2] + GamePlayers[Index].Location.Radius;

    for (int ThisVect = 0; ThisVect < 4; ThisVect++)
    {
        GamePlayers[Index].HitTri[ThisVect] = -1;
    }

    int GArrayPointer, GCount;
    int GIndex = GetGridIndex(TestSphere);    
    
    if (GIndex < 0)
    {
        GCount = 0;
    }
    else
    {
        GArrayPointer = GridHolster->GridData[GIndex].ElementIndex;
        GCount = GridHolster->GridData[GIndex].ElementCount;
    }


    for (int ThisElement = 0; ThisElement < GCount; ThisElement++)
    {
        ushort ThisTri = GridArray[GArrayPointer + ThisElement];
        
        for (int ThisVector = 0; ThisVector < 3; ThisVector++)
        {
            
            if (TestSphere[ThisVector] - (2 *  GamePlayers[Index].Location.Radius) > CollisionBuffer[ThisTri].BoundingMax[ThisVector] + GamePlayers[Index].Location.Radius)
            {
                goto SkipTrianglePointTestA;
            }
            if (TestSphere[ThisVector] + (2 *  GamePlayers[Index].Location.Radius) < CollisionBuffer[ThisTri].BoundingMin[ThisVector] - GamePlayers[Index].Location.Radius)
            {
                goto SkipTrianglePointTestA;
            }
        }
        
        

        int HitResult = -1;        
        switch ((int)CollisionBuffer[ThisTri].NormalDirection)
        {
            case XAXISVECTOR:
            {
                HitResult = CheckYZ(TestSphere, ThisTri);
                break;
            }
            case YAXISVECTOR:
            {
                HitResult = CheckXZ(TestSphere, ThisTri);
                break;
            }
            case FLOORVECTOR:
            case CEILINGVECTOR:
            {
                HitResult = CheckXY(TestSphere, ThisTri);
                break;
            }
        }
        
        if (HitResult > 0)
        {
            
            float PushDistance = 
            (
                CollisionBuffer[ThisTri].Normal[0] * TestSphere[0] +
                CollisionBuffer[ThisTri].Normal[1] * TestSphere[1] +
                CollisionBuffer[ThisTri].Normal[2] * TestSphere[2] +
                CollisionBuffer[ThisTri].VectorDistance - ( GamePlayers[Index].Location.Radius)
            );
            
            if ((PushDistance < 0) && (PushDistance > (GamePlayers[Index].Location.Radius * -1.1f)))
            {
                AnyHit = true;
                GamePlayers[Index].HitTri[CollisionBuffer[ThisTri].NormalDirection] = ThisTri;

                
                GamePlayers[Index].Location.Position[0] -= CollisionBuffer[ThisTri].Normal[0] * PushDistance;
                GamePlayers[Index].Location.Position[1] -= CollisionBuffer[ThisTri].Normal[1] * PushDistance;
                GamePlayers[Index].Location.Position[2] -= CollisionBuffer[ThisTri].Normal[2] * PushDistance;

                if ((CollisionBuffer[ThisTri].NormalDirection == FLOORVECTOR))
                {
                    if (GamePlayers[Index].Location.VelocityFront[2] > 0.0f)
                    {
                        GamePlayers[Index].Location.VelocityFront[2] = 0.0f;
                    }
                }
                if ((CollisionBuffer[ThisTri].NormalDirection == CEILINGVECTOR))
                {
                    if (GamePlayers[Index].Location.VelocityFront[2] < 0.0f)
                    {
                        GamePlayers[Index].Location.VelocityFront[2] = 0.0f;
                    }

                    GamePlayers[Index].Location.Position[2] -= GamePlayers[Index].Location.Radius;
                }
            }
        }



    


        SkipTrianglePointTestA:


    }

    //Head
    TestSphere[0] = GamePlayers[Index].Location.Position[0];
    TestSphere[1] = GamePlayers[Index].Location.Position[1];
    TestSphere[2] = GamePlayers[Index].Location.Position[2] + GamePlayers[Index].Height - GamePlayers[Index].Location.Radius;

    
    
    GIndex = GetGridIndex(TestSphere);    
    
    if (GIndex < 0)
    {
        GCount = 0;
    }
    else
    {
        GArrayPointer = GridHolster->GridData[GIndex].ElementIndex;
        GCount = GridHolster->GridData[GIndex].ElementCount;
    }

    for (int ThisElement = 0; ThisElement < GCount; ThisElement++)
    {
        ushort ThisTri = GridArray[GArrayPointer + ThisElement];

        switch (CollisionBuffer[ThisTri].NormalDirection)
        {
            case FLOORVECTOR:
            {
                //goto SkipTrianglePointTestB;
                break;
            }
        }

        for (int ThisVector = 0; ThisVector < 3; ThisVector++)
        {
            if (TestSphere[ThisVector] - (2 *  GamePlayers[Index].Location.Radius) > CollisionBuffer[ThisTri].BoundingMax[ThisVector])
            {
                goto SkipTrianglePointTestB;
            }
            if (TestSphere[ThisVector] + (2 *  GamePlayers[Index].Location.Radius) < CollisionBuffer[ThisTri].BoundingMin[ThisVector])
            {
                goto SkipTrianglePointTestB;
            }
        }
        
        
        
        int HitResult = -1;
        switch (CollisionBuffer[ThisTri].NormalDirection)
        {
            case XAXISVECTOR:
            {
                HitResult = CheckYZ(TestSphere, ThisTri);
                break;
            }
            case YAXISVECTOR:
            {
                HitResult = CheckXZ(TestSphere, ThisTri);
                break;
            }
            case FLOORVECTOR:
            case CEILINGVECTOR:
            {
                HitResult = CheckXY(TestSphere, ThisTri);
                break;
            }
        }

        if (HitResult > 0)
        {
            
            float PushDistance = 
            (
                CollisionBuffer[ThisTri].Normal[0] * TestSphere[0] +
                CollisionBuffer[ThisTri].Normal[1] * TestSphere[1] +
                CollisionBuffer[ThisTri].Normal[2] * TestSphere[2] +
                CollisionBuffer[ThisTri].VectorDistance - ( GamePlayers[Index].Location.Radius)
            );
            
            if ((PushDistance < 0) && (PushDistance > (GamePlayers[Index].Location.Radius * -1.1f)))
            {
                AnyHit = true;
                GamePlayers[Index].HitTri[CollisionBuffer[ThisTri].NormalDirection] = ThisTri;

                
                GamePlayers[Index].Location.Position[0] -= CollisionBuffer[ThisTri].Normal[0] * PushDistance * 0.9f;
                GamePlayers[Index].Location.Position[1] -= CollisionBuffer[ThisTri].Normal[1] * PushDistance * 0.9f;
                GamePlayers[Index].Location.Position[2] -= CollisionBuffer[ThisTri].Normal[2] * PushDistance * 0.9f;

                if ((CollisionBuffer[ThisTri].NormalDirection == CEILINGVECTOR))
                {
                    if (GamePlayers[Index].Location.VelocityFront[2] < 0.0f)
                    {
                        GamePlayers[Index].Location.VelocityFront[2] = 0.0f;
                    }

                    GamePlayers[Index].Location.Position[2] -= GamePlayers[Index].Location.Radius;
                    
                }

                if ((CollisionBuffer[ThisTri].NormalDirection == FLOORVECTOR))
                {
                    //wtf are we falling through the world geometry?
                    if (GamePlayers[Index].Location.VelocityFront[2] < 0.0f)
                    {
                        GamePlayers[Index].Location.VelocityFront[2] = 0.0f;
                    }

                    GamePlayers[Index].Location.Position[2] += GamePlayers[Index].Height;
                    
                }
                
            }
        }



    


        SkipTrianglePointTestB:


    }
    

    return AnyHit;
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
    for (int i = 0; i < 3; i++) {
        VectorSubtractS(Face[1], Face[0], E1);
        VectorSubtractS(Face[2], Face[0], E2);
        VectorSubtract(End, Start, S);
        VectorCrossProduct(S, E2, H);
        a = VectorDotProduct(E1, H);

        if (a > -EPSILON && a < EPSILON)
            return FALSE;

        f = 1.0 / a;
        VectorSubtractFS(Start, Face[0], Q);
        u = f * VectorDotProduct(Q, H);

        if (u < 0.0 || u > 1.0)
            return FALSE;

        VectorCrossProduct(Q, E1, H);
        v = f * VectorDotProduct(S, H);

        if (v < 0.0 || u + v > 1.0)
            return FALSE;

        // Calculate the intersection point
        float t = f * VectorDotProduct(E2, H);

        if ((t > EPSILON) && (t <= 1.0f)) {
            Intersect[0] = Start[0] + t * S[0];
            Intersect[1] = Start[1] + t * S[1];
            Intersect[2] = Start[2] + t * S[2];
            return t;
        } else {
            return FALSE;
        }
    }
}




float intersectLineTriangleRadius(Vector Start, Vector End, VertexArray Face, Vector Intersect, float Radius) {
        const float EPSILON = 0.000001;

    Vector E1, E2, H, S, Q;
    float a, f, u, v;

    // Calculate vectors
    for (int i = 0; i < 3; i++) {
        VectorSubtractS(Face[1], Face[0], E1);
        VectorSubtractS(Face[2], Face[0], E2);
        VectorSubtract(End, Start, S);
        VectorCrossProduct(S, E2, H);
        a = VectorDotProduct(E1, H);

        if (a > -EPSILON && a < EPSILON)
            return FALSE;

        f = 1.0 / a;
        VectorSubtractFS(Start, Face[0], Q);
        u = f * VectorDotProduct(Q, H);

        if (u < 0.0 || u > 1.0)
            return FALSE;

        VectorCrossProduct(Q, E1, H);
        v = f * VectorDotProduct(S, H);

        if (v < 0.0 || u + v > 1.0)
            return FALSE;

        // Calculate the intersection point
        float t = f * VectorDotProduct(E2, H);

        if ((t > EPSILON) && (t <= 1.0f)) {
            Intersect[0] = Start[0] + t * S[0];
            Intersect[1] = Start[1] + t * S[1];
            Intersect[2] = Start[2] + t * S[2];
            return t;
        } else {
            return FALSE;
        }
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


Vector Intersect, FinalHit, TestLocation;
float Distance, ClosestHit;
short HitTriangle;
Vector MidPoint;
Cylinder CheckCylinder;

void AdjustVelocityTriangle(Vector StartVelocity, Vector NormalDirection, Vector AdjustVelocity) {
    // Project the velocity onto the plane defined by the triangle's normal
    float dot = VectorDotProduct(StartVelocity, NormalDirection);
    Vector projected_velocity;
    projected_velocity[0] = dot * NormalDirection[0];
    projected_velocity[1] = dot * NormalDirection[1];
    projected_velocity[2] = dot * NormalDirection[2];
    
    // Adjust the velocity to move along the surface of the triangle's face
    VectorSubtract(StartVelocity, projected_velocity, AdjustVelocity);
}


void PlayerLevelCollisionB(int PlayerIndex)
{

    //okay so we need to check some collisions.
    Player* LocalPlayer = (Player*)&GamePlayers[PlayerIndex];
    HitTriangle = -1;
    ClosestHit = 1.0f;
    Distance = ClosestHit + 1.0f;
    Vector StartVec, TargetVec, MidPoint, Magnitude, NormalDirection;

    
    
    for (int ThisVect = 0; ThisVect < 4; ThisVect++)
    {
        LocalPlayer->HitTri[ThisVect] = -1;
    }
    
    //Apply velocity to all vectors and reduce current velocity by 90% each frame. Quick stop.
    for (int ThisVector = 0; ThisVector < 3; ThisVector++)
    {
        StartVec[ThisVector] = LocalPlayer->Location.LastPosition[ThisVector];
        TargetVec[ThisVector] = LocalPlayer->Location.Position[ThisVector];
    }

    StartVec[2] += LocalPlayer->Location.Radius;
    TargetVec[2] += LocalPlayer->Location.Radius;

    for (int ThisTri = 0; ThisTri < CollisionCount; ThisTri++)
    {
        
        for (int ThisVector = 0; ThisVector < 3; ThisVector++)
        {
            //can we just ignore this triangle?
            if 
            (
                (TargetVec[ThisVector] - (2.0f *  LocalPlayer->Location.Radius) > CollisionBuffer[ThisTri].BoundingMax[ThisVector]) &&
                (StartVec[ThisVector] - (2.0f *  LocalPlayer->Location.Radius) > CollisionBuffer[ThisTri].BoundingMax[ThisVector])
            )
            {
                goto SkipTrianglePointTestA;
            }

            if 
            (
                (TargetVec[ThisVector] + (2.0f *  LocalPlayer->Location.Radius) < CollisionBuffer[ThisTri].BoundingMin[ThisVector]) &&
                (StartVec[ThisVector] + (2.0f *  LocalPlayer->Location.Radius) < CollisionBuffer[ThisTri].BoundingMin[ThisVector])
            )
            {
                goto SkipTrianglePointTestA;
            }
        }
        
        Distance = intersectLineTriangle(StartVec, TargetVec, CollisionBuffer[ThisTri].Vertex, Intersect);

        if ((Distance != 0) && (Distance < ClosestHit))
        {
            //Distance is the percentage of the ray we have to travel to get to the intersection point (Intersect).
            
            ClosestHit = Distance;
            HitTriangle = ThisTri;
            FinalHit[0] = Intersect[0];
            FinalHit[1] = Intersect[1];
            FinalHit[2] = Intersect[2];
        }

        
        SkipTrianglePointTestA:

    }

    if (HitTriangle != -1)
    {
        //Okay! We hit something in our earlier check.
        
        
        /*
        float PushDistance = 
        (
            CollisionBuffer[HitTriangle].Normal[0] * FinalHit[0] +
            CollisionBuffer[HitTriangle].Normal[1] * FinalHit[1] +
            CollisionBuffer[HitTriangle].Normal[2] * FinalHit[2] +
            CollisionBuffer[HitTriangle].VectorDistan3ce - ( LocalPlayer->Location.Radius)
        );
        */
        for (int ThisVector = 0; ThisVector < 3; ThisVector++)
        {
            
            LocalPlayer->HitTri[CollisionBuffer[HitTriangle].NormalDirection] = HitTriangle;
            LocalPlayer->Location.Position[ThisVector] = LocalPlayer->Location.LastPosition[ThisVector] + (ClosestHit * LocalPlayer->Location.VelocityFront[ThisVector]);
        }
        

        /*
        //Now adjust the velocity to move along the face of the triangle.
        Vector OutVelocity;
        AdjustVelocityTriangle(LocalPlayer->Location.VelocityFront, CollisionBuffer[HitTriangle].Normal, OutVelocity);
        

        LocalPlayer->Location.VelocityFront[0] = OutVelocity[0];
        LocalPlayer->Location.VelocityFront[1] = OutVelocity[1];
        LocalPlayer->Location.VelocityFront[2] = OutVelocity[2];
        
        //Check the world collision mesh against our new player's velocity.
        //Recursion
        PlayerLevelCollisionB(PlayerIndex);
        */
        
    }




}

int CheckViewCone(int PlayerIndex)
{
    ClosestHit = 99999.0f;
    Distance = ClosestHit + 1.0f;
    Vector Eye;
    Eye[0] = 0;
    Eye[1] = 1000;
    Eye[2] = 0;

    AlignXVector(Eye, GameCameras[PlayerIndex].Location.Angle[0]);
    AlignYVector(Eye, GameCameras[PlayerIndex].Location.Angle[1]);
    AlignZVector(Eye, GameCameras[PlayerIndex].Location.Angle[2]);

    Eye[0] += GameCameras[PlayerIndex].Location.Position[0];
    Eye[1] += GameCameras[PlayerIndex].Location.Position[1];
    Eye[2] += GameCameras[PlayerIndex].Location.Position[2];
    int Hit = -1;
    
    for (int ThisPlayer = 0; ThisPlayer < PlayerCount + BotCount; ThisPlayer++)
    {
        if (PlayerIndex == ThisPlayer)
        {
            //you can't see yourself.
            continue;
        }

        Player *LocalPlayer = (Player*)&GamePlayers[ThisPlayer];

        
        CheckCylinder.Radius = LocalPlayer->Location.Radius * 1.5f;
        CheckCylinder.Height = LocalPlayer->Height * 1.5f;
        CheckCylinder.Base[0] = LocalPlayer->Location.Position[0];
        CheckCylinder.Base[1] = LocalPlayer->Location.Position[1];
        CheckCylinder.Base[2] = LocalPlayer->Location.Position[2] - (LocalPlayer->Height * 0.25f);

        Distance = (intersectRayCylinder(GameCameras[PlayerIndex].Location.Position, Eye,(Cylinder*)&CheckCylinder, Intersect));
        if ((Distance > 0) && (Distance < ClosestHit))
        {
            ClosestHit = Distance;
            Hit = ThisPlayer;
        }
    }
    return Hit;
}

void CheckProjectileCollision(int BulletIndex) 
{
    
    Projectile *LocalBullet = (Projectile*)&ProjectileArray[BulletIndex];
    HitTriangle = -1;
    short HitPlayer = -1;
    ClosestHit = 1.00f; //Distance tests use 0->1.0f for return. 

    Distance = ClosestHit + 1.0f;

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

    bool Check = false;

    MidPoint[0] = ((LocalBullet->Location.LastPosition[0] + LocalBullet->Location.Position[0]) * 0.5f);
    MidPoint[1] = ((LocalBullet->Location.LastPosition[1] + LocalBullet->Location.Position[1]) * 0.5f);
    MidPoint[2] = ((LocalBullet->Location.LastPosition[2] + LocalBullet->Location.Position[2]) * 0.5f);




    //Player Test
    for (int ThisPlayer = 0; ThisPlayer < PlayerCount + BotCount; ThisPlayer++)
    {
        if (LocalBullet->Owner == ThisPlayer)
        {
            //you can't shoot yourself.
            continue;
        }
        
        //XY Axis
        for (int ThisVector = 0; ThisVector < 2; ThisVector++)
        {            
            if (MidPoint[ThisVector] - BulletRadi < GamePlayers[ThisPlayer].Location.Position[ThisVector])
            {
                Check = true;
            }
            if (MidPoint[ThisVector] + BulletRadi > GamePlayers[ThisPlayer].Location.Position[ThisVector])
            {
                Check = true;
            }
        }

        //ZAxis
        if (MidPoint[2] - BulletRadi > (GamePlayers[ThisPlayer].Location.Position[2] + (GamePlayers[ThisPlayer].Height * 1.5f)))
        {
            Check = true;
        }
        if (MidPoint[2] + BulletRadi < (GamePlayers[ThisPlayer].Location.Position[2] - (GamePlayers[ThisPlayer].Height * 0.5f)))
        {
            Check = true;
        }

        if (!Check)
        {
            //Bounds Checks are all false.
            continue;
        }



        Player *LocalPlayer = (Player*)&GamePlayers[ThisPlayer];

        CheckCylinder.Base[0] = LocalPlayer->Location.Position[0];
        CheckCylinder.Base[1] = LocalPlayer->Location.Position[1];
        CheckCylinder.Base[2] = LocalPlayer->Location.Position[2];
        CheckCylinder.Radius = LocalPlayer->Location.Radius + 5.0f;
        CheckCylinder.Height = LocalPlayer->Height;

        Distance = (intersectRayCylinder(LocalBullet->Location.LastPosition, LocalBullet->Location.Position,(Cylinder*)&CheckCylinder, Intersect));
        if ((Distance > 0) && (Distance < ClosestHit))
        {
            ClosestHit = Distance;
            HitPlayer = ThisPlayer;
            FinalHit[0] = Intersect[0];
            FinalHit[1] = Intersect[1];
            FinalHit[2] = Intersect[2];
        }
    }


    //Triangle Test
    //Do NOT reset ClosestHit - This allows for comparing against existing target. 
    //Triangle test will return only for triangles inbetween player and target.

    int GArrayPointer, GCount;
    int GIndex = GetGridIndex(MidPoint);    
    
    if (GIndex < 0)
    {
        GCount = 0;
    }
    else
    {
        GArrayPointer = GridHolster->GridData[GIndex].ElementIndex;
        GCount = GridHolster->GridData[GIndex].ElementCount;
    }


    for (int ThisElement = 0; ThisElement < GCount; ThisElement++)
    {
        ushort ThisTri = GridArray[GArrayPointer + ThisElement];
        for (int ThisVector = 0; ThisVector < 3; ThisVector++)
        {            
            if (MidPoint[ThisVector] - BulletRadi > CollisionBuffer[ThisTri].BoundingMax[ThisVector])
            {
                goto SkipTriangleLineTest;
            }
            if (MidPoint[ThisVector] + BulletRadi < CollisionBuffer[ThisTri].BoundingMin[ThisVector])
            {
                goto SkipTriangleLineTest;
            }
        }

        Distance = intersectLineTriangle(LocalBullet->Location.LastPosition, LocalBullet->Location.Position, CollisionBuffer[ThisTri].Vertex, Intersect);
        if ((Distance != 0) && (Distance < ClosestHit))
        {
            ClosestHit = Distance;
            HitTriangle = ThisTri;
            FinalHit[0] = Intersect[0];
            FinalHit[1] = Intersect[1];
            FinalHit[2] = Intersect[2];
        }

        SkipTriangleLineTest:
    }

    
    if (HitTriangle >= 0)
    {
        LocalBullet->Status = BULLET_INACTIVE;
        //If Triangle Hit is true, distance is less than distance to any potential player.
        return;
    }
    if (HitPlayer >= 0)
    {        
        //Can only return true if no triangles were hit closer to target. 
        LocalBullet->Status = BULLET_INACTIVE;
        int BleedThrough = LocalBullet->Damage - GamePlayers[HitPlayer].HealthData.Shield;
        if (GamePlayers[HitPlayer].HealthData.Shield > 0)
        {
            GamePlayers[HitPlayer].HealthData.Shield -= LocalBullet->Damage;
        }
        if (BleedThrough > 0)
        {
            GamePlayers[HitPlayer].HealthData.Health -= BleedThrough;
        }

        if (GamePlayers[HitPlayer].HealthData.Health <= 0)
        {
            GameBots[HitPlayer].Difficulty++;
            initPlayer(HitPlayer);
        }
    }


    
    
}