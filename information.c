#include <stdio.h>

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
	pistol.delay = 10;
	pistol.reach = 5;
	pistol.shape = "¡Ú";
	pistol.damage = 10;
}

Weapon* GetWeaponInfo(char* name)
{
	return &pistol;
}

///////////////////////////
// enemy information
///////////////////////////

Enemy enemy[ENEMY_NUM];

void SetEnemyInfo()
{
	//////////////////////////////
	// Set DoubleCircle information
	//////////////////////////////

	(enemy + 0)->MaxNum = 10;
	for (int i = 0; i < (enemy + 0)->MaxNum; i++)
	{
		(enemy + 0)->XYHP[i][0] = 0;
		(enemy + 0)->XYHP[i][1] = 0;
		(enemy + 0)->XYHP[i][2] = 0;
	}
	(enemy + 0)->hp = 20;
	(enemy + 0)->speed = 50;
	(enemy + 0)->damage = 10;
	(enemy + 0)->CreateDelay = 300;
	(enemy + 0)->shape = "¡Ý";
}

Enemy* GetEnemyInfo()
{
	return enemy;
}