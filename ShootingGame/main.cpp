
#include "stdafx.h"

#include "Game.h"
#include "Title.h"

#pragma comment(lib, "winmm")

int main(void)
{
	extern Game g_Game;

	if (!gm_Init())
	{
		return 1;
	}

	timeBeginPeriod(1);

	while (g_Game.bGameLoop)
	{
		switch (g_Game.scene)
		{
		case eScene_Title:
			title_Update();
			break;

		case eScene_Load:
			gm_Load();
			break;

		case eScene_Game:
			gm_Run();
			break;

		default:
			Assert(0, "not reachable");
		}
	}

	timeEndPeriod(1);

	gm_Release();
	
	return 0;
}





