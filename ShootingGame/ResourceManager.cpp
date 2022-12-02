#include "stdafx.h"
#include "ResourceManager.h"
#include "Title.h"

static Title s_Title;

static bool loadTitle();
static bool releaseTitle();

bool rm_LoadResources() 
{
	loadTitle();

	return true;
}

bool rm_ReleaseResources()
{
	releaseTitle();

	return false;
}

Title* rm_GetTitle()
{
	return &s_Title;
}

static bool loadTitle() 
{
	const char* filename = "TitleScreen.txt";

	FILE* pFile;
	errno_t err = fopen_s(&pFile, filename, "r");
	if (err != 0) 
	{
		LOG("title file open err");
		return false;
	}

	char buffer[128];
	fgets(buffer, 128, pFile);

	char* pNewLine = strchr(buffer, '\n');
	if (pNewLine) 
	{
		*pNewLine = '\0';
	}

	s_Title.nMenus = atoi(buffer);
	s_Title.pMenuCoordList = (COORD*)malloc(sizeof(COORD) * s_Title.nMenus);

	memset(s_Title.screen, '\0', sizeof(s_Title.screen));

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
			LOG("dfSCREEN_WIDTH 범위를 넘어선 표현");
			fclose(pFile);
			return false;
		}	

		strcpy_s(s_Title.screen[line++], dfSCREEN_WIDTH, buffer);
	}

}

static bool releaseTitle()
{
	free(s_Title.pMenuCoordList);

	return true;
}

