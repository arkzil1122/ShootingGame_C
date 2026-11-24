#include "Player.h"
#include "Global.h"
#include "Background.h"
#include "Bullet.h"
#include "Collide.h"
#include "Input.h"        // [추가] IsKeyDown
#include "TimeManager.h"  // [추가] GetDeltaTime

static void PlayerMove();
static void PlayerFire(ULONGLONG _Now);

void PlayerInit() {
	g_Player.pos.X = 3;
	g_Player.pos.Y = (DF_MAP_SIZEY - DF_PLAYER_SIZEY) / 2;
	g_Player.Life = DF_PLAYER_LIFE;

	g_Player.LastFireTime = 0;
}


void PlayerUpdate(ULONGLONG _Now) {
	PlayerMove();
	PlayerFire(_Now);
}


static void PlayerMove() {
	Vector Dir = { 0.f, 0.f };

	if (IsKeyDown(VK_LEFT))  { Dir.X -= 1.f; }
	if (IsKeyDown(VK_RIGHT)) { Dir.X += 1.f; }
	if (IsKeyDown(VK_UP))    { Dir.Y -= 1.f; }
	if (IsKeyDown(VK_DOWN))  { Dir.Y += 1.f; }

	if (Dir.X != 0.f && Dir.Y != 0.f) {
		Dir.X *= DF_DIAGONAL_SCALE;
		Dir.Y *= DF_DIAGONAL_SCALE;
	}

	float DeltaTime = GetDeltaTime();
	g_Player.pos.X += Dir.X * DF_PLAYER_VELOCITY * DeltaTime;
	g_Player.pos.Y += Dir.Y * DF_PLAYER_VELOCITY * DeltaTime;

	const float MaxX = (float)(DF_MAP_SIZEX - 1 - DF_PLAYER_SIZEX);
	const float MaxY = (float)(DF_MAP_SIZEY - 1 - DF_PLAYER_SIZEY);

	if (g_Player.pos.X < 1.f)  { g_Player.pos.X = 1.f; }
	if (g_Player.pos.X > MaxX) { g_Player.pos.X = MaxX; }
	if (g_Player.pos.Y < 1.f)  { g_Player.pos.Y = 1.f; }
	if (g_Player.pos.Y > MaxY) { g_Player.pos.Y = MaxY; }
}

void PlayerDraw(Tile(*_BG)[DF_BG_SIZEX]) {
	for (int y = 0; y < DF_PLAYER_SIZEY; ++y) {
		for (int x = 0; DF_PLAYER_SHAPE[y][x] != '\0'; ++x) {
			char Text = DF_PLAYER_SHAPE[y][x];

			if (Text == ' ') {
				continue;
			}

			BGSetTile(_BG, FloatToInt(g_Player.pos.X + x), FloatToInt(g_Player.pos.Y + y), Text, g_Player.Color);
		}
	}
}


static void PlayerFire(ULONGLONG _Now) {
	if (!IsKeyDown(VK_SPACE)) {
		return;
	}

	if (_Now - g_Player.LastFireTime < DF_PLAYER_FIRE_DELAY) {
		return;
	}

	// 총구에서 발사
	BulletFire(FloatToInt(g_Player.pos.X + DF_PLAYER_GUN_X), FloatToInt(g_Player.pos.Y + DF_PLAYER_GUN_Y), _Now, DF_DIRECTION_RIGHT);
	BulletFire(FloatToInt(g_Player.pos.X + DF_PLAYER_GUN_X), FloatToInt(g_Player.pos.Y + DF_PLAYER_GUN_Y), _Now, DF_DIRECTION_RIGHT_UP);
	BulletFire(FloatToInt(g_Player.pos.X + DF_PLAYER_GUN_X), FloatToInt(g_Player.pos.Y + DF_PLAYER_GUN_Y), _Now, DF_DIRECTION_RIGHT_DOWN);
	
	g_Player.LastFireTime = _Now;
}
