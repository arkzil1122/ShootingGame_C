#include "Input.h"
#include "Define.h"
#include <conio.h>

int GetInputKey() {

	if (!_kbhit()) {
		return DF_KEY_NONE;
	}

	int PressKey = _getch();

	// 방향키는 _getch()로 읽으면 숫자가 2개 연달아 들어온다.
	//   첫 번째: 224 (방향키라는 표시)
	//   두 번째: 72(위) 75(왼쪽) 77(오른쪽) 80(아래)
	// 그래서 224가 오면 한 번 더 읽어서 진짜 방향을 알아낸다.
	if (PressKey == 224 || PressKey == 0) {
		int ArrowKey = _getch();

		switch (ArrowKey) {
		case 72: return DF_KEY_UP;
		case 75: return DF_KEY_LEFT;
		case 77: return DF_KEY_RIGHT;
		case 80: return DF_KEY_DOWN;
		default: return DF_KEY_NONE;
		}
	}

	return PressKey;
}
