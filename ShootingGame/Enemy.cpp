#include "stdafx.h"
#include "Enemy.h"

EnemyInfo g_EnemyInfoList[MAX_ENEMY_INFOS];
int g_nEnemyInfo = 0;

bool enemy_AddInfo(int hp, int movingPatternType, int shotInterval)
{
    if (g_nEnemyInfo >= MAX_ENEMY_INFOS)
    {
        PrintError("g_nEnemyInfo is full\n");
        return false;
    }

    g_EnemyInfoList[g_nEnemyInfo].hp = hp;
    g_EnemyInfoList[g_nEnemyInfo].movingPatternType = movingPatternType;
    g_EnemyInfoList[g_nEnemyInfo].shotInterval = shotInterval;

    ++g_nEnemyInfo;

    return true;
}

void enemy_GetInfo(int enemyInfoIdx, int* out_hp, int* movingPatternType, int* out_shotInterval)
{
    Assert(enemyInfoIdx >= 0 && enemyInfoIdx <= g_nEnemyInfo, "Invalid idx");

    *out_hp = g_EnemyInfoList[enemyInfoIdx].hp;
    *movingPatternType = g_EnemyInfoList[enemyInfoIdx].movingPatternType;
    *out_shotInterval = g_EnemyInfoList[enemyInfoIdx].shotInterval;
}