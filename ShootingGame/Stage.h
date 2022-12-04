#pragma once

#include "Enemy.h"
#include "Player.h"



struct Stage
{
    Enemy enemyList[MAX_ENEMIES];
    Player player;
    int nEnemies = 0;
};

void stage_SetNumberOfStage(int nStages);
bool stage_AddEnemy(int stageIdx, int x, int y, char sprite, int hp, int movingPatternIdx, int shotInterval);


