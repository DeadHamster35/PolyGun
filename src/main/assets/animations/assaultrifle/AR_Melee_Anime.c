//BodyBoneAnime File
//PolyTool Animation Version 1.0


#include <nusys.h>
#include <nualsgi_n.h>
#include "common.h"




//Keyframe Data


static PolyKeyFrame Hand_Translation[8] = 
{
	{0, {200,1700,-5000}, },
	{2, {200,1700,-5000}, },
	{3, {200,1700,-5000}, },
	{4, {200,1700,-5000}, },
	{7, {200,1700,-5000}, },
	{17, {200,1700,-5000}, },
	{23, {200,1700,-5000}, },
	{28, {200,1700,-5000}, }
};
static PolyKeyFrame Hand_Rotation[8] = 
{
	{0, {0,0,0}, },
	{2, {-593,9414,-8522}, },
	{3, {1607,4105,-10626}, },
	{4, {992,3402,-8150}, },
	{7, {956,3280,-7859}, },
	{17, {501,1718,-4116}, },
	{23, {-1966,1203,2845}, },
	{28, {0,0,0}, }
};
static PolyKeyFrame Hand_Scaling[8] = 
{
	{0, {10,10,10} },
	{2, {10,10,10} },
	{3, {10,10,10} },
	{4, {10,10,10} },
	{7, {10,10,10} },
	{17, {10,10,10} },
	{23, {10,10,10} },
	{28, {10,10,10} }
};


static PolyKeyFrame Elbow_Translation[10] = 
{
	{0, {-2700,-250,-3150}, },
	{1, {-2700,-250,-3150}, },
	{3, {-2700,-250,-3150}, },
	{4, {-2700,-250,-3150}, },
	{6, {-2700,-250,-3150}, },
	{12, {-2700,-250,-3150}, },
	{17, {-2700,-250,-3150}, },
	{23, {-2700,-250,-3150}, },
	{26, {-2700,-250,-3150}, },
	{28, {-2700,-250,-3150}, }
};
static PolyKeyFrame Elbow_Rotation[10] = 
{
	{0, {-1339,-2304,5631}, },
	{1, {388,-1012,4065}, },
	{3, {10696,-1601,-7}, },
	{4, {16611,6484,2185}, },
	{6, {12616,9149,685}, },
	{12, {12745,6614,2962}, },
	{17, {8360,-700,2545}, },
	{23, {766,-2208,3896}, },
	{26, {48,-864,6160}, },
	{28, {-1339,-2304,5631}, }
};
static PolyKeyFrame Elbow_Scaling[10] = 
{
	{0, {10,10,10} },
	{1, {10,10,10} },
	{3, {10,10,10} },
	{4, {10,10,10} },
	{6, {10,10,10} },
	{12, {10,10,10} },
	{17, {10,10,10} },
	{23, {10,10,10} },
	{26, {10,10,10} },
	{28, {10,10,10} }
};


static PolyKeyFrame Shoulder_Translation[9] = 
{
	{0, {-4000,1350,-2850}, },
	{2, {-4000,1350,-2850}, },
	{4, {-4000,1350,-2850}, },
	{6, {-4000,1350,-2850}, },
	{12, {-4000,1350,-2850}, },
	{17, {-4000,1350,-2850}, },
	{23, {-4000,1350,-2850}, },
	{26, {-4000,1350,-2850}, },
	{28, {-4000,1350,-2850}, }
};
static PolyKeyFrame Shoulder_Rotation[9] = 
{
	{0, {12607,-1919,-8009}, },
	{2, {15582,3094,-799}, },
	{4, {9152,4679,-2028}, },
	{6, {9275,4443,-2241}, },
	{12, {12293,3100,-517}, },
	{17, {10862,1413,-66}, },
	{23, {11814,-404,-4399}, },
	{26, {12607,-1919,-8009}, },
	{28, {12607,-1919,-8009}, }
};
static PolyKeyFrame Shoulder_Scaling[9] = 
{
	{0, {10,10,10} },
	{2, {10,10,10} },
	{4, {10,10,10} },
	{6, {10,10,10} },
	{12, {10,10,10} },
	{17, {10,10,10} },
	{23, {10,10,10} },
	{26, {10,10,10} },
	{28, {10,10,10} }
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


static PolyKeyFrame AR_Translation[8] = 
{
	{0, {2050,2150,-4150}, },
	{2, {2050,3470,-4150}, },
	{4, {2568,7166,-4150}, },
	{6, {2549,13423,-1255}, },
	{12, {2430,10739,-1945}, },
	{17, {2311,8055,-2634}, },
	{23, {2169,4834,-3461}, },
	{28, {2050,2150,-4150}, }
};
static PolyKeyFrame AR_Rotation[8] = 
{
	{0, {0,0,0}, },
	{2, {3287,-1827,5118}, },
	{4, {5883,-5952,10167}, },
	{6, {2973,-13189,15696}, },
	{12, {5693,-10182,10735}, },
	{17, {3914,-7000,7380}, },
	{23, {1779,-3182,3355}, },
	{28, {0,0,0}, }
};
static PolyKeyFrame AR_Scaling[8] = 
{
	{0, {10,10,10} },
	{2, {10,10,10} },
	{4, {10,10,10} },
	{6, {10,10,10} },
	{12, {10,10,10} },
	{17, {10,10,10} },
	{23, {10,10,10} },
	{28, {10,10,10} }
};


static PolyKeyFrame RightArm_Translation[10] = 
{
	{0, {2050,3200,-4150}, },
	{2, {1453,4456,-4150}, },
	{4, {3247,6075,-3205}, },
	{6, {3410,11501,-601}, },
	{11, {3087,9592,-1189}, },
	{15, {2763,7283,-1506}, },
	{21, {2496,3787,-1874}, },
	{23, {2857,3552,-1422}, },
	{26, {2050,4301,-4150}, },
	{28, {2050,3200,-4150}, }
};
static PolyKeyFrame RightArm_Rotation[10] = 
{
	{0, {0,0,0}, },
	{2, {3287,-1827,5118}, },
	{4, {10114,-9342,-9832}, },
	{6, {13445,-7656,-6330}, },
	{11, {12966,-5822,-9710}, },
	{15, {9873,-9419,-10092}, },
	{21, {9770,-6749,-15406}, },
	{23, {827,490,-8351}, },
	{26, {0,0,0}, },
	{28, {0,0,0}, }
};
static PolyKeyFrame RightArm_Scaling[10] = 
{
	{0, {10,10,10} },
	{2, {10,10,10} },
	{4, {10,10,10} },
	{6, {10,10,10} },
	{11, {10,10,10} },
	{15, {10,10,10} },
	{21, {10,10,10} },
	{23, {10,10,10} },
	{26, {10,10,10} },
	{28, {10,10,10} }
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
	.PositionCount = 8,
	.RotationCount = 8,
	.ScalingCount = 8,
};


static PolyAnime Elbow_Anime = 
{
	.PositionData = (PolyKeyFrame*)&Elbow_Translation,
	.RotationData = (PolyKeyFrame*)&Elbow_Rotation,
	.ScalingData = (PolyKeyFrame*)&Elbow_Scaling,
	.PositionCount = 10,
	.RotationCount = 10,
	.ScalingCount = 10,
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
	.PositionCount = 8,
	.RotationCount = 8,
	.ScalingCount = 8,
};


static PolyAnime RightArm_Anime = 
{
	.PositionData = (PolyKeyFrame*)&RightArm_Translation,
	.RotationData = (PolyKeyFrame*)&RightArm_Rotation,
	.ScalingData = (PolyKeyFrame*)&RightArm_Scaling,
	.PositionCount = 10,
	.RotationCount = 10,
	.ScalingCount = 10,
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
AnimeHolster AR_Melee =
{
	.RootBone = (PolyBone*)&BodyBone_Bone,
	.FrameCount = 29
};










