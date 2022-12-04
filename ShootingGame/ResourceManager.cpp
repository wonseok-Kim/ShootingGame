#include "stdafx.h"
#include "ResourceManager.h"

#include "Enemy.h"
#include "MovingPattern.h"
#include "Stage.h"
#include "Title.h"

static bool loadTitle();
static bool loadStageInfo();
static bool loadEnemyInfo();
static bool loadMovingPatternInfo();

bool rm_LoadResources()
{
	if (!loadTitle())
	{
		return false;
	}

	if (!loadMovingPatternInfo())
	{
		return false;
	}

	if (!loadEnemyInfo())
	{
		return false;
	}

	//if (!loadStageInfo())
	//{
	//	return false;
	//}

	return true;
}

bool rm_ReleaseResources()
{

	return false;
}

static bool loadTitle()
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
		PrintError("title file open err\n");
		return false;
	}

	char buffer[128];
	size_t length;
	int line = 0;

	while (!feof(pFile))
	{
		if (!util_ReadLineInFile(pFile, buffer, _countof(buffer), &length))
		{
			fclose(pFile);
			return false;
		}

		memcpy_s(g_Title.screen[line++], dfSCREEN_WIDTH, buffer, length);
	}

	fclose(pFile);
	return true;
}

bool loadStageInfo()
{
	FILE* pStageInfoFile;
	errno_t err = fopen_s(&pStageInfoFile, "res/StageInfo.txt", "r");
	if (err != 0)
	{
		PrintError("StageInfo.txt open err\n");
		return false;
	}

	char stageFileNames[MAX_STAGES][64];
	int nStages;
	int nRead = fscanf_s(pStageInfoFile, "%d", &nStages);
	if (nRead != 1)
	{
		PrintError("scanf StageInfo.txt error\n");
		fclose(pStageInfoFile);
		return false;
	}
	stage_SetNumberOfStage(nStages);

	for (int i = 0; i < nStages; ++i)
	{
		nRead = fscanf_s(pStageInfoFile, "%s", stageFileNames[i], (unsigned)_countof(stageFileNames[i]));
		if (nRead != 1)
		{
			PrintError("scanf StageInfo.txt error\n");
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
			PrintError("%s file scan error\n", stageFileNames[i]);
			return false;
		}

		char buffer[128];
		size_t length;
		int x;
		int y = 0;

		while (!feof(pStageFile))
		{
			if (!util_ReadLineInFile(pStageFile, buffer, 128, &length))
			{
				fclose(pStageFile);
				return false;
			}

			for (x = 0; x < length; ++x)
			{
				if ('A' <= buffer[x] && buffer[x] <= 'Z')
				{
					stage_AddEnemy(i, x, y, buffer[x], 'A' - buffer[x]);
				}
			}
			++y;
		}

		fclose(pStageFile);
	}

	return true;
}

bool loadEnemyInfo()
{
	char enemyFilenames[MAX_ENEMY_INFOS][64];
	FILE* pFile;
	errno_t err;
	int nRead;
	int nEnemyFiles;
	int i;

	// ========================= //
	// read EnemyInfo file       //
	// ========================= //
	{
		const char* filename = "res/Enemy/EnemyInfo.txt";

		err = fopen_s(&pFile, filename, "r");
		if (err != 0)
		{
			PrintError("%s fopen err", filename);
			return false;
		}

		nRead = fscanf_s(pFile, "%d", &nEnemyFiles);
		if (nRead != 1)
		{
			PrintError("%s fscanf err\n", filename);
			fclose(pFile);
			return false;
		}

		for (i = 0; i < nEnemyFiles; ++i)
		{
			nRead = fscanf_s(pFile, "%s", enemyFilenames[i],
				(unsigned)_countof(enemyFilenames[i]));
			if (nRead != 1)
			{
				PrintError("%s fscanf err\n", filename);
				fclose(pFile);
				return false;
			}
		}

		fclose(pFile);
	}

	int hp;
	int movingPatternIdx;
	int shotInterval;	

	// ============================ //
	// read each movepattern files  //
	// ============================ //
	for (i = 0; i < nEnemyFiles; ++i)
	{
		err = fopen_s(&pFile, enemyFilenames[i], "r");
		if (err != 0)
		{
			PrintError("%s file fopen err\n", enemyFilenames[i]);
			return false;
		}

		nRead = fscanf_s(pFile, "%d %d %d", &hp, &movingPatternIdx, &shotInterval);
		if (nRead != 3)
		{
			PrintError("%s file scanf err", enemyFilenames[i]);
			return false;
		}

		enemy_AddInfo(hp, movingPatternIdx, shotInterval);
		fclose(pFile);
	}

	return true;
}

bool loadMovingPatternInfo()
{
	char patternFilenames[MAX_MOVING_PATTERNS][64];
	FILE* pFile;
	errno_t err;
	int nRead;
	int nPatternFiles;
	int i;

	// ========================= //
	// read movepatterinfo file  //
	// ========================= //
	{
		const char* filename = "res/Pattern/MovePatternInfo.txt";

		err = fopen_s(&pFile, filename, "r");
		if (err != 0)
		{
			PrintError("%s fopen err", filename);
			return false;
		}

		nRead = fscanf_s(pFile, "%d", &nPatternFiles);
		if (nRead != 1)
		{
			PrintError("%s fscanf err\n", filename);
			fclose(pFile);
			return false;
		}

		for (i = 0; i < nPatternFiles; ++i)
		{
			nRead = fscanf_s(pFile, "%s", patternFilenames[i],
				(unsigned)_countof(patternFilenames[i]));
			if (nRead != 1)
			{
				PrintError("%s fscanf err\n", filename);
				fclose(pFile);
				return false;
			}
		}

		fclose(pFile);
	}

	int fpsInterval;
	int nLength;
	COORD coordList[MAX_COORD_LIST_LENGTH];
	
	// ============================ //
	// read each movepattern files  //
	// ============================ //
	for (int i = 0; i < nPatternFiles; ++i)
	{
		err = fopen_s(&pFile, patternFilenames[i], "r");
		if (err != 0)
		{
			PrintError("%s file fopen err\n", patternFilenames[i]);
			return false;
		}

		nRead = fscanf_s(pFile, "%d, %d", &fpsInterval, &nLength);
		if (nRead != 2)
		{
			PrintError("%s file fscanf err\n", patternFilenames[i]);
			fclose(pFile);
			return false;
		}

		for (int i = 0; i < nLength; ++i)
		{
			nRead = fscanf_s(pFile, "%hd, %hd", &coordList[i].X, &coordList[i].Y);
			if (nRead != 2)
			{
				PrintError("%s file fscanf err\n", patternFilenames[i]);
				fclose(pFile);
				return false;
			}
		}

		mp_AddPattern(fpsInterval, nLength, coordList);

		fclose(pFile);
	}

	return true;
}



