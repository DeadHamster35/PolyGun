#include <nusys.h>
#include "main.h"
#include "graphic.h"
#include "common.h"
#include <stdbool.h>

__attribute__((aligned (64)))
ushort H64Tex[32 * 32];

__attribute__((aligned (64)))
ushort PistolReticleTex[32*32];

__attribute__((aligned (64)))
ushort ARReticleTex[32*32];

__attribute__((aligned (64)))
ushort ARAmmoTex[1024];

__attribute__((aligned (64)))
ushort HealthTex[32*32];

__attribute__((aligned (64)))
ushort ShieldTex[1024];

__attribute__((aligned (64)))
ushort ShieldPAL[16];

short TCoords[] = 
{
    1,1,0,0
};
short XCoords[] = 
{
    0,1,1,0
};
/* The vertex coordinate  */
static Vtx_t CharVTX[] = {
    {-16, 16, -5, 0, 32, 480, 0, 0xff, 0, 0xff},
    {16, 16, -5, 0, 480, 480, 0, 0, 0, 0xff},
    {16, -16, -5, 0, 480, 32, 0, 0, 0xff, 0xff},
    {-16, -16, -5, 0, 32, 32, 0xff, 0, 0, 0xff},
};
int VScroll = 0;


void DrawChar(int X, int Y, int S, int T, float Scale)
{
    gSPTextureRectangle(
        glistp++, 
        (X)<<2, 
        (Y)<<2, 
        (short)(X+(Scale * 16))<<2, 
        (short)(Y+(Scale * 14))<<2, 
        0, 
        (short)((S) << 5),
        (short)((T) << 5), 
        (short)((1<<10) / Scale), 
        (short)((1<<10) / Scale)
    );
}
void DrawText(int X, int Y, char* Print, float Scale)
{
    int Index = 0;
    while(true)
    {
        if (Print[Index] == 00)
        {
            break;
        }

        char Target = Print[Index] - 0x30;
        if (Target > 0xA)
        {
            Target-= 7;
        }
        if (Target > 0x29)
        {
            Target-=32;
        }
        int S = 0;
        int T = (14 * Target);

        if (T > 250)
        {
            T -= 252;
            S += 16;
        }
        
        DrawChar(X,Y,S,T,Scale);

        X += (16 * Scale);
        Index++;
    }
}
