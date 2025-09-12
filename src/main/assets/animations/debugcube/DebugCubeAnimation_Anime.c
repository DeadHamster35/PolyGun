//BodyBoneAnime File
//PolyTool Animation Version 1.0


#include <nusys.h>
#include <nualsgi_n.h>
#include "common.h"




//Keyframe Data


static PolyKeyFrame CubeBone_Translation[5] = 
{
	{0, {0,2000,1000}, },
	{15, {0,3000,1000}, },
	{30, {0,2000,1000}, },
	{45, {-1000,1000,1000}, },
	{60, {0,2000,1000}, }
};
static PolyKeyFrame CubeBone_Rotation[5] = 
{
	{0, {0,0,0}, },
	{15, {0,0,32760}, },
	{30, {0,0,0}, },
	{45, {0,0,0}, },
	{60, {0,0,0}, }
};
static PolyKeyFrame CubeBone_Scaling[1] = 
{
	{0, {10,10,10} }
};


static PolyKeyFrame BodyBone_Translation[5] = 
{
	{0, {0,0,0}, },
	{15, {0,0,0}, },
	{30, {0,0,0}, },
	{45, {0,1000,0}, },
	{60, {0,0,0}, }
};
static PolyKeyFrame BodyBone_Rotation[5] = 
{
	{0, {0,0,0}, },
	{15, {0,0,0}, },
	{30, {0,0,0}, },
	{45, {0,0,-8190}, },
	{60, {0,0,0}, }
};
static PolyKeyFrame BodyBone_Scaling[1] = 
{
	{0, {10,10,10} }
};








//Anime Structs


static PolyAnime CubeBone_Anime = 
{
	.PositionData = (PolyKeyFrame*)&CubeBone_Translation,
	.RotationData = (PolyKeyFrame*)&CubeBone_Rotation,
	.ScalingData = (PolyKeyFrame*)&CubeBone_Scaling,
	.PositionCount = 5,
	.RotationCount = 5,
	.ScalingCount = 1,
};


static PolyAnime BodyBone_Anime = 
{
	.PositionData = (PolyKeyFrame*)&BodyBone_Translation,
	.RotationData = (PolyKeyFrame*)&BodyBone_Rotation,
	.ScalingData = (PolyKeyFrame*)&BodyBone_Scaling,
	.PositionCount = 5,
	.RotationCount = 5,
	.ScalingCount = 1,
};








//Model Node Lists
static uint CubeBone_blackwhitechecker_MeshList[] = 
{
	(uint)&Draw_DebugCube_M
};




static PolyNode CubeBone_blackwhitechecker_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_blackwhitechecker_T,
	.MeshOffsets = (uint*)&CubeBone_blackwhitechecker_MeshList,
	.ClosingDL = 0,
};




static uint CubeBone_NodeList[] = 
{
	(uint)&CubeBone_blackwhitechecker_Node,
};


static PolyNode BodyBone_blackwhitechecker_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
	.ClosingDL = 0,
};




static uint BodyBone_NodeList[] = 
{
	(uint)&BodyBone_blackwhitechecker_Node,
};










//PolyBone Structs




static PolyBone CubeBone_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&CubeBone_Anime,
	.NodeCount = 1,
	.NodeOffset = (PolyNode*)CubeBone_NodeList,
	.ChildCount = 0,
	.ChildOffset = (struct PolyBone*)0
};




// ChildArray
static PolyBone* BodyBone_ChildList[] = 
{
	(PolyBone*)&CubeBone_Bone,
};
// PolyBone
static PolyBone BodyBone_Bone = 
{
	.MeshScale = 1,
	.AnimeData = (PolyAnime*)&BodyBone_Anime,
	.NodeCount = 1,
	.NodeOffset = (PolyNode*)BodyBone_NodeList,
	.ChildCount = 1,
	.ChildOffset = (struct PolyBone*)BodyBone_ChildList,
};






//AnimeHolster
AnimeHolster DebugCubeAnimation =
{
	.RootBone = (PolyBone*)&BodyBone_Bone,
	.FrameCount = 61,
    .ActionFrame = 0
};










