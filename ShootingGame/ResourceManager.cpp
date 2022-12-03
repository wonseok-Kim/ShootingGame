#include "stdafx.h"
#include "ResourceManager.h"
#include "Title.h"

bool rm_LoadTitle()
{
	extern Title g_Title;

	memset(g_Title.screen, ' ', sizeof(g_Title.screen));
	for (int i = 0; i < dfSCREEN_HEIGHT; ++i)
	{
		g_Title.screen[i][dfSCREEN_WIDTH - 1] = '\0';
	}

	FILE* pFile;
	errno_t err = fopen_s(&pFile, "res/TitleScreen.txt", "r");
	if (err != 0)
	{
		PRINT_ERROR("title file open err");
		return false;
	}

	char buffer[128];
	int line = 0;

	while (!feof(pFile))
	{
		fgets(buffer, 128, pFile);

		char* pNewLine = strchr(buffer, '\n');
		if (pNewLine)
		{
			*pNewLine = '\0';
		}

		size_t length = strlen(buffer);
		if (length > dfSCREEN_WIDTH - 1)
		{
			PRINT_ERROR("dfSCREEN_WIDTH 범위를 넘어선 표현");
			fclose(pFile);
			return false;
		}

		memcpy_s(g_Title.screen[line++], dfSCREEN_WIDTH, buffer, length);
	}

	fclose(pFile);
	return true;
}

#define MAX_STAGES 20

bool rm_LoadResources()
{	
	FILE* pStageInfoFile;
	errno_t err = fopen_s(&pStageInfoFile, "res/StageInfo.txt", "r");
	if (err != 0)
	{
		PRINT_ERROR("StageInfo.txt open err");
		return false;
	}

	char stageFileNames[MAX_STAGES][64];
	int nStages;
	int nRead = fscanf_s(pStageInfoFile, "%d", &nStages);
	if (nRead != 1)
	{
		PRINT_ERROR("scanf StageInfo.txt error");
		fclose(pStageInfoFile);
		return false;
	}
		
	for (int i = 0; i < nStages; ++i)
	{
		nRead = fscanf_s(pStageInfoFile, "%s", stageFileNames[i], (unsigned)_countof(stageFileNames[i]));
		if (nRead != 1)
		{
			PRINT_ERROR("scanf StageInfo.txt error");
			fclose(pStageInfoFile);
			return false;
		}
	}

	fclose(pStageInfoFile);

	for (int i = 0; i < nStages; ++i)
	{
		FILE* pStageFile;
		err = fopen_s(&pStageFile, stageFileNames[i], "r");
		if (err != 0)
		{
			PRINT_ERROR("%s file scan error", stageFileNames[i]);
			return false;
		}		


	}
		
	return true;
}

bool rm_ReleaseResources()
{

	return false;
}



