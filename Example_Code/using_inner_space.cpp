// using_inner_space
// 내부 영역 데이터 저장
// 2023.12.16

#include "pch.h"
#define _USE_INIT_WINDOW_
#include "tipsware.h"

// 자신이 사용할 윈도우의 전역 속성을 초기화하는 함수
void InitWindow()
{
	// 창 제목을 수정
	gp_window_title = "내부 저장 공간 사용하기";
	// 윈도우 속성 수정
	g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME;
}

// 응용 프로그램이 데이터를 저장할 때 사용할 구조체
typedef struct ApplicationData {
	// 마우스 클릭 여부(0:클릭 안 함, 1:클릭됨, 2:클릭 해제)
	int clicked_flag;
	// 마우스를 클릭했을 때의 좌표, 마우스 클릭을 해제했을 때의 좌표
	POINT start_pos, end_pos;
}AD;

// 마우스 왼쪽 버튼을 눌렀을 때 호출될 함수
void OnMouseLeftDown(int a_mixed_key, POINT a_pos)
{
	// 프로그램 내부에 있는 데이터의 주소를 얻는다.
	AD* p_app = (AD*)GetAppData();
	// 마우스 클릭 상태가 아니라면
	if (p_app->clicked_flag != 1) {
		// 마우스 클릭 상태로 변경
		p_app->clicked_flag = 1;
		// 마우스 클릭 위치 저장
		p_app->start_pos = a_pos;
		// 마우스 커서가 윈도우 영역을 벗어나도 메시지를 받도록 설정
		SetCapture(gh_main_wnd);
	}
}

// 마우스 왼쪽 버튼을 눌렀다가 해제했을 때 호출될 함수
void OnMouseLeftUp(int a_mixed_key, POINT a_pos)
{
	// 프로그램 내부에 있는 데이터의 주소를 얻는다.
	AD* p_app = (AD*)GetAppData();
	// 마우스가 클릭된 상태라면
	if (p_app->clicked_flag == 1)
	{
		// 마우스 클릭 해제로 변경
		p_app->clicked_flag = 2;
		// 마우스 클릭이 해제된 위치 저장
		p_app->end_pos = a_pos;
		// SetCapture 해제
		ReleaseCapture();
	}
}

// 마우스를 이동했을 때 호출될 함수
void OnMouseMove(int a_mixed_key, POINT a_pos)
{
	// 윈도우 배경색 설정
	Clear(0, RGB(40, 48, 60));
	// 프로그램 내부 데이터 주소를 얻는다.
	AD* p_app = (AD*)GetAppData();
	// 마우스가 클릭 혹은 클릭 해제인 경우
	if (p_app->clicked_flag)
	{
		// 선 속성 지정
		SelectPenObject(RGB(239, 212, 91), 3, PS_SOLID);
		// 채우기 속성 지정
		SelectBrushObject(RGB(126, 116, 81));
		// 마우스를 클릭해서 드래그 중이라면 시작점과 현재 마우스 위치를 연결하는 사각형을
		// 그렇지 않으면 시작점과 끝점을 연결하는 사각형을 그림
		if (p_app->clicked_flag == 1)
			Rectangle(p_app->start_pos.x, p_app->start_pos.y, a_pos.x, a_pos.y);
		else
			Rectangle(p_app->start_pos.x, p_app->start_pos.y, p_app->end_pos.x, p_app->end_pos.y);
	}
	// 선 속성 지정
	SelectPenObject(RGB(206, 85, 124), 3, PS_DOT | PS_GEOMETRIC);
	// 수직선을 그림
	Line(a_pos.x, 0, a_pos.x, 250);
	// 마우스 X좌표 출력
	printf(a_pos.x + 5, 0, "x:%d", a_pos.x);
	// 수평선을 그림
	Line(0, a_pos.y, 630, a_pos.y);
	// 마우스 Y좌표 출력
	printf(5, a_pos.y + 2, "y:%d", a_pos.y);
	// 구성된 정보를 윈도우에 출력
	ShowDisplay();
}
// 마우스 이동 메시지를 사용하겠다고 메시지 맵 지정
MOUSE_MESSAGE(OnMouseLeftDown, OnMouseLeftUp, OnMouseMove)

// 프로그램을 수행하기 위한 메인함수
int main()
{
	// 작업 영역의 폭을 630 * 250으로 설정
	ChangeWorkSize(630, 250);
	// 윈도우 배경색 설정
	Clear(0, RGB(40, 48, 60));
	// 응용 프로그램의 데이터 저장 공간을 생성
	CreateAppData(sizeof(AD));
	// 글꼴을 'consolas', 크기 12로 변경
	SelectFontObject("consolas", 17, 0);
	// 출력할 문자열 색상 지정
	SetTextColor(RGB(227, 225, 241));
	// 구성된 정보를 윈도우에 출력
	ShowDisplay();
	// 프로그램 종료
	return 0;
}