#include "stdafx.h"
#include "Scene.h"
#include "Title.h"

Title g_Title;

void title_Input()
{
    extern eScene g_Scene;

    if (GetAsyncKeyState('A') & 0x8001)
    {    
    }


}

void title_Update(bool* out_bGameLoop)
{
    extern eScene g_Scene;

    if (GetAsyncKeyState('A') & 0x8001)
    {
        g_Scene = eScene_Load;
    }
    if (GetAsyncKeyState('B') & 0x8001)
    {
        *out_bGameLoop = false;
    }
    
    for (int i = 0; i < dfSCREEN_HEIGHT; ++i)
    {
        cs_MoveCursor(0, i);
        printf("%s", g_Title.screen[i]);
    }
}

void title_Render()
{}
