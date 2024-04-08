// ChangingFormat(모달창 서식 바꾸기)
// Written by Seongwon Mun
// 2023.12.14

#include "pch.h"			// 컴파일 속도 향상
#define _USE_INIT_WINDOW_	// 윈도우 전역 초기화 함수를 직접 구현하도록 지정
#include "tipsware.h"		// EasyWin32를 사용함

// 자신이 사용할 윈도우의 전역 속성을 초기화 하는 함수
void InitWindow()
{
	// 창 제목 수정
	gp_window_title = "창 제목, 크기, 스타일 및 배경색 지정하기";

	// 윈도우 속성 수정
	g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME; // | WS_CLIPCHILDREN;
}

NOT_USE_MESSAGE // 메시지 사용 X

int main()
{
	ChangeWorkSize(630, 250);  // 작업 영역의 폭을 630, 높이를 250으로 지정
	Clear(0, RGB(80, 162, 232));	// 윈도우 배경색 지정
	
	//SelectBrushObject(RGB(80, 162, 232));	// 블러시 색상 지정
	SelectBrushObject(NULL_BRUSH);		// 블러시를 사용하지 않도록 설정
	
	// 색상이 RGB(20, 102, 172)이고 굵기가 3이며 실선을 사용하도록 설정
	SelectPenObject(RGB(20, 102, 172), 3, PS_SOLID);
	Rectangle(5, 5, 625, 545);

	ShowDisplay();	// 구성한 정보를 윈도에 출력
	return 0;
}