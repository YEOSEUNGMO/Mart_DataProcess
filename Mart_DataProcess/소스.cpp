#include <windows.h>
#include <commctrl.h>
#include<stdlib.h>
#include "resource.h"

#include "Record.h"
#include "Queue.h"
#include "Table.h"
#include "File.hpp"
using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Dlg1(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Dlg2(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND 	 hwnd;
	MSG 	 msg;
	WNDCLASS WndClass;
	hInst = hInstance;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName =NULL;
	WndClass.lpszClassName = "Window Class Name";
	RegisterClass(&WndClass);
	hwnd = CreateWindow("Window Class Name", "Window Title Name",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

#define ID_BTNADD1 101
#define ID_BTNADD2 102
#define ID_BTNADD3 103

HWND hBtnAdd1, hBtnAdd2, hBtnAdd3;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hDlg = NULL;

	switch (iMsg)
	{
	case WM_CREATE:
		hBtnAdd1 = CreateWindow(TEXT("button"), TEXT("상품등록"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 50, 200, 50, hwnd, (HMENU)ID_BTNADD1, hInst, NULL);

		hBtnAdd2 = CreateWindow(TEXT("button"), TEXT("상품 재입고"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 125, 200, 50, hwnd, (HMENU)ID_BTNADD2, hInst, NULL);

		hBtnAdd3 = CreateWindow(TEXT("button"), TEXT("상품 판매"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 200, 200, 50, hwnd, (HMENU)ID_BTNADD3, hInst, NULL);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_BTNADD1:
			if (!IsWindow(hDlg))
			{
				hDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, Dlg1);
				ShowWindow(hDlg, SW_SHOW);
			}
			break;
		case ID_BTNADD2:
			if (!IsWindow(hDlg))
			{
				hDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hwnd, Dlg2);
				ShowWindow(hDlg, SW_SHOW);
			}
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void MakeColumn(HWND hDlg)
{
	char *name[6] = { (char*)"품목",  (char*)"품명",(char*)"품번", (char*)"수량", (char*)"원가", (char*)"판매가" };
	LVCOLUMN lvCol = { 0, };
	HWND hList;
	int i;
	hList = GetDlgItem(hDlg, IDC_LIST1);
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;//사용할 항목
	lvCol.fmt = LVCFMT_LEFT;//정렬방법(:왼쪽정렬)

	for (i = 0; i<6; i++)
	{
		lvCol.cx = 70;//한칸의 폭
		lvCol.pszText = name[i];
		lvCol.iSubItem = i;
		SendMessage(hList, LVM_INSERTCOLUMN, (WPARAM)i, (LPARAM)&lvCol);
	}


}

/*등록 함수*/
void InsertData(HWND hDlg, Table &database, Record data)
{
	int count;
	LVITEM item;
	HWND hList;
	char Category[20], Name[20], Number[20], Quantity[20], Cost_Price[20], Selling_Price[20];

	/*품목*/
	GetDlgItemText(hDlg, IDC_COMBO1, Category, 20);
	SetDlgItemText(hDlg, IDC_COMBO1, "");
	if (strcmp(Category, "") == 0) return;
	/*품명*/
	GetDlgItemText(hDlg, IDC_EDIT1, Name, 20);
	SetDlgItemText(hDlg, IDC_EDIT1, "");
	if (strcmp(Name, "") == 0) return;
	/*품번*/
	GetDlgItemText(hDlg, IDC_EDIT2, Number, 20);
	SetDlgItemText(hDlg, IDC_EDIT2, "");
	if (strcmp(Number, "") == 0) return;
	/*수량*/
	GetDlgItemText(hDlg, IDC_EDIT3, Quantity, 20);
	SetDlgItemText(hDlg, IDC_EDIT3, "");
	if (strcmp(Quantity, "") == 0) return;
	/*원가*/
	GetDlgItemText(hDlg, IDC_EDIT4, Cost_Price, 20);
	SetDlgItemText(hDlg, IDC_EDIT4, "");
	if (strcmp(Cost_Price, "") == 0) return;
	/*원가*/
	GetDlgItemText(hDlg, IDC_EDIT5, Selling_Price, 20);
	SetDlgItemText(hDlg, IDC_EDIT5, "");
	if (strcmp(Selling_Price, "") == 0) return;

	hList = GetDlgItem(hDlg, IDC_LIST1);
	count = ListView_GetItemCount(hList);
	item.mask = LVIF_TEXT;
	item.iItem = count;
	item.iSubItem = 0;
	item.pszText = Category;
	ListView_InsertItem(hList, &item);
	ListView_SetItemText(hList, count, 1, Name);
	ListView_SetItemText(hList, count, 2, Number);
	ListView_SetItemText(hList, count, 3, Quantity);
	ListView_SetItemText(hList, count, 4, Cost_Price);
	ListView_SetItemText(hList, count, 5, Selling_Price);

	data.SetItem(Category);
	data.SetNumber(atoi(Number));
	data.SetName(Name);
	data.SetQuantity(atoi(Quantity));
	data.SetCost_price(atoi(Cost_Price));
	data.SetSelling_price(atoi(Selling_Price));

	database.Add(data);
}

/*리스트 선택*/
int SelectItem(HWND hDlg, LPARAM lParam)
{
	LPNMLISTVIEW nlv;
	HWND hList;
	char Category[20], Name[20], Quantity[10];
	hList = GetDlgItem(hDlg, IDC_LIST1);
	nlv = (LPNMLISTVIEW)lParam;
	/*품목*/
	ListView_GetItemText(hList, nlv->iItem,0, Category, 20);
	SetDlgItemText(hDlg, IDC_COMBO1, Category);
	ListView_GetItemText(hList, nlv->iItem, 1, Name, 20);
	SetDlgItemText(hDlg, IDC_COMBO2, Name);
	return(nlv->iItem);
}
/*문자열 더하기*/
char* Char_Sum(char* A,char*B)
{
	int a, b,sum;
	char SUM[20];
	a = atoi(A);
	b = atoi(B);
	sum = a + b;
	itoa(sum, SUM, 10);
	return SUM;
}
/*상품 수정*/
void ModifyItem(HWND hDlg, int selection)
{
	static HWND hList;
	char  Category[20], Name[20],Quantity[20],New_Quantity[20];
	hList = GetDlgItem(hDlg, IDC_LIST1);
	GetDlgItemText(hDlg, IDC_COMBO1, Category, 20);
	GetDlgItemText(hDlg, IDC_COMBO2, Name, 20);
	GetDlgItemText(hDlg, IDC_EDIT1, New_Quantity, 20);
	ListView_GetItemText(hList, selection, 3, Quantity,20);
	strcpy(Quantity, Char_Sum(Quantity, New_Quantity));
	if (strcmp(Category, "") == 0) return;
	if (strcmp(Name, "") == 0) return;
	if (strcmp(Quantity, "") == 0) return;
	ListView_SetItemText(hList, selection, 0, Category);
	ListView_SetItemText(hList, selection, 1, Name);
	ListView_SetItemText(hList, selection, 3, Quantity);
	SetDlgItemText(hDlg, IDC_COMBO1, "");
	SetDlgItemText(hDlg, IDC_COMBO2, "");
	SetDlgItemText(hDlg, IDC_EDIT1, "");
	return;
}

/*삭제*/
//void DeleteItem(HWND hDlg, int selection)
//{
//	static HWND hList;
//	hList = GetDlgItem(hDlg, IDC_LIST1);
//	ListView_DeleteItem(hList, selection);
//	SetDlgItemText(hDlg, IDC_EDIT1, "");
//	SetDlgItemText(hDlg, IDC_EDIT2, "");
//	SetDlgItemText(hDlg, IDC_COMBO1, "");
//	return;
//}

#define UNSELECTED -1
INT_PTR CALLBACK Dlg1(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HWND  hCombo;
	hCombo = GetDlgItem(hDlg, IDC_COMBO1);
	static int selection;
	char *Category[7] = { (char*)"고기", (char*)"과일", (char*)"생필품", (char*)"야채", (char*)"유제품" , (char*)"음료" , (char*)"주류" };

	Table database;
	Record data;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		database.Load(7);
		selection = UNSELECTED;
		MakeColumn(hDlg);
		for (int i = 0; i < 7; i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)Category[i]);
		}

		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		case ID_INSERT:
			InsertData(hDlg, database, data);
			return 0;
		case IDCANCEL:
			database.Save(7);
			DestroyWindow(hDlg);
			hDlg = NULL;
			return 0;
		}
		break;
	}
	return 0;
}


#define UNSELECTED -1
INT_PTR CALLBACK Dlg2(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	LPNMHDR hdr;
	HWND hList, hCombo;
	hCombo = GetDlgItem(hDlg, IDC_COMBO1);
	static int selection;
	char *Category[7] = { (char*)"고기", (char*)"과일", (char*)"생필품", (char*)"야채", (char*)"유제품" , (char*)"음료" , (char*)"주류" };

	/*임시선언*/
	int count;
	LVITEM item;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		selection = UNSELECTED;
		MakeColumn(hDlg);
		for (int i = 0; i < 7; i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)Category[i]);
		}
		/*임시 등록*/
		hList = GetDlgItem(hDlg, IDC_LIST1);
		count = ListView_GetItemCount(hList);
		item.mask = LVIF_TEXT;
		item.iItem = count;
		item.iSubItem = 0;
		item.pszText = (LPSTR)"고기";
		ListView_InsertItem(hList, &item);
		ListView_SetItemText(hList, count, 1, (LPSTR)"돼지고기");
		ListView_SetItemText(hList, count, 2, (LPSTR)"001");
		ListView_SetItemText(hList, count, 3, (LPSTR)"10");
		ListView_SetItemText(hList, count, 4, (LPSTR)"1000");
		ListView_SetItemText(hList, count, 5, (LPSTR)"2000");
		return 1;

	case WM_NOTIFY:
		hdr = (LPNMHDR)lParam;
		hList = GetDlgItem(hDlg, IDC_LIST1);
		if (hdr->hwndFrom == hList && hdr->code == LVN_ITEMCHANGING)
			selection = SelectItem(hDlg, lParam);
		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_MODIFY:
			if (selection == UNSELECTED) break;
			ModifyItem(hDlg, selection);
			selection = UNSELECTED;
			return 0;
		case IDCANCEL:
			DestroyWindow(hDlg);
			hDlg = NULL;
			return 0;
		}
		break;
	}
	return 0;
}