#include "DoubleBuffering.h"
#include <Windows.h>

static int g_ScreenIndex = 0; 
static HANDLE g_hScreen[2];


static CHAR_INFO g_Cells[DF_BG_SIZEY * DF_BG_SIZEX];


void ScreenInit() {
	for (int i = 0; i < 2; ++i) {   
		g_hScreen[i] = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE, 
			0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL
		);


		COORD BufferSize = { DF_BG_SIZEX, DF_BG_SIZEY + 1 };
		SetConsoleScreenBufferSize(g_hScreen[i], BufferSize);
	}

	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;

	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void ScreenPrint(Tile(*_BG)[DF_BG_SIZEX]) {
	int i = 0;
	for (int y = 0; y < DF_BG_SIZEY; ++y) {
		for (int x = 0; x < DF_BG_SIZEX; ++x) {
			g_Cells[i].Char.UnicodeChar = 0;           
			g_Cells[i].Char.AsciiChar = _BG[y][x].Text;
			g_Cells[i].Attributes = _BG[y][x].Color;
			++i;
		}
	}

	COORD Size = { DF_BG_SIZEX, DF_BG_SIZEY };   
	COORD Start = { 0, 0 };                       
	SMALL_RECT Area = { 0, 0, DF_BG_SIZEX - 1, DF_BG_SIZEY - 1 };

	WriteConsoleOutputA(g_hScreen[g_ScreenIndex], g_Cells, Size, Start, &Area);
}

void ScreenClear() {
	DWORD dw = 0;
	COORD Pos = { 0, 0 };
	FillConsoleOutputCharacterA(
		g_hScreen[g_ScreenIndex], ' ',
		DF_BG_SIZEX * DF_BG_SIZEY,
		Pos, &dw);
}

void ScreenFlipping() {
	SetConsoleActiveScreenBuffer(g_hScreen[g_ScreenIndex]);
	g_ScreenIndex = 1 - g_ScreenIndex;
}

void ScreenRelease() {
	// TODO 종료 화면 만들기.
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}
