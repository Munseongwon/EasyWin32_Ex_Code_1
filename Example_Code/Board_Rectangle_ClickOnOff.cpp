// Board_Rectangle_ClickOnOff
// Written by: Seongwon Mun
// 2023.12.17

#include "pch.h"			// 컴파일 속도 향상
#define _USE_INIT_WINDOW_	// 윈도우 전역 초기화 함수 직접 구현하도록 저장
#include "tipsware.h"		// EasyWin32 사용

#define MAX_X_COUNT 10		// 수평 방향에 사용할 사각형 개수
#define MAX_Y_COUNT 10		// 수직 방향에 사용할 사각형 개수
#define BOARD_X		50		// 사각형 시작 x좌표
#define BOARD_Y		50		// 사각형 시작 y좌표
#define GRID_SIZE	36		// 사각형의 폭과 높이(정사각형)

// 자신이 사용할 윈도우의 전역 속성을 초기화 하는 함수
void InitWindow()
{
	// 창 제목 설정
	gp_window_title = "격자 보드의 사각형을 클릭해서 상태 변경하기";
	// 윈도우 속성 수정
	g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU; // | WS_THICKFRAME | WS_CLIPCHILDREN;
}

typedef struct ApplicationData {
	// 0이면 Off, 1이면 On [10][10]
	UINT8 state[MAX_Y_COUNT][MAX_X_COUNT];
}AD;

// on, off 상태에 따라 사용할 색상 레이블
COLORREF g_state_color[2] = { RGB(126, 116, 81), RGB(166, 176, 141) };

// 사각형 그리기
void OnDraw(AD* ap_app)
{
	// 윈도우 배경색 지정
	Clear(0, RGB(40, 48, 60));
	for (int col = 0; col < MAX_Y_COUNT; ++col)
	{
		for (int row = 0; row < MAX_X_COUNT; ++row)
		{
			// state에 따라 색상을 지정
			SelectBrushObject(g_state_color[ap_app->state[col][row]]);
			Rectangle(BOARD_X + row * GRID_SIZE, BOARD_Y + col * GRID_SIZE,
				BOARD_X + 1 + (row + 1) * GRID_SIZE, BOARD_Y + 1 + (col + 1) * GRID_SIZE);
		}
	}
	// 구성된 정보를 윈도우에 출력
	ShowDisplay();
}

// 마우스 왼쪽 버튼을 눌렀을 때 호출될 함수
void OnMouseLeftDown(int a_mixed_key, POINT a_pos)
{
	// 프로그램 내부 데이ㅓ 주소를 얻어옴
	AD* p_app = (AD*)GetAppData();
	UINT32 row = (UINT32)(a_pos.x - BOARD_X) / GRID_SIZE;
	UINT32 col = (UINT32)(a_pos.y - BOARD_Y) / GRID_SIZE;
	if (row < MAX_X_COUNT && col < MAX_Y_COUNT)
	{
		// state 상태 토글
		p_app->state[col][row] = ~p_app->state[col][row];
		// 사각형 내부 배경색 채우기
		SelectBrushObject(g_state_color[p_app->state[col][row]]);
		// 사각형 출력
		Rectangle(BOARD_X + row * GRID_SIZE, BOARD_Y + col * GRID_SIZE,
			BOARD_X + 1 + (row + 1) * GRID_SIZE, BOARD_Y + 1 + (col + 1) * GRID_SIZE);
		// 구성된 정보를 윈도우에 출력
		ShowDisplay();
	}
}
MOUSE_MESSAGE(OnMouseLeftDown, NULL, NULL)
// 프로그램 메인 함수
int main()
{
	// 작업 영역: 630 * 300
	ChangeWorkSize(630, 500);
	// 응용 프로그램이 사용할 저장 내부 공간 생성
	AD* p_app = (AD*)CreateAppData(sizeof(AD));
	// 사각형의 선 지정
	SelectPenObject(RGB(239, 212, 91), 1, PS_SOLID);
	// 사각형 출력
	OnDraw(p_app);
	// 프로그램 종료
	return 0;
}
