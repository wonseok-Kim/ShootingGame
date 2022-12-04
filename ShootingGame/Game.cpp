#include "stdafx.h"
#include "Game.h"

#include "Console.h"
#include "ResourceManager.h"

Game g_Game;

bool gm_Init()
{
    cs_Init();
    if (!rm_LoadResources())
    {
        return false;
    }

    g_Game.bGameLoop = true;
    g_Game.scene = eScene_Title;
    g_Game.curStageIdx = 0;    

    return true;
}

void gm_Run()
{
    constexpr DWORD FRAME_PER_SEC = 50;
    constexpr DWORD MILLI_SEC_PER_FRAME  = 1000 / 50;

    static DWORD frameCount = 0;
    static DWORD timeElapsed = 0;
    static DWORD timer_1sec = 0;
    static DWORD lastTime = timeGetTime();

    DWORD curTime = timeGetTime();
    DWORD deltaTime = curTime - lastTime;
    lastTime = curTime;
      
    timeElapsed += deltaTime;
    timer_1sec += deltaTime;    

    ++frameCount;

    if (timer_1sec > 1000)
    {
        printf("\n%d\n", timeElapsed);
        printf("%d\n", frameCount);
        printf("%f\n", frameCount / (timeElapsed * 0.001f));

        timer_1sec = 0;
    }
    
    // Input
    // Logic
    // Render    

   

    Sleep(MILLI_SEC_PER_FRAME - (timeGetTime() - curTime));    
}

bool gm_Release()
{
    rm_ReleaseResources();


    return true;
}