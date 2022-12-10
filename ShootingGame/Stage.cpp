#include "stdafx.h"
#include "Stage.h"

#include "Enemy.h"

Stage g_Stages[MAX_STAGES];
int g_nStages = 0;


void stage_SetNumberOfStage(int nStages)
{
	g_nStages = nStages;
}

int stage_GetNumberOfStage()
{
	return g_nStages;
}

bool stage_AddEnemy(int stageIdx, int x, int y, char sprite, int enemyInfoIdx)
{
	if (stageIdx < 0 || stageIdx >= g_nStages)
	{
		PrintError("stageIdx %d가 올바르지 않음.", stageIdx);
		return false;
	}

	int nEnemies = g_Stages[stageIdx].nEnemies;
	Enemy* pEnemy = &g_Stages[stageIdx].enemyList[nEnemies];

	pEnemy->obj.visible = true;
	pEnemy->obj.x = x;
	pEnemy->obj.y = y;
	pEnemy->obj.sprite = sprite;

	pEnemy->infoIdx = enemyInfoIdx;
	pEnemy->movingPatternIdx = 0;

	enemy_GetInfo(enemyInfoIdx, &pEnemy->hp);

	++(g_Stages[stageIdx].nEnemies);
	return true;
}

bool stage_AddPlayer(int stageIdx, int x, int y, char sprite)
{
	if (stageIdx < 0 || stageIdx >= g_nStages)
	{
		PrintError("stageIdx %d가 올바르지 않음.", stageIdx);
		return false;
	}

	Player* pPlayer = &g_Stages[stageIdx].player;
	
	pPlayer->obj.visible = true;
	pPlayer->obj.x = x;
	pPlayer->obj.y = y;
	pPlayer->obj.sprite = sprite;

	
	pPlayer->hp = 3;	
	pPlayer->invincibleFrames = 50;

	return true;
}
