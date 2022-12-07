#pragma once

struct Object
{
	bool visible;
	char sprite;
	int x;
	int y;
};

enum eObject
{
	eObject_Player,
	eObject_Enemy
};

void obj_Draw(const Object* obj);
