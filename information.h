#pragma once
#ifndef _INFORMATION_H_
#define _INFORMATION_H_

///////////////////////////
// map informaion
///////////////////////////

#define CONSOLE_WIDTH 92
#define CONSOLE_HEIGHT 30
#define STATE_SCREEN 10
// 콘솔창 크기 조절하는 변수를 바꾸려고 하면 변수를 바꾸고 map.c 있는 SetConsoleScreen에 있는 값과 main.c에 있는 값을 같이 바꾸어 주어야 한다.
#define MAP_X 100
#define MAP_Y 100
#define BLOCK "■"
#define WALL "□"
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
// 적 종류 가짓수

typedef struct _Enemy
{
	int XYHP[10][3];
	// XYHP의 첫번째 길이가 최대 몹 수, 두번째 인자는 순서대로 x좌표, y좌표, hp다.
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