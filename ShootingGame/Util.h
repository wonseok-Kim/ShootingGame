#pragma once

long util_GetFileSize(FILE* pFile);

bool util_ReadLineInFile(FILE* pFile, char* buffer, int bufferCount, size_t* outnRead);
