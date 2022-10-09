#include <stdio.h>
#include <stdlib.h>

#include "information.h"

///////////////////////////
// player information
///////////////////////////

static Player circle;

void SetPlayerInfo()
{
	circle.position[0] = MAP_X/2;
	circle.position[1] = MAP_Y/2;
	circle.hp = 100;
	circle.FastMovingDelay = 100;
	circle.FastMovingReach = 5;
	circle.Speed = 5;
	circle.shape = "¡Û";

	circle.RemainFastMovingDelay = 0;
}

Player* GetPlayerInfo()
{
	return &circle;
}

///////////////////////////
// weapon information
///////////////////////////

static Weapon pistol;
static Weapon AutoPistol;

void SetPistolInfo()
{
	pistol.FireDelay = 20;
	pistol.reach = 5;
	pistol.name = "pistol";
	pistol.shape = "¡Ú";
	pistol.damage = 10;
	pistol.UpgradeDamage = 5;
	pistol.MaxBullet = 10;
	pistol.ReloadDelay = 100;

	pistol.RemainBullet = 10;
	pistol.RemainReloadDelay = 0;
	pistol.ReloadState = 0;
	pistol.scope = 0;
	pistol.magazine = 0;
	pistol.Auto = 0;
}

void SetAutoPistolInfo()
{
	AutoPistol.FireDelay = 10;
	AutoPistol.reach = 6;
	AutoPistol.name = "AutoPistol";
	AutoPistol.shape = "¡Ù";
	AutoPistol.damage = 15;
	AutoPistol.UpgradeDamage = 5;
	AutoPistol.MaxBullet = 10;
	AutoPistol.ReloadDelay = 50;

	AutoPistol.RemainBullet = 10;
	AutoPistol.RemainReloadDelay = 0;
	AutoPistol.ReloadState = 0;
	AutoPistol.scope = 0;
	AutoPistol.magazine = 0;
	AutoPistol.Auto = 0;
}

void SetWeaponInfo()
{
	SetPistolInfo();
	SetAutoPistolInfo();
}

Weapon* GetWeaponInfo(char* name)
{
	if (name == pistol.name) 
	{
		return &pistol;
	}
	else if (name == AutoPistol.name)
	{
		return &AutoPistol;
	}
}

///////////////////////////
// enemy information
///////////////////////////

static Enemy DoubleCircle;
static Enemy AtSign;
static int BeforeRround = 0;

void SetDoubleCircleInfo()
{
	DoubleCircle.MaxNum = 50;
	for (int i = 1; i < DoubleCircle.MaxNum; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			DoubleCircle.XYHP[i][j] = 0;
		}
	}
	DoubleCircle.hp = 10;
	DoubleCircle.speed = 20;
	DoubleCircle.damage = 10;
	DoubleCircle.CreateDelay = 300;
	DoubleCircle.MaxWave = 2;
	DoubleCircle.GetGold = 1;
	DoubleCircle.shape = "¡Ý";
}

void SetAtSignInfo()
{
	AtSign.MaxNum = 30;
	for (int i = 1; i < AtSign.MaxNum; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			AtSign.XYHP[i][j] = 0;
		}
	}
	AtSign.hp = 30;
	AtSign.speed = 10;
	AtSign.damage = 5;
	AtSign.CreateDelay = 300;
	AtSign.MaxWave = 10;
	AtSign.GetGold = 2;
	AtSign.shape = "£À";
}

void SetEnemyInfo()
{
	SetDoubleCircleInfo();
	SetAtSignInfo();
}

Enemy* GetEnemyInfo(const int round)
{
	switch (round)
	{
	case 1:
		return &DoubleCircle;
		break;
	default:
		return &AtSign;
		break;
	}
}