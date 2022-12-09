#pragma once

#include "Enemy.h"
#include "Player.h"

struct Stage
{
    Enemy enemyList[MAX_ENEMIES];
    Player player;
    int nEnemies;
};

// TODO: 전역변수라 알아서 초기ㅗ하 되지 않나?
void stage_Init();

void stage_SetNumberOfStage(int nStages);
int stage_GetNumberOfStage();

bool stage_AddEnemy(int stageIdx, int x, int y, char sprite, int enemyInfoIdx);
bool stage_AddPlayer(int stageIdx, int x, int y, char sprite);


