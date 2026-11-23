#pragma once

#include "struct.h"
#include "Define.h"

Vector GetDirection(float _velocity, Vector _dir);

extern Player g_Player;
extern Bullet g_Bullets[DF_MAX_BULLET];
extern Enemy  g_Enemies[DF_MAX_ENEMY];

extern int    g_Score;
extern bool   g_IsRunning;
extern int g_FPS;
extern float g_Timer;