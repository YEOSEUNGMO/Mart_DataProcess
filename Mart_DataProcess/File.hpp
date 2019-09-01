#ifndef FILE_H
#define FILE_H
#include<iostream>
#include<fstream>
#include<Windows.h>

using namespace std;
/*
File 입출력을 위한 탬플릿입니다.
Save_File을 사용할때 class에서
oftream& operator<<(ofstream &,T &);이 정의되있어야합니다.

Load_File을 사용할때 class에서
ifstream& operator>>(ifstream &,T &);이 정의되있어야합니다.

주의 : 제작자가 string에.txt를 붙여놔서 .txt파일로만 로드됩니다.
또한 string에 .txt를 안넣어야합니다.
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