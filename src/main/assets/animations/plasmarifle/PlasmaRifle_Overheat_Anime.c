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


static PolyKeyFrame Elbow_Translation[9] = 
{
	{0, {-2700,-250,-3150}, },
	{7, {-2700,-250,-3150}, },
	{20, {-2700,-250,-3150}, },
	{26, {-2700,-250,-3150}, },
	{32, {-2700,-250,-3150}, },
	{38, {-2700,-250,-3150}, },
	{59, {-2700,-250,-3150}, },
	{95, {-2700,-250,-3150}, },
	{110, {-2700,-250,-3150}, }
};
static PolyKeyFrame Elbow_Rotation[9] = 
{
	{0, {-1884,-6738,6815}, },
	{7, {4726,-7601,3154}, },
	{20, {7472,-5917,-431}, },
	{26, {1508,4244,-7336}, },
	{32, {6431,-4488,-4664}, },
	{38, {2329,5176,-6430}, },
	{59, {4917,-407,-3411}, },
	{95, {4270,989,-4166}, },
	{110, {-2828,-6615,7338}, }
};
static PolyKeyFrame Elbow_Scaling[9] = 
{
	{0, {10,10,10} },
	{7, {10,10,10} },
	{20, {10,10,10} },
	{26, {10,10,10} },
	{32, {10,10,10} },
	{38, {10,10,10} },
	{59, {10,10,10} },
	{95, {10,10,10} },
	{110, {10,10,10} }
};


static PolyKeyFrame Shoulder_Translation[9] = 
{
	{0, {-4000,1350,-2850}, },
	{7, {-4000,1350,-2850}, },
	{20, {-4000,1350,-2850}, },
	{26, {-4000,1350,-2850}, },
	{32, {-4000,1350,-2850}, },
	{38, {-4000,1350,-2850}, },
	{59, {-4000,1350,-2850}, },
	{95, {-4000,1350,-2850}, },
	{110, {-4000,1350,-2850}, }
};
static PolyKeyFrame Shoulder_Rotation[9] = 
{
	{0, {7873,-6726,-6310}, },
	{7, {10217,327,-262}, },
	{20, {10032,-230,-739}, },
	{26, {12374,-773,-1157}, },
	{32, {9950,-478,-424}, },
	{38, {9800,-928,149}, },
	{59, {9917,-577,-298}, },
	{95, {9887,-664,-186}, },
	{110, {7873,-6726,-6310}, }
};
static PolyKeyFrame Shoulder_Scaling[9] = 
{
	{0, {10,10,10} },
	{7, {10,10,10} },
	{20, {10,10,10} },
	{26, {10,10,10} },
	{32, {10,10,10} },
	{38, {10,10,10} },
	{59, {10,10,10} },
	{95, {10,10,10} },
	{110, {10,10,10} }
};


static PolyKeyFrame LeftPort_Translation[5] = 
{
	{0, {150,150,1500}, },
	{5, {-249,173,1475}, },
	{79, {-238,173,1476}, },
	{85, {130,151,1499}, },
	{110, {150,150,1500}, }
};
static PolyKeyFrame LeftPort_Rotation[5] = 
{
	{0, {0,0,-910}, },
	{5, {0,0,-910}, },
	{79, {0,0,-910}, },
	{85, {0,0,-910}, },
	{110, {0,0,-910}, }
};
static PolyKeyFrame LeftPort_Scaling[5] = 
{
	{0, {10,10,10} },
	{5, {10,10,10} },
	{79, {10,10,10} },
	{85, {10,10,10} },
	{110, {10,10,10} }
};


static PolyKeyFrame RightPort_Translation[5] = 
{
	{0, {-150,150,1500}, },
	{5, {249,127,1525}, },
	{79, {238,127,1524}, },
	{85, {-130,149,1501}, },
	{110, {-150,150,1500}, }
};
static PolyKeyFrame RightPort_Rotation[5] = 
{
	{0, {0,0,-910}, },
	{5, {0,0,-910}, },
	{79, {0,0,-910}, },
	{85, {0,0,-910}, },
	{110, {0,0,-910}, }
};
static PolyKeyFrame RightPort_Scaling[5] = 
{
	{0, {10,10,10} },
	{5, {10,10,10} },
	{79, {10,10,10} },
	{85, {10,10,10} },
	{110, {10,10,10} }
};


static PolyKeyFrame PR_Translation[13] = 
{
	{0, {2150,5000,-2900}, },
	{7, {2260,5000,-1952}, },
	{10, {2259,5000,-2001}, },
	{13, {2258,5000,-2012}, },
	{16, {2257,5000,-2034}, },
	{21, {2257,5068,-2405}, },
	{29, {2255,5000,-2051}, },
	{35, {2256,5000,-2406}, },
	{45, {2256,5000,-2076}, },
	{79, {2248,5000,-2123}, },
	{83, {2247,5000,-2129}, },
	{98, {2246,5000,-2135}, },
	{110, {2150,5000,-2900}, }
};
static PolyKeyFrame PR_Rotation[13] = 
{
	{0, {0,0,910}, },
	{7, {4626,761,827}, },
	{10, {4366,-448,836}, },
	{13, {4554,882,558}, },
	{16, {4371,-929,830}, },
	{21, {2731,835,469}, },
	{29, {4350,-82,829}, },
	{35, {2609,889,810}, },
	{45, {4230,-72,829}, },
	{79, {3983,-73,835}, },
	{83, {4861,-1590,7}, },
	{98, {4606,-1211,215}, },
	{110, {0,0,910}, }
};
static PolyKeyFrame PR_Scaling[13] = 
{
	{0, {10,10,10} },
	{7, {10,10,10} },
	{10, {10,10,10} },
	{13, {10,10,10} },
	{16, {10,10,10} },
	{21, {10,10,10} },
	{29, {10,10,10} },
	{35, {10,10,10} },
	{45, {10,10,10} },
	{79, {10,10,10} },
	{83, {10,10,10} },
	{98, {10,10,10} },
	{110, {10,10,10} }
};


static PolyKeyFrame RightArm_Translation[13] = 
{
	{0, {2250,4900,-2800}, },
	{7, {2360,4900,-1852}, },
	{10, {2359,4900,-1901}, },
	{13, {2358,4900,-1912}, },
	{16, {2357,4900,-1934}, },
	{21, {2357,4968,-2305}, },
	{29, {2355,4900,-1951}, },
	{35, {2356,4900,-2306}, },
	{45, {2356,4900,-1976}, },
	{79, {2348,4900,-2023}, },
	{83, {2347,4900,-2029}, },
	{98, {2346,4900,-2035}, },
	{110, {2250,4900,-2800}, }
};
static PolyKeyFrame RightArm_Rotation[13] = 
{
	{0, {0,0,-1820}, },
	{7, {4305,1900,-1676}, },
	{10, {4341,663,-1655}, },
	{13, {4205,1999,-1956}, },
	{16, {4459,196,-1653}, },
	{21, {2432,1506,-2186}, },
	{29, {4238,1012,-1664}, },
	{35, {2299,1527,-1852}, },
	{45, {4119,993,-1675}, },
	{79, {3880,930,-1680}, },
	{83, {5086,-342,-2402}, },
	{98, {4749,-33,-2222}, },
	{110, {0,0,-1820}, }
};
static PolyKeyFrame RightArm_Scaling[13] = 
{
	{0, {10,10,10} },
	{7, {10,10,10} },
	{10, {10,10,10} },
	{13, {10,10,10} },
	{16, {10,10,10} },
	{21, {10,10,10} },
	{29, {10,10,10} },
	{35, {10,10,10} },
	{45, {10,10,10} },
	{79, {10,10,10} },
	{83, {10,10,10} },
	{98, {10,10,10} },
	{110, {10,10,10} }
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
	.PositionCount = 9,
	.RotationCount = 9,
	.ScalingCount = 9,
};


static PolyAnime Shoulder_Anime = 
{
	.PositionData = (PolyKeyFrame*)&Shoulder_Translation,
	.RotationData = (PolyKeyFrame*)&Shoulder_Rotation,
	.ScalingData = (PolyKeyFrame*)&Shoulder_Scaling,
	.PositionCount = 9,
	.RotationCount = 9,
	.ScalingCount = 9,
};


static PolyAnime LeftPort_Anime = 
{
	.PositionData = (PolyKeyFrame*)&LeftPort_Translation,
	.RotationData = (PolyKeyFrame*)&LeftPort_Rotation,
	.ScalingData = (PolyKeyFrame*)&LeftPort_Scaling,
	.PositionCount = 5,
	.RotationCount = 5,
	.ScalingCount = 5,
};


static PolyAnime RightPort_Anime = 
{
	.PositionData = (PolyKeyFrame*)&RightPort_Translation,
	.RotationData = (PolyKeyFrame*)&RightPort_Rotation,
	.ScalingData = (PolyKeyFrame*)&RightPort_Scaling,
	.PositionCount = 5,
	.RotationCount = 5,
	.ScalingCount = 5,
};


static PolyAnime PR_Anime = 
{
	.PositionData = (PolyKeyFrame*)&PR_Translation,
	.RotationData = (PolyKeyFrame*)&PR_Rotation,
	.ScalingData = (PolyKeyFrame*)&PR_Scaling,
	.PositionCount = 13,
	.RotationCount = 13,
	.ScalingCount = 13,
};


static PolyAnime RightArm_Anime = 
{
	.PositionData = (PolyKeyFrame*)&RightArm_Translation,
	.RotationData = (PolyKeyFrame*)&RightArm_Rotation,
	.ScalingData = (PolyKeyFrame*)&RightArm_Scaling,
	.PositionCount = 13,
	.RotationCount = 13,
	.ScalingCount = 13,
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
AnimeHolster PlasmaRifle_Overheat =
{
	.RootBone = (PolyBone*)&BodyBone_Bone,
	.FrameCount = 111,
    .ActionFrame = 100
};










