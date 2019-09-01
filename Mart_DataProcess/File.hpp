#ifndef FILE_H
#define FILE_H
#include<iostream>
#include<fstream>
#include<Windows.h>

using namespace std;
/*
File ������� ���� ���ø��Դϴ�.
Save_File�� ����Ҷ� class����
oftream& operator<<(ofstream &,T &);�� ���ǵ��־���մϴ�.

Load_File�� ����Ҷ� class����
ifstream& operator>>(ifstream &,T &);�� ���ǵ��־���մϴ�.

���� : �����ڰ� string��.txt�� �ٿ����� .txt���Ϸθ� �ε�˴ϴ�.
���� string�� .txt�� �ȳ־���մϴ�.
*/

#pragma pack(push,1)
template<class T>
class File
{
public:
	File();

	void Save_File(T &list, string str/*(str).txt*/);
	void Load_File(T &list, string str/*(str).txt*/);

	~File();
};
#pragma pack(pop)

template<class T>
File<T>::File()
{
}

template<class T>
void File<T>::Save_File(T &list, string str)
{
	ofstream save;

	save.open(str + ".txt");

	if (save.good() == true) {
		save << list;
	}
	else {
		//MessageBox(NULL, TEXT("Save File function Not Good"), TEXT("ERRER"), MB_OK);
		cout << "Save File function Not Good" << endl;
	}
	save.close();
}

template<class T>
void File<T>::Load_File(T &list, string str)
{
	ifstream load;

	load.open(str + ".txt");

	if (load.good() == true) {
		load >> list;
	}
	else {
		//MessageBox(NULL, TEXT("Load File function Not Good"), TEXT("ERRER"), MB_OK);
		cout << "Load File function Not Good" << endl;
	}
	load.close();
}



template<class T>
File<T>::~File()
{
}


#endif