#include <stdio.h>
#include <process.h>
#include <Windows.h>

#include "map.h"
#include "cursor.h"
#include "player.h"
#include "DoubleBuffer.h"
#include "information.h"
#include "enemy.h"

int BeforeRound = 0;

void EnemyAct()
{
	while (1)
	{
		if (BeforeRound == GetRoundInfo())
		{
			CreateEnemy(GetEnemyInfo(GetRoundInfo()), ReturnMapData());
			MoveEnemy(GetPlayerInfo(), GetEnemyInfo(GetRoundInfo()), ReturnMapData());
			Sleep(10);
		}
	}
}

void PlayerAct()
{
	while (1)
	{
		if (BeforeRound == GetRoundInfo())
		{
			MovePlayer(GetPlayerInfo(), ReturnMapData());
			HittedEnemy(GetEnemyInfo(GetRoundInfo()), GetWeaponInfo("pistol"), ReturnMapData());
			Sleep(10);
		}
	}
}

void ShopAct()
{
	while (1)
	{
		if (BeforeRound < GetRoundInfo())
		{
			ScreenFlipping();
			ScreenClear();
			BeforeRound += UpgradePlayer(GetPlayerInfo(), GetWeaponInfo("pistol"), PrintShop(GetGoldInfo(), GetScreenInfo()));
			Sleep(10);
		}
	}
}

void RevisionScreen()
{
	// 버퍼 두개의 크기를 한번 늘였다가 줄여줘야지 제대로 프린팅이됨
	ScreenFlipping();
	system("mode con cols=93 lines=40");
	system("mode con cols=92 lines=40");
	ScreenFlipping();
	system("mode con cols=93 lines=40");
	system("mode con cols=92 lines=40");
}

int main()
{
	time_t current = time(NULL);
	srand(current);
	SetPlayerInfo();
	SetWeaponInfo();
	SetMapData();
	ScreenInit();
	SetConsoleScreen();
	SetEnemyInfo();
	RevisionScreen();

	while (1)
	{
		ScreenFlipping();
		ScreenClear();
		int aaa = IntroScreen(GetScreenInfo());
		if (aaa == 0)
		{
			break;
		}
		else if (aaa == 1)
		{
			ScreenClear();
			HowToPlay(GetScreenInfo());
		}
		Sleep(10);
	}
	//SetBarrier();

	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)EnemyAct, NULL, 0, NULL);
	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)PlayerAct, NULL, 0, NULL);
	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)ShopAct, NULL, 0, NULL);

	while (1)
	{
		if (BeforeRound == GetRoundInfo())
		{
			ScreenFlipping();
			ScreenClear();
			GameOver(GetPlayerInfo(), GetScreenInfo());
			PrintStateScreen(GetPlayerInfo(), GetEnemyInfo(GetRoundInfo()), GetWeaponInfo("pistol"), GetRoundInfo(), GetGoldInfo(), GetWaveInfo(), GetScreenInfo());
			MapPrint(GetPlayerInfo(), GetScreenInfo());
			PlayerPrint(GetPlayerInfo(), GetWeaponInfo("pistol"), GetScreenInfo());
			shoot(GetPlayerInfo(), GetWeaponInfo("pistol"), ReturnMapData(), GetScreenInfo());
		}
		Sleep(10);
	}
	ScreenRelese();
}