#include "stdafx.h"

#include "Game.h"
#include "Screen.h"

#pragma comment(lib, "winmm")

extern

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
			titleScreen_Update();
			break;

		case eScene_Win:
			winScreen_Update();
			break;

		case eScene_Lose:
			loseScreen_Update();
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
	
	return 0;
}





