#include <Windows.h>
#include <commctrl.h>

#include "Queue.h"
#include "resource.h"

Queue::Queue()
{
	front = nullptr;
	rear = nullptr;
	len = 0;
}

Queue::Queue(const Queue &a)
{
	front = a.front;
	rear = a.rear;
	len = a.len;
}

void Queue::New_node(Record &data)
{
	Record *temp = new Record;

	temp->SetRecord(data);

	//temp->SetSelling_price(temp->GetCost_price());
	//이익률 계산 기준정해야함

	//std::cout << "(" << len << ")" << "New_node function Start" << std::endl;
	len += 1;
	if (rear == nullptr) {
		rear = temp;
		front = temp;
		return;
	}

	rear->SetRlink(temp);
	rear = temp;
}

void Queue::Delete_node(Record *data)
{
	Record *temp = data;

	if (temp == nullptr) {
		front = nullptr;
		rear = nullptr;
		return;
	}

	//std::cout << "Delete_node function Start" << std::endl;
	len -= 1;
	temp->GetLlink()->SetRlink(temp->GetRlink());		//temp->Llink->Rlink = temp->Rlink;
	temp->GetRlink()->SetLlink(temp->GetLlink());		//temp->Rlink->Llink = temp->Llink;
														//중간에 있는 노드를 고립시키고
														//양옆에 끊겨진 노드를 잇는다.

	SAFEDLETLE(temp);
}

Record* Queue::Search_node(Record & data)
{
	int number = data.GetNumber();
	Record *temp = front;

	while (temp != nullptr) {
		if (temp->GetNumber() == number) {
			return temp;
		}
		temp = temp->GetRlink();
	}

	return nullptr;
}

void Queue::Reinput_node(Record & data, int Quantity)
{
	Record *temp = Search_node(data);

	if (temp == nullptr) {
		//(NULL,TEXT("Reinput is errer"),TEXT("Errer"),MB_OK);
		return;
	}

	temp->SetQuantity(temp->GetQuantity() + Quantity);

	return;
}

void Queue::Setting(HWND hDlg)
{
	int count;
	LVITEM item;
	HWND hList;
	TCHAR Category[20], Name[20], Number[20], Quantity[20], Cost_Price[20], Selling_Price[20];
	Record* temp = front;

	while (temp != nullptr) {
		wsprintf(Name, "%s", temp->GetName());
		wsprintf(Number, "%d", temp->GetNumber());
		wsprintf(Quantity, "%d", temp->GetQuantity());
		wsprintf(Cost_Price, "%d", temp->GetCost_price());
		wsprintf(Selling_Price, "%d", temp->GetSelling_price());

		hList = GetDlgItem(hDlg, IDC_LIST1);
		count = ListView_GetItemCount(hList);
		item.mask = LVIF_TEXT;
		item.iItem = count;
		item.iSubItem = 0;
		item.pszText = temp->GetItem();
		ListView_InsertItem(hList, &item);
		ListView_SetItemText(hList, count, 1, Name);
		ListView_SetItemText(hList, count, 2, Number);
		ListView_SetItemText(hList, count, 3, Quantity);
		ListView_SetItemText(hList, count, 4, Cost_Price);
		ListView_SetItemText(hList, count, 5, Selling_Price);
		
		temp = temp->GetRlink();
	}
}

void Queue::Delete_node(void)
{
	Record *temp = front;

	if (front == nullptr) {
		front = nullptr;
		rear = nullptr;
		return;
	}

	//std::cout << "Delete_node function Start" << std::endl;
	len -= 1;
	front = front->GetRlink();
	SAFEDLETLE(temp);
}

void Queue::Delete_All(void)
{
	Record *temp = front;

	while (front != nullptr) {
		Delete_node();
		temp = front;
	}
	cout << len << " Node All_Delete" << endl;
}

int Queue::Sell_node(Record & data, int Quantity)
{
	Record *temp = Search_node(data);
	int number;

	number = temp->GetQuantity() - Quantity;
	if (number <= 0) {
		Delete_node(temp);
		return 0;
	}
	number = temp->GetSelling_price() * number;

	return number;
}

Record * Queue::GetFront(void) const
{
	return front;
}

Record * Queue::GetRear(void) const
{
	return rear;
}

void Queue::OrderSort(void)
{
	/*
	버블정렬을 하는 형식과 동일합니다.
	아마도?
	*/
	Record *i_temp, *j_temp;
	bool button = false;

	std::cout << "OrderSort function Start" << std::endl;

	i_temp = front;
	while (i_temp != nullptr) {

		j_temp = i_temp;					//첫번째 대상 선정
		while (j_temp != nullptr) {
			if (j_temp->GetNumber() <= i_temp->GetNumber()) {
				j_temp->Swap(*i_temp);		//버블정렬
				button = true;
			}
			j_temp = j_temp->GetRlink();
		}
		if (button == false) {				//정렬을 할 필요가 없을때
			std::cout << "Jump" << std::endl;
			break;							//작업을 생략한다.
		}

		i_temp = i_temp->GetRlink();
	}

	std::cout << "OrderSort function End" << std::endl;
}

void Queue::Print(void)
{
	Record *temp = front;

	std::cout << "Print function Start" << std::endl;

	while (temp != nullptr) {
		std::cout << temp->GetNumber() << std::ends;
		temp = temp->GetRlink();
	}
	std::cout << std::endl;

	std::cout << "Print function End" << std::endl;
}
// Number만 출력

Queue::~Queue()
{
	/*
	복사생성자때문에 Node_Delete작업을
	따로 함수로 빼둠
	*/
}

ofstream& operator<<(ofstream &os, Queue &list)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	Record *temp = list.front;

	list.OrderSort();

	while (temp != nullptr) {
		os << temp->GetItem() << " "
			<< temp->GetNumber() << " "
			<< temp->GetQuantity() << " "
			<< temp->GetName() << " "
			<< temp->GetCost_price() << " "
			<< temp->GetSelling_price() << endl;

		temp = temp->GetRlink();
	}

	return os;
}

ifstream &operator>>(ifstream &of, Queue &list)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	Record temp;
	TCHAR strtemp[MAX_STRING];
	string str;
	int number;

	list.OrderSort();

	while (!of.eof()) {
		getline(of, str, ' ');
		for (int i = 0; i < str.length(); i++) {
			strtemp[i] = (TCHAR)str[i];
		}
		strtemp[str.length()] = '\0';
		temp.SetItem(strtemp);

		getline(of, str, ' ');
		for (int i = 0; i < str.length(); i++) {
			strtemp[i] = (TCHAR)str[i];
		}
		strtemp[str.length()] = '\0';
		number = atoi(strtemp);
		temp.SetNumber(number);

		getline(of, str, ' ');
		for (int i = 0; i < str.length(); i++) {
			strtemp[i] = (TCHAR)str[i];
		}
		strtemp[str.length()] = '\0';
		number = atoi(strtemp);
		temp.SetQuantity(number);

		getline(of, str, ' ');
		for (int i = 0; i < str.length(); i++) {
			strtemp[i] = (TCHAR)str[i];
		}
		strtemp[str.length()] = '\0';
		temp.SetName(strtemp);

		getline(of, str, ' ');
		for (int i = 0; i < str.length(); i++) {
			strtemp[i] = (TCHAR)str[i];
		}
		strtemp[str.length()] = '\0';
		number = atoi(strtemp);
		temp.SetCost_price(number);

		getline(of, str, '\n');
		for (int i = 0; i < str.length(); i++) {
			strtemp[i] = (TCHAR)str[i];
		}
		strtemp[str.length()] = '\0';
		number = atoi(strtemp);
		temp.SetSelling_price(number);

		if (temp.GetNumber() != 0) {
			list.New_node(temp);
		}
	}

	return of;
}