#pragma once

#include "Enemy.h"
#include "Player.h"

struct Stage
{
    Enemy enemyList[MAX_ENEMIES];
    Player player;
    int nEnemies;
};

void stage_SetNumberOfStage(int nStages);
int stage_GetNumberOfStage();

bool stage_AddEnemy(int stageIdx, int x, int y, char sprite, int enemyInfoIdx);
bool stage_AddPlayer(int stageIdx, int x, int y, char sprite);


