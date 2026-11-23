#include <stdlib.h>
#include "Enemy.h"
#include "Global.h"
#include "Background.h"
#include "Collide.h"


static ULONGLONG g_LastSpawnTime = 0;

static void EnemySpawn(ULONGLONG _Now);
static void EnemyMove(ULONGLONG _Now);

void EnemyInit() {
	for (int i = 0; i < DF_MAX_ENEMY; ++i) {
		g_Enemies[i].IsActive = false;
	}

	g_LastSpawnTime = 0;
}

void EnemyUpdate(ULONGLONG _Now) {
	EnemySpawn(_Now);
	EnemyMove(_Now);
}

void EnemyDraw(Tile(*_BG)[DF_BG_SIZEX]) {
	for (int i = 0; i < DF_MAX_ENEMY; ++i) {
		if (!g_Enemies[i].IsActive) {
			continue;
		}

		// Draw 단계에서 text 변경해보기
		// 1move -> 1 change가 불가능해지네.
		//if (g_Enemies[i].Design == DF_ENEMY_TEXT) {
		//	g_Enemies[i].Design = DF_ENEMY_TEXT_2;
		//}
		//else {
		//	g_Enemies[i].Design = DF_ENEMY_TEXT;
		//}
		BGSetTile(_BG, (int)g_Enemies[i].pos.X, (int)g_Enemies[i].pos.Y, Enemy_text[g_Enemies[i].Design], COLOR_LIGHT_RED);
	}
}

static void EnemySpawn(ULONGLONG _Now) {
	if (_Now - g_LastSpawnTime < DF_ENEMY_SPAWN_DELAY) {
		return;
	}

	for (int i = 0; i < DF_MAX_ENEMY; ++i) {
		if (g_Enemies[i].IsActive) {
			continue;
		}

		g_Enemies[i].pos.X = DF_MAP_SIZEX - 2;
		g_Enemies[i].pos.Y = rand() % (DF_MAP_SIZEY - 4) + 2;
		g_Enemies[i].IsActive = true;
		g_Enemies[i].LastMoveTime = _Now;
		g_Enemies[i].Design = ENEMY_TEXT_1;

		// TODO 적이 random한 간격으로 bullet 발사 구현

		break;
	}

	g_LastSpawnTime = _Now;
}

static void EnemyMove(ULONGLONG _Now) {
	for (int i = 0; i < DF_MAX_ENEMY; ++i) {
		Enemy* pEnemy = &g_Enemies[i];

		if (!pEnemy->IsActive) {
			continue;
		}

		if (_Now - pEnemy->LastMoveTime < DF_ENEMY_MOVE_DELAY) {
			continue;
		}

		// Move 단계에서 Design 변경
		// 첫 단계에서는 됨. 이후 움직임에서는 발생X
		// ㅄ.

		int Next = pEnemy->Design + 1;
		if (Next >= ENEMY_TEXT_COUNT) {
			Next = 0;
		}
		pEnemy->Design = (ENEMY_TEXT) Next;
		//
		//if (pEnemy->Design == DF_ENEMY_TEXT) {
		//	pEnemy->Design = DF_ENEMY_TEXT_2;
		//}
		//else {
		//	pEnemy->Design = DF_ENEMY_TEXT;
		//}

		--pEnemy->pos.X;


		pEnemy->LastMoveTime = _Now;

		if (pEnemy->pos.X < 1) {
			pEnemy->IsActive = false;
		}
	}
}
