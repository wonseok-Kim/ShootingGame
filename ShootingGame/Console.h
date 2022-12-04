#pragma once

#define dfSCREEN_WIDTH		(81)		// �ܼ� ���� 80ĭ + NULL
#define dfSCREEN_HEIGHT		(24)		// �ܼ� ���� 24ĭ

struct Console
{
	char screenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
};

void cs_Init(void);
void cs_MoveCursor(int iPosX, int iPosY);
void cs_ClearScreen(void);

void cs_FlipBuffer(void);
void cs_ClearBuffer(void);
void cs_DrawSprite(int iX, int iY, char chSprite);


