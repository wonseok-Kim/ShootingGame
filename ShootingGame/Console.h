#pragma once

#define TEST_HEIGHT (24 + 1 + 2)

#define dfSCREEN_WIDTH		(81)		// ÄÜ¼Ö °¡·Î 80Ä­ + NULL
#define dfSCREEN_HEIGHT		(24)		// ÄÜ¼Ö ¼¼·Î 24Ä­

struct Console
{	
	int top = 1;
	int bottom = 2;
	char screenBuffer[TEST_HEIGHT][dfSCREEN_WIDTH];
};

void cs_Init(void);
void cs_MoveCursor(int iPosX, int iPosY);
void cs_ClearScreen(void);

void cs_FlipBuffer(void);
void cs_ClearBuffer(void);
void cs_DrawSprite(int iX, int iY, char chSprite);
void cs_AllClear();

void cs_SetTopInfoBuffer(const char* format, ...);

