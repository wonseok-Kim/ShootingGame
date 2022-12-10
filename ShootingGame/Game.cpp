#include "stdafx.h"
#include "Game.h"

#include "Bullet.h"
#include "Console.h"
#include "Enemy.h"
#include "Player.h"

Game g_Game;

static DWORD s_TimeElapsed = 0;		  // 한 stage 당 시간 지남 보여주기
static DWORD s_OldTick = 0;
static DWORD s_FrameCountToPrint = 0; // 화면에 fps 출력용 

static void nextStage();

// ResourceLoader.cpp 에 정의
extern bool LoadResources();

bool gm_Init()
{
	srand((unsigned)time(nullptr));
	cs_Init();
	if (!LoadResources())
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

bool gm_Load()
{
	extern Stage g_Stages[];
	extern int g_nStages;

	if (g_Game.curStageIdx >= g_nStages)
	{
		PrintError("Invalid idx. curStageIdx: %d, g_nStages: %d\n", g_Game.curStageIdx, g_nStages);
		g_Game.bGameLoop = false;
		return false;
	}

	memcpy_s(&g_Game.stage, sizeof(Stage), &g_Stages[g_Game.curStageIdx], sizeof(Stage));

	cs_ClearScreen();
	bullet_Clear();
	g_Game.scene = eScene_Game;

	g_Game.gameTick = timeGetTime();
	s_OldTick = timeGetTime();
	return true;
}

void gm_Run()
{
	extern Bullet g_Bullets[MAX_BULLETS];

	Enemy* enemyList = g_Game.stage.enemyList;
	int nEnemies = g_Game.stage.nEnemies;
	Player* pPlayer = &g_Game.stage.player;

	bool bGameEnd = false;
	int i;

	++g_Game.frameCount;

	//  =======  //
	//   input   //
	//  =======  //
	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		--pPlayer->move.X;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		++pPlayer->move.X;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		--pPlayer->move.Y;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		++pPlayer->move.Y;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8001)
	{
		++pPlayer->shot;
	}

	// 강제 스테이지 클리어
	if (GetAsyncKeyState(VK_F1) & 0x0001)
	{
		nextStage();
	}

	// logic
	if (g_Game.stage.nEnemies == 0)
	{
		nextStage();
	}

	player_Update(pPlayer, g_Game.frameCount);
	enemy_Update(g_Game.frameCount);
	bullet_Update(g_Game.frameCount, &bGameEnd);

	if (bGameEnd)
	{
		return;
	}

	// render
	{
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
	}

	// 스크린 상단에 fps 출력	
	++s_FrameCountToPrint;
	DWORD nowTick = timeGetTime();
	s_TimeElapsed += nowTick - s_OldTick;
	s_OldTick = nowTick;
	if (s_TimeElapsed > 1000)
	{
		cs_SetTopInfoBuffer("%02d fps", s_FrameCountToPrint);
		s_TimeElapsed = 0;
		s_FrameCountToPrint = 0;
	}

	// 스크린 하단에 플레이어 정보 출력
	char hpBuffer[16] = { 0, };
	for (int i = 0; i < pPlayer->hp; ++i)
	{ 
		strcat_s(hpBuffer, 16, "♥");
	}
	cs_SetBottomInfoBuffer("HP: %s ", hpBuffer);


	// sleep	
	const DWORD MILLISECONDS_PER_FRAME = 20;	
	DWORD sleepTime = MILLISECONDS_PER_FRAME;

	nowTick = timeGetTime();
	if (nowTick > g_Game.gameTick)
	{
		DWORD diff = nowTick - g_Game.gameTick;
		if (diff > MILLISECONDS_PER_FRAME)
		{
			sleepTime = 0;
		}
		else
		{
			sleepTime = MILLISECONDS_PER_FRAME - diff;
		}
	}

	Sleep(sleepTime);
	g_Game.gameTick += 20;
}

static void nextStage()
{
	Assert(0 <= g_Game.curStageIdx && g_Game.curStageIdx < g_Game.nMaxStages,
		"stageIdx가 범위를 벗어남");

	++g_Game.curStageIdx;
	if (g_Game.curStageIdx == g_Game.nMaxStages)
	{		
		g_Game.scene = eScene_Win;
	}
	else
	{
		g_Game.scene = eScene_Load;
	}
}