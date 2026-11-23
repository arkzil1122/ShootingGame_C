#pragma once

#include <Windows.h>

void FPSUpdate(ULONGLONG _now);

int CalcFPS();
void SetFPS(int _FPS);
float GetDeltaTime();
void DeltaTime(ULONGLONG _now);
void AddFrameCount(ULONGLONG _now);