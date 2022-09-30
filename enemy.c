#include <stdio.h>
#include <Windows.h>

#include "enemy.h"
#include "information.h"

//////////////////////////////////////

static int CreateDelay[ENEMY_NUM] = { 0, };
static int speed[ENEMY_NUM] = { 0, };
static int RandomPosition[4] = { 1, 2, 97, 98 };
static int DamageDelay_0 = 0;
static int DamageDelay = 10;

//////////////////////////////////////

void CreateEnemy(Enemy* enemy)
{
	for (int Enum = 0; Enum < ENEMY_NUM; Enum++)
	{
		if (CreateDelay[Enum] >= (enemy + Enum)->CreateDelay)
		{
			for (int i = 0; i < (enemy + Enum)->MaxNum; i++)
			{
				int x = (rand() % 97) + 1;
				int y = RandomPosition[rand() % 4];
				if ((enemy + Enum)->XYHP[i][2] <= 0)
				{
					(enemy + Enum)->XYHP[i][0] = x;
					(enemy + Enum)->XYHP[i][1] = y;
					(enemy + Enum)->XYHP[i][2] = (enemy + Enum)->hp;
				}
			}
			CreateDelay[Enum] = 0;
		}
		else if (CreateDelay[Enum] < (enemy + Enum)->CreateDelay)
		{
			CreateDelay[Enum]++;
		}
	}
}

void EnemyToMap(const Enemy* enemy, char* MapData[MAP_Y][MAP_X])
{
	for (int Enum = 0; Enum < ENEMY_NUM; Enum++)
	{
		for (int i = 0; i < (enemy + Enum)->MaxNum; i++)
		{
			if ((enemy + Enum)->XYHP[i][2] > 0)
			{
				MapData[(enemy + Enum)->XYHP[i][1]][(enemy + Enum)->XYHP[i][0]] = (enemy + Enum)->shape;
			}
		}
	}
}

void MoveEnemy(Player* player, Enemy* enemy, char* MapData[MAP_Y][MAP_X])
{
	for (int Enum = 0; Enum < ENEMY_NUM; Enum++)
	{
		for (int i = 0; i < (enemy + Enum)->MaxNum; i++)
		{
			if (speed[Enum] >= (enemy + Enum)->speed && (enemy + Enum)->XYHP[i][2] > 0)
			{
				MapData[(enemy + Enum)->XYHP[i][1]][(enemy + Enum)->XYHP[i][0]] = BLANK;
				if (player->position[0] > (enemy + Enum)->XYHP[i][0] && MapData[(enemy + Enum)->XYHP[i][1]][(enemy + Enum)->XYHP[i][0] + 1] != BLOCK)
				{
					(enemy + Enum)->XYHP[i][0]++;
				}
				else if (player->position[0] < (enemy + Enum)->XYHP[i][0] && MapData[(enemy + Enum)->XYHP[i][1]][(enemy + Enum)->XYHP[i][0] - 1] != BLOCK)
				{
					(enemy + Enum)->XYHP[i][0]--;
				}
				if (player->position[1] > (enemy + Enum)->XYHP[i][1] && MapData[(enemy + Enum)->XYHP[i][1] + 1][(enemy + Enum)->XYHP[i][0]] != BLOCK)
				{
					(enemy + Enum)->XYHP[i][1]++;
				}
				else if (player->position[1] < (enemy + Enum)->XYHP[i][1] && MapData[(enemy + Enum)->XYHP[i][1] - 1][(enemy + Enum)->XYHP[i][0]] != BLOCK)
				{
					(enemy + Enum)->XYHP[i][1]--;
				}
				if (player->position[0] == (enemy + Enum)->XYHP[i][0] && player->position[1] == (enemy + Enum)->XYHP[i][1] && DamageDelay_0 <= 0)
				{
					player->hp -= (enemy + Enum)->damage;
					DamageDelay_0 = DamageDelay;
				}
				else if (DamageDelay_0 <= DamageDelay)
				{
					DamageDelay_0 -= 1;
				}
				speed[Enum] = 0;
			}
			else if (speed[Enum] < (enemy + Enum)->speed)
			{
				speed[Enum]++;
			}
		}
	}
}