#include <nusys.h>
#include <nualsgi_n.h>
#include "graphic.h"
#include "common.h"
#include "main.h"
#include "player.h"
#include "pathfinding.h"
#include "math.h"
#include "weapon.h"
#include "player.h"

Actor Elite;


void InitActors()
{
    //Init Elite;
    Elite.FireDistance.Max = 1000;
    Elite.FireDistance.Min = 600;

    Elite.PrimaryWeapon = (WeaponClass*)&AssaultRifle;
    Elite.SecondaryWeapon = (WeaponClass*)&Pistol;
}