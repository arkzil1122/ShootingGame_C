#pragma once
// [추가] ======================================================
// Player.h
// 방향키 1번 = 1칸 이동, 스페이스바 = 발사 (총알은 오른쪽으로).
// 여러 칸짜리 모양: Define.h의 DF_PLAYER_SHAPE
// ============================================================
#include "struct.h"

void PlayerInit();
void PlayerUpdate(int _PressKey, ULONGLONG _Now);
void PlayerDraw(Tile(*_BG)[DF_BG_SIZEX]);
