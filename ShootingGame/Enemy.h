#pragma once

#include "Object.h"
#include "MovingPattern.h"

struct Enemy
{
	Object obj;
	int hp;
	MovingPattern movingPattern;
	int shotInterval; // fps ¥‹¿ß
};