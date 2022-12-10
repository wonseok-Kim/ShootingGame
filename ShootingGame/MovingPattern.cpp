#include "stdafx.h"
#include "MovingPattern.h"

MovingPattern g_MovingPatterns[MAX_MOVING_PATTERNS];
int g_nMovingPatterns = 0;

bool mp_AddPattern(int interval, int nLength, COORD* coordList)
{
	if (g_nMovingPatterns >= MAX_MOVING_PATTERNS)
	{
		PrintError("무빙패턴 저장공간 초과");
		return false;
	}
	if (nLength >= MAX_COORD_LIST_LENGTH)
	{
		PrintError("상대좌표 저장공간 초과");
		return false;
	}

	g_MovingPatterns[g_nMovingPatterns].fpsInterval = interval;
	g_MovingPatterns[g_nMovingPatterns].nLength = nLength;

	for (int i = 0; i < nLength; ++i)
	{
		g_MovingPatterns[g_nMovingPatterns].movingBy[i] = coordList[i];
	}

	++g_nMovingPatterns;

	return true;
}