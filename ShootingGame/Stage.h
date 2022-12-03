#pragma once

struct Enemy;
struct Player;

struct Stage
{
    Enemy* Enemies[MAX_ENEMIES];
    Player* Player;

};