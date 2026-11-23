#pragma once

#include "struct.h"

void ScreenInit(Tile(*_BG)[DF_BG_SIZEX]);
void ScreenPrint(Tile(*_BG)[DF_BG_SIZEX]);
void ScreenClear();
void ScreenFlipping();
void ScreenRelease();