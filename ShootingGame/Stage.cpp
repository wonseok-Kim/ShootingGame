#include "stdafx.h"
#include "Stage.h"

Stage g_Stage[30];
int g_nStages = 0;

void stage_SetNumberOfStage(int nStages)
{
	g_nStages = nStages;
}

bool stage_AddEnemy(int stageIdx, int x, int y, char sprite, int hp, int movingPatternIdx, int shotInterval)
{
	if (stageIdx < 0 && stageIdx >= g_nStages)
	{
		PrintError("stageIdx %d가 g_nStages 보다 크다", stageIdx);
		return false;
	}

	int* pnEnemies = &g_Stage[stageIdx].nEnemies;
	Enemy* pEnemyList = g_Stage[stageIdx].enemyList;

	pEnemyList[(*pnEnemies)].obj.visible = true;
	pEnemyList[(*pnEnemies)].obj.x = x;
	pEnemyList[(*pnEnemies)].obj.y = y;
	pEnemyList[(*pnEnemies)].obj.sprite = sprite;

	pEnemyList[(*pnEnemies)].hp = hp;
	// TODO: moving pattern 삽입
	pEnemyList[(*pnEnemies)].shotInterval = shotInterval;

	++(*pnEnemies);

	return true;
}
