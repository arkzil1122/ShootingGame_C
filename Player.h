#pragma once
#include "struct.h"

void PlayerInit();
void PlayerUpdate(ULONGLONG _Now);
void PlayerDraw(Tile(*_BG)[DF_BG_SIZEX]);
