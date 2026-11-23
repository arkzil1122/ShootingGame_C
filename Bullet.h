#pragma once

#include "struct.h"

void BulletInit();
void BulletFire(int _X, int _Y, ULONGLONG _Now, Vector _dir);
void BulletUpdate(ULONGLONG _Now);
void BulletDraw(Tile(*_BG)[DF_BG_SIZEX]);
void SetBulletDirection(float _velocity, Vector _dir, Bullet* _bullet);