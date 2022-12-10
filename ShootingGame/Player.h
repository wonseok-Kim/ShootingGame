#pragma once

#include "Object.h"

struct Player
{
	Object obj;
	int hp;

	bool bHitted;            // 총알 맞았는지
	DWORD invincibleFrames;  // 맞으면 해당 프레임 만큼 무적

	COORD move;              // 이동 속도 계산용도 (move.X가 2면 1칸 움직인다거나)
	DWORD shot;				 // 슈팅 속도 계산용도 (shot이 4가 되면 1번 쏜다거나)
};

void player_Update(Player* pPlayer, DWORD frameCount)
;