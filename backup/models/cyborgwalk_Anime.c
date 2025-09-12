#include <nusys.h>
#include "../../graphic.h"
#include "../../animations.h"
#include "../../FPGraphics.h"
#include "cyborgwalk.h"


SVector LeftPalm_PositionData[38] = 
{
	{182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, 
	{182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, 
	{182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, 
	{182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, 
	{182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, 
	{182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, 
	{182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, 
	{182, 713, -1087}, {182, 713, -1087}, {182, 713, -1087}, 
};
SVector LeftPalm_AngleData[38] = 
{
	{-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, 
	{-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, 
	{-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, 
	{-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, 
	{-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, 
	{-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, 
	{-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, 
	{-40, 27, 59}, {-40, 27, 59}, {-40, 27, 59}, 
};
SVector LeftPalm_ScaleData[38] = 
{
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, 
};




PolyAnime LeftPalm_Anime = 
{
	.PositionData = (SVector*)&LeftPalm_PositionData,
	.AngleData = (SVector*)&LeftPalm_AngleData,
	.ScalingData = (SVector*)&LeftPalm_ScaleData,
};


SVector LeftHandBone_PositionData[38] = 
{
	{-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, 
	{-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, 
	{-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, 
	{-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, 
	{-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, 
	{-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, 
	{-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, 
	{-400, 0, -650}, {-400, 0, -650}, {-400, 0, -650}, 
};
SVector LeftHandBone_AngleData[38] = 
{
	{11, 6, -18}, {12, 7, -18}, {13, 8, -18}, {13, 10, -19}, {14, 11, -19}, 
	{14, 12, -20}, {15, 13, -20}, {15, 14, -20}, {15, 13, -20}, {14, 11, -19}, 
	{13, 9, -19}, {12, 8, -18}, {11, 6, -18}, {11, 6, -18}, {11, 6, -18}, 
	{11, 6, -18}, {11, 6, -18}, {11, 6, -18}, {11, 6, -18}, {11, 6, -18}, 
	{11, 6, -18}, {11, 6, -18}, {11, 6, -18}, {11, 6, -18}, {11, 6, -18}, 
	{11, 6, -18}, {11, 6, -18}, {11, 6, -18}, {11, 6, -18}, {11, 6, -18}, 
	{11, 6, -18}, {11, 6, -18}, {11, 6, -18}, {11, 6, -18}, {11, 6, -18}, 
	{11, 6, -18}, {11, 6, -18}, {11, 6, -18}, 
};
SVector LeftHandBone_ScaleData[38] = 
{
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, 
};




PolyAnime LeftHandBone_Anime = 
{
	.PositionData = (SVector*)&LeftHandBone_PositionData,
	.AngleData = (SVector*)&LeftHandBone_AngleData,
	.ScalingData = (SVector*)&LeftHandBone_ScaleData,
};


SVector LeftArmBone_PositionData[38] = 
{
	{-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, 
	{-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, 
	{-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, 
	{-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, 
	{-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, 
	{-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, 
	{-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, 
	{-550, -100, 1400}, {-550, -100, 1400}, {-550, -100, 1400}, 
};
SVector LeftArmBone_AngleData[38] = 
{
	{33, 7, -44}, {34, 8, -44}, {34, 8, -44}, {35, 9, -44}, {35, 9, -43}, 
	{36, 10, -43}, {36, 10, -43}, {37, 11, -43}, {36, 10, -43}, {35, 9, -43}, 
	{35, 9, -44}, {34, 8, -44}, {33, 7, -44}, {33, 7, -44}, {33, 7, -44}, 
	{33, 7, -44}, {33, 7, -44}, {33, 7, -44}, {34, 8, -44}, {35, 9, -43}, 
	{36, 10, -43}, {37, 11, -43}, {38, 12, -43}, {38, 13, -43}, {39, 14, -43}, 
	{40, 15, -43}, {39, 13, -43}, {38, 12, -43}, {37, 11, -43}, {36, 10, -43}, 
	{35, 8, -44}, {33, 7, -44}, {33, 7, -44}, {33, 7, -44}, {33, 7, -44}, 
	{33, 7, -44}, {33, 7, -44}, {33, 7, -44}, 
};
SVector LeftArmBone_ScaleData[38] = 
{
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, 
};




PolyAnime LeftArmBone_Anime = 
{
	.PositionData = (SVector*)&LeftArmBone_PositionData,
	.AngleData = (SVector*)&LeftArmBone_AngleData,
	.ScalingData = (SVector*)&LeftArmBone_ScaleData,
};


SVector LeftFootBone_PositionData[38] = 
{
	{-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, 
	{-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, 
	{-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, 
	{-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, 
	{-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, 
	{-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, 
	{-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, 
	{-250, 50, -1650}, {-250, 50, -1650}, {-250, 50, -1650}, 
};
SVector LeftFootBone_AngleData[38] = 
{
	{-23, -3, 1}, {-23, -3, 1}, {-23, -3, 1}, {-23, -3, 1}, {-23, -3, 1}, 
	{-23, -3, 1}, {-23, -3, 1}, {-23, -3, 1}, {-23, -3, 1}, {-23, -3, 1}, 
	{-23, -3, 1}, {-23, -3, 1}, {-23, -3, 1}, {-23, -3, 1}, {-23, -3, 1}, 
	{-23, -3, 1}, {-23, -3, 1}, {-23, -3, 1}, {-23, -3, 1}, {-23, -3, 1}, 
	{-23, -3, 1}, {-23, -3, 1}, {-23, -3, 1}, {-23, -3, 1}, {-23, -3, 1}, 
	{-23, -3, 1}, {-26, -3, 1}, {-29, -4, 1}, {-33, -4, 1}, {-36, -4, 1}, 
	{-39, -4, 1}, {-42, -5, 2}, {-39, -4, 1}, {-36, -4, 1}, {-33, -4, 1}, 
	{-29, -4, 1}, {-26, -3, 1}, {-23, -3, 1}, 
};
SVector LeftFootBone_ScaleData[38] = 
{
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, 
};




PolyAnime LeftFootBone_Anime = 
{
	.PositionData = (SVector*)&LeftFootBone_PositionData,
	.AngleData = (SVector*)&LeftFootBone_AngleData,
	.ScalingData = (SVector*)&LeftFootBone_ScaleData,
};


SVector LeftLegBone_PositionData[38] = 
{
	{-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, 
	{-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, 
	{-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, 
	{-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, 
	{-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, 
	{-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, 
	{-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, 
	{-250, -150, -100}, {-250, -150, -100}, {-250, -150, -100}, 
};
SVector LeftLegBone_AngleData[38] = 
{
	{22, 3, 1}, {24, 3, 1}, {27, 3, 1}, {29, 3, 1}, {32, 4, 1}, 
	{34, 4, 1}, {36, 4, 1}, {39, 4, 2}, {38, 4, 2}, {37, 4, 2}, 
	{35, 4, 1}, {34, 4, 1}, {33, 4, 1}, {32, 4, 1}, {31, 4, 1}, 
	{30, 4, 1}, {29, 3, 1}, {27, 3, 1}, {24, 3, 1}, {21, 3, 1}, 
	{17, 3, 1}, {14, 2, 0}, {10, 2, 0}, {7, 2, 0}, {4, 1, 0}, 
	{0, 1, 0}, {-2, 1, 0}, {-4, 1, 0}, {-6, 1, 0}, {-8, 0, 0}, 
	{-10, 0, 0}, {-13, 0, 0}, {-7, 0, 0}, {-1, 1, 0}, {5, 1, 0}, 
	{10, 2, 0}, {16, 2, 0}, {22, 3, 1}, 
};
SVector LeftLegBone_ScaleData[38] = 
{
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, 
};




PolyAnime LeftLegBone_Anime = 
{
	.PositionData = (SVector*)&LeftLegBone_PositionData,
	.AngleData = (SVector*)&LeftLegBone_AngleData,
	.ScalingData = (SVector*)&LeftLegBone_ScaleData,
};


SVector RightPalm_PositionData[38] = 
{
	{-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, 
	{-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, 
	{-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, 
	{-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, 
	{-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, 
	{-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, 
	{-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, 
	{-152, 615, -1089}, {-152, 615, -1089}, {-152, 615, -1089}, 
};
SVector RightPalm_AngleData[38] = 
{
	{-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, 
	{-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, 
	{-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, 
	{-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, 
	{-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, 
	{-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, 
	{-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, 
	{-42, 10, 2}, {-42, 10, 2}, {-42, 10, 2}, 
};
SVector RightPalm_ScaleData[38] = 
{
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, 
};




PolyAnime RightPalm_Anime = 
{
	.PositionData = (SVector*)&RightPalm_PositionData,
	.AngleData = (SVector*)&RightPalm_AngleData,
	.ScalingData = (SVector*)&RightPalm_ScaleData,
};


SVector RightHandBone_PositionData[38] = 
{
	{400, 0, -650}, {400, 0, -650}, {400, 0, -650}, {400, 0, -650}, {400, 0, -650}, 
	{400, 0, -650}, {400, 0, -650}, {400, 0, -650}, {400, 0, -650}, {400, 0, -650}, 
	{400, 0, -650}, {400, 0, -650}, {400, 0, -650}, {400, 0, -650}, {400, 0, -650}, 
	{400, 0, -650}, {400, 0, -650}, {400, 0, -650}, {400, 0, -650}, {400, 0, -650}, 
	{400, 0, -650}, {400, 0, -650}, {400, 0, -650}, {400, 0, -650}, {400, 0, -650}, 
	{400, 0, -650}, {400, 0, -650}, {400, 0, -650}, {400, 0, -650}, {400, 0, -650}, 
	{400, 0, -650}, {400, 0, -650}, {400, 0, -650}, {400, 0, -650}, {400, 0, -650}, 
	{400, 0, -650}, {400, 0, -650}, {400, 0, -650}, 
};
SVector RightHandBone_AngleData[38] = 
{
	{63, -7, 29}, {63, -7, 29}, {63, -7, 29}, {63, -7, 29}, {63, -7, 29}, 
	{63, -7, 29}, {63, -7, 29}, {63, -7, 29}, {63, -7, 29}, {63, -7, 29}, 
	{63, -7, 29}, {63, -7, 29}, {63, -7, 29}, {63, -7, 29}, {63, -7, 29}, 
	{63, -7, 29}, {63, -7, 29}, {63, -7, 29}, {63, -7, 29}, {63, -7, 29}, 
	{63, -7, 29}, {63, -7, 29}, {63, -7, 29}, {63, -7, 29}, {63, -7, 29}, 
	{63, -7, 29}, {63, -7, 29}, {63, -7, 29}, {63, -7, 29}, {63, -7, 29}, 
	{63, -7, 29}, {63, -7, 29}, {63, -7, 29}, {63, -7, 29}, {63, -7, 29}, 
	{63, -7, 29}, {63, -7, 29}, {63, -7, 29}, 
};
SVector RightHandBone_ScaleData[38] = 
{
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, 
};




PolyAnime RightHandBone_Anime = 
{
	.PositionData = (SVector*)&RightHandBone_PositionData,
	.AngleData = (SVector*)&RightHandBone_AngleData,
	.ScalingData = (SVector*)&RightHandBone_ScaleData,
};


SVector RightArmBone_PositionData[38] = 
{
	{550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, 
	{550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, 
	{550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, 
	{550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, 
	{550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, 
	{550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, 
	{550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, 
	{550, -100, 1400}, {550, -100, 1400}, {550, -100, 1400}, 
};
SVector RightArmBone_AngleData[38] = 
{
	{-18, -9, -33}, {-17, -8, -33}, {-16, -8, -34}, {-15, -7, -34}, {-14, -6, -34}, 
	{-12, -5, -34}, {-11, -4, -34}, {-10, -3, -34}, {-12, -4, -34}, {-13, -6, -34}, 
	{-15, -7, -34}, {-16, -8, -33}, {-18, -9, -33}, {-18, -9, -33}, {-18, -9, -33}, 
	{-18, -9, -33}, {-18, -9, -33}, {-18, -9, -33}, {-18, -9, -33}, {-17, -9, -33}, 
	{-17, -8, -33}, {-16, -8, -34}, {-16, -7, -34}, {-15, -7, -34}, {-15, -7, -34}, 
	{-14, -6, -34}, {-15, -7, -34}, {-15, -7, -34}, {-16, -8, -34}, {-17, -8, -33}, 
	{-17, -9, -33}, {-18, -9, -33}, {-18, -9, -33}, {-18, -9, -33}, {-18, -9, -33}, 
	{-18, -9, -33}, {-18, -9, -33}, {-18, -9, -33}, 
};
SVector RightArmBone_ScaleData[38] = 
{
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, 
};




PolyAnime RightArmBone_Anime = 
{
	.PositionData = (SVector*)&RightArmBone_PositionData,
	.AngleData = (SVector*)&RightArmBone_AngleData,
	.ScalingData = (SVector*)&RightArmBone_ScaleData,
};


SVector RightFootBone_PositionData[38] = 
{
	{250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, 
	{250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, 
	{250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, 
	{250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, 
	{250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, 
	{250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, 
	{250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, 
	{250, 50, -1650}, {250, 50, -1650}, {250, 50, -1650}, 
};
SVector RightFootBone_AngleData[38] = 
{
	{-2, 11, 0}, {-2, 11, 0}, {-34, 13, 0}, {-2, 11, 0}, {-2, 11, 0}, 
	{-28, 13, 0}, {-2, 11, 0}, {-2, 11, 0}, {-2, 11, 0}, {-2, 11, 0}, 
	{-2, 11, 0}, {-2, 11, 0}, {-2, 11, 0}, {-2, 11, 0}, {-2, 11, 0}, 
	{-2, 11, 0}, {-2, 11, 0}, {-2, 11, 0}, {-2, 11, 0}, {-2, 11, 0}, 
	{-2, 11, 0}, {-2, 11, 0}, {-2, 11, 0}, {-2, 11, 0}, {-2, 11, 0}, 
	{-2, 11, 0}, {-2, 11, 0}, {-2, 11, 0}, {-2, 11, 0}, {-2, 11, 0}, 
	{-2, 11, 0}, {-2, 11, 0}, {-2, 11, 0}, {-2, 11, 0}, {-2, 11, 0}, 
	{-2, 11, 0}, {-2, 11, 0}, {-2, 11, 0}, 
};
SVector RightFootBone_ScaleData[38] = 
{
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, 
};




PolyAnime RightFootBone_Anime = 
{
	.PositionData = (SVector*)&RightFootBone_PositionData,
	.AngleData = (SVector*)&RightFootBone_AngleData,
	.ScalingData = (SVector*)&RightFootBone_ScaleData,
};


SVector RightLegBone_PositionData[38] = 
{
	{250, -150, -100}, {250, -150, -100}, {250, -150, -100}, {250, -150, -100}, {250, -150, -100}, 
	{250, -150, -100}, {250, -150, -100}, {250, -150, -100}, {250, -150, -100}, {250, -150, -100}, 
	{250, -150, -100}, {250, -150, -100}, {250, -150, -100}, {250, -150, -100}, {250, -150, -100}, 
	{250, -150, -100}, {250, -150, -100}, {250, -150, -100}, {250, -150, -100}, {250, -150, -100}, 
	{250, -150, -100}, {250, -150, -100}, {250, -150, -100}, {250, -150, -100}, {250, -150, -100}, 
	{250, -150, -100}, {250, -150, -100}, {250, -150, -100}, {250, -150, -100}, {250, -150, -100}, 
	{250, -150, -100}, {250, -150, -100}, {250, -150, -100}, {250, -150, -100}, {250, -150, -100}, 
	{250, -150, -100}, {250, -150, -100}, {250, -150, -100}, 
};
SVector RightLegBone_AngleData[38] = 
{
	{2, -13, 12}, {-2, -12, 13}, {-6, -12, 13}, {-9, -12, 14}, {-13, -11, 15}, 
	{-17, -11, 16}, {-20, -11, 17}, {-24, -10, 17}, {-22, -11, 17}, {-19, -11, 16}, 
	{-17, -11, 16}, {-14, -11, 15}, {-11, -12, 15}, {-11, -12, 15}, {-10, -12, 14}, 
	{-9, -12, 14}, {-8, -12, 14}, {-7, -12, 14}, {-3, -12, 13}, {1, -12, 12}, 
	{6, -12, 11}, {10, -12, 10}, {14, -12, 9}, {18, -12, 8}, {22, -13, 7}, 
	{26, -13, 7}, {28, -13, 6}, {30, -12, 6}, {32, -12, 5}, {34, -12, 5}, 
	{35, -12, 5}, {37, -12, 4}, {31, -12, 5}, {26, -12, 7}, {20, -12, 8}, 
	{14, -12, 9}, {8, -13, 11}, {2, -13, 12}, 
};
SVector RightLegBone_ScaleData[38] = 
{
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, 
};




PolyAnime RightLegBone_Anime = 
{
	.PositionData = (SVector*)&RightLegBone_PositionData,
	.AngleData = (SVector*)&RightLegBone_AngleData,
	.ScalingData = (SVector*)&RightLegBone_ScaleData,
};


SVector BodyBone_PositionData[38] = 
{
	{0, 0, 3151}, {0, 0, 3159}, {0, 0, 3168}, {0, 0, 3176}, {0, 0, 3184}, 
	{0, 0, 3193}, {0, 0, 3201}, {0, 0, 3209}, {0, 0, 3183}, {0, 0, 3158}, 
	{0, 0, 3132}, {0, 0, 3106}, {0, 0, 3080}, {0, 0, 3094}, {0, 0, 3108}, 
	{0, 0, 3122}, {0, 0, 3137}, {0, 0, 3151}, {0, 0, 3180}, {0, 0, 3210}, 
	{0, 0, 3240}, {0, 0, 3269}, {0, 0, 3299}, {0, 0, 3328}, {0, 0, 3358}, 
	{0, 0, 3387}, {0, 0, 3364}, {0, 0, 3341}, {0, 0, 3318}, {0, 0, 3295}, 
	{0, 0, 3272}, {0, 0, 3249}, {0, 0, 3233}, {0, 0, 3217}, {0, 0, 3200}, 
	{0, 0, 3184}, {0, 0, 3167}, {0, 0, 3151}, 
};
SVector BodyBone_AngleData[38] = 
{
	{0, 0, -5}, {0, 0, -5}, {0, 0, -5}, {0, 0, -5}, {0, 0, -5}, 
	{0, 0, -5}, {0, 0, -5}, {0, 0, -5}, {0, 0, -5}, {0, 0, -5}, 
	{0, 0, -5}, {0, 0, -5}, {0, 0, -5}, {0, 0, -5}, {0, 0, -5}, 
	{0, 0, -5}, {0, 0, -5}, {0, 0, -5}, {0, 0, -5}, {0, 0, -5}, 
	{0, 0, -5}, {0, 0, -5}, {0, 0, -5}, {0, 0, -5}, {0, 0, -5}, 
	{0, 0, -5}, {0, 0, -5}, {0, 0, -5}, {0, 0, -5}, {0, 0, -5}, 
	{0, 0, -5}, {0, 0, -5}, {0, 0, -5}, {0, 0, -5}, {0, 0, -5}, 
	{0, 0, -5}, {0, 0, -5}, {0, 0, -5}, 
};
SVector BodyBone_ScaleData[38] = 
{
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, {100, 100, 100}, 
	{100, 100, 100}, {100, 100, 100}, 
};




PolyAnime BodyBone_Anime = 
{
	.PositionData = (SVector*)&BodyBone_PositionData,
	.AngleData = (SVector*)&BodyBone_AngleData,
	.ScalingData = (SVector*)&BodyBone_ScaleData,
};


uint LeftPalm_CyborgTP_MeshList[] = 
{
};


PolyNode LeftPalm_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};


uint LeftPalm_CyborgLimbs_MeshList[] = 
{
};


PolyNode LeftPalm_CyborgLimbs_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};


uint LeftPalm_DefaultMaterial_MeshList[] = 
{
};


PolyNode LeftPalm_DefaultMaterial_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};




uint LeftPalm_NodeList[] = 
{
	(uint)&LeftPalm_CyborgTP_Node,
	(uint)&LeftPalm_CyborgLimbs_Node,
	(uint)&LeftPalm_DefaultMaterial_Node,
};


uint LeftHandBone_CyborgTP_MeshList[] = 
{
};


PolyNode LeftHandBone_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};


uint LeftHandBone_CyborgLimbs_MeshList[] = 
{
	(uint)&Draw_CyborgLeftHand_M
};


PolyNode LeftHandBone_CyborgLimbs_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_CyborgLimbs_T,
	.MeshOffsets = (uint*)&LeftHandBone_CyborgLimbs_MeshList,
};


uint LeftHandBone_DefaultMaterial_MeshList[] = 
{
};


PolyNode LeftHandBone_DefaultMaterial_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};




uint LeftHandBone_NodeList[] = 
{
	(uint)&LeftHandBone_CyborgTP_Node,
	(uint)&LeftHandBone_CyborgLimbs_Node,
	(uint)&LeftHandBone_DefaultMaterial_Node,
};


uint LeftArmBone_CyborgTP_MeshList[] = 
{
};


PolyNode LeftArmBone_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};


uint LeftArmBone_CyborgLimbs_MeshList[] = 
{
	(uint)&Draw_CyborgLeftArm_M
};


PolyNode LeftArmBone_CyborgLimbs_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_CyborgLimbs_T,
	.MeshOffsets = (uint*)&LeftArmBone_CyborgLimbs_MeshList,
};


uint LeftArmBone_DefaultMaterial_MeshList[] = 
{
};


PolyNode LeftArmBone_DefaultMaterial_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};




uint LeftArmBone_NodeList[] = 
{
	(uint)&LeftArmBone_CyborgTP_Node,
	(uint)&LeftArmBone_CyborgLimbs_Node,
	(uint)&LeftArmBone_DefaultMaterial_Node,
};


uint LeftFootBone_CyborgTP_MeshList[] = 
{
};


PolyNode LeftFootBone_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};


uint LeftFootBone_CyborgLimbs_MeshList[] = 
{
	(uint)&Draw_CyborgLeftFoot_M
};


PolyNode LeftFootBone_CyborgLimbs_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_CyborgLimbs_T,
	.MeshOffsets = (uint*)&LeftFootBone_CyborgLimbs_MeshList,
};


uint LeftFootBone_DefaultMaterial_MeshList[] = 
{
};


PolyNode LeftFootBone_DefaultMaterial_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};




uint LeftFootBone_NodeList[] = 
{
	(uint)&LeftFootBone_CyborgTP_Node,
	(uint)&LeftFootBone_CyborgLimbs_Node,
	(uint)&LeftFootBone_DefaultMaterial_Node,
};


uint LeftLegBone_CyborgTP_MeshList[] = 
{
};


PolyNode LeftLegBone_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};


uint LeftLegBone_CyborgLimbs_MeshList[] = 
{
	(uint)&Draw_CyborgLeftThigh_M
};


PolyNode LeftLegBone_CyborgLimbs_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_CyborgLimbs_T,
	.MeshOffsets = (uint*)&LeftLegBone_CyborgLimbs_MeshList,
};


uint LeftLegBone_DefaultMaterial_MeshList[] = 
{
};


PolyNode LeftLegBone_DefaultMaterial_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};




uint LeftLegBone_NodeList[] = 
{
	(uint)&LeftLegBone_CyborgTP_Node,
	(uint)&LeftLegBone_CyborgLimbs_Node,
	(uint)&LeftLegBone_DefaultMaterial_Node,
};


uint RightPalm_CyborgTP_MeshList[] = 
{
};


PolyNode RightPalm_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};


uint RightPalm_CyborgLimbs_MeshList[] = 
{
};


PolyNode RightPalm_CyborgLimbs_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};


uint RightPalm_DefaultMaterial_MeshList[] = 
{
};


PolyNode RightPalm_DefaultMaterial_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};




uint RightPalm_NodeList[] = 
{
	(uint)&RightPalm_CyborgTP_Node,
	(uint)&RightPalm_CyborgLimbs_Node,
	(uint)&RightPalm_DefaultMaterial_Node,
};


uint RightHandBone_CyborgTP_MeshList[] = 
{
};


PolyNode RightHandBone_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};


uint RightHandBone_CyborgLimbs_MeshList[] = 
{
	(uint)&Draw_CyborgRightHand_M
};


PolyNode RightHandBone_CyborgLimbs_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_CyborgLimbs_T,
	.MeshOffsets = (uint*)&RightHandBone_CyborgLimbs_MeshList,
};


uint RightHandBone_DefaultMaterial_MeshList[] = 
{
};


PolyNode RightHandBone_DefaultMaterial_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};




uint RightHandBone_NodeList[] = 
{
	(uint)&RightHandBone_CyborgTP_Node,
	(uint)&RightHandBone_CyborgLimbs_Node,
	(uint)&RightHandBone_DefaultMaterial_Node,
};


uint RightArmBone_CyborgTP_MeshList[] = 
{
};


PolyNode RightArmBone_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};


uint RightArmBone_CyborgLimbs_MeshList[] = 
{
	(uint)&Draw_CyborgRightArm_M
};


PolyNode RightArmBone_CyborgLimbs_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_CyborgLimbs_T,
	.MeshOffsets = (uint*)&RightArmBone_CyborgLimbs_MeshList,
};


uint RightArmBone_DefaultMaterial_MeshList[] = 
{
};


PolyNode RightArmBone_DefaultMaterial_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};




uint RightArmBone_NodeList[] = 
{
	(uint)&RightArmBone_CyborgTP_Node,
	(uint)&RightArmBone_CyborgLimbs_Node,
	(uint)&RightArmBone_DefaultMaterial_Node,
};


uint RightFootBone_CyborgTP_MeshList[] = 
{
};


PolyNode RightFootBone_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};


uint RightFootBone_CyborgLimbs_MeshList[] = 
{
	(uint)&Draw_CyborgRightFoot_M
};


PolyNode RightFootBone_CyborgLimbs_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_CyborgLimbs_T,
	.MeshOffsets = (uint*)&RightFootBone_CyborgLimbs_MeshList,
};


uint RightFootBone_DefaultMaterial_MeshList[] = 
{
};


PolyNode RightFootBone_DefaultMaterial_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};




uint RightFootBone_NodeList[] = 
{
	(uint)&RightFootBone_CyborgTP_Node,
	(uint)&RightFootBone_CyborgLimbs_Node,
	(uint)&RightFootBone_DefaultMaterial_Node,
};


uint RightLegBone_CyborgTP_MeshList[] = 
{
};


PolyNode RightLegBone_CyborgTP_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};


uint RightLegBone_CyborgLimbs_MeshList[] = 
{
	(uint)&Draw_CyborgRightThigh_M
};


PolyNode RightLegBone_CyborgLimbs_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_CyborgLimbs_T,
	.MeshOffsets = (uint*)&RightLegBone_CyborgLimbs_MeshList,
};


uint RightLegBone_DefaultMaterial_MeshList[] = 
{
};


PolyNode RightLegBone_DefaultMaterial_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};




uint RightLegBone_NodeList[] = 
{
	(uint)&RightLegBone_CyborgTP_Node,
	(uint)&RightLegBone_CyborgLimbs_Node,
	(uint)&RightLegBone_DefaultMaterial_Node,
};


uint BodyBone_CyborgTP_MeshList[] = 
{
	(uint)&Draw_CyborgTorso_M
};


PolyNode BodyBone_CyborgTP_Node = 
{
	.MeshCount = 1,
	.TextureOffset = (uint)&Draw_CyborgTP_T,
	.MeshOffsets = (uint*)&BodyBone_CyborgTP_MeshList,
};


uint BodyBone_CyborgLimbs_MeshList[] = 
{
};


PolyNode BodyBone_CyborgLimbs_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};


uint BodyBone_DefaultMaterial_MeshList[] = 
{
};


PolyNode BodyBone_DefaultMaterial_Node = 
{
	.MeshCount = 0,
	.TextureOffset = 0,
	.MeshOffsets = (uint*)0,
};




uint BodyBone_NodeList[] = 
{
	(uint)&BodyBone_CyborgTP_Node,
	(uint)&BodyBone_CyborgLimbs_Node,
	(uint)&BodyBone_DefaultMaterial_Node,
};


uint LeftPalm_ChildList[] = 
{
};


PolyBone LeftPalm_Bone =
{
	.MeshScale = 1,
	.AnimationOffset = &LeftPalm_Anime,
	.NodeCount = 3,
	.NodeOffset = (uint*)LeftPalm_NodeList,
	.ChildCount = 0,
	.ChildOffset = (uint*)LeftPalm_ChildList,
};


uint LeftHandBone_ChildList[] = 
{
	(uint)&LeftPalm_Bone,
};


PolyBone LeftHandBone_Bone =
{
	.MeshScale = 1,
	.AnimationOffset = &LeftHandBone_Anime,
	.NodeCount = 3,
	.NodeOffset = (uint*)LeftHandBone_NodeList,
	.ChildCount = 1,
	.ChildOffset = (uint*)LeftHandBone_ChildList,
};


uint LeftArmBone_ChildList[] = 
{
	(uint)&LeftHandBone_Bone,
};


PolyBone LeftArmBone_Bone =
{
	.MeshScale = 1,
	.AnimationOffset = &LeftArmBone_Anime,
	.NodeCount = 3,
	.NodeOffset = (uint*)LeftArmBone_NodeList,
	.ChildCount = 1,
	.ChildOffset = (uint*)LeftArmBone_ChildList,
};


uint LeftFootBone_ChildList[] = 
{
};


PolyBone LeftFootBone_Bone =
{
	.MeshScale = 1,
	.AnimationOffset = &LeftFootBone_Anime,
	.NodeCount = 3,
	.NodeOffset = (uint*)LeftFootBone_NodeList,
	.ChildCount = 0,
	.ChildOffset = (uint*)LeftFootBone_ChildList,
};


uint LeftLegBone_ChildList[] = 
{
	(uint)&LeftFootBone_Bone,
};


PolyBone LeftLegBone_Bone =
{
	.MeshScale = 1,
	.AnimationOffset = &LeftLegBone_Anime,
	.NodeCount = 3,
	.NodeOffset = (uint*)LeftLegBone_NodeList,
	.ChildCount = 1,
	.ChildOffset = (uint*)LeftLegBone_ChildList,
};


uint RightPalm_ChildList[] = 
{
};


PolyBone RightPalm_Bone =
{
	.MeshScale = 1,
	.AnimationOffset = &RightPalm_Anime,
	.NodeCount = 3,
	.NodeOffset = (uint*)RightPalm_NodeList,
	.ChildCount = 0,
	.ChildOffset = (uint*)RightPalm_ChildList,
};


uint RightHandBone_ChildList[] = 
{
	(uint)&RightPalm_Bone,
};


PolyBone RightHandBone_Bone =
{
	.MeshScale = 1,
	.AnimationOffset = &RightHandBone_Anime,
	.NodeCount = 3,
	.NodeOffset = (uint*)RightHandBone_NodeList,
	.ChildCount = 1,
	.ChildOffset = (uint*)RightHandBone_ChildList,
};


uint RightArmBone_ChildList[] = 
{
	(uint)&RightHandBone_Bone,
};


PolyBone RightArmBone_Bone =
{
	.MeshScale = 1,
	.AnimationOffset = &RightArmBone_Anime,
	.NodeCount = 3,
	.NodeOffset = (uint*)RightArmBone_NodeList,
	.ChildCount = 1,
	.ChildOffset = (uint*)RightArmBone_ChildList,
};


uint RightFootBone_ChildList[] = 
{
};


PolyBone RightFootBone_Bone =
{
	.MeshScale = 1,
	.AnimationOffset = &RightFootBone_Anime,
	.NodeCount = 3,
	.NodeOffset = (uint*)RightFootBone_NodeList,
	.ChildCount = 0,
	.ChildOffset = (uint*)RightFootBone_ChildList,
};


uint RightLegBone_ChildList[] = 
{
	(uint)&RightFootBone_Bone,
};


PolyBone RightLegBone_Bone =
{
	.MeshScale = 1,
	.AnimationOffset = &RightLegBone_Anime,
	.NodeCount = 3,
	.NodeOffset = (uint*)RightLegBone_NodeList,
	.ChildCount = 1,
	.ChildOffset = (uint*)RightLegBone_ChildList,
};


uint BodyBone_ChildList[] = 
{
	(uint)&LeftArmBone_Bone,
	(uint)&LeftLegBone_Bone,
	(uint)&RightArmBone_Bone,
	(uint)&RightLegBone_Bone,
};


PolyBone BodyBone_Bone =
{
	.MeshScale = 1,
	.AnimationOffset = &BodyBone_Anime,
	.NodeCount = 3,
	.NodeOffset = (uint*)BodyBone_NodeList,
	.ChildCount = 4,
	.ChildOffset = (uint*)BodyBone_ChildList,
};




AnimeHolster CyborgHolster = 
{
    .RootBone = (PolyBone*)&BodyBone_Bone,
    .FrameCount = 36,
    .ActionFrame = 0
};