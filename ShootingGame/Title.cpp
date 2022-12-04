#include "stdafx.h"
#include "Title.h"

#include "Game.h"
#include "Scene.h"

Title g_Title;

void title_Input()
{
    if (GetAsyncKeyState('A') & 0x8001)
    {    
    }


}

void title_Update()
{
    extern Game g_Game;

    if (GetAsyncKeyState('A') & 0x8001)
    {
        // TODO: 나중에 수정하기 테스트할라고 Game으로 해둠.
        g_Game.scene = eScene_Game;
    }
    if (GetAsyncKeyState('B') & 0x8001)
    {
        g_Game.bGameLoop = false;
    }
    
    for (int i = 0; i < dfSCREEN_HEIGHT; ++i)
    {
        cs_MoveCursor(0, i);
        printf("%s", g_Title.screen[i]);
    }
}

void title_Render()
{

}
