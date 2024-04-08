#include "pch.h"           // 컴파일 속도 향상을 위해
#define _USE_INIT_WINDOW_  // 윈도우 전역 초기화 함수를 직접 구현하도록 지정
#include "tipsware.h"      // EasyWin32를 사용하기 위해
#define MAX_COUNT    3 // 사용할 사각형의 개수

// 자신이 사용할 윈도우의 전역 속성을 초기화 하는 함수
void InitWindow()
{
    // 창 제목을 수정한다.
    gp_window_title = "여러 개의 사각형을 클릭해서 상태를 On/Off 하기";
    // 윈도우 속성을 수정한다.
    g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU; // | WS_THICKFRAME | WS_CLIPCHILDREN;
}

typedef struct ApplicationData
{
    UINT8 state[MAX_COUNT]; // 0이면 0ff, 1이면 On
    // RECT rect[MAX_COUNT]; // 사각형의 위치 정보를 기억할 변수
} AD;

// on, off 상태에 따라 사용할 색상 테이블
COLORREF g_state_color[2] = { RGB(126, 116, 81), RGB(186, 176, 141) };

void OnDraw(AD* ap_app)
{
    Clear(0, RGB(40, 48, 60)); // 윈도우 배경색 지정

    for (int i = 0; i < MAX_COUNT; i++) {
        // state에 따라 색상을 지정한다.
        SelectBrushObject(g_state_color[ap_app->state[i]]);
        // Rectangle(ap_app->rect + i); // 사각형을 출력한다.
        Rectangle(50 + i * 150, 50, 201 + i * 150, 100);
    }
    ShowDisplay(); // 구성된 정보를 윈도우에 출력
}

// 마우스 왼쪽 버튼을 눌렀을 때 호출될 함수
void OnMouseLeftDown(int a_mixed_key, POINT a_pos)
{
    AD* p_app = (AD*)GetAppData(); // 프로그램 내부 데이터 주소를 얻는다.
    for (int i = 0; i < MAX_COUNT; i++) {
        //if (PtInRect(p_app->rect + i, a_pos)) { // 사각형 내부를 클릭했는지 체크한다.
        //    p_app->state[i] = ~(p_app)->state[i]; // state 상태 토글
        //    OnDraw(p_app); // 변경된 상태를 출력한다.
        //}
        if (a_pos.y >= 50 && a_pos.y <= 100) {
            UINT32 x_index = (a_pos.x - 50) / 150;
            if (x_index < MAX_COUNT) {
                // state 상태 토글
                p_app->state[x_index] = ~p_app->state[x_index];
                // 사각형 내부 배경색 지정
                SelectBrushObject(g_state_color[p_app->state[x_index]]);
                // 사각형 출력
                Rectangle(50 + x_index * 150, 50, 201 + x_index * 150, 100);
                // 구성된 정보를 윈도우에 출력
                ShowDisplay();
            }
        }
    }
}
MOUSE_MESSAGE(OnMouseLeftDown, NULL, NULL)

int main()
{
    ChangeWorkSize(630, 300); // 작업 영역의 폭을 630, 높이를 300으로 지정
    AD* p_app = (AD*)CreateAppData(sizeof(AD)); // 응용 프로그램이 사용할 내부 저장공간 생성

    // 사각형이 초기에 표시될 영역 지정
    /*for (int i = 0; i < MAX_COUNT; i++) {
        SetRect(p_app->rect + i, 50 + i * 150, 50, 200 + i * 150 + 1, 100);
    }*/
    SelectPenObject(RGB(239, 212, 91), 3, PS_SOLID); // 사각형의 선 속성 지정

    OnDraw(p_app); // 사각형 출력
    return 0;
}