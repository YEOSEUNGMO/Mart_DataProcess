#ifndef TABLE_H
#define TABLE_H

#include "Queue.h"
#include "File.hpp"
#define length 7

#pragma pack(push,1)
class Table
{
private:
	Queue list[length];
public:
	Table();

	void OrSort(void);
	void Add(Record &data);
	void Delet(Record &data);		//���� ����
	void Reinput(Record &data, int Quantity);
	void Present(HWND hDlg);

	void Save(int select);			//�κк��� �����ϰ� ����
	void Load(int select);			//�κк��� �������� ����
	void Print(void);				//Console Print

									/*
									void Sum_Cost(void);
									void Sum_Selling(void);

									double Avg_Cost(void);
									double Avg_Selling(void);

									void Search(int number);		//Ex)number = 100102
									�߰����� ����?
									*/

	~Table();
};

#pragma pack(pop)
#endif