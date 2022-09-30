#include <stdio.h>
#include <Windows.h> // ���콺 Ŀ�� �Լ��� ����ϱ� ���� �������� ���

#include "cursor.h" 

void gotoxy(int x, int y) {
	COORD pos = { x,y }; // Windows ����� ����� ����ü, ��ġ �������� ���� ����ü
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);  // pos �������� Ŀ���� �ű��.
}

void HideCursor() // Ŀ�� �����, ����ȭ �Ǿ� ������ �׳� ����ϸ� ��
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
	cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}