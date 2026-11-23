#include <stdio.h>
#include <stdlib.h>

#include "DoubleBuffering.h"
#include "struct.h"

static Tile BG[DF_BG_SIZEY][DF_BG_SIZEX];

void Start(void);
void Update(void);
void Draw(void);
void Render(void);

int main() {

	// 첫 호출 초기화
	Start();
	
	// 메인 게임 루프
	while (true) {
		Update();
		Draw();

		Render();
		
	}
	// 종료시 처리해야 할 것.
	ScreenRelease(); 
	return 0;
}

void Start(void) {
	system("mod con:cols=200 lines=50");
	return;
}

void Render() {
	BG[DF_BG_SIZEY - 1][DF_BG_SIZEX - 1].Text = '\0';

	ScreenClear();
	ScreenPrint(BG);
	ScreenFlipping();

}

void Draw(void) {
	BG[10][10].Text = 'T';
	return;
}
void Update(void) {

	return;
}