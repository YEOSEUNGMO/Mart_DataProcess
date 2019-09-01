#include "Table.h"

Table::Table()
{
	Load(length);				//예외값 줘서 전부 호출
}

void Table::OrSort(void)
{
	for (int i = 0; i < length; i++) {
		list[i].OrderSort();
	}
}

void Table::Add(Record &data)
{
	//스위치 문처럼 하고 싶었으나 상대는 문자열이다.

	if (lstrcmp(data.GetItem(), TEXT("고기")) == 0) {
		list[0].New_node(data);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("과일")) == 0) {
		list[1].New_node(data);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("생필품")) == 0) {
		list[2].New_node(data);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("야채")) == 0) {
		list[3].New_node(data);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("유제품")) == 0) {
		list[4].New_node(data);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("음료")) == 0) {
		list[5].New_node(data);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("주류")) == 0) {
		list[6].New_node(data);
		return;
	}
	else {
		cout << "Table Add function Not able" << endl;
		return;
	}
}

void Table::Delet(Record &data)
{
	if (lstrcmp(data.GetItem(), TEXT("고기")) == 0) {
		list[0].Delete_node(list[0].Search_node(data));
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("과일")) == 0) {
		list[1].Delete_node(list[1].Search_node(data));
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("생필품")) == 0) {
		list[2].Delete_node(list[2].Search_node(data));
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("야채")) == 0) {
		list[3].Delete_node(list[3].Search_node(data));
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("유제품")) == 0) {
		list[4].Delete_node(list[4].Search_node(data));
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("음료")) == 0) {
		list[5].Delete_node(list[5].Search_node(data));
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("주류")) == 0) {
		list[6].Delete_node(list[6].Search_node(data));
		return;
	}
	else {
		//cout << "Table Delet function Not able" << endl;
		for (int i = 0; i < 7; i++) {
			list[i].Delete_All();
		}
		return;
	}
}

void Table::Reinput(Record & data, int Quantity)
{
	if (lstrcmp(data.GetItem(), TEXT("고기")) == 0) {
		list[0].Reinput_node(data, Quantity);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("과일")) == 0) {
		list[1].Reinput_node(data, Quantity);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("생필품")) == 0) {
		list[2].Reinput_node(data, Quantity);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("야채")) == 0) {
		list[3].Reinput_node(data, Quantity);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("유제품")) == 0) {
		list[4].Reinput_node(data, Quantity);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("음료")) == 0) {
		list[5].Reinput_node(data, Quantity);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("주류")) == 0) {
		list[6].Reinput_node(data, Quantity);
		return;
	}
	else {
		cout << "Table Input function Not able" << endl;
		return;
	}
}

void Table::Present(HWND hDlg)
{
	for (int i = 0; i < 7; i++) {
		list[i].Setting(hDlg);
	}
}

void Table::Save(int select)
{
	File<Queue> file;

	TCHAR directory[MAX_PATH] = { 0 };				//변하는 경로값
	TCHAR buffer[MAX_PATH] = { 0 };					//프로젝트 경로값

	GetCurrentDirectory(MAX_PATH, directory);		//프로젝트 경로값을 받음
	lstrcpy(buffer, directory);						//프로젝트 경로값을 저장

	CreateDirectory(TEXT("Test"), NULL);			//프로젝트에 Test란 폴더 생성
	lstrcat(directory, TEXT("\\Test"));				//Test폴더에 접근할 문자열생성
	SetCurrentDirectory(directory);					//Test폴더에 접근


													//데이터들을 파일에 저장시키는 switch문입니다.
	switch (select) {
	case 0:						//고기
		file.Save_File(list[0], "Meet");
		break;
	case 1:						//과일
		file.Save_File(list[1], "Fruit");
		break;
	case 2:						//생필품
		file.Save_File(list[2], "Necessaries");
		break;
	case 3:						//야채
		file.Save_File(list[3], "Vegetable");
		break;
	case 4:						//유제품
		file.Save_File(list[4], "Milk_products");
		break;
	case 5:						//음료
		file.Save_File(list[5], "Drink");
		break;
	case 6:						//주류
		file.Save_File(list[6], "Alcohol");
		break;
	default:					//전부다
		file.Save_File(list[0], "Meet");
		file.Save_File(list[1], "Fruit");
		file.Save_File(list[2], "Necessaries");
		file.Save_File(list[3], "Vegetable");
		file.Save_File(list[4], "Milk_products");
		file.Save_File(list[5], "Drink");
		file.Save_File(list[6], "Alcohol");
		break;
	}

	SetCurrentDirectory(buffer);				//초기 프로젝트 경로값으로 이동
}

void Table::Load(int select)
{
	File<Queue> file;

	TCHAR directory[MAX_PATH] = { 0 };				//변하는 경로값
	TCHAR buffer[MAX_PATH] = { 0 };					//프로젝트 경로값

	GetCurrentDirectory(MAX_PATH, directory);		//프로젝트 경로값을 받음
	lstrcpy(buffer, directory);						//프로젝트 경로값을 저장

	lstrcat(directory, TEXT("\\Test"));				//Test폴더에 접근할 문자열생성
	SetCurrentDirectory(directory);					//Test폴더에 접근

	switch (select) {
	case 0:						//고기
		file.Load_File(list[0], "Meet");
		break;
	case 1:						//과일
		file.Load_File(list[1], "Fruit");
		break;
	case 2:						//생필품
		file.Load_File(list[2], "Necessaries");
		break;
	case 3:						//야채
		file.Load_File(list[3], "Vegetable");
		break;
	case 4:						//유제품
		file.Load_File(list[4], "Milk_products");
		break;
	case 5:						//음료
		file.Load_File(list[5], "Drink");
		break;
	case 6:						//주류
		file.Load_File(list[6], "Alcohol");
		break;
	default:					//전부다
		file.Load_File(list[0], "Meet");
		file.Load_File(list[1], "Fruit");
		file.Load_File(list[2], "Necessaries");
		file.Load_File(list[3], "Vegetable");
		file.Load_File(list[4], "Milk_products");
		file.Load_File(list[5], "Drink");
		file.Load_File(list[6], "Alcohol");
		break;
	}

	SetCurrentDirectory(buffer);				//초기 프로젝트 경로값으로 이동
}

void Table::Print(void)
{
	//Console전용 Print
	for (int i = 0; i < length; i++) {
		list[i].Print();
	}
}


Table::~Table()
{
	Save(length);				//예외값줘서 전부호출
	for (int i = 0; i < length; i++) {
		list[i].Delete_All();
	}
}
