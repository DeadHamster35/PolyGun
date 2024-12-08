#ifndef WeaponH
#define WeaponH

#include <ultra64.h>
#include "common.h"


extern Projectile ProjectileArray[];

extern WeaponClass Pistol;
extern WeaponClass AssaultRifle;

extern void InitWeaponClasses();
extern void FireBullet(int Player);
extern void initProjectiles();
extern int MoveProjectile(int BulletIndex);
extern void CheckProjectiles();


extern Gfx logo_bulletbox[];

#endif


