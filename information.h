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
#define MAP_X 100
#define MAP_Y 100
#define BLOCK "��"
#define WALL "��"
#define BLANK "  "

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
	char* shape;
}Player;

void SetPlayerInfo();

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
	int MaxBullet;
	int ReloadDelay;

	int RemainBullet;
	int RemainReloadDelay;
	int ReloadState;
}Weapon;

void SetPistolInfo();

Weapon* GetWeaponInfo(char* name);

///////////////////////////
// enemy information
///////////////////////////

#define ENEMY_NUM 1
// �� ���� ������

typedef struct _Enemy
{
	int XYHP[10][3];
	// XYHP�� ù��° ���̰� �ִ� �� ��, �ι�° ���ڴ� ������� x��ǥ, y��ǥ, hp��.
	int hp;
	int MaxNum;
	int speed;
	int damage;
	int CreateDelay;
	char* shape;
}Enemy;

void SetEnemyInfo();

Enemy* GetEnemyInfo();

#endif