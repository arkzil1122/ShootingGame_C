#include <conio.h>
#include "Player.h"
#include "Global.h"
#include "Background.h"
#include "Bullet.h"
#include "Collide.h"

static void PlayerFire(ULONGLONG _Now);

void PlayerInit() {
	g_Player.pos.X = 3;
	g_Player.pos.Y = (DF_MAP_SIZEY - DF_PLAYER_SIZEY) / 2;
	g_Player.Life = DF_PLAYER_LIFE;

	g_Player.LastFireTime = 0;
}


void PlayerUpdate(int _PressKey, ULONGLONG _Now) {
	
	const int MaxX = DF_MAP_SIZEX - 1 - DF_PLAYER_SIZEX;
	const int MaxY = DF_MAP_SIZEY - 1 - DF_PLAYER_SIZEY;
	
	switch (_PressKey) {
	case DF_KEY_LEFT:
		if (g_Player.pos.X > 1) {
			g_Player.pos.X--;
		}
		break;
	case DF_KEY_RIGHT:
		if (g_Player.pos.X < MaxX) {
			g_Player.pos.X++;
		}
		break;
	case DF_KEY_UP:
		if (g_Player.pos.Y > 1) {
			g_Player.pos.Y--;
		}
		break;
	case DF_KEY_DOWN:
		if (g_Player.pos.Y < MaxY) {
			g_Player.pos.Y++;
		}
		break;
	case DF_KEY_SPACE:
		PlayerFire(_Now);
		break;
	default:
		break;
	}
}

void PlayerDraw(Tile(*_BG)[DF_BG_SIZEX]) {
	for (int y = 0; y < DF_PLAYER_SIZEY; ++y) {
		for (int x = 0; DF_PLAYER_SHAPE[y][x] != '\0'; ++x) {
			char Text = DF_PLAYER_SHAPE[y][x];

			if (Text == ' ') {
				continue;
			}

			BGSetTile(_BG, (int)g_Player.pos.X + x, (int)g_Player.pos.Y + y, Text, g_Player.Color);
		}
	}
}


static void PlayerFire(ULONGLONG _Now) {
	if (_Now - g_Player.LastFireTime < DF_PLAYER_FIRE_DELAY) {
		return;
	}

	// 총구에서 발사
	BulletFire((int)g_Player.pos.X + DF_PLAYER_GUN_X, (int)g_Player.pos.Y + DF_PLAYER_GUN_Y, _Now, DF_DIRECTION_RIGHT);
	BulletFire((int)g_Player.pos.X + DF_PLAYER_GUN_X, (int)g_Player.pos.Y + DF_PLAYER_GUN_Y, _Now, DF_DIRECTION_RIGHT_UP);
	BulletFire((int)g_Player.pos.X + DF_PLAYER_GUN_X, (int)g_Player.pos.Y + DF_PLAYER_GUN_Y, _Now, DF_DIRECTION_RIGHT_DOWN);
	
	g_Player.LastFireTime = _Now;
}
