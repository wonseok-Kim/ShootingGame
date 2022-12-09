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
	int shotRandom; // 0 ~ 100%
};

struct EnemyInfo
{
	int hp;
	int movingPatternType;
	int shotInterval;
	int shotRandom;
};

bool enemy_AddInfo(int hp, int movingPatternType, int shotInterval, int shotRandom);
void enemy_GetInfo(int enemyInfoIdx,
	int* out_hp,
	int* out_movingPatternType,
	int* out_shotInterval,
	int* out_shotRandom);

void enemy_Update();
