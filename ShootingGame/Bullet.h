#pragma once

#include "Object.h"

#define MAX_BULLETS (100)

enum eBulletFlag
{
	eBulletFlag_PlayerShot,
	eBulletFlag_EnemyShot
};

struct Bullet
{
	Object obj;
	eBulletFlag flag;
	COORD dir;
};

struct Enemy;
struct Player;

bool bullet_EnemyShot(const Enemy* pEnemy);
bool bullet_PlayerShot(const Player* pPlayer);
bool bullet_Shot(const Object* pObject, eBulletFlag flag);

void bullet_Clear();
void bullet_Update();