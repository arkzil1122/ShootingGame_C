#pragma once
// [수정] 원래 이 자리에 있던 #include 한 줄을 지웠어요. 무엇을 include하고 있었는지 원본과 비교해 보세요.
#include <Windows.h>    // [추가] DWORD
#include "Define.h"

#define DF_BG_SIZEX 200
#define DF_BG_SIZEY 40

// 화면 한 칸
struct Tile {
	char Text;
	unsigned short Color;
};

struct Vector {
	float X;
	float Y;
};

struct Player {
	Vector pos;
	int Life;
	ULONGLONG LastFireTime;      // 마지막으로 총을 쏜 시각
	COLOR Color = COLOR_LIGHT_GREEN;
};

struct Bullet {
	Vector pos;
	Vector dir = DF_DIRECTION_RIGHT;
	bool IsActive;
};

struct Enemy {
	Vector pos;
	bool IsActive;
	ENEMY_TEXT Design;
	ULONGLONG LastMoveTime;
};