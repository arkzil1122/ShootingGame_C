#include "Global.h"

Player g_Player = {};
Bullet g_Bullets[DF_MAX_BULLET] = {};
Enemy  g_Enemies[DF_MAX_ENEMY] = {};

int g_Score = 0;
bool   g_IsRunning = true;
int g_FPS = 0;
float g_Timer = 0;


Vector GetDirection(float _velocity, Vector _dir) {
	return { _dir.X * _velocity , _dir.Y * _velocity };
}