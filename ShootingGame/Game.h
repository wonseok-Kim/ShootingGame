#pragma once

#include "Scene.h"
#include "Stage.h"

struct Game
{
	bool bGameLoop;
	eScene scene;
	DWORD fps;
	DWORD frameCount;  // 
	DWORD gameTick;    // 게임 플레이 기준이 되는 tick
	Stage stage;
	int curStageIdx;
	int nMaxStages;
};

bool gm_Init();
bool gm_Load();
void gm_Run();
