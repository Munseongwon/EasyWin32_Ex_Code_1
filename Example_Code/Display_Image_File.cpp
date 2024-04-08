// Display_Image_File
// Written by: Seongwon Mun
// 2023.12.19

#include "pch.h"
#define _USE_INIT_WINDOW_
#include "tipsware.h"

void InitWindow()
{
	gp_window_title = "이미지 파일 출력하기";
	g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN;
}
NOT_USE_MESSAGE

int main()
{
	// 작업 영역의 폭: 697 * 643
	ChangeWorkSize(697, 643);
	// 그리기 영역: RGB(72, 88, 114)로 설정
	Clear(0, RGB(72, 88, 114));
	// 사용할 이미지 읽기
	void* p_image = LoadImageGP("berry.png");
	// 읽은 이미지를 (0,0)위치에 출력
	DrawImageGP(p_image, 0, 0, 697, 643);
	// 읽은 이미지를 (100, 100)위치에 출력
	DrawImageGP(p_image, 100, 100, 348, 321);
	// 읽은 이미지를 (200, 200)위치에 출력
	DrawImageGP(p_image, 200, 200, 0.5, 0.5);
	// 읽은 이미지 정보를 해제
	DeleteImageGP(p_image);
	// 구성된 정보를 윈도우에 출력
	ShowDisplay();
	// 프로그램 종료
	return 0;
}