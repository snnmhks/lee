#pragma once
#ifndef _MAP_H_
#define _MAP_H_

#include "information.h"

void SetConsoleScreen();

void SetMapData();

void SetBarrier();

void MapPrint(const Player* player, HANDLE screen);

void PrintStateScreen(const Player* player, Weapon *weapon,HANDLE screen);

char* ReturnMapData();

#endif