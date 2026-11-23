#include "DoubleBuffering.h"
#include <Windows.h>
#include<string.h>

static int g_ScreenIndex = 0; // 출력할 종이 번호
static HANDLE g_hScreen[2]; // 종이 개수

void ScreenInit(Tile(*_BG)[DF_BG_SIZEX]) {
	

	DWORD dw = 0;
	COORD Pos = { 0,0 };

	unsigned short TempColor = _BG[0][0].Color;
	
	// null 문자용 +1
	char TempBG[(DF_BG_SIZEX * DF_BG_SIZEY) + 1] = {};

	int i = 0;
	for (int y = 0; y < DF_BG_SIZEY; ++y) {
		for (int x = 0; x < DF_BG_SIZEX; ++x) {
			TempBG[i++] = _BG[y][x].Text;

			Pos.X = x;
			Pos.Y = y;
			SetConsoleCursorPosition(g_hScreen[g_ScreenIndex],Pos);
			SetConsoleTextAttribute(g_hScreen[g_ScreenIndex], _BG[y][x].Color);
			WriteFile(g_hScreen[g_ScreenIndex], &_BG[y][x].Text, sizeof(char), &dw, NULL);
		}
	}
	
	if (i != 0) {
		TempBG[i++] = '\0';
		SetConsoleTextAttribute(g_hScreen[g_ScreenIndex], TempColor);
		SetConsoleCursorPosition(g_hScreen[g_ScreenIndex],Pos);
		WriteFile(g_hScreen[g_ScreenIndex], TempBG, strlen(TempBG), & dw, NULL);
	}
}

void ScreenPrint(Tile(*_BG)[DF_BG_SIZEX]) {
	g_hScreen[0] = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE, // bitFlag->비트롤 이용해서 option을 담음
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL
	);
	g_hScreen[0] = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE, // bitFlag->비트롤 이용해서 option을 담음
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL
	);

	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;

	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void ScreenClear() {
	DWORD dw = 0;
	FillConsoleOutputCharacter(
		g_hScreen[g_ScreenIndex], ' ',
		DF_BG_SIZEX * DF_BG_SIZEY,
		COORD(), &dw);
}

void ScreenFlipping() {
	SetConsoleActiveScreenBuffer(g_hScreen[g_ScreenIndex]);
	g_ScreenIndex = 1 - g_ScreenIndex;
}

void ScreenRelease() {
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}