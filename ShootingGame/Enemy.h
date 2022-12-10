#pragma once

#include "Object.h"
#include "MovingPattern.h"

#define MAX_ENEMY_INFOS 20

struct Enemy
{
	Object obj;
	int infoIdx;
	int hp;
	int movingPatternIdx;	
};

struct EnemyInfo
{
	int hp;
	int movingPatternType;
	int shotInterval;
	int shotRandom;
	int nBullets;
	COORD dirBullet[9];
};

bool enemy_AddInfo(int hp, int movingPatternType, int shotInterval, int shotRandom, int nBullets, COORD* dirBullet);
void enemy_GetInfo(int enemyInfoIdx, int* out_hp);

void enemy_Update(DWORD frameCount);
