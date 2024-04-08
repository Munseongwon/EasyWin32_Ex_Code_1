// OutPutGuGuDan.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include <stdio.h>
#define _USE_INIT_WINDOW_
#include "tipsware.h"

void InitWindow()
{
	gp_window_title = "구구단 출력";
	g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN;
}

void OnCommand(INT32 a_ctrl_id, INT32 a_notify_code, void* ap_ctrl)
{
	if (a_ctrl_id == 1001)
	{
		int dan = GetIntDataFromControl(1000);
		void* p_list_box = FindControl(1002);
		char str[32];

		ListBox_ResetContent(p_list_box);
		for (int i = 1; i < 20; ++i)
		{
			sprintf_s(str, 32, "%d x %d = %d", dan, i, dan * i);
			ListBox_InsertString(p_list_box, -1, str, 0);
		}
	}
}
CMD_MESSAGE(OnCommand)

int main()
{
	ChangeWorkSize(500, 360, 1);
	Clear(0, RGB(80, 162, 232));
	SelectFontObject("맑은 고딕", 21, 1);
	TextOut(19, 9, RGB(208, 248, 248), "단 입력:");

	CreateEdit(82, 10, 50, 22, 1000, 0);
	CreateButton("보기", 136, 6, 68, 30, 1001);
	CreateListBox(10, 40, 340, 150, 1002);
	
	ShowDisplay();
	return 0;
}