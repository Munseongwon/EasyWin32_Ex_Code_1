// String And coordinate
// Written by Seongwon Mun
// EasyWin32 - Tut01
// 2023.12.14

#include "pch.h"		// 컴파일 속도 향상
#include "tipsware.h"	// EasyWin32를 사용함

NOT_USE_MESSAGE // 메세지 사용 안함

int main()
{
	// 글꼴을 'consolas', 크기 12로 변경함
	SelectFontObject("consolas", 12, 0);

	// 출력할 문자열 색상을 어두운 회색으로 지정함.
	SetTextColor(RGB(128, 128, 128));

	// X축 방향으로 50픽셀마다 위치 표시
	for (int x = 0; x < 16; ++x)
		printf(x * 50, 0, "%d", x * 50);

	// Y축 방향으로 50픽셀마다 위치 표시
	for (int y = 1; y < 11; ++y)
		printf(0, y * 50, "%d", y * 50);

	// 글꼴을 'consolas', 크기 64, '강조체' 로 변경(0 => default, 1 => Bold)
	SelectFontObject("consolas", 64, 1);
	printf(54, 54, RGB(20, 102, 172), "tipsware");
	printf(50, 50, RGB(80, 162, 232), "tipsware");

	// 글꼴을 '맑은 고딕', 크기 64로 변경
	SelectFontObject("맑은 고딕", 64, 0);
	printf(50, 100, RGB(0, 189, 0), "Win 32로 실습하기");

	// 글꼴을 '맑은 고딕', 크기 64, '강조체' 로 변경
	SelectFontObject("맑은 고딕", 64, 1);
	printf(50, 150, "Win 32로 실습하기");

	ShowDisplay(); // 구성한 정보를 윈도우에 출력
	return 0;
}