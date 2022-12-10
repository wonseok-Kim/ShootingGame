#include "stdafx.h"
#include "Player.h"

#include <math.h>

#include "Bullet.h"

void player_Update(Player* pPlayer, DWORD frameCount)
{	
	// 2프레임 당 1번 움직이게 하기 위해서
	if (abs(pPlayer->move.X) == 2)
	{
		pPlayer->obj.x += pPlayer->move.X / 2;
		pPlayer->move.X = 0;
	}
	if (abs(pPlayer->move.Y) == 2)
	{
		pPlayer->obj.y += pPlayer->move.Y / 2;
		pPlayer->move.Y = 0;
	}

	if (pPlayer->obj.x < 0)
	{
		pPlayer->obj.x = 0;
	}
	if (pPlayer->obj.x > SCREEN_WIDTH - 2)
	{
		pPlayer->obj.x = SCREEN_WIDTH - 2;
	}
	if (pPlayer->obj.y < 0)
	{
		pPlayer->obj.y = 0;
	}
	if (pPlayer->obj.y > SCREEN_HEIGHT - 1)
	{
		pPlayer->obj.y = SCREEN_HEIGHT - 1;
	}

	// 4프레임 당 1번 쏠 수 있게
	if (pPlayer->shot == 4)
	{
		bullet_PlayerShot(pPlayer);
		pPlayer->shot = 0;
	}


	// 맞았을 때 플레이어는 깜빡거리며 무적상태
	static DWORD framesInvincible = 0;

	if (pPlayer->bHitted)
	{
		if (framesInvincible % 10 == 0)
		{
			pPlayer->obj.visible = !pPlayer->obj.visible;
		}

		++framesInvincible;
		if (framesInvincible > pPlayer->invincibleFrames)
		{
			pPlayer->obj.visible = true;
			pPlayer->bHitted = false;
			framesInvincible = 0;
		}
	}
}
