// DrawingShapeAndText2
// Written by Seongwon Mun
// 2023.12.14
// 타원과 사각형을 그리는 여러가지 방법을 알아보기

#include "pch.h"				// 컴파일 속도 향상
#define _USE_INIT_WINDOW_		// 윈도우 전역 초기화 함수
#include "tipsware.h"			// EasyWin32를 사용

// 자신이 사용할 윈도우의 전역 속성을 초기화 하는 함수
void InitWindow()
{
	// 창 제목을 수정
	gp_window_title = "도형 및 텍스트 출력하기";
	// 윈도우 속성을 수정
	g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN;
}
NOT_USE_MESSAGE
int main()
{
	ChangeWorkSize(500, 400);	// 작업 영역(폭, 넓이) 지정
	Clear(0, RGB(72, 88, 114));

	// 선 색상이 RGB(50, 180, 255)이고 선 굵기는 3, 실선으로 지정
	SelectPenObject(RGB(50, 180, 255), 3, PS_SOLID);
	// 채우기 색상을 RGB(0, 100, 200)로 지정
	SelectBrushObject(RGB(0, 100, 200));
	// 내접하는 타원을 그림
	Ellipse(50, 50, 300, 300);

	// 선 색상이 RGB(64, 225, 64)이고 선 굵기는 5, 점선으로 지정
	SelectPenObject(RGB(64, 255, 64), 5, PS_GEOMETRIC);
	// 채우기 색상을 RGB(32, 128, 32)로 지정
	SelectBrushObject(RGB(32, 128, 32));
	// 사각형을 그림
	Rectangle(150, 150, 450, 350);

	// 문자열이 출력될 영역 지정
	RECT r = {150, 150, 450, 350};
	// 문자열 색상 지정
	SetTextColor(RGB(233, 233, 242));
	// 문자열에 사용할 글꼴 지정
	SelectFontObject("배달의민족 주아", 50);
	DrawText(&r, DT_CENTER | DT_VCENTER | DT_SINGLELINE, "프로젝트");
	
	// 문자열 색상 지정
	SetTextColor(RGB(168, 200, 228));
	SelectFontObject("배달의민족 주아", 32);
	
	DrawText(&r, DT_LEFT, "좌/상");
	DrawText(&r, DT_RIGHT, "우/상");
	DrawText(&r, DT_RIGHT | DT_BOTTOM | DT_SINGLELINE, "우/하");
	DrawText(&r, DT_LEFT | DT_BOTTOM | DT_SINGLELINE, "좌/하");
	
	// 구성된 정보를 윈도우에 출력
	ShowDisplay();
	return 0;
}

