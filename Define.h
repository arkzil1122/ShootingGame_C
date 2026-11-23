#pragma once

#define DF_MAP_SIZEX 90          // 테두리 포함
#define DF_MAP_SIZEY 30          // 테두리 포함
#define DF_HUD_X     (DF_MAP_SIZEX + 3)   // 점수·목숨 글자를 찍을 x

// 오브젝트 최대 개수
#define DF_MAX_BULLET 3000
#define DF_MAX_ENEMY  20

// 플레이어 Life
#define DF_PLAYER_LIFE 3

// 시간 간격 (ms) -> 이제는 Delta Time으로 관리할거임.
#define DF_FRAME_DELAY       1
#define DF_PLAYER_FIRE_DELAY 150
#define DF_BULLET_MOVE_DELAY 1
#define DF_ENEMY_MOVE_DELAY  150
#define DF_ENEMY_SPAWN_DELAY 800

// 속도 (1초에 몇칸)
#define DF_PLAYER_VELOCITY 1
#define DF_ENEMY_VELOCITY 1
#define DF_BULLET_VELOCITY 50


// 키보드 입력
#define DF_KEY_NONE   -1      // 입력 없음
#define DF_KEY_SPACE  ' '     // 32
#define DF_KEY_ESC    27
#define DF_KEY_UP     1072
#define DF_KEY_LEFT   1075
#define DF_KEY_RIGHT  1077
#define DF_KEY_DOWN   1080


// ----- 모양 -----
#define DF_WALL_TEXT   '#'

#define DF_BULLET_TEXT '-'

#define DF_ENEMY_TEXT  '<'
#define DF_ENEMY_TEXT_2 '-'

#define DF_ENEMY_HITBOX_X 0.5
#define DF_ENEMY_HITBOX_Y 0.8


enum ENEMY_TEXT {
	ENEMY_TEXT_1,
	ENEMY_TEXT_2,
	ENEMY_TEXT_COUNT
};

const char Enemy_text[ENEMY_TEXT_COUNT] = { '<', '-'};


// ----- 플레이어 모양 (여러 칸) -----
// g_Player.X, Y = 이 모양의 "왼쪽 위" 칸 위치.
// 공백(' ')은 투명 칸 = 그리지 않고, 플레이어 몸도 아님.
//
//   \          (0,0)
//   =>         (0,1) (1,1)
//   /          (0,2)

#define DF_PLAYER_SIZEX 2
#define DF_PLAYER_SIZEY 3

const char* const DF_PLAYER_SHAPE[DF_PLAYER_SIZEY] = {
	"\\ ", 
	"=>",
	"/ ",
};


#define DF_PLAYER_GUN_X 2
#define DF_PLAYER_GUN_Y 1

// 콘솔 색 번호
enum COLOR {
	COLOR_BLACK = 0,
	COLOR_BLUE,           // 1
	COLOR_GREEN,          // 2
	COLOR_CYAN,           // 3
	COLOR_RED,            // 4
	COLOR_MAGENTA,        // 5
	COLOR_YELLOW,         // 6
	COLOR_WHITE,          // 7  (콘솔 기본색)
	COLOR_GRAY,           // 8
	COLOR_LIGHT_BLUE,     // 9
	COLOR_LIGHT_GREEN,    // 10
	COLOR_LIGHT_CYAN,     // 11
	COLOR_LIGHT_RED,      // 12
	COLOR_LIGHT_MAGENTA,  // 13
	COLOR_LIGHT_YELLOW,   // 14
	COLOR_BRIGHT_WHITE,   // 15
};




// TODO 발사 시 우상단이 우하단보다 1칸 더 많이 가는 현상 발생

#define DF_ANGLE 0.2 // 각도 보정
#define DF_DIRECTION_LEFT					{ -1, 0 }	
#define DF_DIRECTION_LEFT_DOWN		{ -1, 1 * DF_ANGLE }
#define DF_DIRECTION_LEFT_UP				{ -1, -1 * DF_ANGLE }
#define DF_DIRECTION_RIGHT					{ 1, 0 }
#define DF_DIRECTION_RIGHT_DOWN		{ 1, 1 * DF_ANGLE }
#define DF_DIRECTION_RIGHT_UP			{ 1, -1 * DF_ANGLE }	


// 바보짓. COORD는 { x, y } 순서.
//#define DF_DIRECTION_LEFT					{ 0, -1 }	
//#define DF_DIRECTION_LEFT_DOWN		{ 1, -1 }
//#define DF_DIRECTION_LEFT_UP				{ -1, -1 }
//#define DF_DIRECTION_RIGHT					{ 0, 1 }
//#define DF_DIRECTION_RIGHT_DOWN		{ 1, 1 }
//#define DF_DIRECTION_RIGHT_UP			{ -1, 1 }	