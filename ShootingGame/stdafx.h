#pragma once

#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "Console.h"

#define PRINT_ERROR(msg, ...) do \
{ \
    fprintf(stderr, "FILE: %s\nFUNC: %s\nLINE: %d\nMSG: ", __FILE__, __FUNCTION__, __LINE__); \
    fprintf(stderr, msg, __VA_ARGS__); \
} while (false)
