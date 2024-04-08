// Moving_Rectangle_KeyBoard
// Written by: Seongwon Mun
// 2023.12.18

#include "pch.h"				// 컴파일 속도 향상
#define _USE_INIT_WINDOW_		// 윈도우 전역 초기화 함수를 직접 구현
#include "tipsware.h"			// EasyWin32 사용

// 자신이 사용할 윈도우의 전역 속성을 초기화 하는 함수
void InitWindow()
{
	// 창 제목 수정
	gp_window_title = "키보드로 사각형 이동하기";
	// 윈도우 속성 지정
	g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN;
}

// 데이터셋 구조체
typedef struct ApplicationData
{
	int pos_x, pos_y;
}AD;

// 윈도우에 발생하는 일반 메시지를 처리하는 함수
int OnUserMsg(HWND ah_wnd, UINT a_msg_id, WPARAM wParam, LPARAM lParam)
{
	// 키를 눌렀을 때 발생
	if (a_msg_id == WM_KEYDOWN) {
		// 프로그램의 내부 데이터 주소를 얻음.
		AD* p_app = (AD*)GetAppData();
		// 변경된 좌표에 사각형을 그리기 위해 기존 그림을 지우고 다시 그림.
		// 그리기 영역을 RGB(72, 88, 114)색으로 채움.
		Clear(0, RGB(72, 88, 114));

		// 왼쪽 이동
		if (wParam == VK_LEFT) {
			p_app->pos_x--;
			TextOut(p_app->pos_x - 25, p_app->pos_y + 30, "◀");
		}
		// 위쪽 이동
		else if (wParam == VK_UP) {
			p_app->pos_y--;
			TextOut(p_app->pos_x + 40, p_app->pos_y - 32, "▲");
		}
		// 오른쪽 이동
		else if (wParam == VK_RIGHT) {
			p_app->pos_x++;
			TextOut(p_app->pos_x + 101, p_app->pos_y + 30, "▶");
		}
		// 아래쪽 이동
		else if (wParam == VK_DOWN) {
			p_app->pos_y++;
			TextOut(p_app->pos_x + 40, p_app->pos_y + 94, "▼");
		}
		// 사각형 출력
		Rectangle(p_app->pos_x, p_app->pos_y, p_app->pos_x + 100, p_app->pos_y + 100);
		// 구성된 정보 윈도우에 출력
		ShowDisplay();
	}
	else if (a_msg_id == WM_KEYUP) {
		// 프로그램의 내부 데이터 주소를 얻는다.
		AD* p_app = (AD*)GetAppData();
		// 변경된 좌표에 사각형을 그리기 위해 기존 그림을 지우고 다시 그림.
		// 그리기 영역을 RGB(72, 88, 114)로 설정
		Clear(0, RGB(72, 88, 114));
		// 사각형을 출력
		Rectangle(p_app->pos_x, p_app->pos_y, p_app->pos_x + 100, p_app->pos_y + 100);
		// 구성된 정보를 윈도우에 출력
		ShowDisplay();
	}
	return 0;
}
CMD_USER_MESSAGE(NULL, NULL, OnUserMsg);

int main()
{
	// 작업 영역의 폭: 550 * 500
	ChangeWorkSize(550, 500);
	// 그리기 영역을 RGB(72, 88, 114)로 설정
	Clear(0, RGB(72, 88, 114));
	// 데이터를 저장할 내부 메모리 설정
	AD* p_app = (AD*)CreateAppData(sizeof(AD));
	// 사각형의 시작 좌표를 (100, 100)으로 지정
	p_app->pos_x = p_app->pos_y = 100;
	// 출력할 문자열 색상 지정
	SetTextColor(RGB(202, 218, 244));
	// 출력할 문자열에 대한 글꼴 지정
	SelectFontObject("맑은 고딕", 32, 1);
	// 선 속성 지정
	SelectPenObject(RGB(42, 58, 84), 3);
	// 채우기 속성 지정
	SelectBrushObject(RGB(102, 118, 144));
	// 사각형 출력
	Rectangle(p_app->pos_x, p_app->pos_y, p_app->pos_x + 100, p_app->pos_y + 100);
	// 구성된 정보를 윈도우에 출력
	ShowDisplay();
	// 프로그램 종료
	return 0;
}