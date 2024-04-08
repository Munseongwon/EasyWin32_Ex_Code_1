#include "pch.h"				// 컴파일러 속도 향상
#define _USE_INIT_WINDOW_		// 윈도우 전역 초기화 함수 직접 지정
#include <time.h>				// _strtime_s 함수 사용(문자열 -> 현재 시간 출력하는 함수)
#include "tipsware.h"			// EasyWin32 사용

NOT_USE_MESSAGE

// 윈도우 전역 초기화 함수 직접 지정
void InitWindow()
{
	// 창 제목 설정
	gp_window_title = "디지털 시계";
	// 윈도우 속성 변경
	g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN;
}

// 프로그램 내부 응용 데이터
typedef struct AppData {
	// 시간 데이터를 저장할 문자열
	char str[32];
}AD;

// 0.5초마다 호출할 타임 함수
TIMER ShowTimeProc(NOT_USE_TIMER_DATA)
{
	// 프로그램 내부 데이터 주소를 받아옴
	AD *p_ap = (AD *)GetAppData();
	// 프로그램 배경 색을 RGB(62, 78, 104)로 지정
	Clear(0, RGB(62, 78, 104));
	// 현재 시간을 '02:12:50' 형식으로 얻음
	_strtime_s(p_ap->str, 32);
	// str에 저장된 문자열 출력
	TextOut(65, 0, RGB(208, 228, 228), p_ap->str);
	// 정보를 윈도우에 출력
	ShowDisplay();
}

// 프로그램 실행하는 메인 함수
int main()
{
	// 작업 영역을 660 * 200으로 설정
	ChangeWorkSize(660, 200);
	// 윈도우 배경색을 RGB(62, 78, 104)로 설정
	Clear(0, RGB(62, 78, 104));
	// 프로그램 내부 데이터 초기화
	AD p_app = { 0, };
	// 응용 프로그램의 주소를 가져옴
	SetAppData(&p_app, sizeof(AD));
	// 응용 프로그램의 글꼴 변경
	SelectFontObject("맑은 고딕", 180, 1);
	// 타이머 설정 1번에 0.5초씩 호출
	SetTimer(1, 500, ShowTimeProc);
	// 정보를 윈도우에 출력
	ShowDisplay();
	// 프로그램 종료
	return 0;
}