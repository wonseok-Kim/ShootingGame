#include "stdafx.h"
#include "Object.h"

void obj_Draw(const Object* obj)
{
	cs_DrawSprite(obj->x, obj->y, obj->sprite);
}