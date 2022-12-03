#include "stdafx.h"

#include "Console.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Title.h"

char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

void Buffer_Flip(void);
void Buffer_Clear(void);
void Sprite_Draw(int iX, int iY, char chSprite);

int main(void)
{
	cs_Initial();
	if (!rm_LoadTitle())
	{
		return 1;
	}
	
	bool bGameLoop = true;
	while (bGameLoop)
	{
		extern eScene g_Scene;
		switch (g_Scene)
		{
		case eScene_Title:
			title_Update(&bGameLoop);
			break;

		case eScene_Load:
			rm_LoadResources();
			break;

		case eScene_Game:
			break;

		default:
			assert(0);
		}
	}

	rm_ReleaseResources();
	return 0;
}

void Buffer_Flip(void)
{
	int iCnt;
	for (iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++)
	{
		cs_MoveCursor(0, iCnt);
		printf(szScreenBuffer[iCnt]);
	}
}

void Buffer_Clear(void)
{
	int iCnt;
	memset(szScreenBuffer, ' ', dfSCREEN_WIDTH * dfSCREEN_HEIGHT);

	for (iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++)
	{
		szScreenBuffer[iCnt][dfSCREEN_WIDTH - 1] = '\0';
	}

}

void Sprite_Draw(int iX, int iY, char chSprite)
{
	if (iX < 0 || iY < 0 || iX >= dfSCREEN_WIDTH - 1 || iY >= dfSCREEN_HEIGHT)
		return;

	szScreenBuffer[iY][iX] = chSprite;
}




