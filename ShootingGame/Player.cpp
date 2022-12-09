#include "stdafx.h"
#include "Player.h"

#include "Bullet.h"

void player_Update(Player* pPlayer, COORD move, bool bShot)
{
	pPlayer->obj.x += move.X;
	pPlayer->obj.y += move.Y;

	if (pPlayer->obj.x < 0)
	{
		pPlayer->obj.x = 0;
	}
	if (pPlayer->obj.x > dfSCREEN_WIDTH - 2)
	{
		pPlayer->obj.x = dfSCREEN_WIDTH - 2;
	}
	if (pPlayer->obj.y < 0)
	{
		pPlayer->obj.y = 0;
	}
	if (pPlayer->obj.y > dfSCREEN_HEIGHT - 1)
	{
		pPlayer->obj.y = dfSCREEN_HEIGHT - 1;
	}

	if (bShot)
	{
		bullet_PlayerShot(pPlayer);
	}
}
