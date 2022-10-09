#pragma once
#ifndef _INFORMATION_H_
#define _INFORMATION_H_

///////////////////////////
// map informaion
///////////////////////////

#define CONSOLE_WIDTH 92
#define CONSOLE_HEIGHT 30
#define STATE_SCREEN 10
// �ܼ�â ũ�� �����ϴ� ������ �ٲٷ��� �ϸ� ������ �ٲٰ� map.c �ִ� SetConsoleScreen�� �ִ� ���� main.c�� �ִ� ���� ���� �ٲپ� �־�� �Ѵ�.
#define MAP_X 50
#define MAP_Y 50
// �ּ� 50 / 50
#define BLOCK "��"
#define WALL "��"
#define BLANK "  "
#define MAX_GOLD_SCALE 5

///////////////////////////
// player information
///////////////////////////

#define A_KEY 65
#define R_KEY 82

typedef struct _Player
{
	int position[2];
	int hp;
	int FastMovingReach;
	int FastMovingDelay;
	int Speed;
	char* shape;

	int RemainFastMovingDelay;
}Player;

void SetWeaponInfo();

Player* GetPlayerInfo();

///////////////////////////
// weapon information
///////////////////////////

typedef struct _Weapon
{
	int FireDelay;
	int reach;
	char* name;
	char* shape;
	int damage;
	int UpgradeDamage;
	int MaxBullet;
	int ReloadDelay;

	int scope;
	int magazine;
	int Auto;
	int RemainBullet;
	int RemainReloadDelay;
	int ReloadState;
}Weapon;

void SetPistolInfo();

Weapon* GetWeaponInfo(char* name);

///////////////////////////
// enemy information
///////////////////////////

#define MAX_ENEMY_NUM 100

typedef struct _Enemy
{
	int MaxNum;
	int XYHP[MAX_ENEMY_NUM][3];
	// XYHP�� ù��° ���̰� �ִ� �� ��, �ι�° ���ڴ� ������� x��ǥ, y��ǥ, hp��.
	int hp;
	int speed;
	int damage;
	int CreateDelay;
	int MaxWave;
	int GetGold;
	char* shape;
}Enemy;

void SetEnemyInfo();

Enemy* GetEnemyInfo(const int round);

#endif