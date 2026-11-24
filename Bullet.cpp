#include "Bullet.h"
#include "Global.h"
#include "Background.h"
#include "TimeManager.h"

static float Timer = 0.f;

void BulletInit() {
	for (int i = 0; i < DF_MAX_BULLET; ++i) {
		g_Bullets[i].IsActive = false;
	}
}

void BulletFire(int _X, int _Y, ULONGLONG _Now, Vector _dir) {
	if (_X > DF_MAP_SIZEX - 2) {
		return;
	}

	for (int i = 0; i < DF_MAX_BULLET; ++i) {
		if (g_Bullets[i].IsActive) {
			continue;
		}

		g_Bullets[i].pos.X = _X;
		g_Bullets[i].pos.Y = _Y;
		g_Bullets[i].IsActive = true;
		g_Bullets[i].LastMoveTime = _Now;
		SetBulletDirection(DF_BULLET_VELOCITY, _dir, &g_Bullets[i]);
		return;
	}
}

void BulletUpdate(ULONGLONG _Now) {
	for (int i = 0; i < DF_MAX_BULLET; ++i) {
		Bullet* pBullet = &g_Bullets[i];

		if (!pBullet->IsActive) {
			continue;
		}

		pBullet->pos.X += pBullet->dir.X * GetDeltaTime();
		pBullet->pos.Y += pBullet->dir.Y * GetDeltaTime();

		pBullet->LastMoveTime = _Now;

		if (FloatToInt(pBullet->pos.X) >= DF_MAP_SIZEX - 2) {
			pBullet->IsActive = false;
		}
		if (FloatToInt(pBullet->pos.Y) > DF_MAP_SIZEY - 2 || FloatToInt(pBullet->pos.Y) < 1) {
			pBullet->IsActive = false;
		}
	}
}

void BulletDraw(Tile(*_BG)[DF_BG_SIZEX]) {
	for (int i = 0; i < DF_MAX_BULLET; ++i) {
		if (!g_Bullets[i].IsActive) {
			continue;
		}

		BGSetTile(_BG, FloatToInt(g_Bullets[i].pos.X), FloatToInt(g_Bullets[i].pos.Y), DF_BULLET_TEXT, COLOR_LIGHT_YELLOW);
	}
}

void SetBulletDirection(float _velocity, Vector _dir, Bullet* _bullet) {
	_bullet->dir.X = _dir.X * _velocity;
	_bullet->dir.Y = _dir.Y * _velocity;
	return;
}