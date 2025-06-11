
#include <nusys.h>
#include <nualsgi_n.h>
#include "common.h"
#include "graphic.h"
#include "math.h"
#include "animations.h"

uint GlobalUIntA, GlobalUIntB;
uint GlobalAddressA, GlobalAddressB;
int GlobalIntA, GlobalIntB;
Vector ObjectPosition;
SVector ObjectAngle;
SVector LinearTranslation, LinearRotation, LinearScaling;



void GetLinear(PolyAnime* AnimeData, float Scale, int Frame)
{
    short KeyTime;
    SVector NDistance;
    float   TDistance, RelativeT;
    float   TRatio;
    if (AnimeData->PositionCount == 1)
    {
        LinearTranslation[0] = AnimeData->PositionData[0].Data[0];
        LinearTranslation[1] = AnimeData->PositionData[0].Data[1];
        LinearTranslation[2] = AnimeData->PositionData[0].Data[2];
    }
    else
    {
        for (int ThisKey = 0; ThisKey < AnimeData->PositionCount; ThisKey++)
        {
            KeyTime = AnimeData->PositionData[ThisKey].Time;
            if (Frame < KeyTime)
            {
                NDistance[0] = AnimeData->PositionData[ThisKey].Data[0] - AnimeData->PositionData[ThisKey - 1].Data[0];
                NDistance[1] = AnimeData->PositionData[ThisKey].Data[1] - AnimeData->PositionData[ThisKey - 1].Data[1];
                NDistance[2] = AnimeData->PositionData[ThisKey].Data[2] - AnimeData->PositionData[ThisKey - 1].Data[2];

                TDistance = (float)(AnimeData->PositionData[ThisKey].Time - AnimeData->PositionData[ThisKey - 1].Time);
                RelativeT = (float)(Frame - AnimeData->PositionData[ThisKey - 1].Time); //Get time relative to last keyframe;
                TRatio = (float)((float)RelativeT / (float)TDistance);
                LinearTranslation[0] = AnimeData->PositionData[ThisKey - 1].Data[0] + (short)(NDistance[0] * (TRatio));
                LinearTranslation[1] = AnimeData->PositionData[ThisKey - 1].Data[1] + (short)(NDistance[1] * (TRatio));
                LinearTranslation[2] = AnimeData->PositionData[ThisKey - 1].Data[2] + (short)(NDistance[2] * (TRatio));
                break;
            }
            if (Frame == KeyTime)
            {
                LinearTranslation[0] = AnimeData->PositionData[ThisKey].Data[0];
                LinearTranslation[1] = AnimeData->PositionData[ThisKey].Data[1];
                LinearTranslation[2] = AnimeData->PositionData[ThisKey].Data[2];
                break;
                
            }
            if (Frame > KeyTime)
            {
                //continue;
            }
        }
    }

    if (AnimeData->RotationCount == 1)
    {
        LinearRotation[0] = AnimeData->RotationData[0].Data[0];
        LinearRotation[1] = AnimeData->RotationData[0].Data[1];
        LinearRotation[2] = AnimeData->RotationData[0].Data[2];
    }
    else
    {
        for (int ThisKey = 0; ThisKey < AnimeData->RotationCount; ThisKey++)
        {
            KeyTime = AnimeData->RotationData[ThisKey].Time;
            if (Frame < KeyTime)
            {
                NDistance[0] = AnimeData->RotationData[ThisKey].Data[0] - AnimeData->RotationData[ThisKey - 1].Data[0];
                NDistance[1] = AnimeData->RotationData[ThisKey].Data[1] - AnimeData->RotationData[ThisKey - 1].Data[1];
                NDistance[2] = AnimeData->RotationData[ThisKey].Data[2] - AnimeData->RotationData[ThisKey - 1].Data[2];

                TDistance = (float)(AnimeData->RotationData[ThisKey].Time - AnimeData->RotationData[ThisKey - 1].Time);
                RelativeT = (float)(Frame - AnimeData->RotationData[ThisKey - 1].Time); //Get time relative to last keyframe;
                TRatio = (float)((float)RelativeT / (float)TDistance);

                LinearRotation[0] = AnimeData->RotationData[ThisKey - 1].Data[0] + (short)(NDistance[0] * (TRatio));
                LinearRotation[1] = AnimeData->RotationData[ThisKey - 1].Data[1] + (short)(NDistance[1] * (TRatio));
                LinearRotation[2] = AnimeData->RotationData[ThisKey - 1].Data[2] + (short)(NDistance[2] * (TRatio));
                break;
            }
            if (Frame == KeyTime)
            {
                LinearRotation[0] = AnimeData->RotationData[ThisKey].Data[0];
                LinearRotation[1] = AnimeData->RotationData[ThisKey].Data[1];
                LinearRotation[2] = AnimeData->RotationData[ThisKey].Data[2];
                break;
                
            }
            if (Frame > KeyTime)
            {
                //continue;
            }
        }
    }


    if (AnimeData->ScalingCount == 1)
    {
        LinearScaling[0] = AnimeData->ScalingData[0].Data[0];
        LinearScaling[1] = AnimeData->ScalingData[0].Data[1];
        LinearScaling[2] = AnimeData->ScalingData[0].Data[2];
    }
    else
    {
        for (int ThisKey = 0; ThisKey < AnimeData->ScalingCount; ThisKey++)
        {
            KeyTime = AnimeData->ScalingData[ThisKey].Time;
            if (Frame < KeyTime)
            {
                NDistance[0] = AnimeData->ScalingData[ThisKey].Data[0] - AnimeData->ScalingData[ThisKey - 1].Data[0];
                NDistance[1] = AnimeData->ScalingData[ThisKey].Data[1] - AnimeData->ScalingData[ThisKey - 1].Data[1];
                NDistance[2] = AnimeData->ScalingData[ThisKey].Data[2] - AnimeData->ScalingData[ThisKey - 1].Data[2];


                TDistance = AnimeData->ScalingData[ThisKey].Time - AnimeData->ScalingData[ThisKey - 1].Time;
                RelativeT = Frame - AnimeData->ScalingData[ThisKey - 1].Time; //Get time relative to last keyframe;
                TRatio = ((float)RelativeT / (float)TDistance);
                LinearScaling[0] = AnimeData->ScalingData[ThisKey - 1].Data[0] + (short)(NDistance[0] * (TRatio));
                LinearScaling[1] = AnimeData->ScalingData[ThisKey - 1].Data[1] + (short)(NDistance[1] * (TRatio));
                LinearScaling[2] = AnimeData->ScalingData[ThisKey - 1].Data[2] + (short)(NDistance[2] * (TRatio));
                break;
            }
            if (Frame == KeyTime)
            {
                LinearScaling[0] = AnimeData->ScalingData[ThisKey].Data[0];
                LinearScaling[1] = AnimeData->ScalingData[ThisKey].Data[1];
                LinearScaling[2] = AnimeData->ScalingData[ThisKey].Data[2];
                break;
            }
            if (Frame > KeyTime)
            {   
                //continue;
            }
        }
    }
    
    

    
}


void SkeletalMatrix(PolyAnime* AnimeData, float Scale, int Frame)
{
    GetLinear(AnimeData, Scale, Frame);
    
    ObjectPosition[0] = (float)LinearTranslation[0] * 0.1f;
    ObjectPosition[1] = (float)LinearTranslation[1] * 0.1f;
    ObjectPosition[2] = (float)LinearTranslation[2] * 0.1f;
    
	
	ObjectAngle[0] = LinearRotation[0];
    ObjectAngle[1] = LinearRotation[1];
    ObjectAngle[2] = LinearRotation[2];

	//CreateModelMatrix(GlobalAffine,ObjectPosition,ObjectAngle);
	//Now apply the scaling size of the object to the matrix and add the drawing code of the 3D model to the F3D. 
	//ScaleMatrixXYZFixed(GlobalAffine,LinearScaling);

    
	//ScalingMatrix(GlobalAffine, Scale);
	


        guTranslate(&EntityMap[CurrentEntity[GlobalFrame % 2]],
                    (ObjectPosition[0]),
                    (ObjectPosition[1]),
                    (ObjectPosition[2]));
        gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
                  G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);

        guRotate(&EntityMap[CurrentEntity[GlobalFrame % 2]],
                 (float)(ObjectAngle[2] / 182.0f),
                 0.0f,
                 0.0f,
                 1.0f);

        gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
                  G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);

        guRotate(&EntityMap[CurrentEntity[GlobalFrame % 2]],
                 (float)(ObjectAngle[1] / 182.0f),
                 0.0f,
                 1.0f,
                 0.0f);

        gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
                  G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);

        guRotate(&EntityMap[CurrentEntity[GlobalFrame % 2]],
                 (float)(ObjectAngle[0] / 182.0f),
                 1.0f,
                 0.0f,
                 0.0f);

        gSPMatrix(glistp++, &EntityMap[CurrentEntity[GlobalFrame % 2]++],
                  G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    
                  
}
extern uint BodyBone_NodeList[];
extern PolyNode BodyBone_CyborgTP_Node;
void DrawAnime(PolyBone* BoneData, int CurrentFrame)
{


	PolyAnime* AnimeData = BoneData->AnimeData;

	
	uint* NodeArray = (uint*) BoneData->NodeOffset;
	
	SkeletalMatrix(AnimeData, 0.01f, CurrentFrame);
	uint LastTextureOffset = 0;

	for (int CurrentNode = 0; CurrentNode < BoneData->NodeCount; CurrentNode++)
	{	
		PolyNode* ThisNode = (PolyNode*)NodeArray[CurrentNode];

		//if (LastTextureOffset != ThisNode->TextureOffset)
		{
			//skip reloading identical textures

			if (ThisNode->TextureOffset != 0)
			{
				gSPDisplayList(glistp++, ThisNode->TextureOffset);						
				LastTextureOffset = ThisNode->TextureOffset;
			}
			
		}

		uint* MeshArray = (uint*) ThisNode->MeshOffsets;
		for (int CurrentMesh = 0; CurrentMesh < ThisNode->MeshCount; CurrentMesh++)
		{	
			gSPDisplayList(glistp++, MeshArray[CurrentMesh]);
		}
        
        if (ThisNode->ClosingDL != 0)
        {
            gSPDisplayList(glistp++, ThisNode->ClosingDL);
        }
	}

	
	
	uint* BoneArray = (uint*) BoneData->ChildOffset;
	for (int CurrentChild = 0; CurrentChild < BoneData->ChildCount; CurrentChild++)
	{
		PolyBone* ThisBone = (PolyBone*)BoneArray[CurrentChild];
		//Recursive Loop for all Children - 
		DrawAnime(ThisBone, CurrentFrame);
	}
    gSPPopMatrix(glistp++,G_MTX_MODELVIEW);
    gSPPopMatrix(glistp++,G_MTX_MODELVIEW);
    gSPPopMatrix(glistp++,G_MTX_MODELVIEW);
    gSPPopMatrix(glistp++,G_MTX_MODELVIEW);
}

void DrawHolster(AnimeHolster* HolsterData, int Frame)
{    
    
	PolyBone* BoneData = HolsterData->RootBone;
	//Begin DrawAnime loop for RootBone
	DrawAnime(BoneData, Frame);
	
	
}