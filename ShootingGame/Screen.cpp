#include "stdafx.h"
#include "Screen.h"

#include "Game.h"
#include "Scene.h"

char g_TitleScreen[SCREEN_HEIGHT][SCREEN_WIDTH];
char g_LoseScreen[SCREEN_HEIGHT][SCREEN_WIDTH];
char g_WinScreen[SCREEN_HEIGHT][SCREEN_WIDTH];

void titleScreen_Update()
{
    extern Game g_Game;

    if (GetAsyncKeyState('A') & 0x0001)
    {        
        g_Game.scene = eScene_Load;
        g_Game.curStageIdx = 0;
    }
    if (GetAsyncKeyState('B') & 0x0001)
    {
        g_Game.bGameLoop = false;
    }
    
    for (int i = 0; i < SCREEN_HEIGHT; ++i)
    {
        cs_MoveCursor(0, i);
        printf("%s", g_TitleScreen[i]);
    }
}

void loseScreen_Update()
{
    extern Game g_Game;

    if (GetAsyncKeyState('A') & 0x0001)
    {
        g_Game.scene = eScene_Load;        
    }
    if (GetAsyncKeyState('B') & 0x0001)
    {
        g_Game.scene = eScene_Title;
    }

    for (int i = 0; i < SCREEN_HEIGHT; ++i)
    {
        cs_MoveCursor(0, i);
        printf("%s", g_LoseScreen[i]);
    }
}

void winScreen_Update()
{
    extern Game g_Game;

    if (GetAsyncKeyState('A') & 0x0001)
    {
        g_Game.scene = eScene_Title;
    }
    if (GetAsyncKeyState('B') & 0x0001)
    {
        g_Game.bGameLoop = false;
    }

    for (int i = 0; i < SCREEN_HEIGHT; ++i)
    {
        cs_MoveCursor(0, i);
        printf("%s", g_WinScreen[i]);
    }
}