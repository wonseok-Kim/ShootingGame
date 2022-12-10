#pragma once

#define SCREEN_WIDTH		(81)		// 콘솔 가로 80칸 + NULL
#define SCREEN_HEIGHT		(24)		// 콘솔 세로 24칸
#define TOTAL_HEIGHT        (24 + 2)	// 상하에 기타 정보들 출력 용도

struct Console
{	
	char screenBuffer[TOTAL_HEIGHT][SCREEN_WIDTH];
};

void cs_Init(void);
void cs_MoveCursor(int iPosX, int iPosY);
void cs_ClearScreen(void);

void cs_FlipBuffer(void);
void cs_ClearBuffer(void);
void cs_DrawSprite(int iX, int iY, char chSprite);

void cs_SetTopInfoBuffer(const char* format, ...);
void cs_SetBottomInfoBuffer(const char* format, ...);


