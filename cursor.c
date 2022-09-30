#include <stdio.h>
#include <Windows.h> // 마우스 커서 함수를 사용하기 위해 가져오는 헤더

#include "cursor.h" 

void gotoxy(int x, int y) {
	COORD pos = { x,y }; // Windows 헤더에 내장된 구조체, 위치 변수만을 가진 구조체
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);  // pos 방향으로 커서를 옮긴다.
}

void HideCursor() // 커서 숨기기, 정형화 되어 있으니 그냥 사용하면 됨
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}