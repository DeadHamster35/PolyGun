//BodyBoneAnime File
//PolyTool Animation Version 1.0


#include <nusys.h>
#include <nualsgi_n.h>
#include "common.h"




//Keyframe Data


static PolyKeyFrame Hand_Translation[12] = 
{
	{0, {200,1700,-5000}, },
	{3, {200,1700,-5000}, },
	{5, {200,1700,-5000}, },
	{18, {200,1700,-5000}, },
	{23, {200,1700,-5000}, },
	{26, {200,1700,-5000}, },
	{30, {200,1700,-5000}, },
	{35, {200,1700,-5000}, },
	{40, {200,1700,-5000}, },
	{45, {200,1700,-5000}, },
	{50, {200,1700,-5000}, },
	{60, {200,1700,-5000}, }
};
static PolyKeyFrame Hand_Rotation[12] = 
{
	{0, {1298,3173,-2211}, },
	{3, {-1885,5006,-2941}, },
	{5, {1298,3173,-2211}, },
	{18, {1298,3173,-2211}, },
	{23, {1298,3173,-2211}, },
	{26, {1298,3173,-2211}, },
	{30, {1298,3173,-2211}, },
	{35, {1298,3173,-2211}, },
	{40, {1298,3173,-2211}, },
	{45, {1298,3173,-2211}, },
	{50, {1298,3173,-2211}, },
	{60, {1298,3173,-2211}, }
};
static PolyKeyFrame Hand_Scaling[12] = 
{
	{0, {10,10,10} },
	{3, {10,10,10} },
	{5, {10,10,10} },
	{18, {10,10,10} },
	{23, {10,10,10} },
	{26, {10,10,10} },
	{30, {10,10,10} },
	{35, {10,10,10} },
	{40, {10,10,10} },
	{45, {10,10,10} },
	{50, {10,10,10} },
	{60, {10,10,10} }
};


static PolyKeyFrame Elbow_Translation[14] = 
{
	{0, {-2700,-250,-3150}, },
	{3, {-2700,-250,-3150}, },
	{5, {-2700,-250,-3150}, },
	{10, {-2700,-250,-3150}, },
	{13, {-2700,-250,-3150}, },
	{18, {-2700,-250,-3150}, },
	{23, {-2700,-250,-3150}, },
	{26, {-2700,-250,-3150}, },
	{30, {-2700,-250,-3150}, },
	{35, {-2700,-250,-3150}, },
	{40, {-2700,-250,-3150}, },
	{45, {-2700,-250,-3150}, },
	{50, {-2700,-250,-3150}, },
	{60, {-2700,-250,-3150}, }
};
static PolyKeyFrame Elbow_Rotation[14] = 
{
	{0, {4803,3241,194}, },
	{3, {3968,5435,705}, },
	{5, {4803,3241,194}, },
	{10, {4803,3241,194}, },
	{13, {4803,3241,194}, },
	{18, {4803,3241,194}, },
	{23, {4803,3241,194}, },
	{26, {4803,3241,194}, },
	{30, {4803,3241,194}, },
	{35, {4803,3241,194}, },
	{40, {4803,3241,194}, },
	{45, {4803,3241,194}, },
	{50, {4803,3241,194}, },
	{60, {4803,3241,194}, }
};
static PolyKeyFrame Elbow_Scaling[14] = 
{
	{0, {10,10,10} },
	{3, {10,10,10} },
	{5, {10,10,10} },
	{10, {10,10,10} },
	{13, {10,10,10} },
	{18, {10,10,10} },
	{23, {10,10,10} },
	{26, {10,10,10} },
	{30, {10,10,10} },
	{35, {10,10,10} },
	{40, {10,10,10} },
	{45, {10,10,10} },
	{50, {10,10,10} },
	{60, {10,10,10} }
};


static PolyKeyFrame Shoulder_Translation[7] = 
{
	{0, {-3504,-1710,-2800}, },
	{3, {-3504,-1710,-2800}, },
	{10, {-3504,-1710,-2800}, },
	{13, {-3504,-1710,-2800}, },
	{50, {-3504,-1710,-2800}, },
	{55, {-3504,-1710,-2800}, },
	{60, {-3504,-1710,-2800}, }
};
static PolyKeyFrame Shoulder_Rotation[7] = 
{
	{0, {10636,-3878,-8064}, },
	{3, {13772,-1680,-6922}, },
	{10, {10704,-2441,-1739}, },
	{13, {8975,-1775,4070}, },
	{50, {7138,-4720,-3595}, },
	{55, {10704,-2441,-6289}, },
	{60, {10636,-3878,-8064}, }
};
static PolyKeyFrame Shoulder_Scaling[7] = 
{
	{0, {10,10,10} },
	{3, {10,10,10} },
	{10, {10,10,10} },
	{13, {10,10,10} },
	{50, {10,10,10} },
	{55, {10,10,10} },
	{60, {10,10,10} }
};


static PolyKeyFrame SlideBone_Translation[1] = 
{
	{0, {20,0,1450}, }
};
static PolyKeyFrame SlideBone_Rotation[1] = 
{
	{0, {0,0,0}, }
};
static PolyKeyFrame SlideBone_Scaling[4] = 
{
	{0, {10,10,10} },
	{3, {10,10,10} },
	{5, {10,10,10} },
	{60, {10,10,10} }
};


static PolyKeyFrame MagazineBone_Translation[4] = 
{
	{0, {20,-150,-2450}, },
	{3, {20,-150,-2450}, },
	{5, {20,-150,-2450}, },
	{60, {20,-150,-2450}, }
};
static PolyKeyFrame MagazineBone_Rotation[1] = 
{
	{0, {0,0,0}, }
};
static PolyKeyFrame MagazineBone_Scaling[4] = 
{
	{0, {10,10,10} },
	{3, {10,10,10} },
	{5, {10,10,10} },
	{60, {10,10,10} }
};


static PolyKeyFrame PistolBone_Translation[13] = 
{
	{0, {780,6500,-3350}, },
	{3, {3965,2330,2720}, },
	{10, {-295,10152,-1518}, },
	{13, {-373,9090,-1338}, },
	{18, {930,8435,-1825}, },
	{23, {939,7135,-2595}, },
	{26, {-68,7759,405}, },
	{30, {602,8412,2997}, },
	{35, {602,6797,2392}, },
	{40, {602,5688,-726}, },
	{45, {-272,6135,-1527}, },
	{50, {716,6135,-1639}, },
	{60, {780,6500,-3350}, }
};
static PolyKeyFrame PistolBone_Rotation[13] = 
{
	{0, {0,0,0}, },
	{3, {31503,-1162,-1635}, },
	{10, {22473,-49,5075}, },
	{13, {17820,577,6919}, },
	{18, {23042,-5186,2037}, },
	{23, {13261,-1445,5366}, },
	{26, {27854,-855,-400}, },
	{30, {-24061,32,-427}, },
	{35, {-14371,-2112,-444}, },
	{40, {1167,495,804}, },
	{45, {8427,-4022,693}, },
	{50, {5520,-3701,726}, },
	{60, {0,0,0}, }
};
static PolyKeyFrame PistolBone_Scaling[13] = 
{
	{0, {10,10,10} },
	{3, {10,10,10} },
	{10, {10,10,10} },
	{13, {10,10,10} },
	{18, {10,10,10} },
	{23, {10,10,10} },
	{26, {10,10,10} },
	{30, {10,10,10} },
	{35, {10,10,10} },
	{40, {10,10,10} },
	{45, {10,10,10} },
	{50, {10,10,10} },
	{60, {10,10,10} }
};


static PolyKeyFrame ArmBone_Translation[13] = 
{
	{0, {800,6500,-3500}, },
	{3, {3985,306,2025}, },
	{10, {524,8156,-1312}, },
	{13, {344,7699,-766}, },
	{18, {1159,6090,-1581}, },
	{23, {1159,6090,-1812}, },
	{26, {1467,6090,-950}, },
	{30, {1159,6090,-1450}, },
	{35, {2547,6090,-1665}, },
	{40, {1159,6090,-1553}, },
	{45, {13,6090,-1351}, },
	{50, {628,6090,-1462}, },
	{60, {800,6500,-3500}, }
};
static PolyKeyFrame ArmBone_Rotation[13] = 
{
	{0, {0,0,0}, },
	{3, {13838,-1493,1341}, },
	{10, {14101,-5896,-1565}, },
	{13, {6943,-4677,3670}, },
	{18, {6943,-4677,1711}, },
	{23, {-646,-2428,4365}, },
	{26, {13942,1176,1086}, },
	{30, {6530,-4612,1889}, },
	{35, {9519,-912,605}, },
	{40, {3759,-4001,2450}, },
	{45, {7563,-4484,3239}, },
	{50, {6252,-4564,981}, },
	{60, {0,0,0}, }
};
static PolyKeyFrame ArmBone_Scaling[13] = 
{
	{0, {10,10,10} },
	{3, {10,10,10} },
	{10, {10,10,10} },
	{13, {10,10,10} },
	{18, {10,10,10} },
	{23, {10,10,10} },
	{26, {10,10,10} },
	{30, {10,10,10} },
	{35, {10,10,10} },
	{40, {10,10,10} },
	{45, {10,10,10} },
	{50, {10,10,10} },
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
	.PositionCount = 12,
	.RotationCount = 12,
	.ScalingCount = 12,
};


static PolyAnime Elbow_Anime = 
{
	.PositionData = (PolyKeyFrame*)&Elbow_Translation,
	.RotationData = (PolyKeyFrame*)&Elbow_Rotation,
	.ScalingData = (PolyKeyFrame*)&Elbow_Scaling,
	.PositionCount = 14,
	.RotationCount = 14,
	.ScalingCount = 14,
};


static PolyAnime Shoulder_Anime = 
{
	.PositionData = (PolyKeyFrame*)&Shoulder_Translation,
	.RotationData = (PolyKeyFrame*)&Shoulder_Rotation,
	.ScalingData = (PolyKeyFrame*)&Shoulder_Scaling,
	.PositionCount = 7,
	.RotationCount = 7,
	.ScalingCount = 7,
};


static PolyAnime SlideBone_Anime = 
{
	.PositionData = (PolyKeyFrame*)&SlideBone_Translation,
	.RotationData = (PolyKeyFrame*)&SlideBone_Rotation,
	.ScalingData = (PolyKeyFrame*)&SlideBone_Scaling,
	.PositionCount = 1,
	.RotationCount = 1,
	.ScalingCount = 4,
};


static PolyAnime MagazineBone_Anime = 
{
	.PositionData = (PolyKeyFrame*)&MagazineBone_Translation,
	.RotationData = (PolyKeyFrame*)&MagazineBone_Rotation,
	.ScalingData = (PolyKeyFrame*)&MagazineBone_Scaling,
	.PositionCount = 4,
	.RotationCount = 1,
	.ScalingCount = 4,
};


static PolyAnime PistolBone_Anime = 
{
	.PositionData = (PolyKeyFrame*)&PistolBone_Translation,
	.RotationData = (PolyKeyFrame*)&PistolBone_Rotation,
	.ScalingData = (PolyKeyFrame*)&PistolBone_Scaling,
	.PositionCount = 13,
	.RotationCount = 13,
	.ScalingCount = 13,
};


static PolyAnime ArmBone_Anime = 
{
	.PositionData = (PolyKeyFrame*)&ArmBone_Translation,
	.RotationData = (PolyKeyFrame*)&ArmBone_Rotation,
	.ScalingData = (PolyKeyFrame*)&ArmBone_Scaling,
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
static PolyNode Hand_hiraw_Node = 
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


static PolyNode Hand_CyborgFP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint Hand_NodeList[] = 
{
	(uint)&Hand_hiraw_Node,
	(uint)&Hand_CyborgTP_Node,
	(uint)&Hand_CyborgFP_Node,
};


static PolyNode Elbow_hiraw_Node = 
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


static PolyNode Elbow_CyborgFP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint Elbow_NodeList[] = 
{
	(uint)&Elbow_hiraw_Node,
	(uint)&Elbow_CyborgTP_Node,
	(uint)&Elbow_CyborgFP_Node,
};


static PolyNode Shoulder_hiraw_Node = 
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


static PolyNode Shoulder_CyborgFP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint Shoulder_NodeList[] = 
{
	(uint)&Shoulder_hiraw_Node,
	(uint)&Shoulder_CyborgTP_Node,
	(uint)&Shoulder_CyborgFP_Node,
};


static uint SlideBone_hiraw_MeshList[] = 
{
	(uint)&Draw_Slide_M
};




static PolyNode SlideBone_hiraw_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_Pistol_T,
	.MeshOffsets = (uint*)&SlideBone_hiraw_MeshList,
	.ClosingDL = (uint)&Draw_Pistol_T_Closing,
};


static PolyNode SlideBone_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};


static PolyNode SlideBone_CyborgFP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint SlideBone_NodeList[] = 
{
	(uint)&SlideBone_hiraw_Node,
	(uint)&SlideBone_CyborgTP_Node,
	(uint)&SlideBone_CyborgFP_Node,
};


static uint MagazineBone_hiraw_MeshList[] = 
{
	(uint)&Draw_HumanPistol_M
};




static PolyNode MagazineBone_hiraw_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_Pistol_T,
	.MeshOffsets = (uint*)&MagazineBone_hiraw_MeshList,
	.ClosingDL = (uint)&Draw_Pistol_T_Closing,
};


static PolyNode MagazineBone_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};


static PolyNode MagazineBone_CyborgFP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint MagazineBone_NodeList[] = 
{
	(uint)&MagazineBone_hiraw_Node,
	(uint)&MagazineBone_CyborgTP_Node,
	(uint)&MagazineBone_CyborgFP_Node,
};


static uint PistolBone_hiraw_MeshList[] = 
{
	(uint)&Draw_Pistol_M
};




static PolyNode PistolBone_hiraw_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_Pistol_T,
	.MeshOffsets = (uint*)&PistolBone_hiraw_MeshList,
	.ClosingDL = (uint)&Draw_Pistol_T_Closing,
};


static PolyNode PistolBone_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};


static PolyNode PistolBone_CyborgFP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint PistolBone_NodeList[] = 
{
	(uint)&PistolBone_hiraw_Node,
	(uint)&PistolBone_CyborgTP_Node,
	(uint)&PistolBone_CyborgFP_Node,
};


static PolyNode ArmBone_hiraw_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};


static uint ArmBone_CyborgTP_MeshList[] = 
{
	(uint)&Draw_RightArm_M
};




static PolyNode ArmBone_CyborgTP_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_CyborgTP_T,
	.MeshOffsets = (uint*)&ArmBone_CyborgTP_MeshList,
	.ClosingDL = (uint)&Draw_CyborgTP_T_Closing,
};


static PolyNode ArmBone_CyborgFP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint ArmBone_NodeList[] = 
{
	(uint)&ArmBone_hiraw_Node,
	(uint)&ArmBone_CyborgTP_Node,
	(uint)&ArmBone_CyborgFP_Node,
};


static PolyNode BodyBone_hiraw_Node = 
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


static PolyNode BodyBone_CyborgFP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint BodyBone_NodeList[] = 
{
	(uint)&BodyBone_hiraw_Node,
	(uint)&BodyBone_CyborgTP_Node,
	(uint)&BodyBone_CyborgFP_Node,
};










//PolyBone Structs




static PolyBone Hand_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&Hand_Anime,
	.NodeCount = 3,
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
	.NodeCount = 3,
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
	.NodeCount = 3,
	.NodeOffset = (PolyNode*)Shoulder_NodeList,
	.ChildCount = 1,
	.ChildOffset = (struct PolyBone*)Shoulder_ChildList,
};




static PolyBone SlideBone_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&SlideBone_Anime,
	.NodeCount = 3,
	.NodeOffset = (PolyNode*)SlideBone_NodeList,
	.ChildCount = 0,
	.ChildOffset = (struct PolyBone*)0
};




static PolyBone MagazineBone_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&MagazineBone_Anime,
	.NodeCount = 3,
	.NodeOffset = (PolyNode*)MagazineBone_NodeList,
	.ChildCount = 0,
	.ChildOffset = (struct PolyBone*)0
};




// ChildArray
static PolyBone* PistolBone_ChildList[] = 
{
	(PolyBone*)&SlideBone_Bone,
	(PolyBone*)&MagazineBone_Bone,
};
// PolyBone
static PolyBone PistolBone_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&PistolBone_Anime,
	.NodeCount = 3,
	.NodeOffset = (PolyNode*)PistolBone_NodeList,
	.ChildCount = 2,
	.ChildOffset = (struct PolyBone*)PistolBone_ChildList,
};




static PolyBone ArmBone_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&ArmBone_Anime,
	.NodeCount = 3,
	.NodeOffset = (PolyNode*)ArmBone_NodeList,
	.ChildCount = 0,
	.ChildOffset = (struct PolyBone*)0
};




// ChildArray
static PolyBone* BodyBone_ChildList[] = 
{
	(PolyBone*)&Shoulder_Bone,
	(PolyBone*)&PistolBone_Bone,
	(PolyBone*)&ArmBone_Bone,
};
// PolyBone
static PolyBone BodyBone_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&BodyBone_Anime,
	.NodeCount = 3,
	.NodeOffset = (PolyNode*)BodyBone_NodeList,
	.ChildCount = 3,
	.ChildOffset = (struct PolyBone*)BodyBone_ChildList,
};






//AnimeHolster
AnimeHolster HP_Melee =
{
	.RootBone = (PolyBone*)&BodyBone_Bone,
	.FrameCount = 61
};










