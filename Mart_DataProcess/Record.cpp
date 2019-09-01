#include "Record.h"

Record::Record()
{
	number = 0;
	cost_price = 0;
	selling_price = 0;
	quantity = 0;

	lstrcpy(item, (TCHAR *)TEXT("품목"));
	lstrcpy(name, (TCHAR *)TEXT("이름"));

	Rlink = nullptr;
	Llink = nullptr;
}

Record::Record(Record & data)
{
	this->cost_price = data.cost_price;
	this->selling_price = data.selling_price;
	this->number = data.number;
	this->quantity = data.quantity;
	lstrcpy(this->item, data.item);
	lstrcpy(this->name, data.name);

	Rlink = nullptr;
	Llink = nullptr;
}

void Record::SetLink(Record *R, Record *L)
{
	R->SetRlink(L);
	L->SetLlink(R);
}

void Record::SetLink(Record **R, Record **L)
{
	(*R)->SetRlink(*L);
	(*L)->SetLlink(*R);
}

void Record::SetNumber(int number)
{
	this->number = number;
}

void Record::SetCost_price(int cost_price)
{
	this->cost_price = cost_price;
}

void Record::SetSelling_price(int selling_price)
{
	this->selling_price = selling_price;
}

void Record::SetItem(TCHAR * item)
{
	lstrcpy(this->item, item);
}

void Record::SetQuantity(int quantity)
{
	this->quantity = quantity;
}

void Record::SetName(TCHAR * name)
{
	lstrcpy(this->name, name);
}

void Record::SetRlink(Record * Rlink)
{
	this->Rlink = Rlink;
}

void Record::SetLlink(Record * Llink)
{
	this->Llink = Llink;
}

int Record::GetNumber(void)
{
	return number;
}

int Record::GetCost_price(void)
{
	return cost_price;
}

int Record::GetSelling_price(void)
{
	return selling_price;
}

int Record::GetQuantity(void)
{
	return quantity;
}

TCHAR * Record::GetItem(void)
{
	return item;
}

TCHAR * Record::GetName(void)
{
	return name;
}

Record * Record::GetRlink(void)
{
	return Rlink;
	return nullptr;
}

Record * Record::GetLlink(void)
{
	return Llink;
	return nullptr;
}

void Record::SetRecord(TCHAR * name, TCHAR * item, int quantity, int number, int cost_price, int selling_price)
{
	SetNumber(number);
	SetCost_price(cost_price);
	SetSelling_price(selling_price);
	SetName(name);
	SetItem(item);
	SetQuantity(quantity);
}

void Record::SetRecord(Record data)
{
	SetNumber(data.number);
	SetCost_price(data.cost_price);
	SetSelling_price(data.selling_price);
	SetName(data.name);
	SetItem(data.item);
	SetQuantity(data.quantity);
}

void Record::Swap(Record &a) {
	Record temp;
	temp.SetRecord(*this);
	this->SetRecord(a);
	a.SetRecord(temp);
}

Record::~Record()
{
}
