#include "stdafx.h"
#include "Stage.h"

#include "Enemy.h"

Stage g_Stages[MAX_STAGES];
int g_nStages = 0;
static bool s_bInit = false;

void stage_Init()
{
	for (int i = 0; i < MAX_STAGES; ++i)
	{
		g_Stages[i].nEnemies = 0;
	}
	s_bInit = true;
}

void stage_SetNumberOfStage(int nStages)
{
	g_nStages = nStages;
}

bool stage_AddEnemy(int stageIdx, int x, int y, char sprite, int enemyInfoIdx)
{
	if (!s_bInit)
	{
		PrintError("g_Stages 초기화 해줘야할 변수 nEnemies가 있음");
		return false;
	}
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

	enemy_GetInfo(enemyInfoIdx, &pEnemy->hp, &pEnemy->movingPattern, &pEnemy->shotInterval);

	++(g_Stages[stageIdx].nEnemies);
	return true;
}
