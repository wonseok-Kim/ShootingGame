#pragma once

struct Object
{
	bool visible;
	char sprite;
	int x;
	int y;
};

void obj_Draw(const Object* obj);
