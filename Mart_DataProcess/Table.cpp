#include "Table.h"

Table::Table()
{
	Load(length);				//���ܰ� �༭ ���� ȣ��
}

void Table::OrSort(void)
{
	for (int i = 0; i < length; i++) {
		list[i].OrderSort();
	}
}

void Table::Add(Record &data)
{
	//����ġ ��ó�� �ϰ� �;����� ���� ���ڿ��̴�.

	if (lstrcmp(data.GetItem(), TEXT("���")) == 0) {
		list[0].New_node(data);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("����")) == 0) {
		list[1].New_node(data);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("����ǰ")) == 0) {
		list[2].New_node(data);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("��ä")) == 0) {
		list[3].New_node(data);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("����ǰ")) == 0) {
		list[4].New_node(data);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("����")) == 0) {
		list[5].New_node(data);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("�ַ�")) == 0) {
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
	if (lstrcmp(data.GetItem(), TEXT("���")) == 0) {
		list[0].Delete_node(list[0].Search_node(data));
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("����")) == 0) {
		list[1].Delete_node(list[1].Search_node(data));
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("����ǰ")) == 0) {
		list[2].Delete_node(list[2].Search_node(data));
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("��ä")) == 0) {
		list[3].Delete_node(list[3].Search_node(data));
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("����ǰ")) == 0) {
		list[4].Delete_node(list[4].Search_node(data));
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("����")) == 0) {
		list[5].Delete_node(list[5].Search_node(data));
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("�ַ�")) == 0) {
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
	if (lstrcmp(data.GetItem(), TEXT("���")) == 0) {
		list[0].Reinput_node(data, Quantity);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("����")) == 0) {
		list[1].Reinput_node(data, Quantity);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("����ǰ")) == 0) {
		list[2].Reinput_node(data, Quantity);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("��ä")) == 0) {
		list[3].Reinput_node(data, Quantity);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("����ǰ")) == 0) {
		list[4].Reinput_node(data, Quantity);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("����")) == 0) {
		list[5].Reinput_node(data, Quantity);
		return;
	}
	else if (lstrcmp(data.GetItem(), TEXT("�ַ�")) == 0) {
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

	TCHAR directory[MAX_PATH] = { 0 };				//���ϴ� ��ΰ�
	TCHAR buffer[MAX_PATH] = { 0 };					//������Ʈ ��ΰ�

	GetCurrentDirectory(MAX_PATH, directory);		//������Ʈ ��ΰ��� ����
	lstrcpy(buffer, directory);						//������Ʈ ��ΰ��� ����

	CreateDirectory(TEXT("Test"), NULL);			//������Ʈ�� Test�� ���� ����
	lstrcat(directory, TEXT("\\Test"));				//Test������ ������ ���ڿ�����
	SetCurrentDirectory(directory);					//Test������ ����


													//�����͵��� ���Ͽ� �����Ű�� switch���Դϴ�.
	switch (select) {
	case 0:						//���
		file.Save_File(list[0], "Meet");
		break;
	case 1:						//����
		file.Save_File(list[1], "Fruit");
		break;
	case 2:						//����ǰ
		file.Save_File(list[2], "Necessaries");
		break;
	case 3:						//��ä
		file.Save_File(list[3], "Vegetable");
		break;
	case 4:						//����ǰ
		file.Save_File(list[4], "Milk_products");
		break;
	case 5:						//����
		file.Save_File(list[5], "Drink");
		break;
	case 6:						//�ַ�
		file.Save_File(list[6], "Alcohol");
		break;
	default:					//���δ�
		file.Save_File(list[0], "Meet");
		file.Save_File(list[1], "Fruit");
		file.Save_File(list[2], "Necessaries");
		file.Save_File(list[3], "Vegetable");
		file.Save_File(list[4], "Milk_products");
		file.Save_File(list[5], "Drink");
		file.Save_File(list[6], "Alcohol");
		break;
	}

	SetCurrentDirectory(buffer);				//�ʱ� ������Ʈ ��ΰ����� �̵�
}

void Table::Load(int select)
{
	File<Queue> file;

	TCHAR directory[MAX_PATH] = { 0 };				//���ϴ� ��ΰ�
	TCHAR buffer[MAX_PATH] = { 0 };					//������Ʈ ��ΰ�

	GetCurrentDirectory(MAX_PATH, directory);		//������Ʈ ��ΰ��� ����
	lstrcpy(buffer, directory);						//������Ʈ ��ΰ��� ����

	lstrcat(directory, TEXT("\\Test"));				//Test������ ������ ���ڿ�����
	SetCurrentDirectory(directory);					//Test������ ����

	switch (select) {
	case 0:						//���
		file.Load_File(list[0], "Meet");
		break;
	case 1:						//����
		file.Load_File(list[1], "Fruit");
		break;
	case 2:						//����ǰ
		file.Load_File(list[2], "Necessaries");
		break;
	case 3:						//��ä
		file.Load_File(list[3], "Vegetable");
		break;
	case 4:						//����ǰ
		file.Load_File(list[4], "Milk_products");
		break;
	case 5:						//����
		file.Load_File(list[5], "Drink");
		break;
	case 6:						//�ַ�
		file.Load_File(list[6], "Alcohol");
		break;
	default:					//���δ�
		file.Load_File(list[0], "Meet");
		file.Load_File(list[1], "Fruit");
		file.Load_File(list[2], "Necessaries");
		file.Load_File(list[3], "Vegetable");
		file.Load_File(list[4], "Milk_products");
		file.Load_File(list[5], "Drink");
		file.Load_File(list[6], "Alcohol");
		break;
	}

	SetCurrentDirectory(buffer);				//�ʱ� ������Ʈ ��ΰ����� �̵�
}

void Table::Print(void)
{
	//Console���� Print
	for (int i = 0; i < length; i++) {
		list[i].Print();
	}
}


Table::~Table()
{
	Save(length);				//���ܰ��༭ ����ȣ��
	for (int i = 0; i < length; i++) {
		list[i].Delete_All();
	}
}
