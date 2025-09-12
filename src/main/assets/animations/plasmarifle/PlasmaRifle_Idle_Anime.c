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


static PolyKeyFrame Elbow_Translation[4] = 
{
	{0, {-2700,-250,-3150}, },
	{20, {-2700,-250,-3150}, },
	{40, {-2700,-250,-3150}, },
	{60, {-2700,-250,-3150}, }
};
static PolyKeyFrame Elbow_Rotation[1] = 
{
	{0, {-2828,-6615,7338}, }
};
static PolyKeyFrame Elbow_Scaling[1] = 
{
	{0, {10,10,10} }
};


static PolyKeyFrame Shoulder_Translation[1] = 
{
	{0, {-4000,1350,-2850}, }
};
static PolyKeyFrame Shoulder_Rotation[4] = 
{
	{0, {7873,-6726,-6310}, },
	{20, {8020,-6644,-6397}, },
	{40, {7873,-6726,-6310}, },
	{60, {7873,-6726,-6310}, }
};
static PolyKeyFrame Shoulder_Scaling[1] = 
{
	{0, {10,10,10} }
};


static PolyKeyFrame LeftPort_Translation[1] = 
{
	{0, {150,150,1500}, }
};
static PolyKeyFrame LeftPort_Rotation[1] = 
{
	{0, {0,0,-910}, }
};
static PolyKeyFrame LeftPort_Scaling[1] = 
{
	{0, {10,10,10} }
};


static PolyKeyFrame RightPort_Translation[1] = 
{
	{0, {-150,150,1500}, }
};
static PolyKeyFrame RightPort_Rotation[1] = 
{
	{0, {0,0,-910}, }
};
static PolyKeyFrame RightPort_Scaling[1] = 
{
	{0, {10,10,10} }
};


static PolyKeyFrame PR_Translation[3] = 
{
	{0, {2150,5000,-2900}, },
	{30, {2150,5000,-2934}, },
	{60, {2150,5000,-2900}, }
};
static PolyKeyFrame PR_Rotation[3] = 
{
	{0, {0,0,910}, },
	{30, {-115,10,910}, },
	{60, {0,0,910}, }
};
static PolyKeyFrame PR_Scaling[1] = 
{
	{0, {10,10,10} }
};


static PolyKeyFrame RightArm_Translation[3] = 
{
	{0, {2250,4900,-2800}, },
	{30, {2250,4900,-2834}, },
	{60, {2250,4900,-2800}, }
};
static PolyKeyFrame RightArm_Rotation[3] = 
{
	{0, {0,0,-1820}, },
	{30, {-113,-20,-1820}, },
	{60, {0,0,-1820}, }
};
static PolyKeyFrame RightArm_Scaling[3] = 
{
	{0, {10,10,10} },
	{30, {10,10,10} },
	{60, {10,10,10} }
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
	.PositionCount = 4,
	.RotationCount = 1,
	.ScalingCount = 1,
};


static PolyAnime Shoulder_Anime = 
{
	.PositionData = (PolyKeyFrame*)&Shoulder_Translation,
	.RotationData = (PolyKeyFrame*)&Shoulder_Rotation,
	.ScalingData = (PolyKeyFrame*)&Shoulder_Scaling,
	.PositionCount = 1,
	.RotationCount = 4,
	.ScalingCount = 1,
};


static PolyAnime LeftPort_Anime = 
{
	.PositionData = (PolyKeyFrame*)&LeftPort_Translation,
	.RotationData = (PolyKeyFrame*)&LeftPort_Rotation,
	.ScalingData = (PolyKeyFrame*)&LeftPort_Scaling,
	.PositionCount = 1,
	.RotationCount = 1,
	.ScalingCount = 1,
};


static PolyAnime RightPort_Anime = 
{
	.PositionData = (PolyKeyFrame*)&RightPort_Translation,
	.RotationData = (PolyKeyFrame*)&RightPort_Rotation,
	.ScalingData = (PolyKeyFrame*)&RightPort_Scaling,
	.PositionCount = 1,
	.RotationCount = 1,
	.ScalingCount = 1,
};


static PolyAnime PR_Anime = 
{
	.PositionData = (PolyKeyFrame*)&PR_Translation,
	.RotationData = (PolyKeyFrame*)&PR_Rotation,
	.ScalingData = (PolyKeyFrame*)&PR_Scaling,
	.PositionCount = 3,
	.RotationCount = 3,
	.ScalingCount = 1,
};


static PolyAnime RightArm_Anime = 
{
	.PositionData = (PolyKeyFrame*)&RightArm_Translation,
	.RotationData = (PolyKeyFrame*)&RightArm_Rotation,
	.ScalingData = (PolyKeyFrame*)&RightArm_Scaling,
	.PositionCount = 3,
	.RotationCount = 3,
	.ScalingCount = 3,
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
static PolyNode Hand_PlasmaRifleIntensity_Node = 
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
	(uint)&Hand_PlasmaRifleIntensity_Node,
	(uint)&Hand_CyborgTP_Node,
};


static PolyNode Elbow_PlasmaRifleIntensity_Node = 
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
	(uint)&Elbow_PlasmaRifleIntensity_Node,
	(uint)&Elbow_CyborgTP_Node,
};


static PolyNode Shoulder_PlasmaRifleIntensity_Node = 
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
	(uint)&Shoulder_PlasmaRifleIntensity_Node,
	(uint)&Shoulder_CyborgTP_Node,
};


static uint LeftPort_PlasmaRifleIntensity_MeshList[] = 
{
	(uint)&Draw_LeftCover_M
};




static PolyNode LeftPort_PlasmaRifleIntensity_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_PlasmaRifleIntensity_T,
	.MeshOffsets = (uint*)&LeftPort_PlasmaRifleIntensity_MeshList,
	.ClosingDL = (uint)&Draw_PlasmaRifleIntensity_T_Closing,
};


static PolyNode LeftPort_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint LeftPort_NodeList[] = 
{
	(uint)&LeftPort_PlasmaRifleIntensity_Node,
	(uint)&LeftPort_CyborgTP_Node,
};


static uint RightPort_PlasmaRifleIntensity_MeshList[] = 
{
	(uint)&Draw_RightCover_M
};




static PolyNode RightPort_PlasmaRifleIntensity_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_PlasmaRifleIntensity_T,
	.MeshOffsets = (uint*)&RightPort_PlasmaRifleIntensity_MeshList,
	.ClosingDL = (uint)&Draw_PlasmaRifleIntensity_T_Closing,
};


static PolyNode RightPort_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint RightPort_NodeList[] = 
{
	(uint)&RightPort_PlasmaRifleIntensity_Node,
	(uint)&RightPort_CyborgTP_Node,
};


static uint PR_PlasmaRifleIntensity_MeshList[] = 
{
	(uint)&Draw_PlasmaRifle_M
};




static PolyNode PR_PlasmaRifleIntensity_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_PlasmaRifleIntensity_T,
	.MeshOffsets = (uint*)&PR_PlasmaRifleIntensity_MeshList,
	.ClosingDL = (uint)&Draw_PlasmaRifleIntensity_T_Closing,
};


static PolyNode PR_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint PR_NodeList[] = 
{
	(uint)&PR_PlasmaRifleIntensity_Node,
	(uint)&PR_CyborgTP_Node,
};


static PolyNode RightArm_PlasmaRifleIntensity_Node = 
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
	(uint)&RightArm_PlasmaRifleIntensity_Node,
	(uint)&RightArm_CyborgTP_Node,
};


static PolyNode BodyBone_PlasmaRifleIntensity_Node = 
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
	(uint)&BodyBone_PlasmaRifleIntensity_Node,
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




static PolyBone LeftPort_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&LeftPort_Anime,
	.NodeCount = 2,
	.NodeOffset = (PolyNode*)LeftPort_NodeList,
	.ChildCount = 0,
	.ChildOffset = (struct PolyBone*)0
};




static PolyBone RightPort_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&RightPort_Anime,
	.NodeCount = 2,
	.NodeOffset = (PolyNode*)RightPort_NodeList,
	.ChildCount = 0,
	.ChildOffset = (struct PolyBone*)0
};




// ChildArray
static PolyBone* PR_ChildList[] = 
{
	(PolyBone*)&LeftPort_Bone,
	(PolyBone*)&RightPort_Bone,
};
// PolyBone
static PolyBone PR_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&PR_Anime,
	.NodeCount = 2,
	.NodeOffset = (PolyNode*)PR_NodeList,
	.ChildCount = 2,
	.ChildOffset = (struct PolyBone*)PR_ChildList,
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
	(PolyBone*)&PR_Bone,
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
AnimeHolster PlasmaRifle_Idle =
{
	.RootBone = (PolyBone*)&BodyBone_Bone,
	.FrameCount = 61,
    .ActionFrame = 0
};










