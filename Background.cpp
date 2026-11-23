#include "Background.h"
#include "Define.h"

void BGClear(Tile(*_BG)[DF_BG_SIZEX]) {
	for (int y = 0; y < DF_BG_SIZEY; ++y) {
		for (int x = 0; x < DF_BG_SIZEX; ++x) {
			_BG[y][x].Text = ' ';
			_BG[y][x].Color = COLOR_WHITE;
		}
	}
}

void BGSetTile(Tile(*_BG)[DF_BG_SIZEX], int _X, int _Y, char _Text, unsigned short _Color) {
	if (_X < 0 || _X >= DF_BG_SIZEX || _Y < 0 || _Y >= DF_BG_SIZEY) {
		return;
	}

	_BG[_Y][_X].Text = _Text;
	_BG[_Y][_X].Color = _Color;
}

void BGPrintText(Tile(*_BG)[DF_BG_SIZEX], int _X, int _Y, const char* _Text, unsigned short _Color) {
	for (int i = 0; _Text[i] != '\0'; ++i) {
		BGSetTile(_BG, _X + i, _Y, _Text[i], _Color);
	}
}

void BGDrawMap(Tile(*_BG)[DF_BG_SIZEX]) {
	for (int y = 0; y < DF_MAP_SIZEY; ++y) {
		for (int x = 0; x < DF_MAP_SIZEX; ++x) {
			bool IsBorder = (x == 0 || x == DF_MAP_SIZEX - 1 ||
			                 y == 0 || y == DF_MAP_SIZEY - 1);

			if (IsBorder) {
				BGSetTile(_BG, x, y, DF_WALL_TEXT, COLOR_GRAY);
			}
		}
	}
}
