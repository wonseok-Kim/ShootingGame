#pragma once

#include "Object.h"
#include "MovingPattern.h"

#define MAX_ENEMY_INFOS 20

struct Enemy
{
	Object obj;
	int hp;
	MovingPattern movingPattern;
	int shotInterval; // fps ¥‹¿ß
};

struct EnemyInfo
{
	int hp;
	int movingPatternIdx;
	int shotInterval;
};

bool enemy_AddInfo(int hp, int movingPatternIdx, int shotInterval);
void enemy_GetInfo(int enemyInfoIdx, int* out_hp, int* out_movingPatternIdx, int* out_shotInterval);
