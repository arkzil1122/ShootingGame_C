#pragma once

#include "Global.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

bool isHit(Bullet* _bullet, Enemy* _enemy);
bool isCollide(Player* _player, Enemy* _enemy);
void HitEnemy();
void HitPlayer();
bool isOverLap(float _ALeft, float _ARight, float _BLeft, float _BRight);