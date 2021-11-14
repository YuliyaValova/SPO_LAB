// daughterProc.cpp : 
#include "pch.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <sstream>

using namespace std;

struct sportsmen {
	char comandName[20];
	char fio[20];
	int age;
	void printConsole() {
		cout << "Command: " << comandName << ", FIO: " << fio << ", Age: " << age << ".\n";
	}

} sportsmens[20];

DWORD n;
int main(int argc, char* argv[]) {
	HANDLE file;
	LPCWSTR filename = L"D:\\лабы ОАиП\\пятый_сем\\Лаба 1\\Лаба 1\\File_New.dat";
	file = CreateFile(
		filename,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (file == INVALID_HANDLE_VALUE)
		cout << "File is not existing"; 

	int kol = 0;

	while (ReadFile(file, &sportsmens[kol].comandName, sizeof(sportsmens[kol].comandName), &n, NULL) && n != 0) {
		kol++;
		ReadFile(file, &sportsmens[kol].fio, sizeof(sportsmens[kol].fio), &n, NULL);
		ReadFile(file, &sportsmens[kol].age, sizeof(sportsmens[kol].age), &n, NULL);
		sportsmens[kol].printConsole();
	}

	int number = stoi(argv[0]); 
	int choice;
	cout << "What field you want to change?:" << endl;
	cout << "1. Command Name:" << endl;
	cout << "2. FIO:" << endl;
	cout << "3. Age:" << endl;
	cin >> choice;
	cout << "Input value" << endl;

	for (int i = 0; i < kol; i++) {

		if (i == number) {
			cout << "Input value" << endl;
			if (choice == 1)
				cin >> sportsmens[i].comandName;
			else if (choice == 2)
				cin >> sportsmens[i].fio;
			else if (choice == 3)
				cin >> sportsmens[i].age;
			else cout << "Invalide choice";
		}

	}

	CloseHandle(file);

	file = CreateFile(
		filename, 
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (file == INVALID_HANDLE_VALUE)
		cout << "Error"; 
	
	for (int i = 0; i < kol; i++) WriteFile(file, &sportsmens[kol], sizeof(sportsmens[kol]), &n, NULL);
	cout << "Change successful" << endl;
}

