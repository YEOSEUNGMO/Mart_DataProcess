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
INT_PTR CALLBACK Dlg3(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
HINSTANCE hInst;
LPCTSTR lpszClass = TEXT("��Ʈ���� �ý���");
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
	WndClass.lpszClassName = lpszClass;
	RegisterClass(&WndClass);
	hwnd = CreateWindow(lpszClass, lpszClass,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		300,
		400,
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
#define ID_BTNADD4 104

HWND hBtnAdd1, hBtnAdd2, hBtnAdd3, hBtnAdd4;
int Total_Sales,Total_Profit;//�� ����,�� ������
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hDlg = NULL;
	char str[100];
	switch (iMsg)
	{
	case WM_CREATE:
		hBtnAdd1 = CreateWindow(TEXT("button"), TEXT("��ǰ ���"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 50, 200, 50, hwnd, (HMENU)ID_BTNADD1, hInst, NULL);

		hBtnAdd2 = CreateWindow(TEXT("button"), TEXT("��ǰ ���԰�"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 125, 200, 50, hwnd, (HMENU)ID_BTNADD2, hInst, NULL);

		hBtnAdd3 = CreateWindow(TEXT("button"), TEXT("��ǰ �Ǹ�"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 200, 200, 50, hwnd, (HMENU)ID_BTNADD3, hInst, NULL);

		hBtnAdd4 = CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 275, 200, 50, hwnd, (HMENU)ID_BTNADD4, hInst, NULL);

		Total_Sales = 0;
		Total_Profit = 0;
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
		case ID_BTNADD3:
			if (!IsWindow(hDlg))
			{
				hDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hwnd, Dlg3);
				ShowWindow(hDlg, SW_SHOW);
			}
			break;
		case ID_BTNADD4:
			wsprintf(str, TEXT("�� ������ %d�� �Դϴ�.\n�� �������� %d�� �Դϴ�."),Total_Sales,Total_Profit);
			MessageBox(hwnd, str, "����", MB_OK);
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
	char *name[6] = { (char*)"ǰ��",  (char*)"ǰ��",(char*)"ǰ��", (char*)"����", (char*)"����", (char*)"�ǸŰ�" };
	LVCOLUMN lvCol = { 0, };
	HWND hList;
	int i;
	hList = GetDlgItem(hDlg, IDC_LIST1);
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;//����� �׸�
	lvCol.fmt = LVCFMT_LEFT;//���Ĺ��(:��������)

	for (i = 0; i<6; i++)
	{
		lvCol.cx = 70;//��ĭ�� ��
		lvCol.pszText = name[i];
		lvCol.iSubItem = i;
		SendMessage(hList, LVM_INSERTCOLUMN, (WPARAM)i, (LPARAM)&lvCol);
	}


}

/*��� �Լ�*/
void InsertData(HWND hDlg, Table &database, Record data)
{
	int count;
	LVITEM item;
	HWND hList;
	char Category[20], Name[20], Number[20], Quantity[20], Cost_Price[20], Selling_Price[20];

	/*ǰ��*/
	GetDlgItemText(hDlg, IDC_COMBO1, Category, 20);
	SetDlgItemText(hDlg, IDC_COMBO1, "");
	if (strcmp(Category, "") == 0) return;
	/*ǰ��*/
	GetDlgItemText(hDlg, IDC_EDIT1, Name, 20);
	SetDlgItemText(hDlg, IDC_EDIT1, "");
	if (strcmp(Name, "") == 0) return;
	/*ǰ��*/
	GetDlgItemText(hDlg, IDC_EDIT2, Number, 20);
	SetDlgItemText(hDlg, IDC_EDIT2, "");
	if (strcmp(Number, "") == 0) return;
	/*����*/
	GetDlgItemText(hDlg, IDC_EDIT3, Quantity, 20);
	SetDlgItemText(hDlg, IDC_EDIT3, "");
	if (strcmp(Quantity, "") == 0) return;
	/*����*/
	GetDlgItemText(hDlg, IDC_EDIT4, Cost_Price, 20);
	SetDlgItemText(hDlg, IDC_EDIT4, "");
	if (strcmp(Cost_Price, "") == 0) return;
	/*�ǸŰ�*/
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

/*����Ʈ ����*/
int SelectItem(HWND hDlg, LPARAM lParam)
{
	LPNMLISTVIEW nlv;
	HWND hList;
	TCHAR Category[20], Name[20], Number[20], Quantity[10];
	hList = GetDlgItem(hDlg, IDC_LIST1);
	nlv = (LPNMLISTVIEW)lParam;
	/*ǰ��*/
	ListView_GetItemText(hList, nlv->iItem,0, Category, 20);
	SetDlgItemText(hDlg, IDC_EDIT3, Category);
	ListView_GetItemText(hList, nlv->iItem, 1, Name, 20);
	SetDlgItemText(hDlg, IDC_EDIT4, Name);
	return(nlv->iItem);
}

/*���ڿ� ���� ���ϱ�*/
char* Char_Add(char* A,char*B)
{
	int a, b,add;
	char ADD[20];
	a = atoi(A);
	b = atoi(B);
	add = a + b;
	itoa(add, ADD, 10);
	return ADD;
}

/*���ڿ� ���� ����*/
char* Char_Sub(char* A, char*B)
{
	int a, b, sub;
	char SUB[20];
	a = atoi(A);
	b = atoi(B);
	sub = a - b;
	itoa(sub, SUB, 10);
	return SUB;
}

/*���� �Լ�*/
void Calculate(char* Cost_Price,char* Selling_Price,char* Quantity)//����,�ǸŰ�,�Ǹż���
{
	Total_Sales += atoi(Selling_Price) * atoi(Quantity);//�� ����+= �ǸŰ� * ����
	Total_Profit += (atoi(Selling_Price) - atoi(Cost_Price))*atoi(Quantity);//�� ������ += (�ǸŰ�-����)*����
}

/*��ǰ ����*/
void ModifyItem(HWND hDlg, int selection, Table &database, Record data,int op)//op:1 ���ϱ� / 2:����
{
	HWND hList;
	TCHAR  Category[20], Name[20], Number[20], Quantity[20], New_Quantity[20], Cost_Price[20], Selling_Price[20];
	hList = GetDlgItem(hDlg, IDC_LIST1);
	GetDlgItemText(hDlg, IDC_EDIT3, Category, 20);
	GetDlgItemText(hDlg, IDC_EDIT4, Name, 20);
	GetDlgItemText(hDlg, IDC_EDIT1, New_Quantity, 20);
	ListView_GetItemText(hList, selection, 2, Number, 20);//���� �޾ƿ���
	ListView_GetItemText(hList, selection, 3, Quantity,20);//���� �޾ƿ���
	ListView_GetItemText(hList, selection, 4, Cost_Price, 20);//���� �޾ƿ���
	ListView_GetItemText(hList, selection, 5, Selling_Price, 20);//�ǸŰ� �޾ƿ���
	if(op==1)//���ϱ�
		strcpy(Quantity, Char_Add(Quantity, New_Quantity));//Quantity(���� ����)���� New_Quantity(���� �Է��Ѽ���)�� ���ؼ� Quantity�� ����.
	else if (op == 2) {//����
		if (atoi(Char_Sub(Quantity, New_Quantity)) < 0) {
			MessageBox(hDlg, TEXT("��� �����մϴ�."), TEXT("��� ����"), MB_OK);
			return;
		}
		strcpy(Quantity, Char_Sub(Quantity, New_Quantity));//Quantity(���� ����)���� New_Quantity(���� �Է��Ѽ���)�� ���� Quantity�� ����.
		Calculate(Cost_Price, Selling_Price, New_Quantity);//�� �ǸŰ�,�� ������ ���� �Լ�
	}
	if (strcmp(Category, "") == 0) return;
	if (strcmp(Number, "") == 0) return;
	if (strcmp(Quantity, "") == 0) return;
	ListView_SetItemText(hList, selection, 0, Category);
	ListView_SetItemText(hList, selection, 1, Name);
	ListView_SetItemText(hList, selection, 3, Quantity);
	SetDlgItemText(hDlg, IDC_EDIT3, "");
	SetDlgItemText(hDlg, IDC_EDIT4, "");
	SetDlgItemText(hDlg, IDC_EDIT1, "");

	data.SetItem(Category);
	data.SetNumber(atoi(Number));
	if (op == 1) {
		database.Reinput(data, atoi(New_Quantity));
	}
	else if (op == 2) {
		database.Reinput(data, atoi(New_Quantity)*(-1));
	}
	return;
}

/*����*/
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

#define UNSELECTED1 -1
INT_PTR CALLBACK Dlg1(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HWND  hCombo;
	hCombo = GetDlgItem(hDlg, IDC_COMBO1);
	static int selection;
	char *Category[7] = { (char*)"���", (char*)"����", (char*)"����ǰ", (char*)"��ä", (char*)"����ǰ" , (char*)"����" , (char*)"�ַ�" };

	Table database;
	Record data;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		selection = UNSELECTED1;
		MakeColumn(hDlg);
		for (int i = 0; i < 7; i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)Category[i]);
		}
		database.Present(hDlg);
		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_INSERT:
			InsertData(hDlg, database, data);
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


#define UNSELECTED2 -1
INT_PTR CALLBACK Dlg2(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	LPNMHDR hdr;
	HWND hList, hEdit1, hEdit2;
	hEdit1 = GetDlgItem(hDlg, IDC_EDIT3);
	hEdit2 = GetDlgItem(hDlg, IDC_EDIT4);
	hList = GetDlgItem(hDlg, IDC_LIST1);
	static int selection;
	TCHAR *Category[7] = { (char*)"���", (char*)"����", (char*)"����ǰ", (char*)"��ä", (char*)"����ǰ" , (char*)"����" , (char*)"�ַ�" };

	Table database;
	Record data;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		selection = UNSELECTED2;
		MakeColumn(hDlg);
		database.Present(hDlg);
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
			if (selection == UNSELECTED2) break;
			ModifyItem(hDlg, selection, database, data, 1);
			selection = UNSELECTED2;
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

#define UNSELECTED3 -1
INT_PTR CALLBACK Dlg3(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	LPNMHDR hdr;
	HWND hList, hEdit1, hEdit2;
	hEdit1 = GetDlgItem(hDlg, IDC_EDIT3);
	hEdit2 = GetDlgItem(hDlg, IDC_EDIT4);
	hList = GetDlgItem(hDlg, IDC_LIST1);
	static int selection;
	char *Category[7] = { (char*)"���", (char*)"����", (char*)"����ǰ", (char*)"��ä", (char*)"����ǰ" , (char*)"����" , (char*)"�ַ�" };

	Table database;
	Record data;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		selection = UNSELECTED3;
		MakeColumn(hDlg);
		database.Present(hDlg);
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
			if (selection == UNSELECTED3) break;
			ModifyItem(hDlg, selection, database, data,2);
			selection = UNSELECTED3;
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