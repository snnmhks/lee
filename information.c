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

static Enemy DoubleCircle;
static Enemy AtSign;
static int BeforeRround = 0;

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
	DoubleCircle.hp = 10;
	DoubleCircle.speed = 20;
	DoubleCircle.damage = 10;
	DoubleCircle.CreateDelay = 300;
	DoubleCircle.MaxWave = 5;
	DoubleCircle.shape = "¡Ý";
}

void SetAtSignInfo()
{
	AtSign.MaxNum = 11;
	AtSign.XYHP = (int**)malloc(sizeof(int*) * AtSign.MaxNum);
	AtSign.XYHP[0] = (int*)malloc(sizeof(int) * AtSign.MaxNum * 3);
	for (int i = 1; i < AtSign.MaxNum; i++)
	{
		AtSign.XYHP[i] = AtSign.XYHP[i - 1] + 3;
	}
	for (int i = 0; i < AtSign.MaxNum; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			AtSign.XYHP[i][j] = 0;
		}
	}
	AtSign.hp = 30;
	AtSign.speed = 10;
	AtSign.damage = 5;
	AtSign.CreateDelay = 200;
	AtSign.MaxWave = 5;
	AtSign.shape = "£À";
}

void SetEnemyInfo(const int round)
{
	while (1)
	{
		if (BeforeRround != round)
		{
			BeforeRround = round;
			switch (round)
			{
			case 1:
				SetDoubleCircleInfo();
				break;
			case 2:
				SetAtSignInfo();
				break;
			}
		}
		Sleep(10);
	}
}

void FreeEnemyInfo(Enemy *enemy)
{
	free(enemy->XYHP[0]);
	free(enemy->XYHP);
}

Enemy* GetEnemyInfo(const int round)
{
	switch (round)
	{
	case 1:
		return &DoubleCircle;
		break;
	case 2:
		return &AtSign;
		break;
	}
}