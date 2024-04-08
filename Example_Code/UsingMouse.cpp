// UsingMouse
// Written by Seongwon Mun
// 마우스 메시지 중에 이동 메시지 처리
// 2023.12.15

#include "pch.h"			// 컴파일 속도 향상 
#include "tipsware.h"		// EasyWin32 사용
#define _USE_INIT_WINDOW_	// 윈도우 전역 초기화 함수를 직접 구현

// 자신이 사용할 윈도우의 전역 속성을 초기화 하는 함수
void InitWindow()
{
	// 윈도우 타이틀 바꾸기
	gp_window_title = "마우스 속성 움직이기";
	// 윈도우 속성 바꾸기
	g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CHILDWINDOW;
}

// 마우스를 이동할 때 호출될 함수
void OnMouseMove(int a_mixed_key, POINT a_pos)
{
	// 윈도우 배경색 지정
	Clear(0, RGB(80, 162, 232));
	// 수직선을 그림
	Line(a_pos.x, 0, a_pos.x, 250);
	// 마우스 x좌표 출력
	printf(a_pos.x + 5, 0, "x:%d", a_pos.x);
	// 수평선을 그림
	Line(0, a_pos.y, 630, a_pos.y);
	// 마우스 y좌표 출력
	printf(0, a_pos.y, "y:%d", a_pos.y);
	// 구성된 정보를 윈도우에 출력
	ShowDisplay();
}

int main()
{

	return 0;
}