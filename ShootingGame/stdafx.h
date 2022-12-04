#pragma once

#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "Console.h"
#include "Util.h"

#define MAX_STAGES 20
#define MAX_ENEMIES 50
#define MAX_MOVING_PATTERNS 20

#define PrintError(msg, ...) do \
{ \
    fprintf(stderr, "FILE: %s\nFUNC: %s\nLINE: %d\nMSG: ", __FILE__, __FUNCTION__, __LINE__); \
    fprintf(stderr, msg, __VA_ARGS__); \
} while (false)

#ifdef _DEBUG

#define Assert(expr, msg) do \
{ \
    if (!(expr)) \
    { \
        printf(msg); \
        assert(expr); \
    } \
} while (false)

#else

#define Assert(expr, msg) ((void)0)

#endif // _DEBUG