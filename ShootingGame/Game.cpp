#include "stdafx.h"
#include "Game.h"

#include "Console.h"
#include "ResourceManager.h"

Game g_Game;

bool gm_Load()
{
	extern Stage g_Stages[];
	extern int g_nStages;

	if (g_Game.curStageIdx >= g_nStages)
	{
		PrintError("Invalid idx. curStageIdx: %d, g_nStages: %d\n", g_Game.curStageIdx, g_nStages);
		// TODO: °í¹Î
		// g_Game.bGameLoop = false;
		return false;
	}

	memcpy_s(&g_Game.stage, sizeof(Stage), &g_Stages[g_Game.curStageIdx], sizeof(Stage));

	g_Game.scene = eScene_Game;
	return true;
}

bool gm_Init()
{
	cs_Init();
	if (!rm_LoadResources())
	{
		return false;
	}

	g_Game.bGameLoop = true;
	g_Game.scene = eScene_Title;
	g_Game.curStageIdx = 0;

	return true;
}

void gm_Run()
{
	Enemy* enemyList = g_Game.stage.enemyList;
	int nEnemies = g_Game.stage.nEnemies;
	Player* pPlayer = &g_Game.stage.player;

	int xMove = 0;
	int yMove = 0;

	// input
	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		--xMove;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		++xMove;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		--yMove;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		++yMove;
	}

	// logic
	pPlayer->obj.x += xMove;
	pPlayer->obj.y += yMove;

	

	// render
	cs_ClearBuffer();

	for (int i = 0; i < nEnemies; ++i)
	{
		obj_Draw(&enemyList[i].obj);		
	}
	obj_Draw(&pPlayer->obj);
	
	cs_FlipBuffer();

	Sleep(50);
}

bool gm_Release()
{
	rm_ReleaseResources();


	return true;
}