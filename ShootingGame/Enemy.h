#pragma once

#include "Object.h"
#include "MovingPattern.h"

#define MAX_ENEMY_INFOS 20

struct Enemy
{
	Object obj;
	int hp;
	int movingPatternType;
	int movingPatternIdx;
	int shotInterval; // fps ¥‹¿ß
};

struct EnemyInfo
{
	int hp;
	int movingPatternType;
	int shotInterval;
};

bool enemy_AddInfo(int hp, int movingPatternType, int shotInterval);
void enemy_GetInfo(int enemyInfoIdx, int* out_hp, int* movingPatternType, int* out_shotInterval);
