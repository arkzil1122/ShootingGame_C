#include <stdlib.h>
#include "Enemy.h"
#include "Global.h"
#include "Background.h"
#include "Collide.h"
#include "TimeManager.h"

static ULONGLONG g_LastSpawnTime = 0;

static void EnemySpawn(ULONGLONG _Now);
static void EnemyMove();

void EnemyInit() {
	for (int i = 0; i < DF_MAX_ENEMY; ++i) {
		g_Enemies[i].IsActive = false;
	}

	g_LastSpawnTime = 0;
}

void EnemyUpdate(ULONGLONG _Now) {
	EnemySpawn(_Now);
	EnemyMove();
}

void EnemyDraw(Tile(*_BG)[DF_BG_SIZEX]) {
	for (int i = 0; i < DF_MAX_ENEMY; ++i) {
		if (!g_Enemies[i].IsActive) {
			continue;
		}

		BGSetTile(_BG, FloatToInt(g_Enemies[i].pos.X), FloatToInt(g_Enemies[i].pos.Y), Enemy_text[g_Enemies[i].Design], COLOR_LIGHT_RED);
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
		g_Enemies[i].Design = ENEMY_TEXT_1;

		// TODO 적이 random한 간격으로 bullet 발사 구현

		break;
	}

	g_LastSpawnTime = _Now;
}

static void EnemyMove() {
	for (int i = 0; i < DF_MAX_ENEMY; ++i) {
		Enemy* pEnemy = &g_Enemies[i];

		if (!pEnemy->IsActive) {
			continue;
		}

		// 적 애니메이션
		int Next = pEnemy->Design + 1;
		if (Next >= ENEMY_TEXT_COUNT) {
			Next = 0;
		}
		pEnemy->Design = (ENEMY_TEXT) Next;

		// 적 이동
		pEnemy->pos.X += pEnemy->dir.X * 
			DF_ENEMY_VELOCITY * GetDeltaTime();

		if (pEnemy->pos.X < 1) {
			pEnemy->IsActive = false;
		}
	}
}
