#define _CRT_SECURE_NO_WARNINGS
// ��ó����, �����ϴٴ� �ǹ�
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

// ���۸� �ʱ�ȭ�ϴ� �Լ�
void ScreenInit()
{
	CONSOLE_CURSOR_INFO cursor;
	COORD size = { CONSOLE_WIDTH,CONSOLE_HEIGHT };
	SMALL_RECT rect = { 0,0,CONSOLE_WIDTH - 1,CONSOLE_HEIGHT - 1 };

	// ȭ�� 2���� ����
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

	cursor.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
	cursor.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
	SetConsoleCursorInfo(screen[0], &cursor);
	SetConsoleCursorInfo(screen[1], &cursor);
}

// ���۸� ��ü�ϴ� �Լ�
void ScreenFlipping()
{
	// ���۴� �ϳ��� Ȱ��ȭ��ų �� �ִ�.
	SetConsoleActiveScreenBuffer(screen[ScreenIndex]);
	// 1, 0�� �Դ� ���� �ϴ� ��
	ScreenIndex = !ScreenIndex;
}

// ���۸� ����� �Լ�
void ScreenClear()
{
	COORD coord = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(screen[ScreenIndex], ' ', CONSOLE_WIDTH * CONSOLE_HEIGHT * 2, coord, &dw);
}

// ���۸� �����ϴ� �Լ�
void ScreenRelese()
{
	CloseHandle(screen[0]);
	CloseHandle(screen[1]);
}

HANDLE GetScreenInfo()
{
	return screen[ScreenIndex];
}