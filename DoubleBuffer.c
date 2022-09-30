#define _CRT_SECURE_NO_WARNINGS
// 전처리기, 안전하다는 의미
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>
#include <string.h>

#include "DoubleBuffer.h"
#include "information.h"

//////////////////////////////////

static int ScreenIndex = 0;
static HANDLE screen[2];

//////////////////////////////////

// 버퍼를 초기화하는 함수
void ScreenInit()
{
	CONSOLE_CURSOR_INFO cursor;
	COORD size = { CONSOLE_WIDTH,CONSOLE_HEIGHT };
	SMALL_RECT rect = { 0,0,CONSOLE_WIDTH - 1,CONSOLE_HEIGHT - 1 };

	// 화면 2개를 생성
	// Front buffer
	screen[0] = CreateConsoleScreenBuffer
	(
		GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, CONSOLE_TEXTMODE_BUFFER, NULL
	);

	SetConsoleScreenBufferSize(screen[0], size);
	SetConsoleWindowInfo(screen[0], TRUE, &rect);

	// Back buffer
	screen[1] = CreateConsoleScreenBuffer
	(
		GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, CONSOLE_TEXTMODE_BUFFER, NULL
	);

	SetConsoleScreenBufferSize(screen[1], size);
	SetConsoleWindowInfo(screen[1], TRUE, &rect);

	cursor.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursor.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(screen[0], &cursor);
	SetConsoleCursorInfo(screen[1], &cursor);
}

// 버퍼를 교체하는 함수
void ScreenFlipping()
{
	// 버퍼는 하나만 활설화시킬 수 있다.
	SetConsoleActiveScreenBuffer(screen[ScreenIndex]);
	// 1, 0을 왔다 갔다 하는 팁
	ScreenIndex = !ScreenIndex;
}

// 버퍼를 지우는 함수
void ScreenClear()
{
	COORD coord = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(screen[ScreenIndex], ' ', CONSOLE_WIDTH * CONSOLE_HEIGHT * 2, coord, &dw);
}

// 버퍼를 해제하는 함수
void ScreenRelese()
{
	CloseHandle(screen[0]);
	CloseHandle(screen[1]);
}

HANDLE GetScreenInfo()
{
	return screen[ScreenIndex];
}