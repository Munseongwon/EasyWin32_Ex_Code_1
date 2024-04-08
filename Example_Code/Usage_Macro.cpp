// Usage_Macro
// 마우스 매크로 기능을 사용하여 봅시다.
// Written by: Seongwon Mun
// 2023.12.18

#include "pch.h"
#define _USE_INIT_WINDOW_
#include "tipsware.h"

void InitWindow() {
	gp_window_title = "마우스 매크로 사용하기";
	g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN;
	g_ex_wnd_style = WS_EX_TOPMOST;
}

typedef struct AppData {
	UINT8 run_flag;
	UINT8 count;
}AD;


void DrawAppState(const char* ap_state_str) {

}

// 매크로 실행 중지 함수
void StopMacro(AD* ap_app) {

}

// 윈도우가 종료될 때 호출될 함수
void OnDestroy() {

}

// 매크로 작업을 시작하는 함수

// 윈도우에 발생하는 일반 메시지를 처리하는 함수

// 윈도우에 발생하는 일반 메시지를 처리하는 함수
int OnUserMsg(HWND ah_wnd, UINT a_message_id, WPARAM wParam, LPARAM lParam) {
	// 시스템 전역 단축키를 눌렀을 경우
	if (a_message_id == WM_HOTKEY) {
		// 프로그램 내부 데이터 주소를 얻음
		AD* p_app = (AD*)GetAppData();
	}
}

// 프로그램을 시작하는 메인 코드
int main()
{
	// 작업 공간의 영역: 500 * 100
	ChangeWorkSize(500, 100);
	// 데이터를 저장할 내부 메모리 생성
	AD* p_app = (AD*)CreateAppData(sizeof(AD));
	// 전역 단축키 등록, 이 키를 누르면 WM_HOTKEY 메시지 발생
	// 매크로 시작
	RegisterHotKey(gh_main_wnd, 26000, MOD_CONTROL, VK_F5);
	// 매크로 중지
	RegisterHotKey(gh_main_wnd, 26001, MOD_CONTROL, VK_F6);
	// 문자열 출력에 사용할 글꼴 지정
	SelectFontObject("맑은 고딕", 50, 1);
	// 중지 상태를 출력
	DrawAppState("매크로 작업이 중지된 상태");
	// 프로그램 종료
	return 0;
}