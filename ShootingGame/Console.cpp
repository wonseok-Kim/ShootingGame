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

	for (iCnt = 0; iCnt < TEST_HEIGHT; iCnt++)
	{
		cs_MoveCursor(0, iCnt);
		printf(s_Console.screenBuffer[iCnt]);
	}
}

void cs_ClearBuffer(void)
{
	int iCnt;
	memset(&s_Console.screenBuffer[s_Console.top], ' ', dfSCREEN_WIDTH * dfSCREEN_HEIGHT);
		
	for (iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++)
	{
		s_Console.screenBuffer[iCnt + s_Console.top][dfSCREEN_WIDTH - 1] = '\0';
	}

}

void cs_AllClear()
{
	int iCnt;
	memset(s_Console.screenBuffer, ' ', dfSCREEN_WIDTH * TEST_HEIGHT);

	for (iCnt = 0; iCnt < TEST_HEIGHT; iCnt++)
	{
		s_Console.screenBuffer[iCnt][dfSCREEN_WIDTH - 1] = '\0';
	}
}

void cs_DrawSprite(int iX, int iY, char chSprite)
{
	if (iX < 0 || iY < 0 || iX >= dfSCREEN_WIDTH - 1 || iY >= dfSCREEN_HEIGHT)
		return;
	
	s_Console.screenBuffer[iY + s_Console.top][iX] = chSprite;
}

void cs_SetTopInfoBuffer(const char* format, ...)
{
	memset(s_Console.screenBuffer[0], ' ', dfSCREEN_WIDTH);
	s_Console.screenBuffer[0][dfSCREEN_WIDTH - 1] = '\0';

	va_list args;	
	va_start(args, format);
	vsprintf_s(s_Console.screenBuffer[0], dfSCREEN_WIDTH, format, args);
	va_end(args);
}
