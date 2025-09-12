#ifndef WeaponH
#define WeaponH

#include <ultra64.h>
#include "common.h"


extern Projectile ProjectileArray[];

extern WeaponClass Pistol;
extern WeaponClass AssaultRifle;
extern WeaponClass PlasmaRifle;
extern WeaponClass *WeaponClassArray[];

extern void InitWeaponClasses();
extern void FireBullet(int Player);
extern void initProjectiles();
extern int MoveProjectile(int BulletIndex);
extern int CheckPickups(int PlayerIndex);
extern void CheckProjectiles();
extern void SwapGun(int PlayerIndex);
extern void CheckReload(int PlayerIndex);
extern void ReloadWeapon(int PlayerIndex);
extern void PlayerMelee(int PlayerIndex);
extern void LoadWeaponAmmo(int PlayerIndex);
extern void PickupObject(int PlayerIndex);

extern Gfx logo_bulletbox[];

#endif


