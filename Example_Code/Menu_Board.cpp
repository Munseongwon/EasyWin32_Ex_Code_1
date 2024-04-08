// Menu_Board
// 메뉴판 구성하기
// Written by: Seongwon Mun
// 2023.12.20

#include "pch.h"
#include <stdio.h>
#define _USE_INIT_WINDOW_
#include "tipsware.h"

// 자신이 사용할 윈도우의 전역 속성을 초기화 하는 함수
void InitWindow()
{
	// 창 제목 수정
	gp_window_title = "메뉴판 프로그램";
	// 윈도우 속성 수정
	g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN;
}
NOT_USE_MESSAGE
// 프로그램을 실행하는 메인 함수
int main()
{
	// 작업 영역의 폭: 720 * 950
	ChangeWorkSize(720, 950);
	// 그리기 영역을 RGB(54, 88, 44)색으로 채움
	Clear(0, RGB(54, 88, 44));
	// 상품 한글 이름
	const wchar_t* p_han_name[9] = {
		L"크로와상 샌드위치", L"치킨 샐러드", L"햄 샌드위치",
		L"아이스 아메리카노", L"아이스 초코 블랜드", L"딸기 밀크티 라떼",
		L"딸기 스무디", L"오렌지 라임 에이드", L"자몽 에이드"
	};
	// 상품 영어 이름
	const wchar_t* p_eng_name[9] = {
		L"croissant sandwich", L"chicken salad", L"ham sandwich",
		L"iced americano", L"ice choco blended", L"strawberry milk tea latte",
		L"strawberry smoothie", L"orange lime ade", L"grapefruit ade"
	};
	// 상품 가격
    const wchar_t* p_money[9] = {
		L"6,200", L"5,500", L"5,500",
		L"3,500", L"5,200", L"6,800",
		L"6,500", L"4,800", L"4,900"
	};
	// GDI+ 객체 생성
	void* p_dcp = CreateDCP(720, 950);
	void* p_image;
	wchar_t file_path[256];
	int x, y;
	RECT r;
	// 메뉴판 배경을 그림
	FillSolidRectDCP(p_dcp, 20, 20, 680, 910, RGB24(237, 234, 223));
	// 위쪽 선을 그림
	FillSolidRectDCP(p_dcp, 20, 20, 680, 10, RGB24(222, 163, 28));
	// 아래쪽 선을 그림
	FillSolidRectDCP(p_dcp, 20, 920, 680, 910, RGB24(222, 163, 28));
	for (int i = 0; i <= 8; ++i) {
		// 읽을 이미지 경로 구성 'menu\0.png'
		swprintf_s(file_path, 256, L"menu\\%d.png", i);
		// 이미지 파일을 읽음
		p_image = LoadImageDCP(p_dcp, file_path);
		// 한 줄에 세 개의 이미지 출력
		x = (i % 3) * 220 + 30;
		// 세 개의 이미지가 출력되면 한 줄 아래로 내림
		y = (i / 3) * 300;
		// 첫 줄의 이미지가 너무 위쪽에 출력되어 강제로 위치를 조정해서 출력
		if (i < 3)
			DrawDCP(p_dcp, p_image, x, y + 40, 200, 200); // 첫 줄
		else
			DrawDCP(p_dcp, p_image, x, y, 200, 200);

		// 상품의 한글 이름을 출력
		SetRect(&r, x, y + 200, x + 200, y + 230);
		// 글꼴 정보를 지정
		ChangeFontDCP(p_dcp, L"배달의민족 주아", 24, 0);
		DrawTextDCP(p_dcp, &r, RGB24(55, 96, 37), p_han_name[i], wcslen(p_han_name[i]),1,1);
		// 상품의 영어 이름을 출력
		SetRect(&r, x, y + 230, x + 200, y + 250);
		// 글꼴 정보를 지정
		ChangeFontDCP(p_dcp, L"배달의민족 주아", 16, 0);
		DrawTextDCP(p_dcp, &r, RGB24(222, 163, 28), p_eng_name[i], wcslen(p_eng_name[i]), 1, 1);
		// 상품의 가격을 출력
		SetRect(&r, x, y + 253, x + 200, y + 278);
		// 글꼴 정보를 지정
		ChangeFontDCP(p_dcp, L"배달의민족 주아", 20, 0);
		DrawTextDCP(p_dcp, &r, RGB24(55, 96, 37), p_money[i], wcslen(p_money[i]), 1, 1);
		// 읽은 이미지 해제
		DeleteImageDCP(p_dcp, p_image);
	}
	
	// GDI+ 객체에 구성된 이미지를 화면에 출력
	DrawDCP(p_dcp);
	// GDI+ 객체를 제거
	DestroyDCP(p_dcp);
	// 구성된 정보를 윈도우에 출력
	ShowDisplay();
	// 프로그램 종료
	return 0;
}