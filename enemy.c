#include <stdio.h>
#include <Windows.h>

#include "enemy.h"
#include "information.h"

//////////////////////////////////////

static int CreateDelay = 0;
static int speed = 0;
static int RandomPosition[4] = { 1, 2, MAP_Y - 3, MAP_Y - 2 };
static int DamageDelay_0 = 0;
static int DamageDelay = 10;
static int round = 1;
static int wave = 0;
static int ResponNum = 10;

//////////////////////////////////////

void CreateEnemy(Enemy* enemy, char* MapData[MAP_Y][MAP_X])
{
	if (CreateDelay >= enemy->CreateDelay)
	{
		int MaxNum = 0;
		for (int i = 0; i < enemy->MaxNum; i++)
		{
			if (enemy->XYHP[i][2] <= 0)
			{
				enemy->XYHP[i][0] = (rand() % (MAP_X - 3)) + 1;
				enemy->XYHP[i][1] = (rand() % (MAP_X - 3)) + 1;
				enemy->XYHP[i][2] = enemy->hp;
				MaxNum++;
			}
			if (MaxNum >= ResponNum)
			{
				break;
			}
		}
		CreateDelay = 0;
		wave++;
	}
	else if (CreateDelay < enemy->CreateDelay)
	{
		CreateDelay++;
	}
	if (wave >= enemy->MaxWave)
	{
		for (int i = 0; i < enemy->MaxNum; i++)
		{
			if (enemy->XYHP[i][2] > 0)
			{
				MapData[enemy->XYHP[i][1]][enemy->XYHP[i][0]] = BLANK;
			}
		}
		round++;
		wave = 0;
		Sleep(1000);
	}
	Sleep(10);
}

void EnemyToMap(const Enemy* enemy, char* MapData[MAP_Y][MAP_X])
{

	for (int i = 0; i < enemy->MaxNum; i++)
	{
		if (enemy->XYHP[i][2] > 0)
		{
			MapData[enemy->XYHP[i][1]][enemy->XYHP[i][0]] = enemy->shape;
		}
	}
	
}

void MoveEnemy(Player* player, Enemy* enemy, char* MapData[MAP_Y][MAP_X])
{
	if (speed >= enemy->speed)
	{
		for (int i = 0; i < enemy->MaxNum; i++)
		{
			if (enemy->XYHP[i][2] > 0)
			{
				MapData[enemy->XYHP[i][1]][enemy->XYHP[i][0]] = BLANK;
				if (player->position[0] > enemy->XYHP[i][0] && MapData[enemy->XYHP[i][1]][enemy->XYHP[i][0] + 1] == BLANK)
				{
					enemy->XYHP[i][0]++;
				}
				else if (player->position[0] < enemy->XYHP[i][0] && MapData[enemy->XYHP[i][1]][enemy->XYHP[i][0] - 1] == BLANK)
				{
					enemy->XYHP[i][0]--;
				}
				if (player->position[1] > enemy->XYHP[i][1] && MapData[enemy->XYHP[i][1] + 1][enemy->XYHP[i][0]] == BLANK)
				{
					enemy->XYHP[i][1]++;
				}
				else if (player->position[1] < enemy->XYHP[i][1] && MapData[enemy->XYHP[i][1] - 1][enemy->XYHP[i][0]] == BLANK)
				{
					enemy->XYHP[i][1]--;
				}
				if (player->position[0] == enemy->XYHP[i][0] && player->position[1] == enemy->XYHP[i][1] && DamageDelay_0 <= 0)
				{
					player->hp -= enemy->damage;
					DamageDelay_0 = DamageDelay;
				}
				else if (DamageDelay_0 <= DamageDelay)
				{
					DamageDelay_0 -= 1;
				}
				speed = 0;
			}
		}
	}
	else if (speed < enemy->speed)
	{
		speed++;
	}
}

int GetRoundInfo()
{
	return round;
}