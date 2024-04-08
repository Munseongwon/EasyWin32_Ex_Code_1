// kiosk_system
// 1. 메뉴판 구성(완)
// 2. 실제 키오스크 계산 화면 만들기*/
// Written by: Seongwon Mun
// 2023.12.21

#include "pch.h"			// 컴파일 속도 향상
#include <stdio.h>			// swprintf_s 함수 사용
#define _USE_INIT_WINDOW_	// 윈도우 전역 초기화 함수 직접 구현
#include "tipsware.h"		// EasyWin32 사용
#define ITEM_COUNT 9		// 상품의 개수

// 자신이 사용할 윈도우의 전역 초기화 함수
void InitWindow()
{
	// 창 제목 설정
	gp_window_title = "키오스크 시스템";
	// 윈도우 속성 수정
	g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN;
}

// 프로그램에서 사용할 내부 속성
typedef struct AppData {
	// GDI+ 객체 주소
	void* p_dcp;
	// 글꼴 기본 정보
	void* p_family;
	// 한글, 영문, 가격표 글꼴에 대한 정보
	void* p_kor_font, * p_eng_font, * p_money_font;
} AD;

// 키오스크에서 판매할 항목의 정보
typedef struct KioskItemData {
	// 상품의 한글, 영문 이름
	const wchar_t* p_kor, * p_eng;
	// 상품의 한글, 영문 이름 길이
	short kor_len, eng_len;
	// 문자열로 변경된 가격정보
	wchar_t price_str[16];
	// 문자열로 변경된 가격정보의 길이
	short price_len;
	// 상품의 이미지 정보
	void* p_image;
	// 상품 이미지를 출력할 때 사용할 y좌표 보정값
	int y_margin;
	// 상품의 가격과 선택 개수
	int price, count;
}KID;

// 상품 아이템 구현
KID g_items[ITEM_COUNT] = {
	{L"크로와상 샌드위치", L"croissant sandwich", 9, 18, L"", 0, NULL, 40, 6200, 0},
	{L"치킨 샐러드", L"chicken salad", 6, 13, L"", 0, NULL, 40, 5500, 0},
	{L"햄 샌드위치", L"ham sandwich", 6, 12, L"", 0, NULL, 40, 5500, 0},
	{L"아이스 아메리카노", L"iced americano", 9, 14, L"", 0, NULL, 0, 3500, 0},
	{L"아이스 초코 블랜드", L"iced choco blended", 10, 18, L"", 0, NULL, 0, 5200, 0},
	{L"딸기 밀크티 라떼", L"strawberry milk tea latte", 9, 25, L"", 0, NULL, 0, 6800, 0},
	{L"딸기 스무디", L"strawberry smoothie", 6, 19, L"", 0, NULL, 0, 6500, 0},
	{L"오렌지 라임 에이드", L"orange lime ade", 10, 15, L"", 0, NULL, 0, 4800, 0},
	{L"자몽 에이드", L"grapefruit ade", 6, 14, L"", 0, NULL, 0, 4900, 0}
};

// 프로그램에서 사용할 글꼴을 생성하는 함수
void CreateAppFont(AD* ap_app)
{
	// 글꼴 집합 생성[CreateFontFamilyDCP()]
	ap_app->p_family = CreateFontFamilyDCP(ap_app->p_dcp, L"배달의민족 주아");
	// 키오스크에서 사용할 한글, 영문, 가격 글꼴을 생성
	ap_app->p_kor_font = CreateFontDCP(ap_app->p_dcp, ap_app->p_family, 24, 0);
	ap_app->p_eng_font = CreateFontDCP(ap_app->p_dcp, ap_app->p_family, 16, 0);
	ap_app->p_money_font = CreateFontDCP(ap_app->p_dcp, ap_app->p_family, 20, 0);
}

// 상품 이미지와 가격을 설정하는 함수
void LoadItemImage(AD* ap_app)
{
	wchar_t file_path[256];
	KID* p = g_items;
	for (int i = 0; i < ITEM_COUNT; ++i, ++p)
	{
		// 읽을 이미지 경로 구성 'menu\0.png'
		swprintf_s(file_path, 256, L"menu\\%d.png", i);
		// 이미지 파일 생성
		p->p_image = LoadImageDCP(ap_app->p_dcp, file_path);
		// 가격을 문자열로 변경[유니코드 함수:MakePriceStringW()]
		p->price_len = MakePriceStringW(p->price_str, p->price);
	}
}

// 프로그램에서 사용하기 위해 만든 글꼴을 제거하는 함수
void DeleteAppFont(AD* ap_app)
{
	// 글꼴 집합 제거
	DeleteFontFamilyDCP(ap_app->p_dcp, ap_app->p_family);
	// 키오스크에서 사용하기 위해 생성한 한글, 영문, 가격 글꼴 제거
	DeleteFontDCP(ap_app->p_dcp, ap_app->p_kor_font);
	DeleteFontDCP(ap_app->p_dcp, ap_app->p_eng_font);
	DeleteFontDCP(ap_app->p_dcp, ap_app->p_money_font);
}

// 보드 그리기
void DrawBoard(AD* ap_app, int a_x, int a_y, int a_cx, int a_cy)
{
	// 메뉴판 배경 그림
	FillSolidRectDCP(ap_app->p_dcp, a_x, a_y + 8, a_cx, a_cy - 36, RGB24(237, 234, 223));
	// 위쪽 선을 그림
	FillSolidRectDCP(ap_app->p_dcp, a_x, a_y, a_cx, 10, RGB24(222, 163, 28));
	// 아래쪽 선을 그림
	FillSolidRectDCP(ap_app->p_dcp, a_x, a_y + a_cy - 30, a_cx, 10, RGB24(222, 163, 28));
}

// 컨트롤을 조작했을 때 호출할 함수(컨트롤의 아이디, 컨트롤의 조작상태, 컨트롤 주소)
void OnCommand(INT32 a_ctrl_id, INT32 a_notify_code, void* ap_ctrl)
{
	// '선택' 버튼이 눌러진 경우
	if (a_ctrl_id >= 1100 && a_ctrl_id < (1100 + ITEM_COUNT))
	{
		// 1100 ~ 1108(0 ~ 8)
		int index = a_ctrl_id - 1100;
		// 선택한 상품 1증가
		g_items[index].count++;
		// 프로그래믜 내부 데이터 주소를 가져옴
		AD* p_app = (AD*)GetAppData();
		// 선택 메뉴 보드를 그림
		DrawBoard(p_app, 720, 20, 360, 800);
		// 합계 가격 표시용 보드를 그림
		DrawBoard(p_app, 720, 820, 360, 130);
		KID* p = g_items;
		wchar_t num_str[16], str[128];
		int len, total_count = 0, total_price = 0;
		for (int i = 0, index = 0; i < ITEM_COUNT; ++i, ++p)
		{
			// 현재 항목이 선택되어 있는 경우
			if (p->count) {
				// 이미지
				DrawDCP(p_app->p_dcp, p->p_image, 730, 45 + index * 80, 80, 80);
				// 한글 상품명 출력
				TextOutDCP(p_app->p_dcp, p_app->p_money_font, 820, 60 + index * 80,
					RGB24(55, 96, 37), p->p_kor, p->kor_len);
				// 영문 상품명 출력
				TextOutDCP(p_app->p_dcp, p_app->p_money_font, 820, 80 + index * 80,
					RGB24(222, 163, 28), p->p_eng, p->eng_len);
				// 상품별 합산 값을 문자열로 구성
				MakePriceStringW(num_str, p->price * p->count);
				len = swprintf_s(str, 128, L"%s * %d = %s원", p->price_str, p->count, num_str);
				// 상품별 합산 값 출력
				TextOutDCP(p_app->p_dcp, p_app->p_money_font, 820, 100 + index * 80,
					RGB24(55, 96, 37), str, len);
				// 상품을 선택한 개수만큼 합산
				total_count += p->count;
				// 상품 선택 금액만큼 합산
				total_price += p->price * p->count;
				++index;
			}
		}
		// 총 합계 금액을 문자열로 변경
		MakePriceStringW(num_str, total_price);
		// 합계 정보 구성
		len = swprintf_s(str, 128, L"총 %d개 주문: %s 원", total_count, num_str);
		RECT r = { 720, 815, 1080, 950 };
		DrawTextDCP(p_app->p_dcp, p_app->p_kor_font, &r, RGB24(55, 96, 37), str, len, 1, 1);
		// GDI+에 구성된 정보를 윈도우에 출력
		ShowDisplayDCP(p_app->p_dcp);
	}
}

// 윈도우가 종료될 때 호출될 함수
void OnDestory()
{
	// 프로그램 내부 데이터 주소를 얻어옴
	AD* p_app = (AD*)GetAppData();
	// 사용하던 상품 이미지를 모두 제거
	for (int i = 0; i < ITEM_COUNT; ++i)
	{
		DeleteImageDCP(p_app->p_dcp, g_items[i].p_image);
	}
	// 프로그램에서 사용하기 위해 만든 글꼴 제거
	DeleteAppFont(p_app);
	// GDI+ 객체 제거
	DestroyDCP(p_app->p_dcp);
}

CMD_MESSAGE(OnCommand, OnDestroy, NULL)

int main()
{
	// 작업 영역의 폭: 720 * 950
	ChangeWorkSize(1100, 950);
	// 배경색을 RGB(54, 88, 44)로 채움
	Clear(0, RGB(54, 88, 44));
	// 데이터를 저장할 내부 메모리 생성
	AD* p_app = (AD*)CreateAppData(sizeof(AD));
	// GDI+ 객체 생성
	p_app->p_dcp = CreateDCP(1100, 950);
	// 프로그램에서 사용할 글꼴 생성
	CreateAppFont(p_app);
	// 상품 이미지와 가격 설정
	LoadItemImage(p_app);
	// 메뉴 보드를 그림
	DrawBoard(p_app, 20, 20, 680, 930);
	// 선택 메뉴 보드를 그림
	DrawBoard(p_app, 720, 20, 360, 800);
	// 합계 가격 표시용 보드를 그림
	DrawBoard(p_app, 720, 820, 360, 130);
	int x, y;
	RECT r;
	void* p_ctrl;
	KID* p = g_items;
	for (int i = 0; i < ITEM_COUNT; ++i, ++p)
	{
		// 한 줄에 세 개의 이미지 그림
		x = (i % 3) * 220 + 30;
		// 세 개의 이미지가 출력되면 한 줄 아래로 내림
		y = (i / 3) * 300;
		// 상품 이미지 처리
		DrawDCP(p_app->p_dcp, p->p_image, x, y + p->y_margin, 200, 200);
		// 상품의 한글 이름 출력
		SetRect(&r, x, y + 200, x + 200, y + 230);
		DrawTextDCP(p_app->p_dcp, p_app->p_kor_font, &r, RGB24(55, 96, 37), p->p_kor, p->kor_len, 1, 1);
		// 상품의 영문 이름 출력
		SetRect(&r, x, y + 230, x + 200, y + 250);
		DrawTextDCP(p_app->p_dcp, p_app->p_eng_font, &r, RGB24(222, 163, 28), p->p_eng, p->eng_len, 1, 1);
		// 상품의 가격 출력
		SetRect(&r, x, y + 253, x + 160, y + 278);
		DrawTextDCP(p_app->p_dcp, p_app->p_money_font, &r, RGB24(55, 96, 37), p->price_str, p->price_len, 1, 1);
		// 제품 선택 버튼 생성
		p_ctrl = CreateButton("선택", x + 120, y + 250, 50, 26, 1100 + i);
		ChangeCtrlColor(p_ctrl, RGB(237, 234, 223), RGB(207, 204, 193),
			RGB(252, 249, 238), RGB(55, 96, 37));
		// 버튼에 적용된 글꼴 변경
		SetCtrlFont(p_ctrl, "배달의민족 주아", 18);
	}	
	// GDI+에 구성된 정보를 윈도우에 출력
	ShowDisplayDCP(p_app->p_dcp);
	// 프로그램 종료
	return 0;
}