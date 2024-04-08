// Student_Score
// Written by: Seongwon Mun
// 학생들 성적 구하기
// 성적 구하기(완) -> 
// 데이터 변경(완) -> 
// 데이터 그래프 작성(완)-> 
// 데이터 저장(완)
// 데이터 삭제
// 2023.12.17 ~ 2023.12.20

#include "pch.h"			// 컴파일 속도 향상
#include <stdio.h>			// sprintf_s 함수 사용
#include <malloc.h>			// malloc, free 함수 사용
#define _USE_INIT_WINDOW_	// 윈도우 전역 초기화 함수를 직접 정의해서 사용
#include "tipsware.h"		// EasyWin32 사용

// 자신이 사용할 윈도우의 전역 속성 초기화 함수
void InitWindow()
{
	// 창 제목 수정
	gp_window_title = "학생 성적 관리 프로그램";
	// 윈도우 속성 수정
	g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN;
}

// 학생 데이터 속성
typedef struct StudentScoreData {
	// 학생 이름
	char student_name[16];
	// 학번, [c언어, cpp, c샵] 성적, 점수 총합 
	int student_id, score_c, score_cpp, score_csharp, score_sum;
	// 평균 점수
	int score_avg;
	// 학점
	char grade;
}SSD;

// 리스트 박스 속성
typedef struct ApplicationData {
	// 성적 리스트 박스의 주소
	void *p_list_box;
}AD;

// 성적의 원본 정보를 구성하는 함수
void MakeSSD(SSD *ap_data)
{
	GetCtrlName(FindControl(1000), ap_data->student_name, 16);
	ap_data->student_id = GetIntDataFromControl(1001);
	ap_data->score_c = GetIntDataFromControl(1002);
	ap_data->score_cpp = GetIntDataFromControl(1003);
	ap_data->score_csharp = GetIntDataFromControl(1004);
	ap_data->score_sum = ap_data->score_c + ap_data->score_cpp + ap_data->score_csharp;
	ap_data->score_avg = ap_data->score_sum / 3;
	switch (ap_data->score_avg / 10) {
	case 10:
	case 9:
		ap_data->grade = 'A';
		break;
	case 8:
		ap_data->grade = 'B';
		break;
	case 7:
		ap_data->grade = 'C';
		break;
	case 6:
		ap_data->grade = 'D';
		break;
	default:
		ap_data->grade = 'F';
		break;
	}
}

// 성적을 추가하는 함수
void AddScore()
{
	// 프로그램 내부 데이터 주소를 얻음
	AD* p_app = (AD*)GetAppData();
	// 원본 데이터를 저장할 메모리 할당
	SSD* p_data = (SSD*)malloc(sizeof(SSD));
	// 성적 원본 데이터를 한 개의 메모리로 구성하고 문자열로 만듦.
	MakeSSD(p_data);
	// str배열에 저장된 문자열을 리스트 박스에 등록
	ListBox_SetItemDataPtrEx(p_app->p_list_box, -1, "", p_data, 1);
}

// 성적을 변경하는 함수
void ModifyScore()
{
	// 프로그램 내부 데이터 주소를 얻음
	AD* p_app = (AD*)GetAppData();
	// 사용자가 선택한 항목의 위치
	int index = ListBox_GetCurSel(p_app->p_list_box);
	// 선택 항목이 있는 지 체크
	if (index != -1) {
		// 원본 데이터 주소
		SSD* p_data = (SSD*)ListBox_GetItemDataPtr(p_app->p_list_box, index);
		// 성적 원본 데이터를 한 개의 메모리로 구성하고 문자열로 만듦.
		MakeSSD(p_data);
		// index 항목을 다시 그림.
		ListBox_SetCurSel(p_app->p_list_box, index);
	}
}
// 성적을 삭제하는 함수
void DeleteScore()
{
	// 프로그램 내부 데이터 주소를 얻음
	AD* p_app = (AD*)GetAppData();
	// 사용자가 선택한 항목의 위치
	int index = ListBox_GetCurSel(p_app->p_list_box);
	if (index != -1) {
		// 원본 데이터 주소
		SSD* p_data = (SSD*)ListBox_GetItemDataPtr(p_app->p_list_box, index);
		char str[64];
		// 이름과 학번을 조합해서 "한민준 (23010501)" 문자열로 구성
		sprintf_s(str, 64, "%s (%2d)", p_data->student_name, p_data->student_id);
		if (IDYES == MessageBox(gh_main_wnd, str, "아래의 학생 정보를 삭제하시겠습니까?",
			MB_ICONQUESTION | MB_YESNO))
		{
			// 선택한 항목 삭제
			ListBox_DeleteString(p_app->p_list_box, index);
			// 확장 데이터 해제
			free(p_data);
			// 현재 항목수를 얻음.
			int count = ListBox_GetCount(p_app->p_list_box);
			// 지워진 항목이 마지막 위치가 아니면 index 위치에 선택을 표시
			// 마지막 위치라면 index-1 위치에 선택을 표시함
			ListBox_SetCurSel(p_app->p_list_box, index);
		}
	}
}

// 리스트 박스의 항목 선택을 변경하면 호출되는 함수
void OnListBoxSelChange()
{
	// 프로그램 내부 데이터 주소를 얻음
	AD* p_app = (AD*)GetAppData();
	// 사용자가 선택한 항목의 위치
	int index = ListBox_GetCurSel(p_app->p_list_box);
	// 원본 데이터 주소
	SSD* p_data = (SSD*)ListBox_GetItemDataPtr(p_app->p_list_box, index);
	// 학생의 이름
	SetCtrlName(FindControl(1000), p_data->student_name);
	// 학번
	SetIntDataToControl(1001, p_data->student_id);
	// c언어 점수
	SetIntDataToControl(1002, p_data->score_c);
	// C++ 점수
	SetIntDataToControl(1003, p_data->score_cpp);
	// C# 점수
	SetIntDataToControl(1004, p_data->score_csharp);
}

// 컨트롤을 조작했을 때 호출할 함수 만들기
void OnCommand(INT32 a_ctrl_id, INT32 a_notify_code, void* ap_ctrl)
{
	// '추가' 버튼을 누른 경우
	if (a_ctrl_id == 1010)
		AddScore();
	// '변경' 버튼을 누른 경우
	else if (a_ctrl_id == 1011)
		ModifyScore();
	// '삭제' 버튼을 누른 경우
	else if (a_ctrl_id == 1012)
		DeleteScore();
	// 리스트 박스 상태 변화
	else if (a_ctrl_id == 1020) {
		if (a_notify_code == LBN_SELCHANGE)
			OnListBoxSelChange();
	}
}

// 학생들의 성적을 파일에 저장하는 함수
void SaveScoreDataToFile(AD* ap_app)
{
	// 파일을 열어서 사용할 파일 포인터
	FILE* p_file = NULL;
	// 바이너리 쓰기 모드로 엶.
	if (0 == fopen_s(&p_file, "score.txt", "wb") && p_file) {
		SSD* p_data;
		// 리스트 박스에 추가된 항목의 수를 얻음.
		int count = ListBox_GetCount(ap_app->p_list_box);
		// 항목의 수를 파일에 기록
		fwrite(&count, sizeof(int), 1, p_file);

		for (int i = 0; i < count; ++i) {
			// i번째 항목에 추가되어 있는 주소를 얻음.
			p_data = (SSD*)ListBox_GetItemDataPtr(ap_app->p_list_box, i);
			// 성적 정보 한 개를 파일에 기록
			fwrite(p_data, sizeof(SSD), 1, p_file);
		}
		fclose(p_file);
	}
}

// 모든 성적 데이터를 삭제하는 함수
void DeleteAllScoreData(AD* ap_app)
{
	SSD* p_data;
	// 리스트 박스에 추가된 항목의 수를 얻음
	int count = ListBox_GetCount(ap_app->p_list_box);
	// 리스트 박스의 항목수만큼 반복하면서 각 항목에 저장된 추가 메모리를 해제
	for (short i = 0; i < count; ++i)
	{
		// i번째 항목에 추가되어 있는 주소를 얻음
		p_data = (SSD*)ListBox_GetItemDataPtr(ap_app->p_list_box, i);
		// 추가 할당된 메모리 해제
		free(p_data);
	}
	// 리스트 박스에 추가된 모든 항목 제거
	ListBox_ResetContent(ap_app->p_list_box);
}

// 윈도우가 종료될 때 호출될 함수
void OnDestroy()
{
	// 프로그램 내부 데이터 주소를 얻음.
	AD* p_app = (AD*)GetAppData();
	// 성적을 파일에 저장
	SaveScoreDataToFile(p_app);
	// 성적 저장을 위해 할당했던 메모리 해제
	DeleteAllScoreData(p_app);
}

CMD_USER_MESSAGE(OnCommand, OnDestroy, NULL)

// 각 출력 항목의 위치 테이블
int g_pos[8] = { 6, 60, 150, 220, 285, 360, 435, 508 };

// ListBox의 항목을 그리는 함수(이 함수는 ListBox에 추가된 항목 수만큼 호출)
void DrawScoreItem(int index, char* ap, int a_str_len, void* ap_data, int a_is_selected, RECT* ap_rect)
{
	if (a_is_selected) SelectPenObject(RGB(200, 255, 255));
	else SelectPenObject(RGB(62, 77, 104));
	SelectBrushObject(RGB(62, 77, 104));

	Rectangle(ap_rect->left, ap_rect->top, ap_rect->right, ap_rect->bottom);
	Line(0, ap_rect->bottom - 2, ap_rect->right, ap_rect->bottom - 2,
		RGB(172, 172, 180), 2, PS_DOT | PS_GEOMETRIC);

	int top = ap_rect->top + 2;
	SSD* p_data = (SSD*)ap_data;

	SelectFontObject("맑은 고딕", 15);
	TextOut(g_pos[0], top, RGB(200, 232, 255), p_data->student_name);
	TextOut(g_pos[1], top, RGB(228, 228, 232), "%2d", p_data->student_id);
	// %4d  %6d  %7d
	SetTextColor(RGB(100, 228, 100));
	TextOut(g_pos[2], top, "%3d", p_data->score_c);
	TextOut(g_pos[3], top, "%3d", p_data->score_cpp);
	TextOut(g_pos[4], top, "%3d", p_data->score_csharp);

	//%8d  %7d" "%9c"
	SetTextColor(RGB(228, 228, 100));
	TextOut(g_pos[5], top, "%d", p_data->score_sum);
	TextOut(g_pos[6], top, "%d", p_data->score_avg);
	TextOut(g_pos[7], top, "%c", p_data->grade);


	int sx = g_pos[7] + 65;
	Rectangle(sx, top, sx + 102, ap_rect->bottom - 2, RGB(128, 128, 30), RGB(64, 64, 32));
	Rectangle(sx + 1, top + 1, sx + p_data->score_sum / 3, ap_rect->bottom - 3, RGB(248, 240, 120), RGB(200, 200, 0));
}

// 파일에서 성적 정보를 가져와서 리스트 박스에 추가하는 함수
void LoadScoreDataFromFile(AD* ap_app)
{
	// 파일을 열어서 사용할 파일 포인터
	FILE* p_file = NULL;
	// 바이너리 읽기 모드로 엶.
	if (0 == fopen_s(&p_file, "score.txt", "rb") && p_file) {
		int count = 0;
		// 항목의 수를 파일에서 읽음.
		fread(&count, sizeof(int), 1, p_file);
		SSD* p_data;
		for (int i = 0; i < count; ++i) {
			// 성적을 저장할 메모리 할당
			p_data = (SSD*)malloc(sizeof(SSD));
			// 성적 정보 한 개를 파일에서 읽음.
			fread(p_data, sizeof(SSD), 1, p_file);
			// 읽은 정보를 성적 목록에 추가
			ListBox_SetItemDataPtrEx(ap_app->p_list_box, -1, "", p_data, 0);
		}
		fclose(p_file);
	}
}

// 프로그램 메인 코드
int main()
{
	// 작업 영역의 폭: 460 * 300 설정
	ChangeWorkSize(750, 350);
	// 그리기 영역을 RGB(80, 162, 232) 색으로 지정
	Clear(0, RGB(72, 87, 114));
	// 데이터를 저장할 내부 메모리 할당
	AD* p_app = (AD*)CreateAppData(sizeof(AD));
	// 상단 과목 제목 배열 지정
	const char* p_titles[8] = { "이름","학번","C언어", "C++", "C#", "총점", "평균", "학점" };
	// 사용할 글꼴 지정
	SelectFontObject("맑은 고딕", 15, 0);
	// 텍스트 색상 지정
	SetTextColor(RGB(218, 248, 248));
	for (short i = 0; i < 5; ++i)
	{
		// 입력할 정보 이름을 출력
		TextOut(19 + i * 60, 9, p_titles[i]);
		// 성적을 입력할 에디트 컨트롤 생성
		CreateEdit(12 + i * 60, 32, 56, 22, 1000 + i, 0);
	}
	// 입력한 성적을 리스트 박스에 추가할 버튼 생성
	CreateButton("추가", 330, 25, 56, 30, 1010);
	CreateButton("변경", 390, 25, 56, 30, 1011);
	CreateButton("삭제", 450, 25, 56, 30, 1012);
	// 직사각형 출력
	Rectangle(10, 62, 700, 86, RGB(122, 137, 164), RGB(92, 107, 134));
	// 출력 정보 이름 출력
	for (int i = 0; i < 8; ++i)
	{
		TextOut(19 + i * 70, 65, p_titles[i]);
	}
	// 성적을 출력할 리스트 박스 생성
	p_app->p_list_box = CreateListBox(10, 90, 690, 200, 1020, DrawScoreItem);
	// 리스트 박스 항목의 높이를 지정
	ListBox_SetItemHeight(p_app->p_list_box, 22);
	// 성적 정보를 파일에서 읽어 리스트 박스에 추가함.
	LoadScoreDataFromFile(p_app);
	// 구성된 정보를 윈도우에 출력
	ShowDisplay();
	// 프로그램 종료
	return 0;
}
