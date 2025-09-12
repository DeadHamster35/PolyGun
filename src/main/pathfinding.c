#include <ultra64.h>
#include <ultralog.h>
#include <sched.h>
#include <stdbool.h>
#include "math.h"
#include "main.h"
#include "player.h"
#include "common.h"
#include "collision.h"
#include "memory.h"
#include "weapon.h"


short   NavPaths[16][ASTAR];
short   ReversePath[ASTAR];
NavNode NavArray[ASTAR];
short   NavSize;

void UpdateTarget(int Player)
{
    if (GameBots[Player].CurrentPathIndex != -1)
    { 
        if (NavPaths[Player][GameBots[Player].CurrentPathIndex] != -1)
        {
            Vector* PotentialTarget = (Vector*)&CollisionBuffer[GameBots[Player].CurrentPathIndex].Center;

            if (CheckRadius((Vector*)&GamePlayers[Player].Location.Position, PotentialTarget, 5.0f, 20.0f))
            {
                GameBots[Player].CurrentPathIndex++;
            }
            else
            {
                
            }
        }
        
    }
}


void ResetNavArray()
{
    for (int ThisNav = 0; ThisNav < NavSize; ThisNav++)
    {
        NavArray[ThisNav].ParentNode = 0;
        NavArray[ThisNav].Closed = 0;
        NavArray[ThisNav].F = -1;
        NavArray[ThisNav].G = 0;
        NavArray[ThisNav].H = 0;
        NavArray[ThisNav].TriIndex = -1;
    }
}


void InitNavArray()
{
    NavSize = ASTAR;
    ResetNavArray();
    NavSize = 0;
}

void ResetNavPath(int Player)
{
    for (int ThisNav = 0; ThisNav < ASTAR; ThisNav++)
    {
        NavPaths[Player][ThisNav] = -1;
    }
}


void BuildNavMesh()
{
    //In this function we will permutate through the entire collision mesh
    //and compare it against the entire collision mesh. We will test all verts
    //against all other verts in an attempt to find triangles whose sides are adjacent.
    //This will create a navmesh that our pathfinding code can then search across.

    
    //Begin Triangle Search Loop
    for (int ThisTri = 0; ThisTri < CollisionCount; ThisTri++)
    {
        CollisionBuffer[ThisTri].NavMesh[0] = -1;
        CollisionBuffer[ThisTri].NavMesh[1] = -1;
        CollisionBuffer[ThisTri].NavMesh[2] = -1;

        //We will not check anything that is not a floor triangle
        if (CollisionBuffer[ThisTri].NormalDirection != FLOORVECTOR)
        {
            continue;
        }
        
        //Keep Track of Current MeshIndex.
        int MeshIndex = 0;

        for (int TargetTri = 0; TargetTri < CollisionCount; TargetTri++)
        {
            //We will not check anything that is not a floor triangle
            if (CollisionBuffer[TargetTri].NormalDirection != FLOORVECTOR)
            {
                continue;
            }

            //We will not check a triangle against itself.
            if (ThisTri == TargetTri)
            {
                continue;            
            }



            //Skip all triangles whose boundaries do not intersect.
            bool Skip = false;
            for (int ThisVector = 0; ThisVector < 3; ThisVector ++)
            {
                if (CollisionBuffer[ThisTri].BoundingMax[ThisVector] < CollisionBuffer[TargetTri].BoundingMin[ThisVector])
                {
                    Skip = true;
                }
                if (CollisionBuffer[ThisTri].BoundingMin[ThisVector] > CollisionBuffer[TargetTri].BoundingMax[ThisVector])
                {
                    Skip = true;
                }
            }
            if (Skip)
            {
                continue;
            }


            //Keep Track of Matching Vertex.
            //Must have 2 Matching Vertex for an Adjacent Triangle.
            int VertexMatch = 0;


            //Begin Vertex Search Loop
            for (int ThisVert = 0; ThisVert < 3; ThisVert++)
            {
                

                if ((ThisVert == 2) & (VertexMatch == 0))
                {
                    //abandon search - cannot be connection.
                    continue;
                }

                for (int TargetVert = 0; TargetVert < 3; TargetVert++)            
                {


                    //Keep Track of Matching Vectors
                    //Must have 3 Matching Vectors for a Matching Vert
                    int VectorMatch = 0;

                    for (int ThisVector = 0; ThisVector < 3; ThisVector++)            
                    {
                        
                        if (CollisionBuffer[ThisTri].Vertex[ThisVert][ThisVector] == CollisionBuffer[TargetTri].Vertex[TargetVert][ThisVector])
                        {
                            //found matching value
                            
                            VectorMatch++;
                        }
                        else
                        {
                            break;
                        }
                    }

                    if (VectorMatch == 3)
                    {
                        
                        //Identical Values on XYZ Vectors.
                        //Matching Vertex Found.
                        VertexMatch++;
                    }
                }                
            }
            
            if (VertexMatch == 2)
            {
                CollisionBuffer[ThisTri].NavMesh[MeshIndex++] = TargetTri;
            }

            if (MeshIndex == 3)
            {
                //We have found all 3 possible connections
                //Stop searching and begin the next triangle.
                TargetTri = MAXTRI;
            }
        }


    }
}

float GetGCost(short ChildNode, short ParentNode)
{
    CompactCollision* Collision = (CompactCollision*)(&CollisionBuffer[NavArray[ChildNode].TriIndex]);
    CompactCollision* Target = (CompactCollision*)(&CollisionBuffer[NavArray[ParentNode].TriIndex]);
    return 
    (
        ( (Collision->Center[0] - Target->Center[0]) * (Collision->Center[0] - Target->Center[0]) ) +
        ( (Collision->Center[1] - Target->Center[1]) * (Collision->Center[1] - Target->Center[1]) ) +
        ( (Collision->Center[2] - Target->Center[2]) * (Collision->Center[2] - Target->Center[2]) )
    );
}

float GetHCost(short NodeIndex, short TargetTriangle)
{
    CompactCollision* Collision = (CompactCollision*)(&CollisionBuffer[NavArray[NodeIndex].TriIndex]);
    CompactCollision* Target = (CompactCollision*)(&CollisionBuffer[TargetTriangle]);
    return 
    (
        ( (Collision->Center[0] - Target->Center[0]) * (Collision->Center[0] - Target->Center[0]) ) +
        ( (Collision->Center[1] - Target->Center[1]) * (Collision->Center[1] - Target->Center[1]) ) +
        ( (Collision->Center[2] - Target->Center[2]) * (Collision->Center[2] - Target->Center[2]) )
    );
}

float GetHCostTarget(short NodeIndex, Vector TargetPosition)
{
    CompactCollision* Collision = (CompactCollision*)(&CollisionBuffer[NavArray[NodeIndex].TriIndex]);
    return 
    (
        ( (Collision->Center[0] - TargetPosition[0]) * (Collision->Center[0] - TargetPosition[0]) ) +
        ( (Collision->Center[1] - TargetPosition[1]) * (Collision->Center[1] - TargetPosition[1]) ) +
        ( (Collision->Center[2] - TargetPosition[2]) * (Collision->Center[2] - TargetPosition[2]) )
    );
}

short GetLowestF()
{
    short CurrentT = -1;
    float CurrentF = 999999999.0f;
    for (int ThisNav = 0; ThisNav < NavSize; ThisNav++)
    {
        if (NavArray[ThisNav].Closed == 1)
        {
            continue;
        }
        
        if (NavArray[ThisNav].F < CurrentF)
        {
            CurrentT = ThisNav;
            CurrentF = NavArray[ThisNav].F;
        }
    }
    return CurrentT;
}


short GetHighestF()
{
    short CurrentT = -1;
    float CurrentF = -0.5f;
    for (int ThisNav = 0; ThisNav < NavSize; ThisNav++)
    {
        if (NavArray[ThisNav].Closed == 1)
        {
            continue;
        }
        
        if (NavArray[ThisNav].F > CurrentF)
        {
            CurrentT = ThisNav;
            CurrentF = NavArray[ThisNav].F;
        }
    }
    return CurrentT;
}


short CheckNodeList(short TargetTri)
{
    for (int ThisNav = 0; ThisNav < NavSize; ThisNav++)
    {
        if (NavArray[ThisNav].TriIndex == TargetTri)
        {
            return ThisNav;
        }
    }
    return -1;
}

void CreateNavPath(int PlayerIndex, short TargetNode)
{
    short NodeCount = 0;
    for (int ThisNode = 0; ; ThisNode++)
    {
        ReversePath[ThisNode] = NavArray[TargetNode].TriIndex;
        TargetNode = NavArray[TargetNode].ParentNode;

        if (TargetNode == -1)
        {
            NodeCount = ThisNode;
            break;
        }
    }
    
    for (int ThisNode = 0; ThisNode < NodeCount; ThisNode++)
    {        
        NavPaths[PlayerIndex][ThisNode] = ReversePath[NodeCount - ThisNode];
    }
    
}



int BStar(int PlayerIndex, short TargetTriangle)
{
    float LowestF;
    short LowestIndex;
    
    

    if (GamePlayers[PlayerIndex].HitTri[FLOORVECTOR] == -1)
    {
        //character is not on floor.
        return -1;
    }
    
    
    ResetNavArray();
    NavSize = 1;    
    NavArray[0].TriIndex = GamePlayers[PlayerIndex].HitTri[FLOORVECTOR];
    NavArray[0].G = 0;
    NavArray[0].F = GetHCost(0,TargetTriangle);
    NavArray[0].ParentNode = -1;
    LowestIndex = 0;
    while(1)
    {
        

        short CurrentNav = (GetLowestF());

        if (CurrentNav == -1)
        {
            //something terrible has happened.
            return -1;
        }

        

        short TriIndex = NavArray[CurrentNav].TriIndex;
        if (TriIndex == TargetTriangle)
        {
            //Yes!!
            //Do more stuff!
            ResetNavPath(PlayerIndex);
            CreateNavPath(PlayerIndex, CurrentNav);
            GameBots[PlayerIndex].CurrentPathIndex = 1;
            ResetNavArray();
            return 1;
        }

        NavArray[CurrentNav].Closed = 1;
        for (int ThisConnect = 0; ThisConnect < 3; ThisConnect++)
        {
            
            short Connection = CollisionBuffer[TriIndex].NavMesh[ThisConnect];


            if(Connection == -1)
            {
                //All connections have been checked
                ThisConnect = 3;
                continue;
            }
            

            short ExistingNode = CheckNodeList(Connection);

            if (ExistingNode != -1)
            {
                //Dejavu
                if (NavArray[ExistingNode].Closed != 0)
                {
                    //We've already covered this triangle and all it's children.
                    continue;
                }

                NavArray[ExistingNode].H = GetHCost(ExistingNode, TargetTriangle);
                float PotentialF = NavArray[ExistingNode].H + NavArray[CurrentNav].G;
                if ( (NavArray[ExistingNode].F == -1) || (NavArray[ExistingNode].F > PotentialF) )
                {
                    NavArray[ExistingNode].ParentNode = CurrentNav;
                    float NewG = GetGCost(ExistingNode, CurrentNav);
                    NavArray[ExistingNode].G = NewG + NavArray[CurrentNav].G;
                    NavArray[ExistingNode].F = PotentialF;
                    NavArray[ExistingNode].Closed = 0;
                }
            }
            else
            {
                if (NavSize < ASTAR)
                {
                    NavArray[NavSize].TriIndex = Connection;
                    NavArray[NavSize].H = GetHCost(NavSize, TargetTriangle);
                    NavArray[NavSize].F = NavArray[NavSize].H + NavArray[CurrentNav].G;
                    NavArray[NavSize].ParentNode = CurrentNav;                
                    float NewG = GetGCost(NavSize, CurrentNav);
                    NavArray[NavSize].G = NewG + NavArray[CurrentNav].G;
                    NavArray[NavSize].Closed = 0;
                    NavSize++;
                }
                else
                {
                    //Out of nodes! Give up and take the closest route we can get. 
                    ResetNavPath(PlayerIndex);
                    CreateNavPath(PlayerIndex, CurrentNav);
                    GameBots[PlayerIndex].CurrentPathIndex = 1;
                    ResetNavArray();
                    return 1;
                }
                
            }

            

        }
    }
}


int BSTARDistance(Vector TargetPosition, short TargetTriangle, float TargetDistance)
{
    //This function aims to work from the target position and find a nearby node that can be traversed to. 
    //The nearby node must be at minimum the TargetDistance from the target position. 

    float LowestF;
    short LowestIndex; 
    
    
    
    ResetNavArray();
    NavSize = 1;    
    NavArray[0].TriIndex = TargetTriangle;
    NavArray[0].G = 0;
    NavArray[0].F = 0;
    NavArray[0].H = 0;
    NavArray[0].ParentNode = -1;
    LowestIndex = 0;
    while(1)
    {
        

        short CurrentNav = (GetLowestF());
        if (CurrentNav == -1)
        {
            //something terrible has happened.
            return -1;
        }
        NavArray[CurrentNav].H = GetHCostTarget(CurrentNav, TargetPosition);
        short TriIndex = NavArray[CurrentNav].TriIndex;
        if (NavArray[CurrentNav].H > (TargetDistance * TargetDistance))
        {
            //Yes!!
            return NavArray[CurrentNav].TriIndex;
        }

        NavArray[CurrentNav].Closed = 1;
        for (int ThisConnect = 0; ThisConnect < 3; ThisConnect++)
        {
            
            short Connection = CollisionBuffer[TriIndex].NavMesh[ThisConnect];


            if(Connection == -1)
            {
                //All connections have been checked
                ThisConnect = 3;
                continue;
            }
            

            short ExistingNode = CheckNodeList(Connection);

            if (ExistingNode != -1)
            {
                //Dejavu
                if (NavArray[ExistingNode].Closed != 0)
                {
                    //We've already covered this triangle and all it's children.
                    continue;
                }

                NavArray[ExistingNode].H = GetHCostTarget(ExistingNode, TargetPosition);
                float PotentialF = NavArray[ExistingNode].H + NavArray[CurrentNav].G;
                if ( (NavArray[ExistingNode].F == -1) || (NavArray[ExistingNode].F < PotentialF) )
                {
                    NavArray[ExistingNode].ParentNode = CurrentNav;
                    float NewG = GetGCost(ExistingNode, CurrentNav);
                    NavArray[ExistingNode].G = NewG + NavArray[CurrentNav].G;
                    NavArray[ExistingNode].F = PotentialF;
                    NavArray[ExistingNode].Closed = 0;
                }
            }
            else
            {
                if (NavSize < ASTAR)
                {
                    NavArray[NavSize].TriIndex = Connection;
                    NavArray[NavSize].H = GetHCostTarget(NavSize, TargetPosition);
                    NavArray[NavSize].F = NavArray[NavSize].H + NavArray[CurrentNav].G;
                    NavArray[NavSize].ParentNode = CurrentNav;                
                    float NewG = GetGCost(NavSize, CurrentNav);
                    NavArray[NavSize].G = NewG + NavArray[CurrentNav].G;
                    NavArray[NavSize].Closed = 0;
                    NavSize++;
                }
                else
                {
                    //Out of nodes! Give up and take the closest route we can get. 
                    return NavArray[CurrentNav].TriIndex;
                }
                
            }

            

        }
    }
}