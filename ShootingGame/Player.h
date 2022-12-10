#pragma once

#include "Object.h"

struct Player
{
	Object obj;
	int hp;

	bool bHitted;            // �Ѿ� �¾Ҵ���
	DWORD invincibleFrames;  // ������ �ش� ������ ��ŭ ����

	COORD move;              // �̵� �ӵ� ���뵵 (move.X�� 2�� 1ĭ �����δٰų�)
	DWORD shot;				 // ���� �ӵ� ���뵵 (shot�� 4�� �Ǹ� 1�� ��ٰų�)
};

void player_Update(Player* pPlayer, DWORD frameCount)
;