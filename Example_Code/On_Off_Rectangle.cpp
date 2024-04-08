// On_Off Rectangle Program
// Written by: Seongwon Mun
// 사각형 이동과 On/Off 까지 구현
// 2023.12.17

#include "pch.h"  // <- 컴파일 속도 향상
#define _USE_INIT_WINDOW_ // 윈도우 전역 초기화 함수를 직접 구현하도록 지정
#include "tipsware.h" // <- EasyWin32 기능을 사용하기 위해

typedef struct ApplicationData {
    // 0이면 off, 1이면 on
    UINT8 state;
    // 사각형의 위치 정보를 기억할 변수
    RECT rect;
    // 0: 사각형 내부 클릭 안됨, 1:출력
    int is_clicked;
    // 이동 거리 계산을 위해 이전 마우스 위치 저장
    POINT prev_pos;
}AD;

// on, off 상태에 따라 사용할 색상 테이블
COLORREF g_state_color[2] = {RGB(126, 116, 81), RGB(186, 176, 141) };

// 자신이 사용할 윈도우의 전역 속성을 초기화하는 함수
void InitWindow()
{
    // 창 제목 수정
    gp_window_title = "사각형 이동하기";
    // 윈도우 속성 지정
    g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
}

// 사각형 그리기
void OnDraw(AD* ap_app)
{
    // 윈도우 배경색 지정
    Clear(0, RGB(40, 48, 60));
    // state에 따라 색상 지정
    SelectBrushObject(g_state_color[ap_app->state]);
    // 사각형 출력
    Rectangle(&ap_app->rect);
    // 구성된 정보를 윈도우에 출력
    ShowDisplay();
}

// 마우스 왼쪽 버튼을 눌렀을 때 호출될 함수
void OnMouseLeftDown(int a_mixed_key, POINT a_pos)
{
    // 프로그램 내부 데이터 주소를 얻어옴
    AD* p_app = (AD*)GetAppData();
    if (!p_app->is_clicked) {
        // 사각형 내부를 클릭했는지 체크
        if (PtInRect(&p_app->rect, a_pos)) {
            // 사각형 내부가 클릭되었음으로 표시
            p_app->is_clicked = 1;
            p_app->prev_pos = a_pos;
            SetCapture(gh_main_wnd);
            p_app->state = ~p_app->state;
            OnDraw(p_app);
        }
    }
}
void OnMouseLeftUp(int a_mixed_key, POINT a_pos)
{
    // 프로그램 내부 데이터 주소를 얻음.
    AD* p_app = (AD*)GetAppData();
    // 사각형 내부를 마우스로 클릭한 상태인지 체크
    if (p_app->is_clicked)
    {
        // 클릭 해제로 설정
        p_app->is_clicked = 0;
        // SetCapture 해제
        ReleaseCapture();
    }
}
// 마우스를 이동할 때 호출될 함수
void OnMouseMove(int a_mixed_key, POINT a_pos)
{
    AD* p_app = (AD*)GetAppData();
    if (p_app->is_clicked)
    {
        int move_cx = a_pos.x - p_app->prev_pos.x;
        int move_cy = a_pos.y - p_app->prev_pos.y;
        OffsetRect(&p_app->rect, move_cx, move_cy);
        p_app->prev_pos = a_pos;
        OnDraw(p_app);
    }
}
MOUSE_MESSAGE(OnMouseLeftDown, OnMouseLeftUp, OnMouseMove)
int main()
{
    // 작업 영역 폭: 630 * 300
    ChangeWorkSize(630, 300);
    // 응용 프로그램이 사용할 내부 저장 공간 지정
    AD* p_app = (AD*)CreateAppData(sizeof(AD));
    // 사각형 영역 지정
    SetRect(&p_app->rect, 50, 50, 200, 100);
    // 사각형의 선 속성 지정
    SelectPenObject(RGB(239, 212, 91), 3, PS_SOLID);
    // 사각형 출력
    OnDraw(p_app);
    return 0;
}