#pragma once
// [추가] ======================================================
// Background.h
// BG(Tile 격자)에 그림을 그리는 도우미 함수들.
// 화면에 직접 찍는 게 아니라 "BG 배열 값만 바꾼다" → 실제 출력은 ScreenPrint.
// ============================================================
#include "struct.h"

void BGClear(Tile(*_BG)[DF_BG_SIZEX]);                                         // 전체를 공백 + 기본색으로
void BGSetTile(Tile(*_BG)[DF_BG_SIZEX], int _X, int _Y, char _Text, unsigned short _Color); // 한 칸
void BGPrintText(Tile(*_BG)[DF_BG_SIZEX], int _X, int _Y, const char* _Text, unsigned short _Color); // 문자열
void BGDrawMap(Tile(*_BG)[DF_BG_SIZEX]);                                       // 게임판 테두리
