#pragma once

#include <Windows.h>

void FPSUpdate(ULONGLONG _now);

int CalcFPS();
void SetFPS(int _FPS);
float GetDeltaTime();           // 지난 프레임부터 지금까지 걸린 시간 (초)
void DeltaTime(ULONGLONG _now);  // [수정] Update() 맨 앞에서 매 프레임 한 번 호출
void AddFrameCount(ULONGLONG _now);