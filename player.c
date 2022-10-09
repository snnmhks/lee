#include <stdio.h>
#include <Windows.h>

#include "player.h"
#include "cursor.h"
#include "information.h"

//////////////////////////////////////////

static int BulletDelay = 0;
static int vector[2] = { 1,0 };
static int EnemyPosition[2] = { -1, -1 };
// 첫번째 인자부터 적 x좌표, 적 y좌표
static int gold = 1000;
static int MoveDelay = 0;

//////////////////////////////////////////

void MovePlayer(Player* player, const char* MapData[MAP_Y][MAP_X])
{
	if (MoveDelay >= player->Speed)
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000 || \
			GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8000)
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
		MoveDelay = 0;
	}
	else if (MoveDelay < player->Speed)
	{
		MoveDelay++;
	}

	if (GetAsyncKeyState(VK_SPACE) && player->RemainFastMovingDelay >= player->FastMovingDelay)
	{
		for (int i = 0; i < player->FastMovingReach; i++)
		{
			if (MapData[player->position[1] + vector[1] * (i + 1)][player->position[0] + vector[0] * (i + 1)] != "  ")
			{
				player->position[0] += vector[0] * i;
				player->position[1] += vector[1] * i;
				player->RemainFastMovingDelay = 0;
				break;
			}
			else if (i == player->FastMovingReach - 1)
			{
				player->position[0] += vector[0] * player->FastMovingReach;
				player->position[1] += vector[1] * player->FastMovingReach;
				player->RemainFastMovingDelay = 0;
			}
		}
	}
	else if (player->RemainFastMovingDelay < player->FastMovingDelay)
	{
		player->RemainFastMovingDelay++;
	}
}

void PlayerPrint(const Player* player, const Weapon* weapon, const HANDLE screen)
{
	DWORD dw;

	int x = player->position[0] * 2;
	int y = player->position[1];
	if (x > CONSOLE_WIDTH/2 && x <= MAP_X*2- CONSOLE_WIDTH / 2)
	{
		x = CONSOLE_WIDTH / 2;
	}
	else if (x > MAP_X * 2 - CONSOLE_WIDTH / 2 && x < MAP_X * 2 - 2)
	{
		x -= MAP_X * 2 - CONSOLE_WIDTH;
	}
	if (y > CONSOLE_HEIGHT/2 && y <= MAP_Y - CONSOLE_HEIGHT / 2)
	{
		y = CONSOLE_HEIGHT / 2;
	}
	else if (y > CONSOLE_HEIGHT / 2 && y < MAP_Y-1)
	{
		y -= MAP_Y - CONSOLE_HEIGHT;
	}

	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(screen, CursorPosition);
	WriteFile(screen, player->shape, 2, &dw, NULL);

	CursorPosition.X += vector[0] * 2;
	CursorPosition.Y += vector[1];
	SetConsoleCursorPosition(screen, CursorPosition);
	WriteFile(screen, weapon->shape, 2, &dw, NULL);
}

void shoot(const Player* player, Weapon* weapon, const char* MapData[MAP_Y][MAP_X], const HANDLE screen)
{
	DWORD dw;

	if (GetAsyncKeyState(A_KEY) && BulletDelay >= weapon->FireDelay && weapon->RemainBullet > 0 && !weapon->ReloadState)
	{
		int x = player->position[0] * 2;
		int y = player->position[1];
		if (x > CONSOLE_WIDTH / 2 && x <= MAP_X * 2 - CONSOLE_WIDTH / 2)
		{
			x = CONSOLE_WIDTH / 2;
		}
		else if (x > MAP_X * 2 - CONSOLE_WIDTH / 2 && x < MAP_X * 2 - 2)
		{
			x -= MAP_X * 2 - CONSOLE_WIDTH;
		}
		if (y > CONSOLE_HEIGHT / 2 && y <= MAP_Y - CONSOLE_HEIGHT / 2)
		{
			y = CONSOLE_HEIGHT / 2;
		}
		else if (y > CONSOLE_HEIGHT / 2 && y < MAP_Y - 1)
		{
			y -= MAP_Y - CONSOLE_HEIGHT;
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
			else if (MapData[player->position[1] + vector[1] * (i + 1)][player->position[0] + vector[0] * (i + 1)] != BLANK)
			{
				COORD CursorPosition = { x + vector[0] * (i + 1) * 2,y + vector[1] * (i + 1) };
				SetConsoleCursorPosition(screen, CursorPosition);
				WriteFile(screen, weapon->shape, 2, &dw, NULL);
				BulletDelay = 0;
				EnemyPosition[0] = player->position[0] + vector[0] * (i + 1);
				EnemyPosition[1] = player->position[1] + vector[1] * (i + 1);
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
		weapon->RemainBullet--;
	}
	if (GetAsyncKeyState(R_KEY) || weapon->ReloadState)
	{
		weapon->ReloadState = 1;
		if (weapon->RemainReloadDelay == weapon->ReloadDelay)
		{
			weapon->RemainBullet = weapon->MaxBullet;
			weapon->ReloadState = 0;
			weapon->RemainReloadDelay = 0;
		}
		else if (weapon->RemainReloadDelay < weapon->ReloadDelay)
		{
			weapon->RemainReloadDelay++;
		}
	}
	else if (BulletDelay < weapon->FireDelay)
	{
		BulletDelay++;
	}
}

void HittedEnemy(Enemy* enemy, const Weapon* weapon, char* MapData[MAP_Y][MAP_X])
{
	for (int Eindex = 0; Eindex < enemy->MaxNum; Eindex++)
	{
		if (enemy->XYHP[Eindex][0] == EnemyPosition[0] && enemy->XYHP[Eindex][1] == EnemyPosition[1])
		{
			enemy->XYHP[Eindex][2] -= weapon->damage;
			if (enemy->XYHP[Eindex][2] <= 0)
			{
				MapData[EnemyPosition[1]][EnemyPosition[0]] = BLANK;
				gold += enemy->GetGold;
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
		COORD CursorPosition = { 40,15 };
		system("cls");
		SetConsoleCursorPosition(screen, CursorPosition);
		WriteFile(screen, "GameOver...", 12, &dw, NULL);
		Sleep(3000);
		exit(1);
	}
}

int UpgradePlayer(Player* player, Weapon* weapon, const int UpNum)
{
	int RandNum = 0;
	switch (UpNum)
	{
	case 1:
		if (gold >= 50)
		{
			weapon->damage += weapon->UpgradeDamage;
			gold -= 50;
		}
		return 0;
		break;
	case 2:
		if (gold >= 200)
		{
			if (player->Speed > 0)
			{
				player->Speed--;
				gold -= 200;
			}
		}
		return 0;
		break;
	case 3:
		if (gold >= 30)
		{
			player->hp += 10;
			gold -= 30;
		}
		return 0;
		break;
	case 4:
		if (gold >= 30)
		{
			RandNum = rand() % 10;
			switch (RandNum)
			{
			case 0:
				weapon->scope = 1;
				weapon->reach += 5;
				break;
			case 1:
				weapon->magazine = 1;
				weapon->MaxBullet += 5;
				break;
			case 2:
				weapon->Auto = 1;
				weapon->FireDelay = weapon->FireDelay / 2;
				break;
			}
			gold -= 300;
		}
		return 0;
		break;
	case 6:
		return 1;
		break;
	default:
		return 0;
		break;
	}
}

int* ReturnVector()
{
	return vector;
}

int GetGoldInfo()
{
	return gold;
}