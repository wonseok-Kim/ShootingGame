#pragma once

#include "Object.h"

struct Player
{
	Object obj;
	int hp;
};

void player_Update(Player* pPlayer, COORD move, bool bShot);