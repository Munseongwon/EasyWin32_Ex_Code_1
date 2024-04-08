// Visual 2022 x86(32비트) Release Mode
// ClipBoard_String_Output

#include "pch.h"				
#define _USE_INIT_WINDOW_		
#include "tipsware.h"

void InitWindow()
{
	gp_window_title = "클립보드 문자열 사용하기";
	g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN;
}

typedef struct AppData {
	void *p_src_list;
}AD;

void OnCommand(INT32 a_ctrl_id, INT32 a_notify_code, void *ap_ctrl)
{
	// 응용 프로그램의 내부 데이터를 가져옴
	AD *p_app = (AD *)GetAppData();
	// '클립보드에서 가져오기'를 클릭한 경우
	if (a_ctrl_id == 1010)
	{
		ListBox_ResetContent(p_app->p_src_list);
	
		char *p_str = NULL;
		int str_len = CopyTextFromClipboard(&p_str, 0);
		if (str_len > 0) {
			char *p = p_str, *p_prev = p_str;
			while (*p) {
				if (*p == '\r' || *p == '\n') {
					*p++ = 0;
					ListBox_InsertString(p_app->p_src_list, -1, p_prev, 0);
					if (*p == '\r' || *p == '\n') p++;
					p_prev = p;
				}else p++;
			}

			if (p != p_prev)ListBox_InsertString(p_app->p_src_list, -1, p_prev, 0);
			free(p_str);
		}
	}
	// '선택한 항목을 클립 보드에 저장하기'를 클릭한 경우
	else if (a_ctrl_id == 1011)
	{
		int index = ListBox_GetCurSel(p_app->p_src_list);
		if (index != -1) {
			char str[1024];
			ListBox_GetText(p_app->p_src_list, index, str, 1024);
			CopyTextToClipboard(str);
		}
	}
}
CMD_MESSAGE(OnCommand)

int main()
{
	ChangeWorkSize(600, 355);
	Clear(0, RGB(82, 97, 124));

	AD *p_app = (AD *)CreateAppData(sizeof(AD));
	p_app->p_src_list = CreateListBox(5, 5, 590, 310, 1000, NULL, 0);

	CreateButton("클립보드에서 가져오기", 5, 320, 156, 30, 1010);
	CreateButton("선택 항목을 클립보드에 저장하기", 165, 320, 210, 30, 1011);
	ShowDisplay();
	return 0;
}