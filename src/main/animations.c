
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
SVector* TranslationData;
SVector* AngleData;
SVector* ScalingData;




void SkeletalMatrix(PolyAnime* AnimeData, Vector Position, SVector Angle, float Scale, int Frame)
{

    ObjectPosition[0] = ((float)(AnimeData->PositionData[Frame][0]) * 0.1) ;
	ObjectPosition[1] = ((float)(AnimeData->PositionData[Frame][1]) * 0.1) ;
	ObjectPosition[2] = ((float)(AnimeData->PositionData[Frame][2]) * 0.1) ;
	
	
		

	ObjectAngle[0] = (AnimeData->AngleData[Frame][0] * DEG1);
	ObjectAngle[1] = (AnimeData->AngleData[Frame][1] * DEG1);
	ObjectAngle[2] = (AnimeData->AngleData[Frame][2] * DEG1);	

	//CreateModelMatrix(GlobalAffine,ObjectPosition,ObjectAngle);
	//Now apply the scaling size of the object to the matrix and add the drawing code of the 3D model to the F3D. 
	ScaleMatrixXYZFixed(GlobalAffine,AnimeData->ScalingData[Frame]);
	ScalingMatrix(GlobalAffine, Scale);
	


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
void DrawAnime(PolyBone* BoneData, int CurrentFrame, Vector BasePosition, SVector BaseAngle)
{


	PolyAnime* AnimeData = BoneData->AnimationOffset;

	
	uint* NodeArray = (uint*) BoneData->NodeOffset;
	
	SkeletalMatrix(AnimeData, BasePosition, BaseAngle, 0.1f, CurrentFrame);
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

	}

	
	
	uint* BoneArray = (uint*) BoneData->ChildOffset;
	for (int CurrentChild = 0; CurrentChild < BoneData->ChildCount; CurrentChild++)
	{
		PolyBone* ThisBone = (PolyBone*)BoneArray[CurrentChild];
		//Recursive Loop for all Children - 
		DrawAnime(ThisBone, CurrentFrame, BasePosition, BaseAngle);
	}
    gSPPopMatrix(glistp++,G_MTX_MODELVIEW);
    gSPPopMatrix(glistp++,G_MTX_MODELVIEW);
    gSPPopMatrix(glistp++,G_MTX_MODELVIEW);
    gSPPopMatrix(glistp++,G_MTX_MODELVIEW);
}

void DrawHolster(AnimeHolster* HolsterData, Vector BasePosition, SVector BaseAngle)
{    
	PolyBone* BoneData = HolsterData->RootBone;
	//Begin DrawAnime loop for RootBone
	DrawAnime(BoneData, (HolsterData->CurrentFrame), BasePosition, BaseAngle);
	
	
}