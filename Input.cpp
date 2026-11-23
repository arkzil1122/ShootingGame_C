#include "Input.h"
#include <Windows.h>

#define DF_KEY_COUNT 256    // 가상 키 코드는 0~255

static bool g_CurrKey[DF_KEY_COUNT] = {};   // 이번 프레임 상태
static bool g_PrevKey[DF_KEY_COUNT] = {};   // 지난 프레임 상태

void InputUpdate() {
	for (int i = 0; i < DF_KEY_COUNT; ++i) {
		g_PrevKey[i] = g_CurrKey[i];
		g_CurrKey[i] = (GetAsyncKeyState(i) & 0x8000) != 0;
	}
}

bool IsKeyDown(int _VirtualKey) {
	if (_VirtualKey < 0 || _VirtualKey >= DF_KEY_COUNT) {
		return false;
	}
	return g_CurrKey[_VirtualKey];
}

// 방금 눌림 검사
bool IsKeyPressed(int _VirtualKey) {
	if (_VirtualKey < 0 || _VirtualKey >= DF_KEY_COUNT) {
		return false;
	}
	return g_CurrKey[_VirtualKey] && !g_PrevKey[_VirtualKey];
}
