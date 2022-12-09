#pragma once

#include "Scene.h"
#include "Stage.h"

struct Game
{
	bool bGameLoop;
	eScene scene;
	DWORD fps;
	DWORD frameCount;
	DWORD gameTick;
	Stage stage;
	int curStageIdx;
	int nMaxStages;
};

bool gm_Load();

bool gm_Init();
void gm_Run();
bool gm_Release();
