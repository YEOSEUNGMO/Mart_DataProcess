#ifndef RECORD_H
#define RECORD_H

#include <Windows.h>
#include <iostream>

#define MAX_STRING 50
#define SAFEDLETLE(p) if(p) { delete p; p = nullptr; }
using namespace std;

/*
Record를 정의한 헤더 파일입니다.
꺼내쓰는것과 Swap이 정의되있습니다.
*/

#pragma pack(push,1)
class Record
{
private:
	int number, cost_price, selling_price, quantity;
	TCHAR item[MAX_STRING], name[MAX_STRING];
	Record *Rlink, *Llink;
public:
	Record();
	Record(Record &data);

	void SetNumber(int number);
	void SetCost_price(int cost_price);
	void SetSelling_price(int selling_price);
	void SetQuantity(int quantity);
	void SetItem(TCHAR *item);
	void SetName(TCHAR *name);
	void SetRlink(Record *Rlink);
	void SetLlink(Record *Llink);

	void SetLink(Record *R, Record *L);
	void SetLink(Record **R, Record **L);

	int GetNumber(void);
	int GetCost_price(void);
	int GetSelling_price(void);
	int GetQuantity(void);
	TCHAR* GetItem(void);
	TCHAR* GetName(void);
	Record* GetRlink(void);
	Record* GetLlink(void);

	void Swap(Record &a);

	void SetRecord(TCHAR *name, TCHAR *item, int quantity, int number, int cost_price, int selling_price);
	void SetRecord(Record data);

	~Record();
};

#pragma pack(pop)
#endif