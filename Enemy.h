#pragma once

#include "struct.h"

void EnemyInit();
void EnemyUpdate(ULONGLONG _Now);    // 생성 + 이동
void EnemyDraw(Tile(*_BG)[DF_BG_SIZEX]);
