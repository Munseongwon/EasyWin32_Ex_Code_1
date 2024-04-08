// Mouse_Moving
// Written by Seongwon Mun
// 2023.12.15
// 마우스 무빙을 구현해보자!(X,Y표 이동) ==> 완료
// 드래그하면서 사각형을 그려봅시다!

#include "pch.h"				// 컴파일 속도 향상 
#define _USE_INIT_WINDOW_		// 윈도우 속성 사용
#include "tipsware.h"			// EasyWin32 사용

// 자신이 사용할 윈도우의 전역 속성을 초기화하는 함수
void InitWindow()
{	
	// 창 제목 수정
	gp_window_title = "마우스 사용하기";
	// 윈도우 속성 수정
	g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME; // | WS_CLIPCHILDREN
}

// 마우스 클릭 여부(0: 클릭 안 함/초기, 1: 클릭됨, 2:클릭 해제)
int g_clicked_flag = 0;
// 마우스를 클릭했을 때의 좌표와 마우스 클릭을 해제 했을 때의 좌표
POINT g_start_pos, g_end_pos;

// 마우스 왼쪽 버튼을 눌렀을 때 호출될 함수
void OnMouseLeftDown(int a_mixed_key, POINT a_pos)
{
	// 마우스 클릭 상태가 아니라면
	if (g_clicked_flag != 1) {
		// 마우스 클릭 상태로 변경
		g_clicked_flag = 1; 
		// 마우스 클릭 위치 저장
		g_start_pos = a_pos;
		// 마우스 커서가 윈도우 영역을 벗어나더라도 메시지 받을 수 있도록 설정
		SetCapture(gh_main_wnd);
	}
}

// 마우스 왼쪽 버튼을 눌렀다가 해제했을 때 호출될 함수
void OnMouseLeftUp(int a_mixed_key, POINT a_pos)
{
	// 마우스가 클릭된 상태
	if (g_clicked_flag == 1)
	{
		// 마우스 클릭 해제로 변경
		g_clicked_flag = 2;
		// 클릭이 해제된 위치 저장
		g_end_pos = a_pos;
		// SetCapture 해제
		ReleaseCapture();
	}
}


// 마우스를 이동할 때 호출될 함수
void OnMouseMove(int a_mixed_key, POINT a_pos)
{
	// 윈도우 배경색 지정
	Clear(0, RGB(80, 162, 232));

	// 1또는 2인 경우!
	if (g_clicked_flag)
	{
		// 선 속성 지정
		SelectPenObject(RGB(239, 212, 91), 3, PS_SOLID);
		// 채우기 속성 지정
		SelectBrushObject(RGB(126, 116, 81));
		// 마우스를 클릭해서 드래그 중이라면 시작점과 현재 마우스 위치를 연결하는
		// 사각형을 그리고 그렇지 않다면 시작점과 끝점을 연결하는 사각형을 그린다.
		if (g_clicked_flag == 1)
			Rectangle(g_start_pos.x, g_start_pos.y, a_pos.x, a_pos.y);
		else
			Rectangle(g_start_pos.x, g_start_pos.y, g_end_pos.x, g_end_pos.y);
	}

	// 선 속성 지정(도트 | 점선)
	SelectPenObject(RGB(20, 102, 173), 3, PS_DOT | PS_GEOMETRIC);
	// 수직선을 그림
	Line(a_pos.x, 0, a_pos.x, 250);
	// 마우스 x좌표 출력
	printf(a_pos.x + 5, 0, "x:%d", a_pos.x);
	// 수평선을 그림
	Line(0, a_pos.y, 630, a_pos.y);
	// 마우스 y좌표 출력
	printf(5, a_pos.y + 2, "y:%d", a_pos.y);
	// 구성된 정보를 윈도우에 출력
	ShowDisplay();
}

// 마우스 이동 메시지를 사용하겠다고 메시지 맵 지정
MOUSE_MESSAGE(OnMouseLeftDown, OnMouseLeftUp, OnMouseMove)

// 프로그램 메인 코드
int main()
{
	// 작업 영역의 폭을 630 * 250으로 설정
	ChangeWorkSize(630, 250); 
	// 윈도우 배경색 지정
	Clear(0, RGB(80, 162, 232));
	// 글꼴을 'consolas'로 지정
	SelectFontObject("consolas", 17, 0);
	// 출력할 문자열 색상 지정
	SetTextColor(RGB(128, 228, 228));
	// 구성된 정보를 윈도우에 출력
	ShowDisplay();
	// 프로그램 종료
	return 0;
}

