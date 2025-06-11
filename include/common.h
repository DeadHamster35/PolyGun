#ifndef CommonH
#define CommonH


#include <ultra64.h>

#define DEG1 0xB6
#define DEGF 182.0f



#define MENUSEQUENCE 0
#define LEVELSEQUENCE 1

#define	SegmentOffset(a)	((unsigned int)(a) & 0x00ffffff)
#define	SegmentNumber(a)	(((unsigned int)(a) << 4) >> 28)
#define	SegmentAddress(num, off)	(((num) << 24) + (off))

#define MathABS(x)	((x) < 0 ? -(x) : (x))
/* Buttons */

#define CONT_A      0x8000
#define CONT_B      0x4000
#define CONT_G	    0x2000
#define CONT_START  0x1000
#define CONT_UP     0x0800
#define CONT_DOWN   0x0400
#define CONT_LEFT   0x0200
#define CONT_RIGHT  0x0100
#define CONT_L      0x0020
#define CONT_R      0x0010
#define CONT_E      0x0008
#define CONT_D      0x0004
#define CONT_C      0x0002
#define CONT_F      0x0001

/* Nintendo's official button names */

#define BTN_A	        CONT_A
#define BTN_B	        CONT_B
#define BTN_L		    CONT_L
#define BTN_R		    CONT_R
#define BTN_Z		    CONT_G
#define BTN_START	    CONT_START
#define BTN_DUP		    CONT_UP
#define BTN_DLEFT		CONT_LEFT
#define BTN_DRIGHT		CONT_RIGHT
#define BTN_DDOWN		CONT_DOWN
#define BTN_CUP	        CONT_E
#define BTN_CLEFT	    CONT_C
#define BTN_CRIGHT	    CONT_F
#define BTN_CDOWN	    CONT_D


#define	Align128(n)		(((uint)(n)+15)&0xfffffff0)
#define	Align64(n)		(((uint)(n)+7)&0xfffffff8)
#define	Align32(n)		(((uint)(n)+3)&0xfffffffc)
#define	Align16(n)		(((uint)(n)+1)&0xfffffffe)

typedef unsigned int uint;
typedef unsigned short ushort;
typedef float AffineMtx[4][4];
typedef float Vector[3];
typedef short SVector[3];

#define ASTAR   128
#define MAXTRI 9001
#define XAXISVECTOR 0
#define YAXISVECTOR 1
#define FLOORVECTOR 2
#define CEILINGVECTOR 3
#define WTFAXISVECTOR 4

#define THIRYFPS 2.0f
#define GRAVITY 0.2f * THIRYFPS
#define MAXSPEED 1.75f * THIRYFPS
#define JUMPHEIGHT -2.75f * THIRYFPS
#define TERMINALVELOCITY 16.0f * THIRYFPS
#define MINIMALVELOCITY 0.1f * THIRYFPS
#define MAXLOOK 45
#define MAXBULLETS 100


#define BULLET_ACTIVE 1
#define BULLET_INACTIVE 0

typedef Vector  VertexArrayF[3];
typedef SVector VertexArray[3];


typedef struct {
    Vector  Start;
    Vector  End;
    Vector  VelocityFront;
} Line;


typedef struct {

    Vector  Base;
    float   Radius;
    float   Height;

} Cylinder;

typedef struct {

    Vector  Center;
    float  Radius;

} Sphere;


typedef struct {
    
    short       TriIndex, Closed;
    short       ParentNode, PADDING;
    float       F,G,H;
} NavNode;


//don't use.
typedef struct {
    Vector          BoundingMax;
    Vector          BoundingMin;
    short           NormalDirection, SurfaceType;
    float           VectorDistance;
    Vector          Vertex[3];
    Vector          Edge[3];
    Vector          Center;
    Vector          Normal;
    SVector         NavMesh;
} CollisionTri;
//don't use


typedef struct {

    short       BoundingMax[3]; //6
    short       BoundingMin[3]; //12    
    short       NormalDirection, SurfaceType; //18

    float       VectorDistance; //22

    short       Vertex[3][3]; //40
    short       Edge[3][3];  //58
    short       Center[3];  //64  
    
    short       NavMesh[3];  //70
    Vector      Normal;  //82

}   CompactCollision;



typedef struct {
    ushort  ElementCount;
    ushort  ElementIndex;
} CollisionGrid;

typedef struct {

    short          GridWidth, GridLength;
    ushort          ChunkWidth, ChunkLength;
    short          GridMin[2], GridMax[2];
    CollisionGrid   GridData[32*32];


}   CollisionGridHolster;

typedef struct {
    
    Vector      Position;
    Vector      LastPosition;
    Vector      VelocityFront;
    Vector      VelocityTotal;
    SVector     Angle;
    short       Radius;
} Locate;

typedef struct{
    ushort  Size[2];
    ushort  Position[2];
} PGScreen;

typedef struct {
    Locate      Location;
    Vector      LookAt;
    Vector      UpVector;
    short       FOVY, Impulse;
    short       Near,Far;
    PGScreen    Screen;
} PGCamera;

typedef struct PolyKeyFrame
{
    short       Time;
    SVector     Data;
    
} PolyKeyFrame;

typedef struct PolyAnime
{
	PolyKeyFrame*   PositionData;
    PolyKeyFrame*   RotationData;
    PolyKeyFrame*   ScalingData;
	ushort			PositionCount, RotationCount, ScalingCount;
}PolyAnime;

typedef struct PolyNode{
    uint    TextureOffset;	
	uint	MeshCount;
	uint*   MeshOffsets;
    uint    ClosingDL;
} PolyNode;

typedef struct PB{
    	float               MeshScale;
	    PolyAnime*		AnimeData;
    	ushort              NodeCount, ChildCount;
    	PolyNode*           NodeOffset;
    	struct PolyBone*    ChildOffset;
} PolyBone;



typedef struct {
    PolyBone*   RootBone;
    int       FrameCount;
} AnimeHolster;


typedef struct {
    AnimeHolster*   Idle;
    AnimeHolster*   ReloadFull;
    AnimeHolster*   ReloadEmpty;
    AnimeHolster*   Melee;
    AnimeHolster*   Grenade;
    AnimeHolster*   Fire;
} WeaponBandolier;


typedef struct {
    short           FiringRate, BulletSpeed;
    short           BaseDamage, ErrorAccel;
    short           ErrorMin, ErrorMax;
    short           MagazineSize, MaxAmmo;
    short           ReloadTime, BulletLife;
    short           CameraRecoilX, CameraRecoilY;
    short           CameraImpulseX, CameraImpulseY;
    short           MaxImpulseX, MaxImpulseY;
    WeaponBandolier Bandolier;
    Gfx             (*Reticle);  
}   WeaponClass;

typedef struct {
    WeaponClass*    Class;    
    short           Magazine,Ammo;
}   WeaponEquipment;

typedef struct {
    short       Status, Owner;
    Locate      Location;
    short       Distance, Lifespan;
    short       Damage, InitialSpeed;
    ushort      Weight, RGB;
} Projectile;

typedef struct{
    short Health,Shield;
} PlayerHealth;


/*
0x1
0x2
0x4
0x8
0x10
0x20
0x40
0x80
0x100
0x200
0x400
0x800
0x1000
0x2000
0x4000
0x8000
*/



#define ACTIONJUMP          0x01 //A
#define ACTIONMELEE         0x02 //B
#define ACTIONFIRE          0x04 //Z
#define ACTIONSWAPGUN       0x08 //R+A
#define ACTIONRELOAD        0x10 //R+B
#define ACTIONGRENADE       0x20 //R+Z


#define STATUSCROUCH        0x01
#define STATUSFPS           0x02
#define STATUSBSTAR         0x04
#define STATUSINAIR         0x08
#define STATUSRELOADING     0x10
#define STATUSSWAPGUN       0x20
#define STATUSFIRING        0x40
#define STATUSMELEE         0x80

typedef struct {
    short   CurrentTime, MaxTime;
} AnimeTimer;

typedef struct{
    short               PlayerIndex, IsCPU;
    Locate              Location;    
    Vector              PushVelocity[3];   
    float               Height;
    short               HitTri[4];
    short               JumpTimer, PAD;
    AnimeTimer          FPAnimeTimer, AnimeTimer;
    short               PlayerTarget;
    char                ZTarget, SelectedWeapon;
    short               IFrames, FFrames;
    ushort              ActionBits, StatusBits;
    PlayerHealth        HealthData;
    AnimeHolster        *Anime, *FPAnime;
    WeaponEquipment     WeaponArray[2];
} Player;

typedef struct{
    short   Min, Max;    
} MinMax;

typedef struct{
    MinMax  FireDistance;
    WeaponClass*    PrimaryWeapon;
    WeaponClass*    SecondaryWeapon;
} Actor;

typedef struct{
    Vector      CurrentTarget;
    Vector      LookAt;
    SVector     WalkVector;
    short       CurrentPathIndex, Difficulty;
    short       PathLocked, PathTimer;
    short       TargetPlayer, MovementStress;
    Actor*      ActorData;
} BotStruct;

typedef struct {

    uint    Segment4ROM;
    uint    Segment5ROM;
    uint    Segment6ROM;

    uint    Segment4SizeCompressed;
    uint    Segment5SizeCompressed;
    uint    Segment6SizeCompressed;

} LevelHeaderStruct;

typedef struct {
    SVector     Position;
    SVector     Angle;
    short       FlagA, FlagB;
} ObjectClass;

#include "../src/main/assets/assets.h"
#endif

