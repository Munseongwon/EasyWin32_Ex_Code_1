// DrawShape
// Written by Seongwon Mun
// 목표: 선, 타원, 선, 파이형의 도형을 그리기

#include "pch.h"		// 컴파일 속도 향상
#include "tipsware.h"	// EasyWin32를 사용하기 위해

NOT_USE_MESSAGE // 메시지 처리X

int main()
{	
	// 글꼴을 'consolas', 크기 12로 변경
	SelectFontObject("consolas", 12, 0);
	// 출력할 문자열 색상을 어두운 회색으로 지정
	SetTextColor(RGB(128, 128, 128));
	// X축 방향으로 50픽셀마다 위치 표시
	for (int x = 0; x < 16; ++x)
	{
		Line(x * 50, 0, x * 50, 600);
		printf(x * 50, 0, "%d", x * 50);
	}
	// y축 방향으로 50픽셀마다 위치 표시
	for (int y = 1; y < 11; ++y)
	{
		Line(0, y * 50, 800, y * 50);
		printf(0, y * 50, "%d", y * 50);
	}
	// 선 색상이 검은색이고 굵기는 1이며 실선을 사용
	SelectPenObject(RGB(0, 0, 0),1,PS_SOLID);
	Rectangle(50, 50, 100, 100);			// 사각형
	Ellipse(50, 150, 100, 200);				// 타원
	Line(50, 250, 100, 300);				// 선
	PieDegree(50, 350, 100, 400, 0, 60);	// 파이

	// 선 색상이 하늘색이고 굵기는 1이며 실선을 사용
	SelectPenObject(RGB(80, 162, 232), 1, PS_SOLID);
	Rectangle(150, 50, 200, 100);			// 사각형
	Ellipse(150, 150, 200, 200);				// 타원
	Line(150, 250, 200, 300);				// 선
	PieDegree(150, 350, 200, 400, 30, 120);	// 파이

	// 채우기 색상을 밝은 하늘색으로 사용
	SelectBrushObject(RGB(228, 238, 255));
	Rectangle(250, 50, 300, 100);
	Ellipse(250, 150, 300, 200);
	Line(250, 250, 300, 300);
	PieDegree(250, 350, 300, 400, 90, 150);

	// 선 굵기를 1에서 3으로 사용
	SelectPenObject(RGB(80, 162, 232), 3, PS_SOLID);
	Rectangle(350, 50, 400, 100);
	Ellipse(350, 150, 400, 200);
	Line(350, 250, 400, 300);
	PieDegree(350, 350, 400, 400, 120, 180);
	
	// 선 종류를 실선에서 점선으로 변경
	SelectPenObject(RGB(80, 162, 232), 3, PS_DOT | PS_GEOMETRIC);
	Rectangle(450, 50, 500, 100);
	Ellipse(450, 150, 500, 200);
	Line(450, 250, 500, 300);
	PieDegree(450, 350, 500, 400, 160, 250);

	ShowDisplay(); // 구성된 정보를 윈도우에 출력
	return 0;
}
