//BodyBoneAnime File
//PolyTool Animation Version 1.0


#include <nusys.h>
#include <nualsgi_n.h>
#include "common.h"




//Keyframe Data


static PolyKeyFrame Hand_Translation[6] = 
{
	{0, {200,1700,-5000}, },
	{2, {200,1700,-5000}, },
	{4, {200,1700,-5000}, },
	{8, {200,1700,-5000}, },
	{48, {200,1700,-5000}, },
	{50, {200,1700,-5000}, }
};
static PolyKeyFrame Hand_Rotation[6] = 
{
	{0, {0,0,0}, },
	{2, {0,0,0}, },
	{4, {-2323,5334,-6101}, },
	{8, {-1906,4332,-6461}, },
	{48, {0,0,0}, },
	{50, {0,0,0}, }
};
static PolyKeyFrame Hand_Scaling[6] = 
{
	{0, {10,10,10} },
	{2, {10,10,10} },
	{4, {10,10,10} },
	{8, {10,10,10} },
	{48, {10,10,10} },
	{50, {10,10,10} }
};


static PolyKeyFrame Elbow_Translation[6] = 
{
	{0, {-2700,-250,-3150}, },
	{2, {-2700,-250,-3150}, },
	{4, {-2700,-250,-3150}, },
	{8, {-2700,-250,-3150}, },
	{48, {-2700,-250,-3150}, },
	{50, {-2700,-250,-3150}, }
};
static PolyKeyFrame Elbow_Rotation[6] = 
{
	{0, {185,-4671,2728}, },
	{2, {6212,-784,-6492}, },
	{4, {6883,5135,-10652}, },
	{8, {8608,-1506,-7493}, },
	{48, {-2828,-6615,7338}, },
	{50, {-2828,-6615,7338}, }
};
static PolyKeyFrame Elbow_Scaling[6] = 
{
	{0, {10,10,10} },
	{2, {10,10,10} },
	{4, {10,10,10} },
	{8, {10,10,10} },
	{48, {10,10,10} },
	{50, {10,10,10} }
};


static PolyKeyFrame Shoulder_Translation[10] = 
{
	{0, {-4000,1350,-2850}, },
	{2, {-4000,1350,-2850}, },
	{4, {-4000,1350,-2850}, },
	{8, {-4000,1350,-2850}, },
	{13, {-4000,1350,-2850}, },
	{17, {-4000,1350,-2850}, },
	{33, {-4000,1350,-2850}, },
	{43, {-4000,1350,-2850}, },
	{48, {-4000,1350,-2850}, },
	{50, {-4000,1350,-2850}, }
};
static PolyKeyFrame Shoulder_Rotation[10] = 
{
	{0, {7873,-6726,-6310}, },
	{2, {13216,-201,-2420}, },
	{4, {14411,0,-4200}, },
	{8, {12207,611,6737}, },
	{13, {9080,497,13745}, },
	{17, {3765,4129,7054}, },
	{33, {8276,-4319,-808}, },
	{43, {7873,-6726,-6310}, },
	{48, {7873,-6726,-6310}, },
	{50, {7873,-6726,-6310}, }
};
static PolyKeyFrame Shoulder_Scaling[10] = 
{
	{0, {10,10,10} },
	{2, {10,10,10} },
	{4, {10,10,10} },
	{8, {10,10,10} },
	{13, {10,10,10} },
	{17, {10,10,10} },
	{33, {10,10,10} },
	{43, {10,10,10} },
	{48, {10,10,10} },
	{50, {10,10,10} }
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


static PolyKeyFrame PR_Translation[14] = 
{
	{0, {2150,5000,-2900}, },
	{2, {3245,4513,2792}, },
	{4, {4183,1801,5060}, },
	{7, {3200,5581,3188}, },
	{8, {89,8103,-978}, },
	{11, {-148,7960,-8405}, },
	{14, {-798,5742,-7889}, },
	{20, {-1314,6707,-6284}, },
	{30, {548,5488,-2756}, },
	{34, {1057,5000,-2249}, },
	{37, {1525,5000,-2223}, },
	{41, {2150,5000,-2900}, },
	{48, {2150,5000,-2900}, },
	{50, {2150,5000,-2900}, }
};
static PolyKeyFrame PR_Rotation[14] = 
{
	{0, {0,0,910}, },
	{2, {11035,-590,2448}, },
	{4, {11758,-811,2338}, },
	{7, {16098,-1703,1767}, },
	{8, {5628,571,5618}, },
	{11, {-2824,-164,5205}, },
	{14, {-4009,-3521,12439}, },
	{20, {-2020,-1906,9674}, },
	{30, {1375,-1061,8426}, },
	{34, {2733,-723,6289}, },
	{37, {1562,-413,4919}, },
	{41, {0,0,910}, },
	{48, {0,0,910}, },
	{50, {0,0,910}, }
};
static PolyKeyFrame PR_Scaling[14] = 
{
	{0, {10,10,10} },
	{2, {10,10,10} },
	{4, {10,10,10} },
	{7, {10,10,10} },
	{8, {10,10,10} },
	{11, {10,10,10} },
	{14, {10,10,10} },
	{20, {10,10,10} },
	{30, {10,10,10} },
	{34, {10,10,10} },
	{37, {10,10,10} },
	{41, {10,10,10} },
	{48, {10,10,10} },
	{50, {10,10,10} }
};


static PolyKeyFrame RightArm_Translation[14] = 
{
	{0, {2250,4900,-2800}, },
	{2, {3345,4413,2892}, },
	{4, {4283,1701,5160}, },
	{7, {3300,5481,3288}, },
	{8, {189,8003,-878}, },
	{11, {-48,7860,-8305}, },
	{14, {-698,5642,-7789}, },
	{20, {-1214,6607,-6184}, },
	{30, {648,5388,-2656}, },
	{34, {1157,4900,-2149}, },
	{37, {1625,4900,-2123}, },
	{41, {2250,4900,-2800}, },
	{48, {2250,4900,-2800}, },
	{50, {2250,4900,-2800}, }
};
static PolyKeyFrame RightArm_Rotation[14] = 
{
	{0, {0,0,-1820}, },
	{2, {10957,1788,1101}, },
	{4, {11715,1627,1191}, },
	{7, {16103,964,1718}, },
	{8, {5375,1903,3438}, },
	{11, {-2705,-776,2758}, },
	{14, {-3048,-4317,9852}, },
	{20, {-1515,-2278,7117}, },
	{30, {1585,-651,5813}, },
	{34, {2825,0,3654}, },
	{37, {1614,0,2244}, },
	{41, {0,0,-1820}, },
	{48, {0,0,-1820}, },
	{50, {0,0,-1820}, }
};
static PolyKeyFrame RightArm_Scaling[14] = 
{
	{0, {10,10,10} },
	{2, {10,10,10} },
	{4, {10,10,10} },
	{7, {10,10,10} },
	{8, {10,10,10} },
	{11, {10,10,10} },
	{14, {10,10,10} },
	{20, {10,10,10} },
	{30, {10,10,10} },
	{34, {10,10,10} },
	{37, {10,10,10} },
	{41, {10,10,10} },
	{48, {10,10,10} },
	{50, {10,10,10} }
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
	.PositionCount = 6,
	.RotationCount = 6,
	.ScalingCount = 6,
};


static PolyAnime Elbow_Anime = 
{
	.PositionData = (PolyKeyFrame*)&Elbow_Translation,
	.RotationData = (PolyKeyFrame*)&Elbow_Rotation,
	.ScalingData = (PolyKeyFrame*)&Elbow_Scaling,
	.PositionCount = 6,
	.RotationCount = 6,
	.ScalingCount = 6,
};


static PolyAnime Shoulder_Anime = 
{
	.PositionData = (PolyKeyFrame*)&Shoulder_Translation,
	.RotationData = (PolyKeyFrame*)&Shoulder_Rotation,
	.ScalingData = (PolyKeyFrame*)&Shoulder_Scaling,
	.PositionCount = 10,
	.RotationCount = 10,
	.ScalingCount = 10,
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
	.PositionCount = 14,
	.RotationCount = 14,
	.ScalingCount = 14,
};


static PolyAnime RightArm_Anime = 
{
	.PositionData = (PolyKeyFrame*)&RightArm_Translation,
	.RotationData = (PolyKeyFrame*)&RightArm_Rotation,
	.ScalingData = (PolyKeyFrame*)&RightArm_Scaling,
	.PositionCount = 14,
	.RotationCount = 14,
	.ScalingCount = 14,
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
AnimeHolster PlasmaRifle_Melee =
{
	.RootBone = (PolyBone*)&BodyBone_Bone,
	.FrameCount = 51,
    .ActionFrame = 0
};










