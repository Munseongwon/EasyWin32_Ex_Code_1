#include "pch.h"           // 컴파일 속도 향상을 위해
#define _USE_INIT_WINDOW_  // 윈도우 전역 초기화 함수를 직접 구현하도록 지정
#include "tipsware.h"      // EasyWin32를 사용하기 위해

// 자신이 사용할 윈도우의 전역 속성을 초기화 하는 함수
void InitWindow()
{
    // 창 제목 설정
    gp_window_title = "기본 글꼴에 포함된 그림 문자 출력하기";
    // 윈도우 속성 변경
    g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN;
}

NOT_USE_MESSAGE

int main()
{
    ChangeWorkSize(550, 300);
    Clear(0, RGB(72, 88, 114));

    SetTextColor(RGB(172, 188, 214));
    SelectFontObject("맑은 고딕", 128, 1);

    TextOut(80, 80, "▲▼◀▶");
    ShowDisplay();

    return 0;
}