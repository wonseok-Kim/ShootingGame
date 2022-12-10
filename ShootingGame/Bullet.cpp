#include "stdafx.h"
#include "Bullet.h"

#include "Enemy.h"
#include "Game.h"
#include "Player.h"

Bullet g_Bullets[MAX_BULLETS];
int g_idxBlankBullet = 0;

static bool nextBlankIdx()
{
	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		++g_idxBlankBullet;
		if (g_idxBlankBullet >= MAX_BULLETS)
		{
			g_idxBlankBullet = 0;
		}

		if (g_Bullets[g_idxBlankBullet].obj.visible == false)
		{
			return true;
		}
	}

	return false;
}

bool bullet_EnemyShot(const Enemy* pEnemy)
{
	extern EnemyInfo g_EnemyInfoList[MAX_ENEMY_INFOS];

	EnemyInfo* pEnemyInfo = &g_EnemyInfoList[pEnemy->infoIdx];

	for (int i = 0; i < pEnemyInfo->nBullets; ++i)
	{
		Bullet* pBullet = &g_Bullets[g_idxBlankBullet];

		pBullet->flag = eBulletFlag_EnemyShot;

		pBullet->obj.visible = true;
		pBullet->obj.x = pEnemy->obj.x;
		pBullet->obj.y = pEnemy->obj.y;
		pBullet->obj.sprite = '*';

		pBullet->dir.X = pEnemyInfo->dirBullet[i].X;
		pBullet->dir.Y = pEnemyInfo->dirBullet[i].Y;

		if (!nextBlankIdx())
		{
			PrintError("ÃÑ¾Ë °³¼ö ²ËÂü.\n");
			return false;
		}
	}
	return true;
}

bool bullet_PlayerShot(const Player* pPlayer)
{
	Bullet* pBullet = &g_Bullets[g_idxBlankBullet];

	pBullet->flag = eBulletFlag_PlayerShot;

	pBullet->obj.visible = true;
	pBullet->obj.x = pPlayer->obj.x;
	pBullet->obj.y = pPlayer->obj.y;
	pBullet->obj.sprite = '*';

	pBullet->dir.X = 0;
	pBullet->dir.Y = -1;

	if (!nextBlankIdx())
	{
		PrintError("ÃÑ¾Ë °³¼ö ²ËÂü.\n");
		return false;
	}
	return true;
}

bool bullet_Shot(const Object* pObject, eBulletFlag flag)
{
	Bullet* pBullet = &g_Bullets[g_idxBlankBullet];

	pBullet->flag = flag;

	pBullet->obj.visible = true;
	pBullet->obj.x = pObject->x;
	pBullet->obj.y = pObject->y;
	pBullet->obj.sprite = '*';

	if (flag == eBulletFlag_EnemyShot)
	{
		pBullet->dir.X = 0;
		pBullet->dir.Y = 1;
	}
	else if (flag == eBulletFlag_PlayerShot)
	{
		pBullet->dir.X = 0;
		pBullet->dir.Y = -1;
	}

	if (!nextBlankIdx())
	{
		PrintError("ÃÑ¾Ë °³¼ö ²ËÂü.\n");
		return false;
	}
	return true;
}

void bullet_Clear()
{
	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		g_Bullets[i].obj.visible = false;
	}
}

void bullet_Update(DWORD frameCount, bool* out_bGameEnd)
{
	extern Game g_Game;

	Enemy* pEnemyList = g_Game.stage.enemyList;
	Player* pPlayer = &g_Game.stage.player;

	for (int iBullets = 0; iBullets < MAX_BULLETS; ++iBullets)
	{
		if (!g_Bullets[iBullets].obj.visible)
		{
			continue;
		}

		if (frameCount % 4 == 0)
		{
			g_Bullets[iBullets].obj.x += g_Bullets[iBullets].dir.X;
			g_Bullets[iBullets].obj.y += g_Bullets[iBullets].dir.Y;
		}

		if (g_Bullets[iBullets].flag == eBulletFlag_EnemyShot)
		{ 
			if (pPlayer->obj.x == g_Bullets[iBullets].obj.x &&
				pPlayer->obj.y == g_Bullets[iBullets].obj.y &&
				pPlayer->bHitted == false)
			{
				Assert(pPlayer->hp > 0, "hp ÀÌ»ó");

				--pPlayer->hp;
				if (pPlayer->hp == 0)
				{
					g_Game.scene = eScene_Lose;
					*out_bGameEnd = true;
					cs_ClearScreen();
					return;
				}
				else
				{
					pPlayer->bHitted = true;
				}

				g_Bullets[iBullets].obj.visible = false;
			}
		}
		if (g_Bullets[iBullets].flag == eBulletFlag_PlayerShot)
		{
			for (int iEnemies = 0; iEnemies < MAX_ENEMIES; ++iEnemies)
			{
				if (pEnemyList[iEnemies].obj.visible == false)
				{
					continue;
				}

				if (pEnemyList[iEnemies].obj.x == g_Bullets[iBullets].obj.x &&
					pEnemyList[iEnemies].obj.y == g_Bullets[iBullets].obj.y)
				{
					Assert(pEnemyList[iEnemies].hp > 0, "hp ÀÌ»ó");

					--pEnemyList[iEnemies].hp;
					if (pEnemyList[iEnemies].hp == 0)
					{
						--g_Game.stage.nEnemies;
						pEnemyList[iEnemies].obj.visible = false;
					}

					g_Bullets[iBullets].obj.visible = false;
					break;
				}
			}
		}

		if ((g_Bullets[iBullets].obj.x < 0 || g_Bullets[iBullets].obj.x >= SCREEN_WIDTH - 1) ||
			(g_Bullets[iBullets].obj.y < 0 || g_Bullets[iBullets].obj.y >= SCREEN_HEIGHT))
		{
			g_Bullets[iBullets].obj.visible = false;
		}		
	}
}