#include <stdio.h>
#include <process.h>
#include <Windows.h>

#include "map.h"
#include "cursor.h"
#include "player.h"
#include "DoubleBuffer.h"
#include "information.h"
#include "enemy.h"

int main()
{
	SetPlayerInfo();
	SetPistolInfo();
	SetEnemyInfo();
	SetMapData();
	ScreenInit();
	SetConsoleScreen();
	//SetBarrier();

	int RevisionScreen = 0;
	while (1)
	{
		ScreenFlipping();
		ScreenClear();
		GameOver(GetPlayerInfo(), GetScreenInfo());
		PrintStateScreen(GetPlayerInfo(), GetWeaponInfo("pistol"), GetRoundInfo(), GetGoldInfo(), GetScreenInfo());
		CreateEnemy(GetEnemyInfo(GetRoundInfo()));
		MoveEnemy(GetPlayerInfo(), GetEnemyInfo(GetRoundInfo()), ReturnMapData());
		EnemyToMap(GetEnemyInfo(GetRoundInfo()), ReturnMapData());
		MapPrint(GetPlayerInfo(), GetScreenInfo());
		MovePlayer(GetPlayerInfo(), ReturnMapData());;
		PlayerPrint(GetPlayerInfo(), GetWeaponInfo("pistol"), GetScreenInfo());
		shoot(GetPlayerInfo(), GetWeaponInfo("pistol"), ReturnMapData(), GetScreenInfo());
		HittedEnemy(GetEnemyInfo(GetRoundInfo()), GetWeaponInfo("pistol"), ReturnMapData());
		if (RevisionScreen != 2)
			// ���� �ΰ��� ũ�⸦ �ѹ� �ÿ��ٰ� �ٿ������ ����� �������̵�
		{
			system("mode con cols=93 lines=40");
			system("mode con cols=92 lines=40");
			RevisionScreen++;
		}
		Sleep(10);
	}
	ScreenRelese();
}