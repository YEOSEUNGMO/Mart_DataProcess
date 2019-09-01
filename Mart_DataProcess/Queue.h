#ifndef QUEUE_H
#define QUEUE_H
#include "Record.h"
#include <fstream>
#include <string>

/*
LinkedList�� ������ ��������Դϴ�.
����� ����,����
Front,Rear�� �ּ� ��ȯ
Search front -> rear
��������
File ������� ���� �����ڿ������̵��� ���ֽ��ϴ�.
*/

#pragma pack(push,1)
class Queue
{
private:
	Record * front, *rear;
	int len;
public:
	Queue();
	Queue(const Queue &a);

	void New_node(Record &data);		//New Node Rear
	void Delete_node(Record *data);		//Middle Delete
	void Delete_node(void);				//Front Delete
	void Delete_All(void);
	Record* Search_node(Record &data);	//Search Node
	void Reinput_node(Record& data, int Quantity);
	void Setting(HWND hDlg);
	//Quantity Change
	int Sell_node(Record& data, int Quantity);
	Record* GetFront(void) const;
	Record* GetRear(void) const;

	int GetLength(void) {
		return len;
	}

	void OrderSort(void);				//Buble Sort

	void Print(void);					//Console Print
	
	friend ofstream& operator<<(ofstream& os, Queue &list);
	//File Input
	friend ifstream& operator>>(ifstream& of, Queue &list);
	//File Output
	~Queue();
};

#pragma pack(pop)
#endif