#include <stdio.h>
#include <Windows.h>
#include <math.h>

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
static float vector[2] = { 0,0 };
static int MassCenter[2] = { 0,0 };
static int SectorPosition[2][2] = { {0,0},{0,0} };

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
	if (wave > enemy->MaxWave)
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
				MapData[enemy->XYHP[i][1]][enemy->XYHP[i][0]] = enemy->shape;
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

void MiddleBossPattern1(Player* player, Boss* boss, char* MapData[MAP_Y][MAP_X])
{
	int TmpReach = 5;
	int x = player->position[0] - boss->XYHP[0];
	int y = player->position[0] - boss->XYHP[0];
	// 보스와 플레이어의 간격
	vector[0] = x/sqrt(x*x + y*y);
	vector[1] = y/sqrt(x*x + y*y);
	// 보스에서 플레이어를 향한 단위 벡터
	MassCenter[0] = boss->XYHP[0] + vector[0] * TmpReach;
	MassCenter[1] = boss->XYHP[1] + vector[1] * TmpReach;
	// 보스와 플레이어 사이의 적당한 무게 중심
	int TmpVector = vector[0];
	vector[0] = vector[1];
	vector[1] = TmpVector;
	// 벡터의 수직화
	SectorPosition[0][0] = MassCenter[0] + vector[0] * boss->Pattern1Reach;
	SectorPosition[0][1] = MassCenter[1] + vector[1] * boss->Pattern1Reach;
	SectorPosition[1][0] = MassCenter[0] - vector[0] * boss->Pattern1Reach;
	SectorPosition[1][1] = MassCenter[1] - vector[1] * boss->Pattern1Reach;
	// 부채꼴 라인의 한 점 -> 선을 긋기 위한 방향을 구하려고 가져옴
	while (1)
	{

	}
}

int GetRoundInfo()
{
	return round;
}

int GetWaveInfo()
{
	return wave;
}