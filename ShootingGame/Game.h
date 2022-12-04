#pragma once

#include "Scene.h"
#include "Stage.h"

struct Game
{
	bool bGameLoop;
	eScene scene;
	int curStageIdx;
	Stage stage;
};

bool gm_Init();
void gm_Run();
bool gm_Release();
