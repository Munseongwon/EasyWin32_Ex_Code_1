#include "pch.h"           // 컴파일 속도 향상을 위해
#include <stdio.h>
#define _USE_INIT_WINDOW_  // 윈도우 전역 초기화 함수를 직접 구현하도록 지정
#include "tipsware.h"      // EasyWin32를 사용하기 위해

#define AddEventString(p_app, str) ListBox_InsertString(p_app->p_event_list, -1, str)

void InitWindow()   // 자신이 사용할 윈도우의 전역 속성을 초기화 하는 함수
{
    gp_window_title = "마우스 매크로 사용하기";
    g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN; // 윈도우 속성을 수정
    g_ex_wnd_style = WS_EX_TOPMOST; // 최상위 윈도우로 지정
}

typedef struct AppData // 프로그램에서 사용할 내부 데이터
{
    UINT8 run_flag; // 매크로 실행 상태 (0: 중지, 1: 실행)
    int x, y, cx, cy;
    int interval, limit;
    int count;
    void *p_event_list;
} AD;

// 매크로 실행을 중지하는 함수
void StopMacro(AD* ap_app)
{
    if (ap_app->run_flag) { // 실행 상태인지 체크
        ap_app->run_flag = 0; // 중지 상태로 변경
        KillTimer(1); // 작업 타이머 중지
        AddEventString(ap_app, "매크로 작업을 중지합니다."); // 중지 상태를 출력
    }
}

// 윈도우가 종료될 때 호출될 함수
void OnDestroy()
{
    AD* p_app = (AD*)GetAppData(); // 프로그램 내부 데이터 주소를 얻는다.

    // 매크로 시작 및 중지 용으로 등록한 단축키를 해제한다.
    UnregisterHotKey(gh_main_wnd, 26000);
    UnregisterHotKey(gh_main_wnd, 26001);

    StopMacro(p_app); // 매크로 작업이 진행중이라면 중지
}

TIMER MacroTimer(NOT_USE_TIMER_DATA)
{
    AD* p_app = (AD*)GetAppData(); // 프로그램 내부 데이터 주소를 얻는다.

    if (p_app->count < p_app->limit) { // 다섯번만 그리기
        int x = p_app->x + p_app->count * (p_app->cx + p_app->interval); // 작업할 마우스 x 좌표 계산
        MouseClickDown(x, p_app->y, 1); // 마우스 왼쪽 버튼 누름
        Sleep(100); // 0.1초 대기
        MouseClickUp(x+p_app->cx, p_app->y+p_app->cy, 1); // 마우스 왼쪽 버튼 누름 해제
        Sleep(100); // 0.1초 대기
        MouseClickWrite(x, p_app->y+p_app->cy+50, 1); // 마우스 왼쪽 버튼을 클릭(Down & Up)
        
        p_app->count++; // 매크로 진행 횟수 증가
        char str[64];
        sprintf_s(str, 64, "매크로 작업: %d/%d번째 진행", p_app->count, p_app->limit);
        AddEventString(p_app, str);
    }
    else { // 5회 이상이 되면 중지
        StopMacro(p_app);
    }
}

// 매크로 작업을 시작하는 함수
void StartMacro(AD* ap_app)
{
    if (!ap_app->run_flag) { // 매크로 작업이 중지 상태인지 체크
        ap_app->limit = GetIntDataFromControl(1025);
        if (ap_app->limit > 0) {
            ap_app->run_flag = 1; // 작업 중 상태로 변경
            ap_app->count = 0; // 실행 횟수 초기화
            ap_app->x = GetIntDataFromControl(1020);
            ap_app->y = GetIntDataFromControl(1021);
            ap_app->cx = GetIntDataFromControl(1022);
            ap_app->cy = GetIntDataFromControl(1023);
            ap_app->interval = GetIntDataFromControl(1024);
            AddEventString(ap_app, "매크로 작업 중"); // 매크로 진행 상태를 출력
            SetTimer(1, 500, MacroTimer); // 0.5초마다 MacroTimer 함수를 호출하는 타이머 생성
        }
        else AddEventString(ap_app, "개수는 0보다 큰 값이어야 합니다. 매크로를 실행할 수 없습니다.");
    }
}

// 윈도우에 발생하는 일반 메시지를 처리하는 함수
int OnUserMsg(HWND ah_wnd, UINT a_message_id, WPARAM wParam, LPARAM lParam)
{
    if (a_message_id == WM_HOTKEY) { // 시스템 전역 단축키를 눌렀을 때
        AD* p_app = (AD*)GetAppData(); // 프로그램 내부 데이터 주소를 얻는다.

        if (wParam == 26000) { // Ctrl + F5, 매크로 시작
            StartMacro(p_app); // 매크로 작업을 시작
            return 1;
        }
        else if (wParam == 26001) { // Ctrl + F6, 매크로 중지
            StopMacro(p_app); // 매크로 작업을 중지
            return 1;
        }
    }
    return 0;
}

CMD_USER_MESSAGE(NULL, OnDestroy, OnUserMsg)

int main()
{
    ChangeWorkSize(500, 245); // 작업 영역(폭, 높이)을 지정
    Clear(0, RGB(82, 97, 124));
    SetTextColor(RGB(200, 228, 246));
    SelectFontObject("맑은 고딕", 16); // 문자열 출력에 사용할 글꼴 지정

    const char *p_attr_name[6] = { "시작 X", "시작 Y", "폭", "높이", "간격", "개수" };
    
    int init_value[6] = { 100, 200, 60, 100, 20, 5 };
    AD *p_app = (AD*)CreateAppData(sizeof(AD)); // 데이터를 저장할 내부 메모리 생성
    p_app->p_event_list = CreateListBox(5, 5, 490, 190, 1000, NULL, 0);
    for (int i = 0; i < 6; ++i)
    {
        TextOut(12 + i * 55, 200, p_attr_name[i]);
        CreateEdit(5 + i * 55, 218, 50, 22, 1020 + i, 0);
        SetIntDataToControl(1020 + i, init_value[i]);
    }
    
    // 전역 단축키 등록, 이 키를 누르면 WM_HOTKEY 메시지가 발생
    RegisterHotKey(gh_main_wnd, 26000, MOD_CONTROL, VK_F5); // 매크로 시작
    RegisterHotKey(gh_main_wnd, 26001, MOD_CONTROL, VK_F6); // 매크로 중지
    AddEventString(p_app,"전역 단축키를 등록했습니다. (Ctrl+F5:시작, Ctrl+F6:중지)"); // 중지 상태를 출력
    
    ShowDisplay();
    return 0;
}