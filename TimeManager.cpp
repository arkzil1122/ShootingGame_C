#include "TimeManager.h"
#include "Global.h"

#include <Windows.h>

// 게임 시작 시간
static ULONGLONG StartTick = GetTickCount64();

int FPS = 0;
int FPSCount = 0;
int PlayTime = 0;

static ULONGLONG DeltaTick = StartTick;
static ULONGLONG PreTick = StartTick;

// FPS 측정기
void FPSUpdate(ULONGLONG _now)
{
    // 매 순간 프레임 계산을 한다.
    AddFrameCount(_now);
    g_Timer += GetDeltaTime();

    // 1초에 한번씩 playtime을 추가한다.
    if (_now - StartTick >= 1000) {
        SetFPS(CalcFPS());
        StartTick = _now;
         ++PlayTime;
    }
}

int CalcFPS()
{
    int nowFPS = 0;
    if (PlayTime >= 1) {
        nowFPS = FPSCount / PlayTime;
    }
    return nowFPS;
}

void SetFPS(int _FPS) {
    if (PlayTime >= 1) {
        g_FPS = _FPS;
    }
    return;
}

void AddFrameCount(ULONGLONG _now)
{
    ++FPSCount;
    DeltaTime(_now);
}


float GetDeltaTime()
{
    return DeltaTick * 0.001f;
}

void DeltaTime(ULONGLONG _now)
{
    DeltaTick = _now - PreTick;
    PreTick = _now;
}