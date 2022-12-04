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
	do
	{
		if (!fgets(buffer, bufferCount, pFile))
		{
			PrintError("fgets error\n");
			DebugBreak();
			return false;
		}
	} while (strncmp(buffer, "//", 2) == 0);

	char* pNewLine = strchr(buffer, '\n');
	if (pNewLine)
	{
		*pNewLine = '\0';
	}

	char* comment = strstr(buffer, "//");
	if (comment)
	{
		*comment = '\0';
	}

	*out_nRead = strlen(buffer);
	if (*out_nRead > dfSCREEN_WIDTH - 1)
	{
		PrintError("dfSCREEN_WIDTH 범위를 넘어선 표현\n");		
		return false;
	}

	return true;
}
