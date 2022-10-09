#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "information.h"

void MovePlayer(Player* player, const char* MapData[MAP_Y][MAP_X]);

void PlayerPrint(const Player* player, Weapon* weapon, const HANDLE screen);

void shoot(const Player* player, const Weapon* weapon, const char* MapData[MAP_Y][MAP_X], const HANDLE screen);

void HittedEnemy(Enemy* enemy, const Weapon* weapon, char* MapData[MAP_Y][MAP_X]);

void GameOver(const Player* player, const HANDLE screen);

int UpgradePlayer(Player* player, Weapon* weapon, const int UpNum);

int* ReturnVector();

int GetGoldInfo();

#endif