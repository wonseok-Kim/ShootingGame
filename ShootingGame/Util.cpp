#include "stdafx.h"
#include "Util.h"

long util_GetFileSize(FILE* pFile)
{
	Assert(pFile, "pFile must not be null");

	long curPos = ftell(pFile);

	fseek(pFile, 0, SEEK_END);
	long endPos = ftell(pFile);

	fseek(pFile, curPos, SEEK_SET);

	return endPos;
}

bool util_ReadLineInFile(FILE* pFile, char* buffer, int bufferCount, size_t* out_nRead)
{
	if (!fgets(buffer, bufferCount, pFile))
	{
		PrintError("fgets error\n");
		DebugBreak();
		return false;
	}

	char* pNewLine = strchr(buffer, '\n');
	if (pNewLine)
	{
		*pNewLine = '\0';
	}

	*out_nRead = strlen(buffer);
	if (*out_nRead > SCREEN_WIDTH - 1)
	{
		PrintError("dfSCREEN_WIDTH 범위를 넘어선 표현\n");
		return false;
	}

	return true;
}


// [min, max] 랜덤 값 반환
int util_randInt(int min, int max)
{
	float random = (float)rand() / RAND_MAX;

	return min + (int)(random * (max - min));
}
