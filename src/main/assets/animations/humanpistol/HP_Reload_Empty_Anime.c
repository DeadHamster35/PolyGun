//BodyBoneAnime File
//PolyTool Animation Version 1.0


#include <nusys.h>
#include <nualsgi_n.h>
#include "common.h"




//Keyframe Data


static PolyKeyFrame Hand_Translation[15] = 
{
	{0, {200,1700,-5000}, },
	{8, {200,1700,-5000}, },
	{12, {200,1700,-5000}, },
	{16, {200,1700,-5000}, },
	{21, {200,1700,-5000}, },
	{26, {200,1700,-5000}, },
	{28, {200,1700,-5000}, },
	{30, {200,1700,-5000}, },
	{32, {200,1700,-5000}, },
	{38, {200,1700,-5000}, },
	{41, {200,1700,-5000}, },
	{50, {200,1700,-5000}, },
	{58, {200,1700,-5000}, },
	{61, {200,1700,-5000}, },
	{64, {200,1700,-5000}, }
};
static PolyKeyFrame Hand_Rotation[15] = 
{
	{0, {1298,3173,-2211}, },
	{8, {1298,3173,-2211}, },
	{12, {1312,4038,-2565}, },
	{16, {1326,4903,-2919}, },
	{21, {1343,5985,-3361}, },
	{26, {1360,7067,-3803}, },
	{28, {1354,6696,-3652}, },
	{30, {1348,6325,-3500}, },
	{32, {1342,5954,-3348}, },
	{38, {1325,4842,-2893}, },
	{41, {1321,4619,-2802}, },
	{50, {1310,3952,-2529}, },
	{58, {1301,3358,-2287}, },
	{61, {1298,3204,-2223}, },
	{64, {1298,3173,-2211}, }
};
static PolyKeyFrame Hand_Scaling[15] = 
{
	{0, {10,10,10} },
	{8, {10,10,10} },
	{12, {10,10,10} },
	{16, {10,10,10} },
	{21, {10,10,10} },
	{26, {10,10,10} },
	{28, {10,10,10} },
	{30, {10,10,10} },
	{32, {10,10,10} },
	{38, {10,10,10} },
	{41, {10,10,10} },
	{50, {10,10,10} },
	{58, {10,10,10} },
	{61, {10,10,10} },
	{64, {10,10,10} }
};


static PolyKeyFrame Elbow_Translation[15] = 
{
	{0, {-2700,-250,-3150}, },
	{8, {-2700,-250,-3150}, },
	{12, {-2700,-250,-3150}, },
	{16, {-2700,-250,-3150}, },
	{21, {-2700,-250,-3150}, },
	{26, {-2700,-250,-3150}, },
	{28, {-2700,-250,-3150}, },
	{30, {-2700,-250,-3150}, },
	{32, {-2700,-250,-3150}, },
	{38, {-2700,-250,-3150}, },
	{41, {-2700,-250,-3150}, },
	{50, {-2700,-250,-3150}, },
	{58, {-2700,-250,-3150}, },
	{61, {-2700,-250,-3150}, },
	{64, {-2700,-250,-3150}, }
};
static PolyKeyFrame Elbow_Rotation[15] = 
{
	{0, {4803,3241,194}, },
	{8, {4803,3241,194}, },
	{12, {4395,3254,795}, },
	{16, {3987,3268,1395}, },
	{21, {9473,10083,1338}, },
	{26, {9014,7179,-2545}, },
	{28, {7853,8282,-3263}, },
	{30, {6692,9384,-3981}, },
	{32, {5530,10487,-4699}, },
	{38, {6222,7975,-2303}, },
	{41, {6033,7344,-1970}, },
	{50, {7117,3313,1696}, },
	{58, {4961,3767,-83}, },
	{61, {4830,3329,148}, },
	{64, {4803,3241,194}, }
};
static PolyKeyFrame Elbow_Scaling[15] = 
{
	{0, {10,10,10} },
	{8, {10,10,10} },
	{12, {10,10,10} },
	{16, {10,10,10} },
	{21, {10,10,10} },
	{26, {10,10,10} },
	{28, {10,10,10} },
	{30, {10,10,10} },
	{32, {10,10,10} },
	{38, {10,10,10} },
	{41, {10,10,10} },
	{50, {10,10,10} },
	{58, {10,10,10} },
	{61, {10,10,10} },
	{64, {10,10,10} }
};


static PolyKeyFrame Shoulder_Translation[15] = 
{
	{0, {-3504,-1710,-2800}, },
	{8, {-3504,-1710,-2800}, },
	{12, {-3504,-1710,-2800}, },
	{16, {-3504,-1710,-2800}, },
	{21, {-3078,-800,-2800}, },
	{26, {-3504,-1206,-2800}, },
	{28, {-3504,-1254,-2800}, },
	{30, {-3504,-1302,-2800}, },
	{32, {-3504,-1350,-2800}, },
	{38, {-3504,-1494,-2800}, },
	{41, {-3504,-1523,-2800}, },
	{50, {-3504,-1609,-2800}, },
	{58, {-3504,-1686,-2800}, },
	{61, {-3504,-1706,-2800}, },
	{64, {-3504,-1710,-2800}, }
};
static PolyKeyFrame Shoulder_Rotation[15] = 
{
	{0, {10636,-3878,-8064}, },
	{8, {4849,-5029,-960}, },
	{12, {5171,-4965,-1355}, },
	{16, {6732,-4654,-3272}, },
	{21, {5511,-7091,-5607}, },
	{26, {6852,-5016,-4828}, },
	{28, {7796,-4968,-5947}, },
	{30, {8739,-4920,-7066}, },
	{32, {9683,-4872,-8185}, },
	{38, {10064,-4474,-5959}, },
	{41, {10140,-4395,-6239}, },
	{50, {10369,-4156,-7393}, },
	{58, {10573,-3944,-7830}, },
	{61, {10625,-3889,-8025}, },
	{64, {10636,-3878,-8064}, }
};
static PolyKeyFrame Shoulder_Scaling[15] = 
{
	{0, {10,10,10} },
	{8, {10,10,10} },
	{12, {10,10,10} },
	{16, {10,10,10} },
	{21, {10,10,10} },
	{26, {10,10,10} },
	{28, {10,10,10} },
	{30, {10,10,10} },
	{32, {10,10,10} },
	{38, {10,10,10} },
	{41, {10,10,10} },
	{50, {10,10,10} },
	{58, {10,10,10} },
	{61, {10,10,10} },
	{64, {10,10,10} }
};


static PolyKeyFrame SlideBone_Translation[5] = 
{
	{0, {20,0,1450}, },
	{2, {20,-500,1450}, },
	{40, {20,-492,1450}, },
	{45, {20,0,1450}, },
	{64, {20,0,1450}, }
};
static PolyKeyFrame SlideBone_Rotation[1] = 
{
	{0, {0,0,0}, }
};
static PolyKeyFrame SlideBone_Scaling[5] = 
{
	{0, {10,10,10} },
	{2, {10,10,10} },
	{40, {10,10,10} },
	{45, {10,10,10} },
	{64, {10,10,10} }
};


static PolyKeyFrame MagazineBone_Translation[15] = 
{
	{0, {20,-150,-2450}, },
	{8, {20,-150,-2450}, },
	{12, {20,-150,-2450}, },
	{16, {-17,-386,-4668}, },
	{21, {-86,-3527,-7529}, },
	{26, {-447,-1298,-5591}, },
	{28, {-294,-908,-4551}, },
	{30, {-142,-517,-3511}, },
	{32, {11,-127,-2472}, },
	{38, {15,-136,-2463}, },
	{41, {15,-136,-2463}, },
	{50, {15,-138,-2461}, },
	{58, {19,-148,-2451}, },
	{61, {20,-150,-2450}, },
	{64, {20,-150,-2450}, }
};
static PolyKeyFrame MagazineBone_Rotation[15] = 
{
	{0, {0,0,0}, },
	{8, {0,0,0}, },
	{12, {0,0,0}, },
	{16, {0,0,0}, },
	{21, {-4825,826,-2560}, },
	{26, {-1220,4355,703}, },
	{28, {-1400,999,-388}, },
	{30, {-526,760,-269}, },
	{32, {0,0,0}, },
	{38, {0,0,0}, },
	{41, {0,0,0}, },
	{50, {0,0,0}, },
	{58, {0,0,0}, },
	{61, {0,0,0}, },
	{64, {0,0,0}, }
};
static PolyKeyFrame MagazineBone_Scaling[15] = 
{
	{0, {10,10,10} },
	{8, {10,10,10} },
	{12, {10,10,10} },
	{16, {10,10,10} },
	{21, {10,10,10} },
	{26, {10,10,10} },
	{28, {10,10,10} },
	{30, {10,10,10} },
	{32, {10,10,10} },
	{38, {10,10,10} },
	{41, {10,10,10} },
	{50, {10,10,10} },
	{58, {10,10,10} },
	{61, {10,10,10} },
	{64, {10,10,10} }
};


static PolyKeyFrame PistolBone_Translation[15] = 
{
	{0, {780,6500,-3350}, },
	{8, {2889,6500,-1130}, },
	{12, {2229,6500,-1811}, },
	{16, {2724,6500,-1300}, },
	{21, {2779,6500,-1244}, },
	{26, {2835,6500,-1187}, },
	{28, {2639,6500,-1393}, },
	{30, {2443,6500,-1599}, },
	{32, {2248,6500,-1805}, },
	{38, {1661,6500,-2423}, },
	{41, {1631,6500,-2454}, },
	{50, {1543,6500,-2547}, },
	{58, {878,6500,-3247}, },
	{61, {796,6500,-3333}, },
	{64, {780,6500,-3350}, }
};
static PolyKeyFrame PistolBone_Rotation[15] = 
{
	{0, {0,0,0}, },
	{8, {7546,1859,5040}, },
	{12, {6332,2548,6345}, },
	{16, {7242,2032,5366}, },
	{21, {9500,5477,5917}, },
	{26, {10295,6533,9320}, },
	{28, {10094,7053,8998}, },
	{30, {9894,7573,8677}, },
	{32, {9693,8093,8356}, },
	{38, {5816,4856,5013}, },
	{41, {5622,4694,4846}, },
	{50, {5040,4208,4345}, },
	{58, {646,540,557}, },
	{61, {108,90,93}, },
	{64, {0,0,0}, }
};
static PolyKeyFrame PistolBone_Scaling[15] = 
{
	{0, {10,10,10} },
	{8, {10,10,10} },
	{12, {10,10,10} },
	{16, {10,10,10} },
	{21, {10,10,10} },
	{26, {10,10,10} },
	{28, {10,10,10} },
	{30, {10,10,10} },
	{32, {10,10,10} },
	{38, {10,10,10} },
	{41, {10,10,10} },
	{50, {10,10,10} },
	{58, {10,10,10} },
	{61, {10,10,10} },
	{64, {10,10,10} }
};


static PolyKeyFrame ArmBone_Translation[15] = 
{
	{0, {800,6500,-3500}, },
	{8, {2909,6500,-1280}, },
	{12, {2249,6500,-1961}, },
	{16, {2744,6500,-1450}, },
	{21, {2799,6500,-1394}, },
	{26, {2855,6500,-1337}, },
	{28, {2659,6500,-1543}, },
	{30, {2463,6500,-1749}, },
	{32, {2268,6500,-1955}, },
	{38, {1681,6500,-2573}, },
	{41, {1651,6500,-2604}, },
	{50, {1563,6500,-2697}, },
	{58, {898,6500,-3397}, },
	{61, {816,6500,-3483}, },
	{64, {800,6500,-3500}, }
};
static PolyKeyFrame ArmBone_Rotation[15] = 
{
	{0, {0,0,0}, },
	{8, {7546,1859,5040}, },
	{12, {6332,2548,6345}, },
	{16, {7242,2032,5366}, },
	{21, {9500,5477,5917}, },
	{26, {10295,6533,9320}, },
	{28, {10094,7053,8998}, },
	{30, {9894,7573,8677}, },
	{32, {9693,8093,8356}, },
	{38, {5816,4856,5013}, },
	{41, {5622,4694,4846}, },
	{50, {5040,4208,4345}, },
	{58, {646,540,557}, },
	{61, {108,90,93}, },
	{64, {0,0,0}, }
};
static PolyKeyFrame ArmBone_Scaling[15] = 
{
	{0, {10,10,10} },
	{8, {10,10,10} },
	{12, {10,10,10} },
	{16, {10,10,10} },
	{21, {10,10,10} },
	{26, {10,10,10} },
	{28, {10,10,10} },
	{30, {10,10,10} },
	{32, {10,10,10} },
	{38, {10,10,10} },
	{41, {10,10,10} },
	{50, {10,10,10} },
	{58, {10,10,10} },
	{61, {10,10,10} },
	{64, {10,10,10} }
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
	.PositionCount = 15,
	.RotationCount = 15,
	.ScalingCount = 15,
};


static PolyAnime Elbow_Anime = 
{
	.PositionData = (PolyKeyFrame*)&Elbow_Translation,
	.RotationData = (PolyKeyFrame*)&Elbow_Rotation,
	.ScalingData = (PolyKeyFrame*)&Elbow_Scaling,
	.PositionCount = 15,
	.RotationCount = 15,
	.ScalingCount = 15,
};


static PolyAnime Shoulder_Anime = 
{
	.PositionData = (PolyKeyFrame*)&Shoulder_Translation,
	.RotationData = (PolyKeyFrame*)&Shoulder_Rotation,
	.ScalingData = (PolyKeyFrame*)&Shoulder_Scaling,
	.PositionCount = 15,
	.RotationCount = 15,
	.ScalingCount = 15,
};


static PolyAnime SlideBone_Anime = 
{
	.PositionData = (PolyKeyFrame*)&SlideBone_Translation,
	.RotationData = (PolyKeyFrame*)&SlideBone_Rotation,
	.ScalingData = (PolyKeyFrame*)&SlideBone_Scaling,
	.PositionCount = 5,
	.RotationCount = 1,
	.ScalingCount = 5,
};


static PolyAnime MagazineBone_Anime = 
{
	.PositionData = (PolyKeyFrame*)&MagazineBone_Translation,
	.RotationData = (PolyKeyFrame*)&MagazineBone_Rotation,
	.ScalingData = (PolyKeyFrame*)&MagazineBone_Scaling,
	.PositionCount = 15,
	.RotationCount = 15,
	.ScalingCount = 15,
};


static PolyAnime PistolBone_Anime = 
{
	.PositionData = (PolyKeyFrame*)&PistolBone_Translation,
	.RotationData = (PolyKeyFrame*)&PistolBone_Rotation,
	.ScalingData = (PolyKeyFrame*)&PistolBone_Scaling,
	.PositionCount = 15,
	.RotationCount = 15,
	.ScalingCount = 15,
};


static PolyAnime ArmBone_Anime = 
{
	.PositionData = (PolyKeyFrame*)&ArmBone_Translation,
	.RotationData = (PolyKeyFrame*)&ArmBone_Rotation,
	.ScalingData = (PolyKeyFrame*)&ArmBone_Scaling,
	.PositionCount = 15,
	.RotationCount = 15,
	.ScalingCount = 15,
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
AnimeHolster HP_Reload_Empty =
{
	.RootBone = (PolyBone*)&BodyBone_Bone,
	.FrameCount = 65
};










