#include <stdio.h>
#include <Windows.h>

#include "map.h"
#include "cursor.h"
#include "information.h"

//////////////////////////////////

static char* map[MAP_Y][MAP_X];
static int index = 1;
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

void MapPrint(const Player* player, const HANDLE screen)
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

void PrintStateScreen(const Player* player, const Enemy *enemy, const Weapon *weapon, const int round, const int gold, const int wave, const HANDLE screen)
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
	WriteFile(screen, "STATUS", 7, &dw, NULL);

	CursorPosition.X = 0;
	CursorPosition.Y = CONSOLE_HEIGHT + 2;
	SetConsoleCursorPosition(screen, CursorPosition);
	for (int i = 0; i < CONSOLE_WIDTH; i++)
	{
		WriteFile(screen, "-", 2, &dw, NULL);
	}

	char hp[4];
	sprintf_s(hp, 4, "%d", player->hp);
	if (player->hp < 100 && player->hp >= 10)
	{
		strcat_s(hp,4, " ");
	}
	else if (player->hp < 10)
	{
		strcat_s(hp,4, " ");
		strcat_s(hp,4, " ");
	}
	CursorPosition.X = 2;
	CursorPosition.Y = CONSOLE_HEIGHT + 4;
	SetConsoleCursorPosition(screen, CursorPosition);
	WriteFile(screen, "HP : ", 6, &dw, NULL);
	WriteFile(screen, hp, 4, &dw, NULL);

	CursorPosition.Y = CONSOLE_HEIGHT + 6;
	SetConsoleCursorPosition(screen, CursorPosition);
	WriteFile(screen, "Weapon : ", 10, &dw, NULL);
	WriteFile(screen, weapon->name, strlen(weapon->name), &dw, NULL);

	CursorPosition.Y = CONSOLE_HEIGHT + 8;
	SetConsoleCursorPosition(screen, CursorPosition);
	if (!weapon->ReloadState)
	{
		WriteFile(screen, "Bullet : ", 10, &dw, NULL);
		for (int i = 0; i < weapon->RemainBullet; i++)
		{
			WriteFile(screen, weapon->shape, 2, &dw, NULL);
		}
	}
	else if (weapon->ReloadState)
	{
		WriteFile(screen, "Reload! ", 9, &dw, NULL);
		for (int i = 0; i < 10 - (weapon->RemainReloadDelay*10)/weapon->ReloadDelay; i++)
		{
			WriteFile(screen, "□", 2, &dw, NULL);
		}
	}

	CursorPosition.X = CONSOLE_WIDTH/3;
	CursorPosition.Y = CONSOLE_HEIGHT + 4;
	SetConsoleCursorPosition(screen, CursorPosition);
	WriteFile(screen, "Space ", 7, &dw, NULL);
	for (int i = 0; i < 10 - (player->RemainFastMovingDelay * 10) / player->FastMovingDelay; i++)
	{
		WriteFile(screen, "□", 2, &dw, NULL);
	}

	char r[3];
	sprintf_s(r, 3, "%d", round);
	if (round < 10)
	{
		strcat_s(r, 3, " ");
	}
	CursorPosition.Y = CONSOLE_HEIGHT + 6;
	SetConsoleCursorPosition(screen, CursorPosition);
	WriteFile(screen, "Round : ", 9, &dw, NULL);
	WriteFile(screen, r, 3, &dw, NULL);

	char g[MAX_GOLD_SCALE+1];
	int TmpGold = gold;
	int GoldScale = 1;
	sprintf_s(g, MAX_GOLD_SCALE + 1, "%d", gold);
	while(TmpGold/10 != 0)
	{
		TmpGold = TmpGold / 10;
		GoldScale++;
	}
	for (int i = 0; i < MAX_GOLD_SCALE - GoldScale; i++)
	{
		strcat_s(g, MAX_GOLD_SCALE + 1, " ");
	}

	CursorPosition.X = CONSOLE_WIDTH*2/3;
	CursorPosition.Y = CONSOLE_HEIGHT + 4;
	SetConsoleCursorPosition(screen, CursorPosition);
	WriteFile(screen, "Gold : ", 8, &dw, NULL);
	WriteFile(screen, g, MAX_GOLD_SCALE + 1, &dw, NULL);

	char w[2 + 1];
	int TmpWave = wave;
	int WaveScale = 1;
	sprintf_s(w, 2 + 1, "%d", wave);
	while (TmpWave / 10 != 0)
	{
		TmpWave = TmpWave / 10;
		WaveScale++;
	}
	for (int i = 0; i < 2 - WaveScale; i++)
	{
		strcat_s(w, 2 + 1, " ");
	}

	CursorPosition.Y = CONSOLE_HEIGHT + 6;
	SetConsoleCursorPosition(screen, CursorPosition);
	WriteFile(screen, "Wave : ", 7, &dw, NULL);
	WriteFile(screen, w, 2 + 1, &dw, NULL);

	char mw[2 + 1];
	int TmpMaxWave = enemy->MaxWave;
	int MaxWaveScale = 1;
	sprintf_s(mw, 2 + 1, "%d", enemy->MaxWave);
	while (TmpMaxWave / 10 != 0)
	{
		TmpMaxWave = TmpMaxWave / 10;
		MaxWaveScale++;
	}
	for (int i = 0; i < 2 - MaxWaveScale; i++)
	{
		strcat_s(mw, 2 + 1, " ");
	}

	WriteFile(screen, "/ ", 3, &dw, NULL);
	WriteFile(screen, mw, 2 + 1, &dw, NULL);
}

int PrintShop(int gold, const HANDLE screen)
{
	COORD ShopPosition = { 0,0 };
	DWORD dw;

	ShopPosition.X = CONSOLE_WIDTH / 2 - 2;
	ShopPosition.Y = 1;
	SetConsoleCursorPosition(screen, ShopPosition);
	WriteFile(screen, "SHOP", 5, &dw, NULL);

	ShopPosition.X = 0;
	ShopPosition.Y = 2;
	SetConsoleCursorPosition(screen, ShopPosition);
	for (int i = 0; i < CONSOLE_WIDTH; i++)
	{
		WriteFile(screen, "-", 2, &dw, NULL);
	}

	ShopPosition.X = CONSOLE_WIDTH / 2 - 7;
	ShopPosition.Y = 4;
	SetConsoleCursorPosition(screen, ShopPosition);
	if (index == 1)
	{
		WriteFile(screen, ">", 2, &dw, NULL);
	}
	WriteFile(screen, "Upgrade Damage (50G)", 21, &dw, NULL);

	ShopPosition.Y++;
	SetConsoleCursorPosition(screen, ShopPosition);
	if (index == 2)
	{
		WriteFile(screen, ">", 2, &dw, NULL);
	}
	WriteFile(screen, "Upgrade Speed (200G)", 21, &dw, NULL);

	ShopPosition.Y++;
	SetConsoleCursorPosition(screen, ShopPosition);
	if (index == 3)
	{
		WriteFile(screen, ">", 2, &dw, NULL);
	}
	WriteFile(screen, "Upgrade HP (30G)", 17, &dw, NULL);

	ShopPosition.Y++;
	SetConsoleCursorPosition(screen, ShopPosition);
	if (index == 4)
	{
		WriteFile(screen, ">", 2, &dw, NULL);
	}
	WriteFile(screen, "Buy Part (300G)", 16, &dw, NULL);

	ShopPosition.Y++;
	SetConsoleCursorPosition(screen, ShopPosition);
	if (index == 5)
	{
		WriteFile(screen, ">", 2, &dw, NULL);
	}
	WriteFile(screen, "Random Gun Draw (X)", 20, &dw, NULL);

	ShopPosition.Y++;
	SetConsoleCursorPosition(screen, ShopPosition);
	if (index == 6)
	{
		WriteFile(screen, ">", 2, &dw, NULL);
	}
	WriteFile(screen, "Finish", 7, &dw, NULL);

	ShopPosition.X = 0;
	ShopPosition.Y += 2;
	SetConsoleCursorPosition(screen, ShopPosition);
	for (int i = 0; i < CONSOLE_WIDTH; i++)
	{
		WriteFile(screen, "-", 2, &dw, NULL);
	}

	ShopPosition.X = CONSOLE_WIDTH/3;
	ShopPosition.Y += 2;
	SetConsoleCursorPosition(screen, ShopPosition);
	switch (index)
	{
	case 1:
		WriteFile(screen, "총의 공격력 상승. 총마다 올라가는 수치는 다르다.", 49, &dw, NULL);
		break;
	case 2:
		WriteFile(screen, "이동 속도 상승. 최대 5번 가능하다.", 35, &dw, NULL);
		break;
	case 3:
		WriteFile(screen, "최대 체력 상승. 10씩 올라간다.", 31, &dw, NULL);
		break;
	case 4:
		WriteFile(screen, "랜덤으로 부품을 산다. 중복 적용은 안된다.", 42, &dw, NULL);
		break;
	case 5:
		WriteFile(screen, "랜덤으로 총을 뽑는다. 뭐가나올지는 아무도 모른다.", 50, &dw, NULL);
		break;
	case 6:
		WriteFile(screen, "상점을 끝내고 다음 라운드로 넘어간다.", 38, &dw, NULL);
		break;
	}

	ShopPosition.X = CONSOLE_WIDTH / 2 - 7;
	ShopPosition.Y += 2;
	SetConsoleCursorPosition(screen, ShopPosition);
	char g[MAX_GOLD_SCALE + 1];
	int TmpGold = gold;
	int GoldScale = 1;
	sprintf_s(g, MAX_GOLD_SCALE + 1, "%d", gold);
	while (TmpGold / 10 != 0)
	{
		TmpGold = TmpGold / 10;
		GoldScale++;
	}
	for (int i = 0; i < MAX_GOLD_SCALE - GoldScale; i++)
	{
		strcat_s(g, MAX_GOLD_SCALE + 1, " ");
	}
	WriteFile(screen, "Gold : ", 8, &dw, NULL);
	WriteFile(screen, g, MAX_GOLD_SCALE + 1, &dw, NULL);

	if (GetAsyncKeyState(VK_UP) & 0x0001)
	{
		index--;
		if (index < 1)
		{
			index = 1;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x0001)
	{
		index++;
		if (index > 6)
		{
			index = 6;
		}
	}
	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		return index;
	}
	else
	{
		return 0;
	}
}

char* ReturnMapData()
{
	return map;
}