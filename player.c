#include <stdio.h>
#include <Windows.h>

#include "player.h"
#include "cursor.h"
#include "information.h"

//////////////////////////////////////////

static int BulletDelay = 0;
static int FastMovingDelay = 0;
static int vector[2] = { 1,0 };
static int EnemyPosition[3] = { -1, -1, 0 };
// 첫번째 인자부터 적 x좌표, 적 y좌표, 적 종류다.

//////////////////////////////////////////

void MovePlayer(Player* player, const char* MapData[MAP_Y][MAP_X])
{
	if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vector[0] = 0;
		vector[1] = 0;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		player->position[1] -= 1;
		if (MapData[player->position[1]][player->position[0]] != "  ")
		{
			player->position[1] += 1;
		}
		vector[1] = -1;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		player->position[1] += 1;
		if (MapData[player->position[1]][player->position[0]] != "  ")
		{
			player->position[1] -= 1;
		}
		vector[1] = 1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		player->position[0] += 1;
		if (MapData[player->position[1]][player->position[0]] != "  ")
		{
			player->position[0] -= 1;
		}
		vector[0] = 1;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		player->position[0] -= 1;
		if (MapData[player->position[1]][player->position[0]] != "  ")
		{
			player->position[0] += 1;
		}
		vector[0] = -1;
	}
	if (GetAsyncKeyState(VK_SPACE) && FastMovingDelay >= player->FastMovingDelay)
	{
		for (int i = 0; i < player->FastMovingReach; i++)
		{
			if (MapData[player->position[1] + vector[1] * (i + 1)][player->position[0] + vector[0] * (i + 1)] != "  ")
			{
				player->position[0] += vector[0] * i;
				player->position[1] += vector[1] * i;
				FastMovingDelay = 0;
				break;
			}
			else if (i == player->FastMovingReach - 1)
			{
				player->position[0] += vector[0] * player->FastMovingReach;
				player->position[1] += vector[1] * player->FastMovingReach;
				FastMovingDelay = 0;
			}
		}
	}
	else if (FastMovingDelay < player->FastMovingDelay)
	{
		FastMovingDelay++;
	}
}

void PlayerPrint(const Player* player, const Weapon* weapon, const HANDLE screen)
{
	DWORD dw;

	int x = player->position[0] * 2;
	int y = player->position[1];
	if (x > 46 && x <= 154)
	{
		x = 46;
	}
	else if (x > 154 && x < 198)
	{
		x -= 108;
	}
	if (y > 15 && y <= 85)
	{
		y = 15;
	}
	else if (y > 85 && y < 99)
	{
		y -= 70;
	}

	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(screen, CursorPosition);
	WriteFile(screen, player->shape, 2, &dw, NULL);

	CursorPosition.X += vector[0] * 2;
	CursorPosition.Y += vector[1];
	SetConsoleCursorPosition(screen, CursorPosition);
	WriteFile(screen, weapon->shape, 2, &dw, NULL);
}

void shoot(const Player* player, const Weapon* weapon, const Enemy* enemy, const char* MapData[MAP_Y][MAP_X], const HANDLE screen)
{
	DWORD dw;

	if (GetAsyncKeyState(A_KEY) && BulletDelay >= weapon->delay)
	{
		int x = player->position[0] * 2;
		int y = player->position[1];
		if (x > 46 && x <= 154)
		{
			x = 46;
		}
		else if (x > 154 && x < 198)
		{
			x -= 108;
		}
		if (y > 15 && y <= 85)
		{
			y = 15;
		}
		else if (y > 85 && y < 99)
		{
			y -= 70;
		}
		for (int i = 0; i < weapon->reach; i++)
		{
			if (MapData[player->position[1] + vector[1] * (i + 1)][player->position[0] + vector[0] * (i + 1)] == WALL)
			{
				switch (i)
				{
				case 0:
					i++;
					break;
				}
				COORD CursorPosition = { x + vector[0] * i * 2,y + vector[1] * i };
				SetConsoleCursorPosition(screen, CursorPosition);
				WriteFile(screen, weapon->shape, 2, &dw, NULL);
				BulletDelay = 0;
				break;
			}
			else if (MapData[player->position[1] + vector[1] * (i + 1)][player->position[0] + vector[0] * (i + 1)] != BLANK && \
				MapData[player->position[1] + vector[1] * (i + 1)][player->position[0] + vector[0] * (i + 1)] != BLOCK)
			{
				COORD CursorPosition = { x + vector[0] * (i + 1) * 2,y + vector[1] * (i + 1) };
				SetConsoleCursorPosition(screen, CursorPosition);
				WriteFile(screen, weapon->shape, 2, &dw, NULL);
				BulletDelay = 0;
				for (int Enum = 0; Enum < ENEMY_NUM; Enum++)
				{
					EnemyPosition[0] = player->position[0] + vector[0] * (i + 1);
					EnemyPosition[1] = player->position[1] + vector[1] * (i + 1);
					EnemyPosition[2] = Enum;

				}
				break;
			}
			else if (i == weapon->reach - 1)
			{
				int tmp = 0;
				if (MapData[player->position[1] + vector[1] * (i + 1)][player->position[0] + vector[0] * (i + 1)] == BLOCK)
				{
					tmp = -1;
				}
				COORD CursorPosition = { x + vector[0] * (weapon->reach + tmp) * 2, y + vector[1] * (weapon->reach + tmp) };
				SetConsoleCursorPosition(screen, CursorPosition);
				WriteFile(screen, weapon->shape, 2, &dw, NULL);
				BulletDelay = 0;
			}
		}

	}
	else if (BulletDelay < weapon->delay)
	{
		BulletDelay++;
	}
}

void HittedEnemy(Enemy* enemy, const Weapon* weapon, char* MapData[MAP_Y][MAP_X])
{
	for (int Eindex = 0; Eindex < (enemy + EnemyPosition[2])->MaxNum; Eindex++)
	{
		if ((enemy + EnemyPosition[2])->XYHP[Eindex][0] == EnemyPosition[0] && (enemy + EnemyPosition[2])->XYHP[Eindex][1] == EnemyPosition[1])
		{
			(enemy + EnemyPosition[2])->XYHP[Eindex][2] -= weapon->damage;
			if ((enemy + EnemyPosition[2])->XYHP[Eindex][2] <= 0)
			{
				MapData[EnemyPosition[1]][EnemyPosition[0]] = BLANK;
			}
			EnemyPosition[0] = -1;
			EnemyPosition[1] = -1;
		}
	}
}

void GameOver(const Player* player, const HANDLE screen)
{
	if (player->hp <= 0)
	{
		DWORD dw;
		COORD CursorPosition = { 0,0 };
		FillConsoleOutputCharacter(screen, ' ', CONSOLE_WIDTH * CONSOLE_HEIGHT * 2, CursorPosition, &dw);
		CursorPosition.X = 40;
		CursorPosition.Y = 20;
		SetConsoleCursorPosition(screen, CursorPosition);
		WriteFile(screen, "GameOver...", 12, &dw, NULL);
		_getch();
		//exit(1);
	}
}

int* ReturnVector()
{
	return vector;
}