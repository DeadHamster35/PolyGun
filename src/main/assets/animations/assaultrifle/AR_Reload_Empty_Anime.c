//BodyBoneAnime File
//PolyTool Animation Version 1.0


#include <nusys.h>
#include <nualsgi_n.h>
#include "common.h"




//Keyframe Data


static PolyKeyFrame Hand_Translation[25] = 
{
	{0, {200,1700,-5000}, },
	{4, {200,1700,-5000}, },
	{9, {200,1700,-5000}, },
	{13, {200,1700,-5000}, },
	{17, {200,1700,-5000}, },
	{22, {200,1700,-5000}, },
	{27, {200,1700,-5000}, },
	{31, {200,1700,-5000}, },
	{35, {200,1700,-5000}, },
	{39, {200,1700,-5000}, },
	{45, {200,1700,-5000}, },
	{49, {200,1700,-5000}, },
	{53, {200,1700,-5000}, },
	{58, {200,1700,-5000}, },
	{60, {200,1700,-5000}, },
	{62, {200,1700,-5000}, },
	{66, {200,1700,-5000}, },
	{70, {200,1700,-5000}, },
	{73, {200,1700,-5000}, },
	{76, {200,1700,-5000}, },
	{80, {200,1700,-5000}, },
	{83, {200,1700,-5000}, },
	{86, {200,1700,-5000}, },
	{89, {200,1700,-5000}, },
	{94, {200,1700,-5000}, }
};
static PolyKeyFrame Hand_Rotation[25] = 
{
	{0, {0,0,0}, },
	{4, {0,0,0}, },
	{9, {0,0,0}, },
	{13, {-1192,-348,-8151}, },
	{17, {-3422,-1662,-1095}, },
	{22, {-1711,-831,-547}, },
	{27, {0,0,0}, },
	{31, {1036,3761,-1364}, },
	{35, {2417,8775,-3183}, },
	{39, {3453,12536,-4547}, },
	{45, {3453,12536,-4547}, },
	{49, {5257,7718,-3207}, },
	{53, {1542,1722,2391}, },
	{58, {-5183,-1875,6209}, },
	{60, {-2673,-134,4102}, },
	{62, {-162,1607,1996}, },
	{66, {3269,-859,-2814}, },
	{70, {2452,-644,-2110}, },
	{73, {3497,1469,982}, },
	{76, {1635,-430,-1407}, },
	{80, {2436,-187,-2505}, },
	{83, {5037,3527,-2171}, },
	{86, {801,-210,-689}, },
	{89, {267,-70,-230}, },
	{94, {0,0,0}, }
};
static PolyKeyFrame Hand_Scaling[25] = 
{
	{0, {10,10,10} },
	{4, {10,10,10} },
	{9, {10,10,10} },
	{13, {10,10,10} },
	{17, {10,10,10} },
	{22, {10,10,10} },
	{27, {10,10,10} },
	{31, {10,10,10} },
	{35, {10,10,10} },
	{39, {10,10,10} },
	{45, {10,10,10} },
	{49, {10,10,10} },
	{53, {10,10,10} },
	{58, {10,10,10} },
	{60, {10,10,10} },
	{62, {10,10,10} },
	{66, {10,10,10} },
	{70, {10,10,10} },
	{73, {10,10,10} },
	{76, {10,10,10} },
	{80, {10,10,10} },
	{83, {10,10,10} },
	{86, {10,10,10} },
	{89, {10,10,10} },
	{94, {10,10,10} }
};


static PolyKeyFrame Elbow_Translation[25] = 
{
	{0, {-2700,-250,-3150}, },
	{4, {-2700,-250,-3150}, },
	{9, {-2700,-250,-3150}, },
	{13, {-2700,-250,-3150}, },
	{17, {-2700,-250,-3150}, },
	{22, {-2700,-250,-3150}, },
	{27, {-2700,-250,-3150}, },
	{31, {-2700,-250,-3150}, },
	{35, {-2700,-250,-3150}, },
	{39, {-2700,-250,-3150}, },
	{45, {-2700,-250,-3150}, },
	{49, {-2700,-250,-3150}, },
	{53, {-2700,-250,-3150}, },
	{58, {-2700,-250,-3150}, },
	{60, {-2700,-250,-3150}, },
	{62, {-2700,-250,-3150}, },
	{66, {-2700,-250,-3150}, },
	{70, {-2700,-250,-3150}, },
	{73, {-2700,-250,-3150}, },
	{76, {-2700,-250,-3150}, },
	{80, {-2700,-250,-3150}, },
	{83, {-2700,-250,-3150}, },
	{86, {-2700,-250,-3150}, },
	{89, {-2700,-250,-3150}, },
	{94, {-2700,-250,-3150}, }
};
static PolyKeyFrame Elbow_Rotation[25] = 
{
	{0, {-1339,-2304,5631}, },
	{4, {-3959,-838,7616}, },
	{9, {8461,4551,-7318}, },
	{13, {8743,2938,-10900}, },
	{17, {10811,3400,-11241}, },
	{22, {12993,1130,-1423}, },
	{27, {2711,-11294,3083}, },
	{31, {42,-5513,1863}, },
	{35, {2589,-1459,-1323}, },
	{39, {2194,2032,-5562}, },
	{45, {2942,545,-1221}, },
	{49, {5030,-1776,-238}, },
	{53, {6421,-3324,416}, },
	{58, {2632,-4620,3603}, },
	{60, {1228,-8011,4968}, },
	{62, {-176,-11402,6333}, },
	{66, {-1769,-12510,8102}, },
	{70, {4886,-5568,1235}, },
	{73, {8213,-2097,-2198}, },
	{76, {8971,3159,-5896}, },
	{80, {11059,6818,-3490}, },
	{83, {9120,5247,-1062}, },
	{86, {1475,-251,6542}, },
	{89, {-2940,-337,8466}, },
	{94, {-1339,-2304,5631}, }
};
static PolyKeyFrame Elbow_Scaling[25] = 
{
	{0, {10,10,10} },
	{4, {10,10,10} },
	{9, {10,10,10} },
	{13, {10,10,10} },
	{17, {10,10,10} },
	{22, {10,10,10} },
	{27, {10,10,10} },
	{31, {10,10,10} },
	{35, {10,10,10} },
	{39, {10,10,10} },
	{45, {10,10,10} },
	{49, {10,10,10} },
	{53, {10,10,10} },
	{58, {10,10,10} },
	{60, {10,10,10} },
	{62, {10,10,10} },
	{66, {10,10,10} },
	{70, {10,10,10} },
	{73, {10,10,10} },
	{76, {10,10,10} },
	{80, {10,10,10} },
	{83, {10,10,10} },
	{86, {10,10,10} },
	{89, {10,10,10} },
	{94, {10,10,10} }
};


static PolyKeyFrame Shoulder_Translation[25] = 
{
	{0, {-4000,1350,-2850}, },
	{4, {-4000,1350,-2850}, },
	{9, {-4000,1350,-2850}, },
	{13, {-4000,1350,-2850}, },
	{17, {-4000,1350,-2850}, },
	{22, {-4000,1350,-2850}, },
	{27, {-4000,1350,-2850}, },
	{31, {-4000,1350,-2850}, },
	{35, {-4000,1350,-2850}, },
	{39, {-4000,1350,-2850}, },
	{45, {-4000,1350,-2850}, },
	{49, {-4000,1350,-2850}, },
	{53, {-4000,1350,-2850}, },
	{58, {-4000,1350,-2850}, },
	{60, {-4000,1350,-2850}, },
	{62, {-4000,1350,-2850}, },
	{66, {-4000,1350,-2850}, },
	{70, {-4000,1350,-2850}, },
	{73, {-4000,1350,-2850}, },
	{76, {-4000,264,-2850}, },
	{80, {-4000,1350,-2850}, },
	{83, {-4000,1350,-2850}, },
	{86, {-4000,1350,-2850}, },
	{89, {-4000,1350,-2850}, },
	{94, {-4000,1350,-2850}, }
};
static PolyKeyFrame Shoulder_Rotation[25] = 
{
	{0, {12607,-1919,-8009}, },
	{4, {14029,-1081,-4687}, },
	{9, {14473,-509,-6483}, },
	{13, {15156,-472,-7966}, },
	{17, {14416,-512,-8129}, },
	{22, {11452,-674,-8782}, },
	{27, {6344,857,-8527}, },
	{31, {12363,3554,-4227}, },
	{35, {9772,4859,-6958}, },
	{39, {3555,4704,-8940}, },
	{45, {7501,2502,-7771}, },
	{49, {5542,1904,-8398}, },
	{53, {6298,3790,-8338}, },
	{58, {8320,3209,-9904}, },
	{60, {5568,2423,-11389}, },
	{62, {2816,1636,-12874}, },
	{66, {4812,192,-13121}, },
	{70, {9161,3067,-5307}, },
	{73, {13291,4987,-2358}, },
	{76, {13511,5941,-8413}, },
	{80, {11496,5736,-9184}, },
	{83, {13895,6191,-6989}, },
	{86, {14424,2919,-6066}, },
	{89, {13213,-306,-7362}, },
	{94, {12607,-1919,-8009}, }
};
static PolyKeyFrame Shoulder_Scaling[25] = 
{
	{0, {10,10,10} },
	{4, {10,10,10} },
	{9, {10,10,10} },
	{13, {10,10,10} },
	{17, {10,10,10} },
	{22, {10,10,10} },
	{27, {10,10,10} },
	{31, {10,10,10} },
	{35, {10,10,10} },
	{39, {10,10,10} },
	{45, {10,10,10} },
	{49, {10,10,10} },
	{53, {10,10,10} },
	{58, {10,10,10} },
	{60, {10,10,10} },
	{62, {10,10,10} },
	{66, {10,10,10} },
	{70, {10,10,10} },
	{73, {10,10,10} },
	{76, {10,10,10} },
	{80, {10,10,10} },
	{83, {10,10,10} },
	{86, {10,10,10} },
	{89, {10,10,10} },
	{94, {10,10,10} }
};


static PolyKeyFrame ChargingPort_Translation[24] = 
{
	{0, {-100,1250,2200}, },
	{12, {-100,1250,2200}, },
	{13, {-100,1200,2200}, },
	{17, {-115,237,2184}, },
	{22, {-108,269,2192}, },
	{27, {-100,300,2200}, },
	{31, {-100,300,2200}, },
	{35, {-100,300,2200}, },
	{39, {-100,300,2200}, },
	{45, {-100,300,2200}, },
	{49, {-100,300,2200}, },
	{53, {-100,300,2200}, },
	{58, {-100,300,2200}, },
	{60, {-100,300,2200}, },
	{62, {-100,300,2200}, },
	{66, {-100,300,2200}, },
	{70, {-100,300,2200}, },
	{73, {-100,300,2200}, },
	{76, {-100,300,2200}, },
	{80, {-65,1310,2193}, },
	{83, {-75,1293,2195}, },
	{86, {-85,1276,2197}, },
	{89, {-95,1259,2199}, },
	{94, {-100,1250,2200}, }
};
static PolyKeyFrame ChargingPort_Rotation[1] = 
{
	{0, {0,0,0}, }
};
static PolyKeyFrame ChargingPort_Scaling[24] = 
{
	{0, {10,10,10} },
	{12, {10,10,10} },
	{13, {10,10,10} },
	{17, {10,10,10} },
	{22, {10,10,10} },
	{27, {10,10,10} },
	{31, {10,10,10} },
	{35, {10,10,10} },
	{39, {10,10,10} },
	{45, {10,10,10} },
	{49, {10,10,10} },
	{53, {10,10,10} },
	{58, {10,10,10} },
	{60, {10,10,10} },
	{62, {10,10,10} },
	{66, {10,10,10} },
	{70, {10,10,10} },
	{73, {10,10,10} },
	{76, {10,10,10} },
	{80, {10,10,10} },
	{83, {10,10,10} },
	{86, {10,10,10} },
	{89, {10,10,10} },
	{94, {10,10,10} }
};


static PolyKeyFrame Magazine_Translation[18] = 
{
	{0, {0,-2000,-1200}, },
	{4, {0,-2000,-1200}, },
	{9, {0,-2000,-1200}, },
	{13, {0,-2000,-1200}, },
	{17, {0,-2000,-1200}, },
	{22, {0,-2000,-1200}, },
	{27, {0,-2000,-1200}, },
	{31, {-2019,1409,-5718}, },
	{35, {-1554,1199,-6487}, },
	{39, {-4242,-1908,-7315}, },
	{45, {-2605,-1148,-6980}, },
	{49, {-1718,-2244,-6297}, },
	{53, {-1329,1012,-5652}, },
	{58, {-178,-215,-5322}, },
	{60, {8,-2832,-4529}, },
	{62, {167,-4085,-2891}, },
	{66, {6,-2025,-1200}, },
	{94, {1,-1998,-1174}, }
};
static PolyKeyFrame Magazine_Rotation[18] = 
{
	{0, {0,0,0}, },
	{4, {0,0,0}, },
	{9, {0,0,0}, },
	{13, {0,0,0}, },
	{17, {0,0,0}, },
	{22, {0,0,0}, },
	{27, {0,0,0}, },
	{31, {14769,-649,-597}, },
	{35, {22651,-865,-1493}, },
	{39, {31057,-1282,-2093}, },
	{45, {29978,5069,6813}, },
	{49, {24349,1160,1228}, },
	{53, {11317,-755,-1388}, },
	{58, {-2621,-716,-279}, },
	{60, {-2452,-1403,797}, },
	{62, {-5748,-428,576}, },
	{66, {-48,-399,-562}, },
	{94, {0,871,0}, }
};
static PolyKeyFrame Magazine_Scaling[18] = 
{
	{0, {10,10,10} },
	{4, {10,10,10} },
	{9, {10,10,10} },
	{13, {10,10,10} },
	{17, {10,10,10} },
	{22, {10,10,10} },
	{27, {10,10,10} },
	{31, {10,10,10} },
	{35, {10,10,10} },
	{39, {10,10,10} },
	{45, {10,10,10} },
	{49, {10,10,10} },
	{53, {10,10,10} },
	{58, {10,10,10} },
	{60, {10,10,10} },
	{62, {10,10,10} },
	{66, {10,10,10} },
	{94, {10,10,10} }
};


static PolyKeyFrame AR_Translation[25] = 
{
	{0, {2050,2150,-4150}, },
	{4, {2072,2272,-3992}, },
	{9, {2114,2505,-3691}, },
	{13, {2069,2259,-4009}, },
	{17, {2109,2478,-3727}, },
	{22, {2266,3353,-2595}, },
	{27, {2423,5562,-1463}, },
	{31, {2421,4218,-1463}, },
	{35, {2526,4203,-2061}, },
	{39, {2416,4191,-2254}, },
	{45, {2318,4358,-1565}, },
	{49, {2294,4034,-1441}, },
	{53, {2278,3420,-1853}, },
	{58, {2229,3148,-1460}, },
	{60, {2209,3035,-1456}, },
	{62, {2188,2921,-1452}, },
	{66, {2180,2876,-1841}, },
	{70, {2148,3147,-2418}, },
	{73, {2131,3283,-2707}, },
	{76, {2115,3418,-2996}, },
	{80, {2124,3341,-2831}, },
	{83, {2103,3001,-3208}, },
	{86, {2082,2660,-3585}, },
	{89, {2061,2320,-3962}, },
	{94, {2050,2150,-4150}, }
};
static PolyKeyFrame AR_Rotation[25] = 
{
	{0, {0,0,0}, },
	{4, {619,-37,64}, },
	{9, {1797,-107,185}, },
	{13, {550,-33,57}, },
	{17, {1658,-99,171}, },
	{22, {6091,-364,627}, },
	{27, {11015,3896,-2477}, },
	{31, {10466,-625,1078}, },
	{35, {10389,-621,1070}, },
	{39, {10332,-617,1064}, },
	{45, {12009,-734,524}, },
	{49, {11437,-673,469}, },
	{53, {9157,-542,540}, },
	{58, {10837,-546,253}, },
	{60, {10600,180,-962}, },
	{62, {10364,905,-2176}, },
	{66, {10613,-431,75}, },
	{70, {6595,-315,84}, },
	{73, {4585,-257,88}, },
	{76, {2576,-198,92}, },
	{80, {3724,-232,90}, },
	{83, {2660,-165,64}, },
	{86, {1596,-99,38}, },
	{89, {532,-33,13}, },
	{94, {0,0,0}, }
};
static PolyKeyFrame AR_Scaling[25] = 
{
	{0, {10,10,10} },
	{4, {10,10,10} },
	{9, {10,10,10} },
	{13, {10,10,10} },
	{17, {10,10,10} },
	{22, {10,10,10} },
	{27, {10,10,10} },
	{31, {10,10,10} },
	{35, {10,10,10} },
	{39, {10,10,10} },
	{45, {10,10,10} },
	{49, {10,10,10} },
	{53, {10,10,10} },
	{58, {10,10,10} },
	{60, {10,10,10} },
	{62, {10,10,10} },
	{66, {10,10,10} },
	{70, {10,10,10} },
	{73, {10,10,10} },
	{76, {10,10,10} },
	{80, {10,10,10} },
	{83, {10,10,10} },
	{86, {10,10,10} },
	{89, {10,10,10} },
	{94, {10,10,10} }
};


static PolyKeyFrame RightArm_Translation[25] = 
{
	{0, {2050,3200,-4150}, },
	{4, {2072,3322,-3992}, },
	{9, {2114,3555,-3691}, },
	{13, {2069,3309,-4009}, },
	{17, {2109,3528,-3727}, },
	{22, {2266,4403,-2595}, },
	{27, {2423,6612,-1463}, },
	{31, {2421,5268,-1463}, },
	{35, {2526,5253,-2061}, },
	{39, {2416,5241,-2254}, },
	{45, {2318,5408,-1565}, },
	{49, {2294,5084,-1441}, },
	{53, {2278,4470,-1853}, },
	{58, {2229,4198,-1460}, },
	{60, {2209,4085,-1456}, },
	{62, {2188,3971,-1452}, },
	{66, {2180,3926,-1841}, },
	{70, {2148,4197,-2418}, },
	{73, {2131,4333,-2707}, },
	{76, {2115,4468,-2996}, },
	{80, {2124,4391,-2831}, },
	{83, {2103,4051,-3208}, },
	{86, {2082,3710,-3585}, },
	{89, {2061,3370,-3962}, },
	{94, {2050,3200,-4150}, }
};
static PolyKeyFrame RightArm_Rotation[25] = 
{
	{0, {0,0,0}, },
	{4, {619,-37,64}, },
	{9, {1797,-107,185}, },
	{13, {550,-33,57}, },
	{17, {1658,-99,171}, },
	{22, {6091,-364,627}, },
	{27, {11015,3896,-2477}, },
	{31, {10466,-625,1078}, },
	{35, {10389,-621,1070}, },
	{39, {10332,-617,1064}, },
	{45, {12009,-734,524}, },
	{49, {11437,-673,469}, },
	{53, {9157,-542,540}, },
	{58, {10837,-546,253}, },
	{60, {10600,180,-962}, },
	{62, {10364,905,-2176}, },
	{66, {10613,-431,75}, },
	{70, {6595,-315,84}, },
	{73, {4585,-257,88}, },
	{76, {2576,-198,92}, },
	{80, {3724,-232,90}, },
	{83, {2660,-165,64}, },
	{86, {1596,-99,38}, },
	{89, {532,-33,13}, },
	{94, {0,0,0}, }
};
static PolyKeyFrame RightArm_Scaling[25] = 
{
	{0, {10,10,10} },
	{4, {10,10,10} },
	{9, {10,10,10} },
	{13, {10,10,10} },
	{17, {10,10,10} },
	{22, {10,10,10} },
	{27, {10,10,10} },
	{31, {10,10,10} },
	{35, {10,10,10} },
	{39, {10,10,10} },
	{45, {10,10,10} },
	{49, {10,10,10} },
	{53, {10,10,10} },
	{58, {10,10,10} },
	{60, {10,10,10} },
	{62, {10,10,10} },
	{66, {10,10,10} },
	{70, {10,10,10} },
	{73, {10,10,10} },
	{76, {10,10,10} },
	{80, {10,10,10} },
	{83, {10,10,10} },
	{86, {10,10,10} },
	{89, {10,10,10} },
	{94, {10,10,10} }
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
	.PositionCount = 25,
	.RotationCount = 25,
	.ScalingCount = 25,
};


static PolyAnime Elbow_Anime = 
{
	.PositionData = (PolyKeyFrame*)&Elbow_Translation,
	.RotationData = (PolyKeyFrame*)&Elbow_Rotation,
	.ScalingData = (PolyKeyFrame*)&Elbow_Scaling,
	.PositionCount = 25,
	.RotationCount = 25,
	.ScalingCount = 25,
};


static PolyAnime Shoulder_Anime = 
{
	.PositionData = (PolyKeyFrame*)&Shoulder_Translation,
	.RotationData = (PolyKeyFrame*)&Shoulder_Rotation,
	.ScalingData = (PolyKeyFrame*)&Shoulder_Scaling,
	.PositionCount = 25,
	.RotationCount = 25,
	.ScalingCount = 25,
};


static PolyAnime ChargingPort_Anime = 
{
	.PositionData = (PolyKeyFrame*)&ChargingPort_Translation,
	.RotationData = (PolyKeyFrame*)&ChargingPort_Rotation,
	.ScalingData = (PolyKeyFrame*)&ChargingPort_Scaling,
	.PositionCount = 24,
	.RotationCount = 1,
	.ScalingCount = 24,
};


static PolyAnime Magazine_Anime = 
{
	.PositionData = (PolyKeyFrame*)&Magazine_Translation,
	.RotationData = (PolyKeyFrame*)&Magazine_Rotation,
	.ScalingData = (PolyKeyFrame*)&Magazine_Scaling,
	.PositionCount = 18,
	.RotationCount = 18,
	.ScalingCount = 18,
};


static PolyAnime AR_Anime = 
{
	.PositionData = (PolyKeyFrame*)&AR_Translation,
	.RotationData = (PolyKeyFrame*)&AR_Rotation,
	.ScalingData = (PolyKeyFrame*)&AR_Scaling,
	.PositionCount = 25,
	.RotationCount = 25,
	.ScalingCount = 25,
};


static PolyAnime RightArm_Anime = 
{
	.PositionData = (PolyKeyFrame*)&RightArm_Translation,
	.RotationData = (PolyKeyFrame*)&RightArm_Rotation,
	.ScalingData = (PolyKeyFrame*)&RightArm_Scaling,
	.PositionCount = 25,
	.RotationCount = 25,
	.ScalingCount = 25,
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


static PolyNode Hand_ar_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint Hand_NodeList[] = 
{
	(uint)&Hand_CyborgTP_Node,
	(uint)&Hand_ar_Node,
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


static PolyNode Elbow_ar_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint Elbow_NodeList[] = 
{
	(uint)&Elbow_CyborgTP_Node,
	(uint)&Elbow_ar_Node,
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


static PolyNode Shoulder_ar_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint Shoulder_NodeList[] = 
{
	(uint)&Shoulder_CyborgTP_Node,
	(uint)&Shoulder_ar_Node,
};


static PolyNode ChargingPort_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
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




static uint ChargingPort_NodeList[] = 
{
	(uint)&ChargingPort_CyborgTP_Node,
	(uint)&ChargingPort_ar_Node,
};


static PolyNode Magazine_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
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




static uint Magazine_NodeList[] = 
{
	(uint)&Magazine_CyborgTP_Node,
	(uint)&Magazine_ar_Node,
};


static PolyNode AR_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
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




static uint AR_NodeList[] = 
{
	(uint)&AR_CyborgTP_Node,
	(uint)&AR_ar_Node,
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


static PolyNode RightArm_ar_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint RightArm_NodeList[] = 
{
	(uint)&RightArm_CyborgTP_Node,
	(uint)&RightArm_ar_Node,
};


static PolyNode BodyBone_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};


static PolyNode BodyBone_ar_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint BodyBone_NodeList[] = 
{
	(uint)&BodyBone_CyborgTP_Node,
	(uint)&BodyBone_ar_Node,
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
AnimeHolster AR_Reload_Empty =
{
	.RootBone = (PolyBone*)&BodyBone_Bone,
	.FrameCount = 95
};










