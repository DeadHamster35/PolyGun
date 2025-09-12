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
Actor MPBot;


void InitActors()
{
    //Init Elite;
    Elite.FireDistance.Max = 1250;
    Elite.FireDistance.Min = 25;
    Elite.OptimalDistance = 300;
    Elite.PanicThreshold = 2000;

    Elite.PrimaryWeapon = (WeaponClass*)&PlasmaRifle;
    Elite.SecondaryWeapon = (WeaponClass*)&Pistol;

    MPBot.FireDistance.Max = 1000;
    MPBot.FireDistance.Min = 15;
    MPBot.OptimalDistance = 75;
    MPBot.PanicThreshold = -1;

    MPBot.PrimaryWeapon = (WeaponClass*)&AssaultRifle;
    MPBot.SecondaryWeapon = (WeaponClass*)&Pistol;
}