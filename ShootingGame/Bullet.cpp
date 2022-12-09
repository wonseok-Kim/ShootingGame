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
	Bullet* pBullet = &g_Bullets[g_idxBlankBullet];

	pBullet->flag = eBulletFlag_EnemyShot;	

	pBullet->obj.visible = true;
	pBullet->obj.x = pEnemy->obj.x;
	pBullet->obj.y = pEnemy->obj.y;
	pBullet->obj.sprite = '*';

	pBullet->dir.X = 0;
	pBullet->dir.Y = 1;

	if (!nextBlankIdx())
	{
		PrintError("ÃÑ¾Ë °³¼ö ²ËÂü.\n");
		return false;
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

void bullet_Update()
{
	static DWORD frameCount = 0;

	extern Game g_Game;

	Enemy* pEnemyList = g_Game.stage.enemyList;
	Player* pPlayer = &g_Game.stage.player;

	++frameCount;

	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		if (!g_Bullets[i].obj.visible)
		{
			continue;
		}

		if (frameCount % 2 == 0)
		{
			g_Bullets[i].obj.x += g_Bullets[i].dir.X;
			g_Bullets[i].obj.y += g_Bullets[i].dir.Y;
		}

		if (g_Bullets[i].flag == eBulletFlag_EnemyShot)
		{ 
			if (pPlayer->obj.x == g_Bullets[i].obj.x &&
				pPlayer->obj.y == g_Bullets[i].obj.y)
			{
				Assert(pPlayer->hp > 0, "hp ÀÌ»ó");

				--pPlayer->hp;
				if (pPlayer->hp == 0)
				{
					// TODO: ÆÐ¹è Ã³¸®
					g_Game.scene = eScene_Title;
				}

				g_Bullets[i].obj.visible = false;
			}
		}
		if (g_Bullets[i].flag == eBulletFlag_PlayerShot)
		{
			for (int j = 0; j < MAX_ENEMIES; ++j)
			{
				if (pEnemyList[j].obj.visible == false)
				{
					continue;
				}

				if (pEnemyList[j].obj.x == g_Bullets[i].obj.x &&
					pEnemyList[j].obj.y == g_Bullets[i].obj.y)
				{
					Assert(pEnemyList[j].hp > 0, "hp ÀÌ»ó");

					--pEnemyList[j].hp;
					if (pEnemyList[j].hp == 0)
					{
						--g_Game.stage.nEnemies;
						pEnemyList[j].obj.visible = false;
					}

					g_Bullets[j].obj.visible = false;
				}
			}
		}

		if ((g_Bullets[i].obj.x < 0 || g_Bullets[i].obj.x >= dfSCREEN_WIDTH - 1) ||
			(g_Bullets[i].obj.y < 0 || g_Bullets[i].obj.y >= dfSCREEN_HEIGHT))
		{
			g_Bullets[i].obj.visible = false;
		}		
	}
}