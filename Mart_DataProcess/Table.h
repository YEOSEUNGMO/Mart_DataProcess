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
	void Delet(Record &data);		//생각 귀찮
	void Reinput(Record &data, int Quantity);
	void Present(HWND hDlg);

	void Save(int select);			//부분별로 저장하게 만듬
	void Load(int select);			//부분별로 꺼내오게 만듬
	void Print(void);				//Console Print

									/*
									void Sum_Cost(void);
									void Sum_Selling(void);

									double Avg_Cost(void);
									double Avg_Selling(void);

									void Search(int number);		//Ex)number = 100102
									추가적인 사항?
									*/

	~Table();
};

#pragma pack(pop)
#endif