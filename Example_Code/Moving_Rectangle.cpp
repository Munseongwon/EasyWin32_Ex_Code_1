// Moving_Rectangle
// 사각형 이동하기
// 2023.12.16

#include "pch.h"
#define _USE_INIT_WINDOW_
#include "tipsware.h"

typedef struct ApplicationData
{
	// 0: 사각형 내부 클릭 안됨
	// 1: 클릭
	int is_clicked;
	// 이동 거리 계산을 위해 이전 마우스 위치 저장
	POINT prev_pos;
	// 사각형의 위치 정보를 기억할 변수
	RECT pos;
}AD;

// 자신이 사용할 윈도우의 전역 속성을 초기화 하는 함수
void InitWindow()
{
	// 창 제목을 수정
	gp_window_title = "마우스로 사각형 옮기기";
	// 윈도우 속성을 수정
	g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME;
}

// 마우스 왼쪽 버튼을 눌렀을 때 호출될 함수
void OnMouseLeftDown(int a_mixed_key, POINT a_pos)
{
	// 프로그램 내부 데이터 주소 얻어옴
	AD* p_app = (AD*)GetAppData();
	// 사각형 내부를 마우스로 클릭했는지 체크
	if (!p_app->is_clicked)
	{
		if (PtInRect(&p_app->pos, a_pos))
			// 사각형 내부가 클릭되었음을 표시
			p_app->is_clicked = 1;
			// 이동 거리 계산을 위해 현재 마우스 위치 기억
			p_app->prev_pos = a_pos;
			// 마우스 커서가 윈도우 영역을 벗어나도 메시지 받도록 수정
			SetCapture(gh_main_wnd);
	}
}
// 마우스 왼쪽 버튼을 눌렀다가 해제했을 때 호출될 함수
void OnMouseLeftUp(int a_mixed_key, POINT a_pos)
{
	// 프로그램 내부 주소 데이터를 얻음
	AD* p_app = (AD*)GetAppData();
	// 사각형 내부를 클릭했는 지 체크
	if (p_app->is_clicked)
	{
		// 클릭 해제 상태
		p_app->is_clicked = 0;
		// SetCapture 해제 상태
		ReleaseCapture();
	}
}
// 사각형 그리기
void OnDraw(AD* ap_app)
{
	// 윈도우 배경색 설정
	Clear(0, RGB(40, 48, 60));
	// 사각혀 출력
	Rectangle(&ap_app->pos);
	// 문자열 출력
	TextCenterOut(&ap_app->pos, "Tipsware");
	// 구성된 정보를 윈도우에 출력
	ShowDisplay();
}
// 마우스를 이동할 때 호출될 함수
void OnMouseMove(int a_mixed_key, POINT a_pos)
{
	// 프로그램 내부 데이터 주소 얻기
	AD* p_app = (AD*)GetAppData();
	// 사각형 클릭 여부 확인
	if (p_app->is_clicked)
	{
		// x축 이동거리
		int move_cx = a_pos.x - p_app->prev_pos.x; 
		// y축 이동거리
		int move_cy = a_pos.y - p_app->prev_pos.y;
		// 이동 거리를 사각형 좌표에 반영
		OffsetRect(&p_app->pos, move_cx, move_cy);
		// 이동 거리 계산을 위해 현재 좌표 기억
		p_app->prev_pos = a_pos;
		// 사각형과 문자열 출력
		OnDraw(p_app);
	}
}
MOUSE_MESSAGE(OnMouseLeftDown, OnMouseLeftUp, OnMouseMove)

int main()
{
	// 작업 영역 설정
	ChangeWorkSize(630, 300);
	// 응용 프로그램이 사용할 내부 저장공간 생성
	AD* p_app = (AD*)CreateAppData(sizeof(AD));
	// 사각형이 초기에 표시될 영역 지정
	SetRect(&p_app->pos, 50, 50, 200, 100);
	// 선 색상 지정
	SelectPenObject(RGB(227, 225, 241));
	// 채우기 색상 지정
	SelectBrushObject(RGB(126, 116, 81));
	// 출력할 문자열 색상 지정
	SetTextColor(RGB(227, 225, 241));
	// 글꼴 지정
	SelectFontObject("consolas", 26, 1);
	// 사각형과 문자열 출력
	OnDraw(p_app);
	// 프로그램 종료
	return 0;
}