#include "stdafx.h"
#include "Game.h"

#include "Bullet.h"
#include "Console.h"
#include "Enemy.h"
#include "Player.h"
#include "ResourceManager.h"

Game g_Game;

bool gm_Load()
{
	extern Stage g_Stages[];
	extern int g_nStages;

	if (g_Game.curStageIdx >= g_nStages)
	{
		PrintError("Invalid idx. curStageIdx: %d, g_nStages: %d\n", g_Game.curStageIdx, g_nStages);
		// TODO: 고민
		// g_Game.bGameLoop = false;
		return false;
	}

	memcpy_s(&g_Game.stage, sizeof(Stage), &g_Stages[g_Game.curStageIdx], sizeof(Stage));
	
	cs_AllClear();
	bullet_Clear();
	g_Game.scene = eScene_Game;

	g_Game.gameTick = timeGetTime();
	return true;
}

bool gm_Init()
{
	srand((unsigned) time(nullptr));	
	cs_Init();
	if (!rm_LoadResources())
	{
		return false;
	}

	g_Game.bGameLoop = true;
	g_Game.scene = eScene_Title;
	g_Game.fps = 50;
	g_Game.frameCount = 0;
	g_Game.curStageIdx = 0;
	g_Game.nMaxStages = stage_GetNumberOfStage();

	return true;
}

void gm_Run()
{
	static DWORD timeElapsed = 0;	
	static DWORD frameCount = 0;
	static DWORD oldTick = g_Game.gameTick;


	extern Bullet g_Bullets[MAX_BULLETS];

	Enemy* enemyList = g_Game.stage.enemyList;
	int nEnemies = g_Game.stage.nEnemies;
	Player* pPlayer = &g_Game.stage.player;

	COORD move = { 0, };
	bool bShot = false;
	int i;

	++frameCount;
	++g_Game.frameCount;

	// input
	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		--move.X;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		++move.X;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		--move.Y;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		++move.Y;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8001)
	{
		bShot = true;
	}
	if (GetAsyncKeyState(VK_F1) & 0x0001)
	{ 
		++g_Game.curStageIdx;
		g_Game.scene = eScene_Load;
		timeElapsed = 0;
	}

	// logic
	if (g_Game.stage.nEnemies == 0)
	{
		++g_Game.curStageIdx;
		if (g_Game.curStageIdx == g_Game.nMaxStages)
		{
			// TODO: 나중에 추가하기
			// g_Game.scene = eScene_Victory;
		}
		g_Game.scene = eScene_Load;		
		timeElapsed = 0;
	}

	player_Update(pPlayer, move, bShot);
	enemy_Update();
	bullet_Update();

	/*
	pPlayer->obj.x += move.X;
	pPlayer->obj.y += move.Y;

	if (bShot)
	{
		bullet_PlayerShot(pPlayer);
	}
	*/

	// render
	cs_ClearBuffer();

	for (i = 0; i < MAX_ENEMIES; ++i)
	{
		obj_Draw(&enemyList[i].obj);		
	}
	for (i = 0; i < MAX_BULLETS; ++i)
	{
		obj_Draw(&g_Bullets[i].obj);
	}
	obj_Draw(&pPlayer->obj);
	
	cs_FlipBuffer();


	DWORD nowTick = timeGetTime();
	DWORD sleepTime;

	timeElapsed += nowTick - oldTick;
	oldTick = nowTick;
	if (timeElapsed > 1000)
	{
		cs_SetTopInfoBuffer("%02d fps", frameCount);
		timeElapsed = 0;
		frameCount = 0;
	}

	if (nowTick - g_Game.gameTick < 20)
	{
		sleepTime = 20 - (nowTick - g_Game.gameTick);
		Sleep(sleepTime);
	}

	g_Game.gameTick += 20;
}

bool gm_Release()
{
	rm_ReleaseResources();


	return true;
}