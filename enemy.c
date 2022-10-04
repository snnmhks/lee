#include <stdio.h>
#include <Windows.h>

#include "enemy.h"
#include "information.h"

//////////////////////////////////////

static int CreateDelay = 0;
static int speed = 0;
static int RandomPosition[4] = { 1, 2, 97, 98 };
static int DamageDelay_0 = 0;
static int DamageDelay = 10;

//////////////////////////////////////

void CreateEnemy(Enemy* enemy)
{
	if (CreateDelay >= enemy->CreateDelay)
	{
		for (int i = 0; i < enemy->MaxNum; i++)
		{
			int x = (rand() % (MAP_X - 3)) + 1;
			int y = RandomPosition[rand() % 4];
			if (enemy->XYHP[i][2] <= 0)
			{
				enemy->XYHP[i][0] = x;
				enemy->XYHP[i][1] = y;
				enemy->XYHP[i][2] = enemy->hp;
			}
		}
		CreateDelay = 0;
	}
	else if (CreateDelay < enemy->CreateDelay)
	{
		CreateDelay++;
	}
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
	for (int i = 0; i < enemy->MaxNum; i++)
	{
		if (speed >= enemy->speed && enemy->XYHP[i][2] > 0)
		{
			MapData[enemy->XYHP[i][1]][enemy->XYHP[i][0]] = BLANK;
			if (player->position[0] > enemy->XYHP[i][0] && MapData[enemy->XYHP[i][1]][enemy->XYHP[i][0] + 1] != BLOCK)
			{
				enemy->XYHP[i][0]++;
			}
			else if (player->position[0] < enemy->XYHP[i][0] && MapData[enemy->XYHP[i][1]][enemy->XYHP[i][0] - 1] != BLOCK)
			{
				enemy->XYHP[i][0]--;
			}
			if (player->position[1] > enemy->XYHP[i][1] && MapData[enemy->XYHP[i][1] + 1][enemy->XYHP[i][0]] != BLOCK)
			{
				enemy->XYHP[i][1]++;
			}
			else if (player->position[1] < enemy->XYHP[i][1] && MapData[enemy->XYHP[i][1] - 1][enemy->XYHP[i][0]] != BLOCK)
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
		else if (speed< enemy->speed)
		{
			speed++;
		}
	}
}
