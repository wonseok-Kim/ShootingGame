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
		PrintError("g_Stages �ʱ�ȭ ������� ���� nEnemies�� ����");
		return false;
	}
	if (stageIdx < 0 || stageIdx >= g_nStages)
	{
		PrintError("stageIdx %d�� �ùٸ��� ����.", stageIdx);
		return false;
	}

	int nEnemies = g_Stages[stageIdx].nEnemies;
	Enemy* pEnemy = &g_Stages[stageIdx].enemyList[nEnemies];

	pEnemy->obj.visible = true;
	pEnemy->obj.x = x;
	pEnemy->obj.y = y;
	pEnemy->obj.sprite = sprite;
	pEnemy->movingPatternIdx = 0;

	enemy_GetInfo(enemyInfoIdx, &pEnemy->hp, &pEnemy->movingPatternType, &pEnemy->shotInterval);

	++(g_Stages[stageIdx].nEnemies);
	return true;
}

bool stage_AddPlayer(int stageIdx, int x, int y, char sprite)
{
	// TODO: stageIDx assert�� üũ

	Player* pPlayer = &g_Stages[stageIdx].player;
	
	pPlayer->obj.visible = true;
	pPlayer->obj.x = x;
	pPlayer->obj.y = y;
	pPlayer->obj.sprite = sprite;

	// TODO: ���߿� ���Ϸ� ����
	pPlayer->hp = 3;	

	return true;
}
