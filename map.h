#pragma once
#ifndef _MAP_H_
#define _MAP_H_

#include "information.h"

void SetConsoleScreen();

void SetMapData();

void SetBarrier();

void MapPrint(const Player* player, const HANDLE screen);

void PrintStateScreen(const Player* player, const Enemy *enemy,const Weapon *weapon, const int round, const int gold, const int wave, const HANDLE screen);

int PrintShop(int gold, const HANDLE screen);

char* ReturnMapData();

#endif