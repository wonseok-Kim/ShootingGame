#include "stdafx.h"
#include "Enemy.h"

#include "Bullet.h"
#include "Game.h"

EnemyInfo g_EnemyInfoList[MAX_ENEMY_INFOS];
int g_nEnemyInfo = 0;

bool enemy_AddInfo(int hp, int movingPatternType, int shotInterval, int shotRandom)
{
    if (g_nEnemyInfo >= MAX_ENEMY_INFOS)
    {
        PrintError("g_nEnemyInfo is full\n");
        return false;
    }

    g_EnemyInfoList[g_nEnemyInfo].hp = hp;
    g_EnemyInfoList[g_nEnemyInfo].movingPatternType = movingPatternType;
    g_EnemyInfoList[g_nEnemyInfo].shotInterval = shotInterval;
	g_EnemyInfoList[g_nEnemyInfo].shotRandom = shotRandom;

    ++g_nEnemyInfo;

    return true;
}

void enemy_GetInfo(int enemyInfoIdx, 
	int* out_hp, 
	int* out_movingPatternType, 
	int* out_shotInterval,
	int* out_shotRandom)
{
    Assert(enemyInfoIdx >= 0 && enemyInfoIdx <= g_nEnemyInfo, "Invalid idx");

    *out_hp = g_EnemyInfoList[enemyInfoIdx].hp;
    *out_movingPatternType = g_EnemyInfoList[enemyInfoIdx].movingPatternType;
    *out_shotInterval = g_EnemyInfoList[enemyInfoIdx].shotInterval;
	*out_shotRandom = g_EnemyInfoList[enemyInfoIdx].shotRandom;
}

void enemy_Update()
{
	static DWORD frameCount = 0;

	extern MovingPattern g_MovingPatterns[MAX_MOVING_PATTERNS];
	extern Game g_Game;

	Enemy* pEnemyList = g_Game.stage.enemyList;
	MovingPattern* pMovingPattern;
	int* pPatternType;
	int* pPatternIdx;
	Enemy* pEnemy;

	++frameCount;

	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		if (!pEnemyList[i].obj.visible)
		{
			continue;
		}

		pEnemy = &pEnemyList[i];
		pPatternType = &pEnemy->movingPatternType;
		pPatternIdx = &pEnemy->movingPatternIdx;
		pMovingPattern = &g_MovingPatterns[*pPatternType];

		// 捞悼 贸府
		if (frameCount % pMovingPattern->fpsInterval == 0)
		{
			pEnemy->obj.x += pMovingPattern->movingBy[*pPatternIdx].X;
			pEnemy->obj.y += pMovingPattern->movingBy[*pPatternIdx].Y;

			*pPatternIdx = (*pPatternIdx + 1) % pMovingPattern->nLength;
		}

		// 鸡 贸府
		if (frameCount % pEnemy->shotInterval == 0)
		{
			int shotRandom = util_randInt(0, 100);
			if (shotRandom <= pEnemy->shotRandom)
			{
				bullet_EnemyShot(pEnemy);
			}
		}
	}
}
