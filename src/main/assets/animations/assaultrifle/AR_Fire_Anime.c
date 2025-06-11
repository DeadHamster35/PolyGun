//BodyBoneAnime File
//PolyTool Animation Version 1.0


#include <nusys.h>
#include <nualsgi_n.h>
#include "common.h"




//Keyframe Data


static PolyKeyFrame Hand_Translation[1] = 
{
	{0, {200,1700,-5000}, }
};
static PolyKeyFrame Hand_Rotation[1] = 
{
	{0, {0,0,0}, }
};
static PolyKeyFrame Hand_Scaling[1] = 
{
	{0, {10,10,10} }
};


static PolyKeyFrame Elbow_Translation[1] = 
{
	{0, {-2700,-250,-3150}, }
};
static PolyKeyFrame Elbow_Rotation[1] = 
{
	{0, {-1339,-2304,5631}, }
};
static PolyKeyFrame Elbow_Scaling[1] = 
{
	{0, {10,10,10} }
};


static PolyKeyFrame Shoulder_Translation[1] = 
{
	{0, {-4000,1350,-2850}, }
};
static PolyKeyFrame Shoulder_Rotation[1] = 
{
	{0, {12607,-1919,-8009}, }
};
static PolyKeyFrame Shoulder_Scaling[1] = 
{
	{0, {10,10,10} }
};


static PolyKeyFrame ChargingPort_Translation[1] = 
{
	{0, {-100,1250,2200}, }
};
static PolyKeyFrame ChargingPort_Rotation[1] = 
{
	{0, {0,0,0}, }
};
static PolyKeyFrame ChargingPort_Scaling[1] = 
{
	{0, {10,10,10} }
};


static PolyKeyFrame Magazine_Translation[1] = 
{
	{0, {0,-2000,-1200}, }
};
static PolyKeyFrame Magazine_Rotation[1] = 
{
	{0, {0,0,0}, }
};
static PolyKeyFrame Magazine_Scaling[1] = 
{
	{0, {10,10,10} }
};


static PolyKeyFrame AR_Translation[1] = 
{
	{0, {2050,2150,-4150}, }
};
static PolyKeyFrame AR_Rotation[1] = 
{
	{0, {0,0,0}, }
};
static PolyKeyFrame AR_Scaling[1] = 
{
	{0, {10,10,10} }
};


static PolyKeyFrame RightArm_Translation[1] = 
{
	{0, {2050,3200,-4150}, }
};
static PolyKeyFrame RightArm_Rotation[1] = 
{
	{0, {0,0,0}, }
};
static PolyKeyFrame RightArm_Scaling[1] = 
{
	{0, {10,10,10} }
};


static PolyKeyFrame BodyBone_Translation[1] = 
{
	{0, {0,0,0}, }
};
static PolyKeyFrame BodyBone_Rotation[1] = 
{
	{0, {0,0,0}, }
};
static PolyKeyFrame BodyBone_Scaling[1] = 
{
	{0, {10,10,10} }
};








//Anime Structs


static PolyAnime Hand_Anime = 
{
	.PositionData = (PolyKeyFrame*)&Hand_Translation,
	.RotationData = (PolyKeyFrame*)&Hand_Rotation,
	.ScalingData = (PolyKeyFrame*)&Hand_Scaling,
	.PositionCount = 1,
	.RotationCount = 1,
	.ScalingCount = 1,
};


static PolyAnime Elbow_Anime = 
{
	.PositionData = (PolyKeyFrame*)&Elbow_Translation,
	.RotationData = (PolyKeyFrame*)&Elbow_Rotation,
	.ScalingData = (PolyKeyFrame*)&Elbow_Scaling,
	.PositionCount = 1,
	.RotationCount = 1,
	.ScalingCount = 1,
};


static PolyAnime Shoulder_Anime = 
{
	.PositionData = (PolyKeyFrame*)&Shoulder_Translation,
	.RotationData = (PolyKeyFrame*)&Shoulder_Rotation,
	.ScalingData = (PolyKeyFrame*)&Shoulder_Scaling,
	.PositionCount = 1,
	.RotationCount = 1,
	.ScalingCount = 1,
};


static PolyAnime ChargingPort_Anime = 
{
	.PositionData = (PolyKeyFrame*)&ChargingPort_Translation,
	.RotationData = (PolyKeyFrame*)&ChargingPort_Rotation,
	.ScalingData = (PolyKeyFrame*)&ChargingPort_Scaling,
	.PositionCount = 1,
	.RotationCount = 1,
	.ScalingCount = 1,
};


static PolyAnime Magazine_Anime = 
{
	.PositionData = (PolyKeyFrame*)&Magazine_Translation,
	.RotationData = (PolyKeyFrame*)&Magazine_Rotation,
	.ScalingData = (PolyKeyFrame*)&Magazine_Scaling,
	.PositionCount = 1,
	.RotationCount = 1,
	.ScalingCount = 1,
};


static PolyAnime AR_Anime = 
{
	.PositionData = (PolyKeyFrame*)&AR_Translation,
	.RotationData = (PolyKeyFrame*)&AR_Rotation,
	.ScalingData = (PolyKeyFrame*)&AR_Scaling,
	.PositionCount = 1,
	.RotationCount = 1,
	.ScalingCount = 1,
};


static PolyAnime RightArm_Anime = 
{
	.PositionData = (PolyKeyFrame*)&RightArm_Translation,
	.RotationData = (PolyKeyFrame*)&RightArm_Rotation,
	.ScalingData = (PolyKeyFrame*)&RightArm_Scaling,
	.PositionCount = 1,
	.RotationCount = 1,
	.ScalingCount = 1,
};


static PolyAnime BodyBone_Anime = 
{
	.PositionData = (PolyKeyFrame*)&BodyBone_Translation,
	.RotationData = (PolyKeyFrame*)&BodyBone_Rotation,
	.ScalingData = (PolyKeyFrame*)&BodyBone_Scaling,
	.PositionCount = 1,
	.RotationCount = 1,
	.ScalingCount = 1,
};








//Model Node Lists
static PolyNode Hand_ar_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};


static uint Hand_CyborgTP_MeshList[] = 
{
	(uint)&Draw_LeftHand_M
};




static PolyNode Hand_CyborgTP_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_CyborgTP_T,
	.MeshOffsets = (uint*)&Hand_CyborgTP_MeshList,
	.ClosingDL = (uint)&Draw_CyborgTP_T_Closing,
};




static uint Hand_NodeList[] = 
{
	(uint)&Hand_ar_Node,
	(uint)&Hand_CyborgTP_Node,
};


static PolyNode Elbow_ar_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};


static uint Elbow_CyborgTP_MeshList[] = 
{
	(uint)&Draw_LeftArm_M
};




static PolyNode Elbow_CyborgTP_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_CyborgTP_T,
	.MeshOffsets = (uint*)&Elbow_CyborgTP_MeshList,
	.ClosingDL = (uint)&Draw_CyborgTP_T_Closing,
};




static uint Elbow_NodeList[] = 
{
	(uint)&Elbow_ar_Node,
	(uint)&Elbow_CyborgTP_Node,
};


static PolyNode Shoulder_ar_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};


static uint Shoulder_CyborgTP_MeshList[] = 
{
	(uint)&Draw_LeftShoulder_M
};




static PolyNode Shoulder_CyborgTP_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_CyborgTP_T,
	.MeshOffsets = (uint*)&Shoulder_CyborgTP_MeshList,
	.ClosingDL = (uint)&Draw_CyborgTP_T_Closing,
};




static uint Shoulder_NodeList[] = 
{
	(uint)&Shoulder_ar_Node,
	(uint)&Shoulder_CyborgTP_Node,
};


static uint ChargingPort_ar_MeshList[] = 
{
	(uint)&Draw_Charging_M
};




static PolyNode ChargingPort_ar_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_ar_T,
	.MeshOffsets = (uint*)&ChargingPort_ar_MeshList,
	.ClosingDL = (uint)&Draw_ar_T_Closing,
};


static PolyNode ChargingPort_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint ChargingPort_NodeList[] = 
{
	(uint)&ChargingPort_ar_Node,
	(uint)&ChargingPort_CyborgTP_Node,
};


static uint Magazine_ar_MeshList[] = 
{
	(uint)&Draw_Magazine_M
};




static PolyNode Magazine_ar_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_ar_T,
	.MeshOffsets = (uint*)&Magazine_ar_MeshList,
	.ClosingDL = (uint)&Draw_ar_T_Closing,
};


static PolyNode Magazine_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint Magazine_NodeList[] = 
{
	(uint)&Magazine_ar_Node,
	(uint)&Magazine_CyborgTP_Node,
};


static uint AR_ar_MeshList[] = 
{
	(uint)&Draw_Assault_Rifle_M
};




static PolyNode AR_ar_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_ar_T,
	.MeshOffsets = (uint*)&AR_ar_MeshList,
	.ClosingDL = (uint)&Draw_ar_T_Closing,
};


static PolyNode AR_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint AR_NodeList[] = 
{
	(uint)&AR_ar_Node,
	(uint)&AR_CyborgTP_Node,
};


static PolyNode RightArm_ar_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};


static uint RightArm_CyborgTP_MeshList[] = 
{
	(uint)&Draw_RightArm_M
};




static PolyNode RightArm_CyborgTP_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_CyborgTP_T,
	.MeshOffsets = (uint*)&RightArm_CyborgTP_MeshList,
	.ClosingDL = (uint)&Draw_CyborgTP_T_Closing,
};




static uint RightArm_NodeList[] = 
{
	(uint)&RightArm_ar_Node,
	(uint)&RightArm_CyborgTP_Node,
};


static PolyNode BodyBone_ar_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};


static PolyNode BodyBone_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint BodyBone_NodeList[] = 
{
	(uint)&BodyBone_ar_Node,
	(uint)&BodyBone_CyborgTP_Node,
};










//PolyBone Structs




static PolyBone Hand_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&Hand_Anime,
	.NodeCount = 2,
	.NodeOffset = (PolyNode*)Hand_NodeList,
	.ChildCount = 0,
	.ChildOffset = (struct PolyBone*)0
};




// ChildArray
static PolyBone* Elbow_ChildList[] = 
{
	(PolyBone*)&Hand_Bone,
};
// PolyBone
static PolyBone Elbow_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&Elbow_Anime,
	.NodeCount = 2,
	.NodeOffset = (PolyNode*)Elbow_NodeList,
	.ChildCount = 1,
	.ChildOffset = (struct PolyBone*)Elbow_ChildList,
};




// ChildArray
static PolyBone* Shoulder_ChildList[] = 
{
	(PolyBone*)&Elbow_Bone,
};
// PolyBone
static PolyBone Shoulder_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&Shoulder_Anime,
	.NodeCount = 2,
	.NodeOffset = (PolyNode*)Shoulder_NodeList,
	.ChildCount = 1,
	.ChildOffset = (struct PolyBone*)Shoulder_ChildList,
};




static PolyBone ChargingPort_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&ChargingPort_Anime,
	.NodeCount = 2,
	.NodeOffset = (PolyNode*)ChargingPort_NodeList,
	.ChildCount = 0,
	.ChildOffset = (struct PolyBone*)0
};




static PolyBone Magazine_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&Magazine_Anime,
	.NodeCount = 2,
	.NodeOffset = (PolyNode*)Magazine_NodeList,
	.ChildCount = 0,
	.ChildOffset = (struct PolyBone*)0
};




// ChildArray
static PolyBone* AR_ChildList[] = 
{
	(PolyBone*)&ChargingPort_Bone,
	(PolyBone*)&Magazine_Bone,
};
// PolyBone
static PolyBone AR_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&AR_Anime,
	.NodeCount = 2,
	.NodeOffset = (PolyNode*)AR_NodeList,
	.ChildCount = 2,
	.ChildOffset = (struct PolyBone*)AR_ChildList,
};




static PolyBone RightArm_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&RightArm_Anime,
	.NodeCount = 2,
	.NodeOffset = (PolyNode*)RightArm_NodeList,
	.ChildCount = 0,
	.ChildOffset = (struct PolyBone*)0
};




// ChildArray
static PolyBone* BodyBone_ChildList[] = 
{
	(PolyBone*)&Shoulder_Bone,
	(PolyBone*)&AR_Bone,
	(PolyBone*)&RightArm_Bone,
};
// PolyBone
static PolyBone BodyBone_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&BodyBone_Anime,
	.NodeCount = 2,
	.NodeOffset = (PolyNode*)BodyBone_NodeList,
	.ChildCount = 3,
	.ChildOffset = (struct PolyBone*)BodyBone_ChildList,
};






//AnimeHolster
AnimeHolster AR_Fire =
{
	.RootBone = (PolyBone*)&BodyBone_Bone,
	.FrameCount = 2
};










