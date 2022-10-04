#include <stdio.h>
#include <Windows.h>

#include "map.h"
#include "cursor.h"
#include "information.h"

//////////////////////////////////

static char* map[MAP_Y][MAP_X];

//////////////////////////////////

void SetConsoleScreen()
{
	system("mode con cols=92 lines=40");
	//SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	// 최대 크기

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
	// 휠업바 지우는 코드
}

void SetMapData()
{
	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			if (i == 0 || i == MAP_Y - 1 || j == 0 || j == MAP_X - 1)
			{
				map[i][j] = WALL;
			}
			else
			{
				map[i][j] = BLANK;
			}
		}
	}
}

void SetBarrier()
{
	int BlockNum = 20;
	int x[MAP_X - 2] = { 0, };
	int y[MAP_Y - 2] = { 0, };
	int tmp[MAP_X - 2] = { 0, };

	time_t current = time(NULL);
	srand(current);

	for (int i = 0; i < MAP_X - 2; i++)
	{
		x[i] = i + 1;
		y[i] = i + 1;
		tmp[i] = i + 1;
	}

	for (int i = 0; i < BlockNum; i++) {
		int choice = tmp[rand() % (MAP_Y - 3 - i)];
		int temp = x[choice];
		x[choice] = x[BlockNum - i];
		x[BlockNum - i] = temp;
	}
	for (int i = 0; i < BlockNum; i++) {
		int choice = tmp[rand() % (MAP_Y - 3 - i)];
		int temp = y[choice];
		y[choice] = y[BlockNum - i];
		y[BlockNum - i] = temp;
	}

	for (int i = 0; i < BlockNum; i += 2)
	{
		for (int j = 1; j < BlockNum; j += 2)
		{
			map[x[i]][y[j]] = BLOCK;
		}
	}
	for (int i = 1; i < BlockNum; i += 2)
	{
		for (int j = 0; j < BlockNum; j += 2)
		{
			map[x[i]][y[j]] = BLOCK;
		}
	}

}

void MapPrint(const Player* player, HANDLE screen)
{
	COORD CursorPosition = { 0,0 };
	DWORD dw;

	int x = player->position[0];
	int y = player->position[1];

	if (x < CONSOLE_WIDTH / 4)
	{
		x = CONSOLE_WIDTH / 4;
	}
	else if (x + CONSOLE_WIDTH / 4 > MAP_X)
	{
		x = MAP_X - CONSOLE_WIDTH / 4;
	}
	if (y < CONSOLE_HEIGHT / 2)
	{
		y = CONSOLE_HEIGHT / 2;
	}
	else if (y + CONSOLE_HEIGHT / 2 > MAP_Y)
	{
		y = MAP_Y - CONSOLE_HEIGHT / 2;
	}
	SetConsoleCursorPosition(screen, CursorPosition);
	for (int i = y - CONSOLE_HEIGHT / 2; i < y + CONSOLE_HEIGHT / 2; i++)
	{
		for (int j = x - CONSOLE_WIDTH / 4; j < x + CONSOLE_WIDTH / 4; j++)
		{
			WriteFile(screen, map[i][j], 2, &dw, NULL);
		}
	}
}

void PrintStateScreen(const Player* player, Weapon *weapon, HANDLE screen)
{
	COORD CursorPosition = { 0, CONSOLE_HEIGHT };
	DWORD dw;
	SetConsoleCursorPosition(screen, CursorPosition);
	for (int i = 0; i < CONSOLE_WIDTH; i++)
	{
		WriteFile(screen,"-", 1, &dw, NULL);
	}
	
	CursorPosition.X = CONSOLE_WIDTH/2 - 3;
	CursorPosition.Y = CONSOLE_HEIGHT + 1;
	SetConsoleCursorPosition(screen, CursorPosition);
	WriteFile(screen, "STATUS", 6, &dw, NULL);

	CursorPosition.X = 0;
	CursorPosition.Y = CONSOLE_HEIGHT + 2;
	SetConsoleCursorPosition(screen, CursorPosition);
	for (int i = 0; i < CONSOLE_WIDTH; i++)
	{
		WriteFile(screen, "-", 1, &dw, NULL);
	}

	char hp[6];
	sprintf_s(hp, 6, "%d", player->hp);
	if (player->hp < 100 && player->hp >= 10)
	{
		strcat_s(hp,6, " ");
	}
	else if (player->hp < 10)
	{
		strcat_s(hp,6, " ");
		strcat_s(hp,6, " ");
	}
	CursorPosition.X = 2;
	CursorPosition.Y = CONSOLE_HEIGHT + 4;
	SetConsoleCursorPosition(screen, CursorPosition);
	WriteFile(screen, "HP : ", 5, &dw, NULL);
	WriteFile(screen, hp, 6, &dw, NULL);

	CursorPosition.Y = CONSOLE_HEIGHT + 6;
	SetConsoleCursorPosition(screen, CursorPosition);
	WriteFile(screen, "Weapon : ", 9, &dw, NULL);
	WriteFile(screen, weapon->name, strlen(weapon->name), &dw, NULL);

	CursorPosition.Y = CONSOLE_HEIGHT + 8;
	SetConsoleCursorPosition(screen, CursorPosition);
	if (!weapon->ReloadState)
	{
		WriteFile(screen, "Bullet : ", 9, &dw, NULL);
		for (int i = 0; i < weapon->RemainBullet; i++)
		{
			WriteFile(screen, weapon->shape, 2, &dw, NULL);
		}
	}
	else if (weapon->ReloadState)
	{
		WriteFile(screen, "Reload! ", 8, &dw, NULL);
		for (int i = 0; i < 10 - (weapon->RemainReloadDelay*10)/weapon->ReloadDelay; i++)
		{
			WriteFile(screen, "□", 2, &dw, NULL);
		}
	}
}

char* ReturnMapData()
{
	return map;
}