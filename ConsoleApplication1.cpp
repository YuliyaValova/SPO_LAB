//5. Информация об участниках спортивных соревнований содержит название команды, ФИО игрока, возраст. 
//Вывести информацию о спортсменах, возраст которых не достиг 18 лет.
//В программе предусмотреть сохранение вводимых данных в файл и возможность чтения из ранее сохраненного файла. Результаты выводить на
//экран и в текстовой файл.

#include "pch.h"
#include <windows.h>
#include <iostream>
using namespace std;

struct sportsmen {
	char comandName[20];
	char fio[20];
	int age;
	void printConsole() {
		cout << "Command: " << comandName << ", FIO: " << fio << ", Age: " << age << ".\n";
	}

} sportsmens[20];

HANDLE createFile() {
	LPCTSTR fileName = TEXT("File_New.dat");
	HANDLE myFile = CreateFile(
		fileName,
		GENERIC_READ | GENERIC_WRITE,  //параметры доступа
		FILE_SHARE_READ | FILE_SHARE_WRITE,  //режим совместного использования
		NULL,                              //указатель на дескриптор защиты
		CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL,     //атрибут файла(обычный)
		NULL);     //указатель на TemplateFile
	if (myFile == INVALID_HANDLE_VALUE) {
		cout << "Error";
		return NULL;
	}
	else cout << "File is created\n";
	return myFile;
}

HANDLE openFileForReading() {
	LPCTSTR fileName = TEXT("File_New.dat");
	HANDLE myFile = CreateFile(
		fileName,
		GENERIC_READ,  //параметры доступа
		NULL,  //режим совместного использования
		NULL,                              //указатель на дескриптор защиты
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,     //атрибут файла(обычный)
		NULL);     //указатель на TemplateFile
	if (myFile == INVALID_HANDLE_VALUE) {
		cout << "Error";
		return NULL;
	}
	else cout << "File is opened\n";
	return myFile;

}

void writeToFile(sportsmen mas[], HANDLE file) {
	DWORD n;
	cout << "From IDE:" << endl;
	for (int i = 0; i < 4; i++) {
		if (mas[i].age < 18) {
			mas[i].printConsole();
			WriteFile(file, &mas[i].comandName, sizeof(mas[i].comandName), &n, NULL);
			WriteFile(file, &mas[i].fio, sizeof(mas[i].fio), &n, NULL);
			WriteFile(file, &mas[i].age, sizeof(mas[i].age), &n, NULL);
		}
	}

	FlushFileBuffers(file);
}

void readFromFile(HANDLE file2) {
	DWORD n;
	cout << "From file:" << endl;
	sportsmen sp;

	while (ReadFile(file2, &sp.comandName, sizeof(sp.comandName), &n, NULL) && n != 0) {		ReadFile(file2, &sp.fio, sizeof(sp.fio), &n, NULL);		ReadFile(file2, &sp.age, sizeof(sp.age), &n, NULL);		sp.printConsole();	}
}

	
int main()
{
	sportsmen mas[10] = { {"Star", "Sokolov Vasiliy", 17}, {"Sky", "Ivanov Petr", 19}, {"Sun", "Sidorov Ivan", 15}, {"Space", "Kozlov Maksim", 16} };

	HANDLE file = createFile();	writeToFile(mas, file);	CloseHandle(file);	HANDLE file2 = openFileForReading();	   	
	readFromFile(file2);	CloseHandle(file2);

	

}


