#pragma once

#include "Enemy.h"
#include "Player.h"

struct Stage
{
    Enemy enemyList[MAX_ENEMIES];
    Player player;
    int nEnemies;
};

void stage_Init();
void stage_SetNumberOfStage(int nStages);
bool stage_AddEnemy(int stageIdx, int x, int y, char sprite, int enemyInfoIdx);
bool stage_AddPlayer(int stageIdx, int x, int y, char sprite);


