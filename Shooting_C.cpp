#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "DoubleBuffering.h"
#include "struct.h"
#include "Define.h"
#include "Global.h"
#include "Background.h"
#include "Input.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "TimeManager.h"
#include "Collide.h"

static Tile BG[DF_BG_SIZEY][DF_BG_SIZEX];

void Start(void);
void Update(void);
void Draw(void);
void Render(void);
static void DrawHUD(void);

int main() {

	Start();

	while (g_IsRunning) {
		Update();
		Draw();

		Render();

		//Sleep(DF_FRAME_DELAY);
	}


	ScreenRelease();
	return 0;
}

// TODO 게임 로고 출력
void GameLogo() {
}

void Start(void) {
	system("mode con:cols=200 lines=50");
	srand(GetTickCount64());

	//GameLogo();
	//system("pause");

	ScreenInit(); 
	PlayerInit();
	BulletInit(); 
	EnemyInit(); 

	g_Score = 0;
	g_IsRunning = true;
	return;
}

void Render() {

	ScreenClear();
	ScreenPrint(BG);
	ScreenFlipping();

}

void Draw(void) {
	BGClear(BG);

	BGDrawMap(BG);
	EnemyDraw(BG);
	BulletDraw(BG);
	PlayerDraw(BG);
	DrawHUD();
	return;
}


void Update(void) {
	int PressKey = GetInputKey();

	if (PressKey == DF_KEY_ESC) {
		g_IsRunning = false;
		return;
	}

	ULONGLONG Now = GetTickCount64();

	PlayerUpdate(PressKey, Now);
	BulletUpdate(Now);
	EnemyUpdate(Now);
	FPSUpdate(Now);

	// =========================================================
	// TODO: 충돌 판정
	HitEnemy();
	HitPlayer();
	// =========================================================
	return;
}

static void DrawHUD(void) {
	char Text[32] = {};

	sprintf_s(Text, sizeof(Text), "SCORE : %d", g_Score);
	BGPrintText(BG, DF_HUD_X, 2, Text, COLOR_BRIGHT_WHITE);

	sprintf_s(Text, sizeof(Text), "LIFE  : %d", g_Player.Life);
	BGPrintText(BG, DF_HUD_X, 4, Text, COLOR_LIGHT_GREEN);

	sprintf_s(Text, sizeof(Text), "FPS : %d", g_FPS);
	BGPrintText(BG, DF_HUD_X, 6, Text, COLOR_GRAY);
	sprintf_s(Text, sizeof(Text), "Time : %.5fs", g_Timer);
	BGPrintText(BG, DF_HUD_X, 7, Text, COLOR_GRAY);

	BGPrintText(BG, DF_HUD_X, 9, "MOVE  : Arrow", COLOR_GRAY);
	BGPrintText(BG, DF_HUD_X, 10, "FIRE  : Space", COLOR_GRAY);
	BGPrintText(BG, DF_HUD_X, 11, "QUIT  : ESC", COLOR_GRAY);
}

