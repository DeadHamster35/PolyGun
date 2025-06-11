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
	{0, {1298,3173,-2211}, }
};
static PolyKeyFrame Hand_Scaling[1] = 
{
	{0, {10,10,10} }
};


static PolyKeyFrame Elbow_Translation[1] = 
{
	{0, {-2700,-250,-3150}, }
};
static PolyKeyFrame Elbow_Rotation[4] = 
{
	{0, {4803,3241,194}, },
	{3, {4581,3201,358}, },
	{6, {5076,3294,-5}, },
	{10, {4803,3241,194}, }
};
static PolyKeyFrame Elbow_Scaling[4] = 
{
	{0, {10,10,10} },
	{3, {10,10,10} },
	{6, {10,10,10} },
	{10, {10,10,10} }
};


static PolyKeyFrame Shoulder_Translation[4] = 
{
	{0, {-3500,-1700,-2800}, },
	{3, {-3500,-2071,-2800}, },
	{6, {-3500,-2331,-2800}, },
	{10, {-3500,-1700,-2800}, }
};
static PolyKeyFrame Shoulder_Rotation[4] = 
{
	{0, {10636,-3878,-8064}, },
	{3, {10926,-3610,-8166}, },
	{6, {10950,-3588,-8174}, },
	{10, {10636,-3878,-8064}, }
};
static PolyKeyFrame Shoulder_Scaling[4] = 
{
	{0, {10,10,10} },
	{3, {10,10,10} },
	{6, {10,10,10} },
	{10, {10,10,10} }
};


static PolyKeyFrame SlideBone_Translation[4] = 
{
	{0, {0,0,1450}, },
	{3, {0,-453,1450}, },
	{6, {0,0,1450}, },
	{10, {0,0,1450}, }
};
static PolyKeyFrame SlideBone_Rotation[1] = 
{
	{0, {0,0,0}, }
};
static PolyKeyFrame SlideBone_Scaling[1] = 
{
	{0, {10,10,10} }
};


static PolyKeyFrame MagazineBone_Translation[1] = 
{
	{0, {0,-150,-2450}, }
};
static PolyKeyFrame MagazineBone_Rotation[1] = 
{
	{0, {0,0,0}, }
};
static PolyKeyFrame MagazineBone_Scaling[1] = 
{
	{0, {10,10,10} }
};


static PolyKeyFrame PistolBone_Translation[4] = 
{
	{0, {800,6500,-3350}, },
	{3, {800,6129,-3350}, },
	{6, {800,5917,-2956}, },
	{10, {800,6500,-3350}, }
};
static PolyKeyFrame PistolBone_Rotation[4] = 
{
	{0, {0,0,0}, },
	{3, {818,0,0}, },
	{6, {1246,0,0}, },
	{10, {0,0,0}, }
};
static PolyKeyFrame PistolBone_Scaling[4] = 
{
	{0, {10,10,10} },
	{3, {10,10,10} },
	{6, {10,10,10} },
	{10, {10,10,10} }
};


static PolyKeyFrame ArmBone_Translation[4] = 
{
	{0, {800,6500,-3500}, },
	{3, {800,6129,-3500}, },
	{6, {800,5917,-3106}, },
	{10, {800,6500,-3500}, }
};
static PolyKeyFrame ArmBone_Rotation[4] = 
{
	{0, {0,0,0}, },
	{3, {818,0,0}, },
	{6, {1246,0,0}, },
	{10, {0,0,0}, }
};
static PolyKeyFrame ArmBone_Scaling[4] = 
{
	{0, {10,10,10} },
	{3, {10,10,10} },
	{6, {10,10,10} },
	{10, {10,10,10} }
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
	.RotationCount = 4,
	.ScalingCount = 4,
};


static PolyAnime Shoulder_Anime = 
{
	.PositionData = (PolyKeyFrame*)&Shoulder_Translation,
	.RotationData = (PolyKeyFrame*)&Shoulder_Rotation,
	.ScalingData = (PolyKeyFrame*)&Shoulder_Scaling,
	.PositionCount = 4,
	.RotationCount = 4,
	.ScalingCount = 4,
};


static PolyAnime SlideBone_Anime = 
{
	.PositionData = (PolyKeyFrame*)&SlideBone_Translation,
	.RotationData = (PolyKeyFrame*)&SlideBone_Rotation,
	.ScalingData = (PolyKeyFrame*)&SlideBone_Scaling,
	.PositionCount = 4,
	.RotationCount = 1,
	.ScalingCount = 1,
};


static PolyAnime MagazineBone_Anime = 
{
	.PositionData = (PolyKeyFrame*)&MagazineBone_Translation,
	.RotationData = (PolyKeyFrame*)&MagazineBone_Rotation,
	.ScalingData = (PolyKeyFrame*)&MagazineBone_Scaling,
	.PositionCount = 1,
	.RotationCount = 1,
	.ScalingCount = 1,
};


static PolyAnime PistolBone_Anime = 
{
	.PositionData = (PolyKeyFrame*)&PistolBone_Translation,
	.RotationData = (PolyKeyFrame*)&PistolBone_Rotation,
	.ScalingData = (PolyKeyFrame*)&PistolBone_Scaling,
	.PositionCount = 4,
	.RotationCount = 4,
	.ScalingCount = 4,
};


static PolyAnime ArmBone_Anime = 
{
	.PositionData = (PolyKeyFrame*)&ArmBone_Translation,
	.RotationData = (PolyKeyFrame*)&ArmBone_Rotation,
	.ScalingData = (PolyKeyFrame*)&ArmBone_Scaling,
	.PositionCount = 4,
	.RotationCount = 4,
	.ScalingCount = 4,
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




static uint Hand_NodeList[] = 
{
	(uint)&Hand_hiraw_Node,
	(uint)&Hand_CyborgTP_Node,
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




static uint Elbow_NodeList[] = 
{
	(uint)&Elbow_hiraw_Node,
	(uint)&Elbow_CyborgTP_Node,
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




static uint Shoulder_NodeList[] = 
{
	(uint)&Shoulder_hiraw_Node,
	(uint)&Shoulder_CyborgTP_Node,
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




static uint SlideBone_NodeList[] = 
{
	(uint)&SlideBone_hiraw_Node,
	(uint)&SlideBone_CyborgTP_Node,
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




static uint MagazineBone_NodeList[] = 
{
	(uint)&MagazineBone_hiraw_Node,
	(uint)&MagazineBone_CyborgTP_Node,
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




static uint PistolBone_NodeList[] = 
{
	(uint)&PistolBone_hiraw_Node,
	(uint)&PistolBone_CyborgTP_Node,
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




static uint ArmBone_NodeList[] = 
{
	(uint)&ArmBone_hiraw_Node,
	(uint)&ArmBone_CyborgTP_Node,
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




static uint BodyBone_NodeList[] = 
{
	(uint)&BodyBone_hiraw_Node,
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




static PolyBone SlideBone_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&SlideBone_Anime,
	.NodeCount = 2,
	.NodeOffset = (PolyNode*)SlideBone_NodeList,
	.ChildCount = 0,
	.ChildOffset = (struct PolyBone*)0
};




static PolyBone MagazineBone_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&MagazineBone_Anime,
	.NodeCount = 2,
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
	.NodeCount = 2,
	.NodeOffset = (PolyNode*)PistolBone_NodeList,
	.ChildCount = 2,
	.ChildOffset = (struct PolyBone*)PistolBone_ChildList,
};




static PolyBone ArmBone_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&ArmBone_Anime,
	.NodeCount = 2,
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
	.NodeCount = 2,
	.NodeOffset = (PolyNode*)BodyBone_NodeList,
	.ChildCount = 3,
	.ChildOffset = (struct PolyBone*)BodyBone_ChildList,
};






//AnimeHolster
AnimeHolster HP_Fire =
{
	.RootBone = (PolyBone*)&BodyBone_Bone,
	.FrameCount = 11
};










