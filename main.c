#include <stdio.h>
#include <process.h>
#include <Windows.h>

#include "map.h"
#include "cursor.h"
#include "player.h"
#include "DoubleBuffer.h"
#include "information.h"
#include "enemy.h"

void EnemyAct()
{
	while (1)
	{
		CreateEnemy(GetEnemyInfo(GetRoundInfo()), ReturnMapData());
		MoveEnemy(GetPlayerInfo(), GetEnemyInfo(GetRoundInfo()), ReturnMapData());
		EnemyToMap(GetEnemyInfo(GetRoundInfo()), ReturnMapData());
		Sleep(10);
	}
}

void PlayerAct()
{
	while (1)
	{
		MovePlayer(GetPlayerInfo(), ReturnMapData());
		HittedEnemy(GetEnemyInfo(GetRoundInfo()), GetWeaponInfo("AutoPistol"), ReturnMapData());
		Sleep(10);
	}
}

int main()
{
	SetPlayerInfo();
	SetWeaponInfo();
	SetMapData();
	ScreenInit();
	SetConsoleScreen();
	SetEnemyInfo();
	//SetBarrier();

	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)EnemyAct, NULL, 0, NULL);
	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)PlayerAct, NULL, 0, NULL);

	int RevisionScreen = 0;
	while (1)
	{
		ScreenFlipping();
		ScreenClear();
		GameOver(GetPlayerInfo(), GetScreenInfo());
		PrintStateScreen(GetPlayerInfo(), GetWeaponInfo("AutoPistol"), GetRoundInfo(), GetGoldInfo(), GetScreenInfo());
		MapPrint(GetPlayerInfo(), GetScreenInfo());
		PlayerPrint(GetPlayerInfo(), GetWeaponInfo("AutoPistol"), GetScreenInfo());
		shoot(GetPlayerInfo(), GetWeaponInfo("AutoPistol"), ReturnMapData(), GetScreenInfo());
		if (RevisionScreen != 2)
		// 버퍼 두개의 크기를 한번 늘였다가 줄여줘야지 제대로 프린팅이됨
		{
			system("mode con cols=93 lines=40");
			system("mode con cols=92 lines=40");
			RevisionScreen++;
		}
		Sleep(10);
	}
	ScreenRelese();
}