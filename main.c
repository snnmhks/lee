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
		PrintStateScreen(GetPlayerInfo(), GetWeaponInfo("pistol"), GetScreenInfo());
		CreateEnemy(GetEnemyInfo());
		MoveEnemy(GetPlayerInfo(), GetEnemyInfo(), ReturnMapData());
		EnemyToMap(GetEnemyInfo(), ReturnMapData());
		MapPrint(GetPlayerInfo(), GetScreenInfo());
		MovePlayer(GetPlayerInfo(), ReturnMapData());;
		PlayerPrint(GetPlayerInfo(), GetWeaponInfo("pistol"), GetScreenInfo());
		shoot(GetPlayerInfo(), GetWeaponInfo("pistol"), GetEnemyInfo(), ReturnMapData(), GetScreenInfo());
		HittedEnemy(GetEnemyInfo(), GetWeaponInfo("pistol"), ReturnMapData());
		GameOver(GetPlayerInfo(), GetScreenInfo());
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