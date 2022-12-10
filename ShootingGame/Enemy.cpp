#include "stdafx.h"
#include "Enemy.h"

#include "Bullet.h"
#include "Game.h"

EnemyInfo g_EnemyInfoList[MAX_ENEMY_INFOS];
int g_nEnemyInfo = 0;

bool enemy_AddInfo(int hp, int movingPatternType, int shotInterval, int shotRandom, int nBullets, COORD* dirBullet)
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
	g_EnemyInfoList[g_nEnemyInfo].nBullets = nBullets;

	for (int i = 0; i < nBullets; ++i)
	{
		g_EnemyInfoList[g_nEnemyInfo].dirBullet[i].X = dirBullet[i].X;
		g_EnemyInfoList[g_nEnemyInfo].dirBullet[i].Y = dirBullet[i].Y;
	}

	++g_nEnemyInfo;

	return true;
}

void enemy_GetInfo(int enemyInfoIdx, int* out_hp)
{
	Assert(enemyInfoIdx >= 0 && enemyInfoIdx <= g_nEnemyInfo, "Invalid idx");

	*out_hp = g_EnemyInfoList[enemyInfoIdx].hp;	
}

void enemy_Update(DWORD frameCount)
{
	extern MovingPattern g_MovingPatterns[MAX_MOVING_PATTERNS];
	extern Game g_Game;

	Enemy* pEnemyList = g_Game.stage.enemyList;

	MovingPattern* pMovingPattern;
	int patternType;
	int* pPatternIdx;

	Enemy* pEnemy;
	int idxEnemyInfo;

	int shotInterval;
	int shotRandom;

	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		if (!pEnemyList[i].obj.visible)
		{
			continue;
		}

		pEnemy = &pEnemyList[i];
		idxEnemyInfo = pEnemy->infoIdx;

		patternType = g_EnemyInfoList[idxEnemyInfo].movingPatternType;
		pMovingPattern = &g_MovingPatterns[patternType];
		pPatternIdx = &pEnemy->movingPatternIdx;

		// 捞悼 贸府
		if (frameCount % pMovingPattern->fpsInterval == 0)
		{
			pEnemy->obj.x += pMovingPattern->movingBy[*pPatternIdx].X;
			pEnemy->obj.y += pMovingPattern->movingBy[*pPatternIdx].Y;

			*pPatternIdx = (*pPatternIdx + 1) % pMovingPattern->nLength;
		}

		// 鸡 贸府
		shotInterval = g_EnemyInfoList[idxEnemyInfo].shotInterval;
		shotRandom = g_EnemyInfoList[idxEnemyInfo].shotRandom;

		if (frameCount % shotInterval == 0)
		{
			int random = util_randInt(0, 100);
			if (random <= shotRandom)
			{
				bullet_EnemyShot(pEnemy);
			}
		}
	}
}
