#include <stdio.h>
#include <stdlib.h>

#include "information.h"

///////////////////////////
// player information
///////////////////////////

static Player circle;

void SetPlayerInfo()
{
	circle.position[0] = 50;
	circle.position[1] = 50;
	circle.hp = 100;
	circle.FastMovingDelay = 100;
	circle.FastMovingReach = 5;
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

void SetPistolInfo()
{
	pistol.FireDelay = 20;
	pistol.reach = 5;
	pistol.name = "pistol";
	pistol.shape = "¡Ú";
	pistol.damage = 10;
	pistol.MaxBullet = 10;
	pistol.ReloadDelay = 100;

	pistol.RemainBullet = 10;
	pistol.RemainReloadDelay = 0;
	pistol.ReloadState = 0;
}

Weapon* GetWeaponInfo(char* name)
{
	return &pistol;
}

///////////////////////////
// enemy information
///////////////////////////

Enemy enemy[ENEMY_NUM];

Enemy DoubleCircle;

void SetDoubleCircleInfo()
{
	DoubleCircle.MaxNum = 20;
	DoubleCircle.XYHP = (int**)malloc(sizeof(int*) * DoubleCircle.MaxNum);
	DoubleCircle.XYHP[0] = (int*)malloc(sizeof(int) * DoubleCircle.MaxNum * 3);
	for (int i = 1; i < DoubleCircle.MaxNum; i++)
	{
		DoubleCircle.XYHP[i] = DoubleCircle.XYHP[i-1] + 3;
	}
	for (int i = 0; i < DoubleCircle.MaxNum; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			DoubleCircle.XYHP[i][j] = 0;
		}
	}
	DoubleCircle.hp = 20;
	DoubleCircle.speed = 20;
	DoubleCircle.damage = 10;
	DoubleCircle.CreateDelay = 300;
	DoubleCircle.shape = "¡Ý";
}

void SetEnemyInfo()
{
	SetDoubleCircleInfo();
}

void FreeEnemyInfo(Enemy *enemy)
{
	free(enemy->XYHP[0]);
	free(enemy->XYHP);
}

Enemy* GetEnemyInfo()
{
	return &DoubleCircle;
}