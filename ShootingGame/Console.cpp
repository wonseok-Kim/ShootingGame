#include "stdafx.h"
#include "Console.h"

#include <stdarg.h>

static Console s_Console;

void cs_Init(void)
{
	CONSOLE_CURSOR_INFO stConsoleCursor;
	stConsoleCursor.bVisible = FALSE;
	stConsoleCursor.dwSize = 1;
		
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &stConsoleCursor);

	cs_ClearBuffer();
}

void cs_MoveCursor(int iPosX, int iPosY)
{
	COORD stCoord;
	stCoord.X = iPosX;
	stCoord.Y = iPosY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), stCoord);
}

void cs_ClearScreen(void)
{
	DWORD dw;

	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 100 * 100, { 0, 0 }, &dw);
}

void cs_FlipBuffer(void)
{
	int iCnt;

	for (iCnt = 0; iCnt < TOTAL_HEIGHT; iCnt++)
	{
		cs_MoveCursor(0, iCnt);
		printf(s_Console.screenBuffer[iCnt]);
	}
}

void cs_ClearBuffer(void)
{
	int iCnt;
	memset(&s_Console.screenBuffer[1], ' ', SCREEN_WIDTH * SCREEN_HEIGHT);
		
	for (iCnt = 0; iCnt < SCREEN_HEIGHT; iCnt++)
	{
		s_Console.screenBuffer[iCnt + 1][SCREEN_WIDTH - 1] = '\0';
	}
}

void cs_DrawSprite(int iX, int iY, char chSprite)
{
	if (iX < 0 || iY < 0 || iX >= SCREEN_WIDTH - 1 || iY >= SCREEN_HEIGHT)
		return;
	
	s_Console.screenBuffer[iY + 1][iX] = chSprite;
}

void cs_SetTopInfoBuffer(const char* format, ...)
{
	va_list args;	
	va_start(args, format);
	int length = vsprintf_s(s_Console.screenBuffer[0], SCREEN_WIDTH, format, args);
	va_end(args);

	memset(&s_Console.screenBuffer[0][length], ' ', SCREEN_WIDTH - length);	
	s_Console.screenBuffer[0][SCREEN_WIDTH - 1] = '\0';
}

void cs_SetBottomInfoBuffer(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	int length = vsprintf_s(s_Console.screenBuffer[TOTAL_HEIGHT - 1], SCREEN_WIDTH, format, args);
	va_end(args);

	memset(&s_Console.screenBuffer[TOTAL_HEIGHT - 1][length], ' ', SCREEN_WIDTH - length);
	s_Console.screenBuffer[0][SCREEN_WIDTH - 1] = '\0';
}
