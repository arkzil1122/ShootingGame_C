#include "Collide.h"
#include <Windows.h>

bool isHit(Bullet* _bullet, Enemy* _enemy)
{
	if (_bullet->pos.X >= _enemy->pos.X - DF_ENEMY_HITBOX_X &&
		_bullet->pos.X <= _enemy->pos.X + DF_ENEMY_HITBOX_X &&
		_bullet->pos.Y >= _enemy->pos.Y - DF_ENEMY_HITBOX_Y &&
		_bullet->pos.Y <= _enemy->pos.Y + DF_ENEMY_HITBOX_Y
		) {
		return true;
	}
	return false;
}

bool isCollide(Player* _player, Enemy* _enemy)
{
	if (_enemy->pos.X >= _player->pos.X &&
		_enemy->pos.X <= _player->pos.X + DF_PLAYER_SIZEX &&
		_enemy->pos.Y >= _player->pos.Y &&
		_enemy->pos.Y <= _player->pos.Y + DF_PLAYER_SIZEY) {
		return true;
	}
	return false;
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