#include "Collide.h"
#include <Windows.h>

bool isHit(Bullet* _bullet, Enemy* _enemy)
{
	const float EnemyLeft = _enemy->pos.X - DF_ENEMY_HITBOX_X;
	const float EnemyRight = _enemy->pos.X + DF_ENEMY_HITBOX_X;
	const float EnemyTop = _enemy->pos.Y - DF_ENEMY_HITBOX_Y;
	const float EnemyBottom = _enemy->pos.Y + DF_ENEMY_HITBOX_Y;

	return isOverLap(_bullet->pos.X, _bullet->pos.X, EnemyLeft, EnemyRight)
		&& isOverLap(_bullet->pos.Y, _bullet->pos.Y, EnemyTop, EnemyBottom);
}

bool isCollide(Player* _player, Enemy* _enemy)
{
	// player의 시작점은 가운데가 아님.
	const float OffsetX = (DF_PLAYER_SIZEX - DF_PLAYER_HITBOX_X) * 0.5f;
	const float OffsetY = (DF_PLAYER_SIZEY - DF_PLAYER_HITBOX_Y) * 0.5f;

	const float PlayerLeft = _player->pos.X - 0.5f + OffsetX;
	const float PlayerRight = PlayerLeft + DF_PLAYER_HITBOX_X;
	const float PlayerTop = _player->pos.Y - 0.5f + OffsetY;
	const float PlayerBottom = PlayerTop + DF_PLAYER_HITBOX_Y;
	
	const float EnemyLeft = _enemy->pos.X - DF_ENEMY_HITBOX_X;
	const float EnemyRight = _enemy->pos.X + DF_ENEMY_HITBOX_X;
	const float EnemyTop = _enemy->pos.Y - DF_ENEMY_HITBOX_Y;
	const float EnemyBottom = _enemy->pos.Y + DF_ENEMY_HITBOX_Y;

	return isOverLap(EnemyLeft, EnemyRight, PlayerLeft, PlayerRight) &&
		isOverLap(EnemyTop, EnemyBottom, PlayerTop, PlayerBottom);
}

void HitEnemy() {
	for (int i = 0; i < DF_MAX_ENEMY; i++) {
		if (!g_Enemies[i].IsActive) {
			continue;
		}
		for (int j = 0; j < DF_MAX_BULLET; j++) {
			if (!g_Bullets[j].IsActive) {
				continue;
			}
			if (isHit(&g_Bullets[j], &g_Enemies[i])) {
				g_Bullets[j].IsActive = false;
				g_Enemies[i].IsActive = false;
				g_Score += 100 + rand() % 30;
			}
		}
	}
}

void HitPlayer() {
	for (int i = 0; i < DF_MAX_ENEMY; i++) {
		if (!g_Enemies[i].IsActive) {
			continue;
		}
		if (isCollide(&g_Player, &g_Enemies[i])) {
			g_Player.Life--;

			// TODO 충돌시 플레이어 색상 변경.
			//g_Player.Color = COLOR_MAGENTA;

			g_Enemies[i].IsActive = false;
			if (g_Player.Life <= 0) {
				g_IsRunning = false;
			}
		}
	}
}

bool isOverLap(float _ALeft, float _ARight, float _BLeft, float _BRight) {
	return (_ALeft <= _BRight && _ARight >= _BLeft);
}