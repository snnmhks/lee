#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "information.h"

void CreateEnemy(Enemy* enemy, char* MapData[MAP_Y][MAP_X]);

void MoveEnemy(Player* player, Enemy* enemy, char* MapData[MAP_Y][MAP_X]);

int GetRoundInfo();

int GetWaveInfo();

#endif