#pragma once

#define MAX_COORD_LIST_LENGTH (65)

struct MovingPattern
{
	COORD movingBy[MAX_COORD_LIST_LENGTH]; 
	int nLength;			// movingBy의 진짜 길이	
	int fpsInterval;		// fpsInterval만큼 프레임이 지나면 이동
};

bool mp_AddPattern(int interval, int nLength, COORD* coordList);

