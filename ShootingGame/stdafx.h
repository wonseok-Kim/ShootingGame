#pragma once

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "Console.h"

#define LOG(msg)	fprintf(stderr, "FILE: %s \n FUNC: %s \n LINE: %d \n MSG: %s \n", __FILE__, __FUNCTION__, __LINE__, msg)