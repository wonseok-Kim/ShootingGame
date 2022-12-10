#pragma once

#define SCREEN_WIDTH		(81)		// �ܼ� ���� 80ĭ + NULL
#define SCREEN_HEIGHT		(24)		// �ܼ� ���� 24ĭ
#define TOTAL_HEIGHT        (24 + 2)	// ���Ͽ� ��Ÿ ������ ��� �뵵

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


