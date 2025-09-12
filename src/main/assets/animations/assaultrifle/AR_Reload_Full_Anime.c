//BodyBoneAnime File
//PolyTool Animation Version 1.0


#include <nusys.h>
#include <nualsgi_n.h>
#include "common.h"




//Keyframe Data


static PolyKeyFrame Hand_Translation[14] = 
{
	{0, {200,1700,-5000}, },
	{9, {200,1700,-5000}, },
	{13, {200,1700,-5000}, },
	{17, {200,1700,-5000}, },
	{22, {200,1700,-5000}, },
	{27, {200,1700,-5000}, },
	{31, {200,1700,-5000}, },
	{35, {200,1700,-5000}, },
	{39, {200,1700,-5000}, },
	{41, {200,1700,-5000}, },
	{43, {200,1700,-5000}, },
	{46, {200,1700,-5000}, },
	{52, {200,1700,-5000}, },
	{59, {200,1700,-5000}, }
};
static PolyKeyFrame Hand_Rotation[14] = 
{
	{0, {0,0,0}, },
	{9, {0,0,0}, },
	{13, {1036,3761,-1364}, },
	{17, {2417,8775,-3183}, },
	{22, {3453,12536,-4547}, },
	{27, {3453,12536,-4547}, },
	{31, {5257,7718,-3207}, },
	{35, {1542,1722,2391}, },
	{39, {-6334,-241,12691}, },
	{41, {-3327,-2114,7748}, },
	{43, {-319,-3987,2805}, },
	{46, {3269,-859,-2814}, },
	{52, {81,660,-944}, },
	{59, {0,0,0}, }
};
static PolyKeyFrame Hand_Scaling[14] = 
{
	{0, {10,10,10} },
	{9, {10,10,10} },
	{13, {10,10,10} },
	{17, {10,10,10} },
	{22, {10,10,10} },
	{27, {10,10,10} },
	{31, {10,10,10} },
	{35, {10,10,10} },
	{39, {10,10,10} },
	{41, {10,10,10} },
	{43, {10,10,10} },
	{46, {10,10,10} },
	{52, {10,10,10} },
	{59, {10,10,10} }
};


static PolyKeyFrame Elbow_Translation[14] = 
{
	{0, {-2700,-250,-3150}, },
	{9, {-2700,-250,-3150}, },
	{13, {-2700,-250,-3150}, },
	{17, {-2700,-250,-3150}, },
	{22, {-2700,-250,-3150}, },
	{27, {-2700,-250,-3150}, },
	{31, {-2700,-250,-3150}, },
	{35, {-2700,-250,-3150}, },
	{39, {-2700,-250,-3150}, },
	{41, {-2700,-250,-3150}, },
	{43, {-2700,-250,-3150}, },
	{46, {-2700,-250,-3150}, },
	{52, {-2700,-250,-3150}, },
	{59, {-2700,-250,-3150}, }
};
static PolyKeyFrame Elbow_Rotation[14] = 
{
	{0, {-1339,-2304,5631}, },
	{9, {2711,-11294,3083}, },
	{13, {42,-5513,1863}, },
	{17, {2589,-1459,-1323}, },
	{22, {2194,2032,-5562}, },
	{27, {2942,545,-1221}, },
	{31, {5030,-1776,-238}, },
	{35, {6421,-3324,416}, },
	{39, {4759,-3105,1534}, },
	{41, {2039,-7024,4271}, },
	{43, {-681,-10943,7007}, },
	{46, {-1769,-12510,8102}, },
	{52, {3018,-3863,3987}, },
	{59, {-1339,-2304,5631}, }
};
static PolyKeyFrame Elbow_Scaling[14] = 
{
	{0, {10,10,10} },
	{9, {10,10,10} },
	{13, {10,10,10} },
	{17, {10,10,10} },
	{22, {10,10,10} },
	{27, {10,10,10} },
	{31, {10,10,10} },
	{35, {10,10,10} },
	{39, {10,10,10} },
	{41, {10,10,10} },
	{43, {10,10,10} },
	{46, {10,10,10} },
	{52, {10,10,10} },
	{59, {10,10,10} }
};


static PolyKeyFrame Shoulder_Translation[14] = 
{
	{0, {-4000,1350,-2850}, },
	{9, {-4000,1350,-2850}, },
	{13, {-4000,1350,-2850}, },
	{17, {-4000,1350,-2850}, },
	{22, {-4000,1350,-2850}, },
	{27, {-4000,1350,-2850}, },
	{31, {-4000,1350,-2850}, },
	{35, {-4000,1350,-2850}, },
	{39, {-4000,1350,-2850}, },
	{41, {-4000,1350,-2850}, },
	{43, {-4000,1350,-2850}, },
	{46, {-4000,1350,-2850}, },
	{52, {-4000,1350,-2850}, },
	{59, {-4000,1350,-2850}, }
};
static PolyKeyFrame Shoulder_Rotation[14] = 
{
	{0, {12607,-1919,-8009}, },
	{9, {6344,857,-8527}, },
	{13, {12363,3554,-4227}, },
	{17, {9772,4859,-6958}, },
	{22, {3555,4704,-8940}, },
	{27, {7501,2502,-7771}, },
	{31, {5542,1904,-8398}, },
	{35, {6298,3790,-8338}, },
	{39, {8320,3209,-9904}, },
	{41, {5568,2423,-11389}, },
	{43, {2816,1636,-12874}, },
	{46, {4812,192,-13121}, },
	{52, {10499,980,-7972}, },
	{59, {12607,-1919,-8009}, }
};
static PolyKeyFrame Shoulder_Scaling[14] = 
{
	{0, {10,10,10} },
	{9, {10,10,10} },
	{13, {10,10,10} },
	{17, {10,10,10} },
	{22, {10,10,10} },
	{27, {10,10,10} },
	{31, {10,10,10} },
	{35, {10,10,10} },
	{39, {10,10,10} },
	{41, {10,10,10} },
	{43, {10,10,10} },
	{46, {10,10,10} },
	{52, {10,10,10} },
	{59, {10,10,10} }
};


static PolyKeyFrame ChargingPort_Translation[4] = 
{
	{0, {-100,1250,2200}, },
	{41, {-100,1250,2200}, },
	{52, {-100,1250,2200}, },
	{59, {-100,1250,2200}, }
};
static PolyKeyFrame ChargingPort_Rotation[1] = 
{
	{0, {0,0,0}, }
};
static PolyKeyFrame ChargingPort_Scaling[4] = 
{
	{0, {10,10,10} },
	{41, {10,10,10} },
	{52, {10,10,10} },
	{59, {10,10,10} }
};


static PolyKeyFrame Magazine_Translation[14] = 
{
	{0, {0,-2000,-1200}, },
	{9, {0,-2000,-1200}, },
	{13, {-2019,1409,-5718}, },
	{17, {-1554,1199,-6487}, },
	{22, {-4242,-1908,-7315}, },
	{27, {-2605,-1148,-6980}, },
	{31, {-1718,-2244,-6297}, },
	{35, {-1329,1012,-5652}, },
	{39, {-146,351,-5538}, },
	{41, {-19,-2680,-4980}, },
	{43, {69,-3821,-3253}, },
	{46, {6,-2025,-1200}, },
	{52, {3,-2010,-1186}, },
	{59, {1,-1998,-1174}, }
};
static PolyKeyFrame Magazine_Rotation[14] = 
{
	{0, {0,0,0}, },
	{9, {0,0,0}, },
	{13, {14769,-649,-597}, },
	{17, {22651,-865,-1493}, },
	{22, {31057,-1282,-2093}, },
	{27, {29978,5069,6813}, },
	{31, {24349,1160,1228}, },
	{35, {11317,-755,-1388}, },
	{39, {-1368,-748,-374}, },
	{41, {-2766,-672,-118}, },
	{43, {-6884,-331,-354}, },
	{46, {-48,-399,-562}, },
	{52, {-22,294,-256}, },
	{59, {0,871,0}, }
};
static PolyKeyFrame Magazine_Scaling[14] = 
{
	{0, {10,10,10} },
	{9, {10,10,10} },
	{13, {10,10,10} },
	{17, {10,10,10} },
	{22, {10,10,10} },
	{27, {10,10,10} },
	{31, {10,10,10} },
	{35, {10,10,10} },
	{39, {10,10,10} },
	{41, {10,10,10} },
	{43, {10,10,10} },
	{46, {10,10,10} },
	{52, {10,10,10} },
	{59, {10,10,10} }
};


static PolyKeyFrame AR_Translation[14] = 
{
	{0, {2050,2150,-4150}, },
	{9, {2423,5562,-1463}, },
	{13, {2421,4218,-1463}, },
	{17, {2526,4203,-2061}, },
	{22, {2416,4191,-2254}, },
	{27, {2318,4358,-1565}, },
	{31, {2294,4034,-1441}, },
	{35, {2278,3420,-1853}, },
	{39, {2229,3148,-1460}, },
	{41, {2209,3035,-1456}, },
	{43, {2188,2921,-1452}, },
	{46, {2180,2876,-1841}, },
	{52, {2109,2480,-3100}, },
	{59, {2050,2150,-4150}, }
};
static PolyKeyFrame AR_Rotation[14] = 
{
	{0, {0,0,0}, },
	{9, {11015,3896,-2477}, },
	{13, {10466,-625,1078}, },
	{17, {10389,-621,1070}, },
	{22, {10332,-617,1064}, },
	{27, {12009,-734,524}, },
	{31, {11437,-673,469}, },
	{35, {9157,-542,540}, },
	{39, {10837,-546,253}, },
	{41, {10600,180,-962}, },
	{43, {10364,905,-2176}, },
	{46, {10613,-431,75}, },
	{52, {4824,-196,34}, },
	{59, {0,0,0}, }
};
static PolyKeyFrame AR_Scaling[14] = 
{
	{0, {10,10,10} },
	{9, {10,10,10} },
	{13, {10,10,10} },
	{17, {10,10,10} },
	{22, {10,10,10} },
	{27, {10,10,10} },
	{31, {10,10,10} },
	{35, {10,10,10} },
	{39, {10,10,10} },
	{41, {10,10,10} },
	{43, {10,10,10} },
	{46, {10,10,10} },
	{52, {10,10,10} },
	{59, {10,10,10} }
};


static PolyKeyFrame RightArm_Translation[14] = 
{
	{0, {2050,3200,-4150}, },
	{9, {2423,6612,-1463}, },
	{13, {2421,5268,-1463}, },
	{17, {2526,5253,-2061}, },
	{22, {2416,5241,-2254}, },
	{27, {2318,5408,-1565}, },
	{31, {2294,5084,-1441}, },
	{35, {2278,4470,-1853}, },
	{39, {2229,4198,-1460}, },
	{41, {2209,4085,-1456}, },
	{43, {2188,3971,-1452}, },
	{46, {2180,3926,-1841}, },
	{52, {2109,3530,-3100}, },
	{59, {2050,3200,-4150}, }
};
static PolyKeyFrame RightArm_Rotation[14] = 
{
	{0, {0,0,0}, },
	{9, {11015,3896,-2477}, },
	{13, {10466,-625,1078}, },
	{17, {10389,-621,1070}, },
	{22, {10332,-617,1064}, },
	{27, {12009,-734,524}, },
	{31, {11437,-673,469}, },
	{35, {9157,-542,540}, },
	{39, {10837,-546,253}, },
	{41, {10600,180,-962}, },
	{43, {10364,905,-2176}, },
	{46, {10613,-431,75}, },
	{52, {4824,-196,34}, },
	{59, {0,0,0}, }
};
static PolyKeyFrame RightArm_Scaling[14] = 
{
	{0, {10,10,10} },
	{9, {10,10,10} },
	{13, {10,10,10} },
	{17, {10,10,10} },
	{22, {10,10,10} },
	{27, {10,10,10} },
	{31, {10,10,10} },
	{35, {10,10,10} },
	{39, {10,10,10} },
	{41, {10,10,10} },
	{43, {10,10,10} },
	{46, {10,10,10} },
	{52, {10,10,10} },
	{59, {10,10,10} }
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
	.PositionCount = 14,
	.RotationCount = 14,
	.ScalingCount = 14,
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
	.PositionCount = 14,
	.RotationCount = 14,
	.ScalingCount = 14,
};


static PolyAnime ChargingPort_Anime = 
{
	.PositionData = (PolyKeyFrame*)&ChargingPort_Translation,
	.RotationData = (PolyKeyFrame*)&ChargingPort_Rotation,
	.ScalingData = (PolyKeyFrame*)&ChargingPort_Scaling,
	.PositionCount = 4,
	.RotationCount = 1,
	.ScalingCount = 4,
};


static PolyAnime Magazine_Anime = 
{
	.PositionData = (PolyKeyFrame*)&Magazine_Translation,
	.RotationData = (PolyKeyFrame*)&Magazine_Rotation,
	.ScalingData = (PolyKeyFrame*)&Magazine_Scaling,
	.PositionCount = 14,
	.RotationCount = 14,
	.ScalingCount = 14,
};


static PolyAnime AR_Anime = 
{
	.PositionData = (PolyKeyFrame*)&AR_Translation,
	.RotationData = (PolyKeyFrame*)&AR_Rotation,
	.ScalingData = (PolyKeyFrame*)&AR_Scaling,
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
AnimeHolster AR_Reload_Full =
{
	.RootBone = (PolyBone*)&BodyBone_Bone,
	.FrameCount = 60,
    .ActionFrame = 47
};










