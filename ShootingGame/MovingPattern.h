#pragma once

#define MAX_COORD_LIST_LENGTH (30)

struct MovingPattern
{
	COORD movingBy[MAX_COORD_LIST_LENGTH]; 
	int nLength;			// movingBy�� ��¥ ����
	int curIdx;
	int fpsInterval;		// fpsInterval��ŭ �������� ������ �̵�
};

bool mp_AddPattern(int interval, int nLength, COORD* coordList);

