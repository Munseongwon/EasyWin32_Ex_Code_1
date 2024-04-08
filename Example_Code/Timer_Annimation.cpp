// Timer_Annimation
// Written By: Seongwon Mun
// 2023.12.20

#include "pch.h"				// 컴파일러 향상
#include <stdio.h>				// swprintf_s함수 사용
#define _USE_INIT_WINDOW_		// 윈도우 전역 초기화 함수를 직접 구현하도록 지정
#include "tipsware.h"			// EasyWin32를 사용하기 위해
#define IMAGE_COUNT 8			// 사용할 이미지 개수

// 자신이 사용할 윈도우의 전역 속성을 초기화 하는 함수
void InitWindow()
{
	// 창 제목 설정
	gp_window_title = "애니메이션 타이머 프로그램";
	// 윈도우 속성 수정
	g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN;
}

typedef struct ApplicationData {
	// GDI+ 객체의 주소
	void* p_dcp;
	// 사용할 이미지 목록의 주소
	void* p_image[IMAGE_COUNT];
	// 현재 보여주고 있는 그림의 위치값(0~7)
	int index;
}AD;

// 윈도우가 종료될 때 호출될 함수
void OnDestroy() {
	// 프로그램의 내부 데이터 주소를 얻음
	AD* p_app = (AD*)GetAppData();
	// 1번 타이머 제거
	KillTimer(1);
	// 사용하던 이미지 모두 제거
	for (int i = 0; i < IMAGE_COUNT; ++i) {
		DeleteImageDCP(p_app->p_dcp, p_app->p_image[i]);
	}
	// GDI+ 객체 모두 제거
	DestroyDCP(p_app->p_dcp);
}
MOUSE_MESSAGE_EX(NULL, NULL, NULL, OnDestroy)

TIMER ShowRunImage(NOT_USE_TIMER_DATA)
{
	// 프로그램의 내부 데이터 주소를 얻음
	AD* p_app = (AD*)GetAppData();
	//p_app->index++;
	//if (p_app->index >= IMAGE_COUNT) {
	//	p_app->index = 0;
	//}
	// 다음 이미지로 이동
	p_app->index = (p_app->index + 1) % IMAGE_COUNT;
	// 그리기 영역을 지정한 색으로 채움
	Clear(0, RGB(72, 88, 114));
	// GDI+ 이미지 버퍼를 지정한 색으로 채움
	ClearDCP(p_app->p_dcp, RGB(72, 88, 114));
	// index 번째 그림을 (0, 0) 위치에 출력
	DrawDCP(p_app->p_dcp, p_app->p_image[p_app->index], 0, 0);
	// GDI+ 이미지 버퍼 내용을 출력 장치용 이미지 버퍼에 복사
	DrawDCP(p_app->p_dcp);
	// 구성된 정보를 윈도우에 출력
	ShowDisplay();

}

int main()
{
	// 작업 영역: 550 * 598
	ChangeWorkSize(550, 598);
	// 그리기 영역을 지정한 색으로 채움
	Clear(0, RGB(72, 88, 114));
	// 데이터를 저장할 내부 메모리 생성
	AD* p_app = (AD*)CreateAppData(sizeof(AD));
	// GDI+ 객체 생성
	p_app->p_dcp = CreateDCP(550, 598);
	wchar_t file_path[256];
	// 순서대로 이미지 경로를 구성
	for (int i = 0; i < IMAGE_COUNT; ++i) {
		swprintf_s(file_path, 256, L"run\\%d.png", i);
		// 이미지를 읽음
		p_app->p_image[i] = LoadImageDCP(p_app->p_dcp, file_path);
	}
	// 첫 번째 그림을 (0, 0) 위치에 출력
	DrawDCP(p_app->p_dcp, p_app->p_image[0], 0, 0);
	// GDI+ 이미지 버퍼 내용을 출력 장치용 이미지 버퍼에 복사
	DrawDCP(p_app->p_dcp);
	// 구성된 정보를 윈도우에 출력
	ShowDisplay();
	// 0.1초 마다 ShowRunImage 함수를 호출하는 타이머 생성
	SetTimer(1, 100, ShowRunImage);
	// 프로그램 종료
	return 0;
}