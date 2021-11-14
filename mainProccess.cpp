
#pragma warning (suppress : 4996)
#include "pch.h"
#include <string>
#include <iostream>
#include <sstream>
#include <Windows.h>

using namespace std;

struct sportsmen {
	char comandName[20];
	char fio[20];
	int age;
	void printConsole() {
		cout << "Command: " << comandName << ", FIO: " << fio << ", Age: " << age << ".\n";
	}

} sportsmens[20];

HANDLE file;
DWORD n;

LPWSTR CharToLPWSTR(LPCSTR char_string)
{
	LPWSTR res;
	DWORD res_len = MultiByteToWideChar(1251, 0, char_string, -1, NULL, 0);
	res = (LPWSTR)GlobalAlloc(GPTR, (res_len + 1) * sizeof(WCHAR));
	MultiByteToWideChar(1251, 0, char_string, -1, res, res_len);
	return res;
}

int main() {
	sportsmen sp;
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

	while (ReadFile(file, &sp.comandName, sizeof(sp.comandName), &n, NULL) && n != 0) {
		ReadFile(file, &sp.fio, sizeof(sp.fio), &n, NULL);
		ReadFile(file, &sp.age, sizeof(sp.age), &n, NULL);	
		sp.printConsole();
	};
	cout << "Input a number of structure you want to change" << endl;
	int number;
	cin >> number;
	/*string num;
	stringstream ss;
	ss << number;
	num = ss.str();*/
	
	CloseHandle(file);

	STARTUPINFO StartupInfo;
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof(StartupInfo);
	PROCESS_INFORMATION ProcInfo;
	ZeroMemory(&ProcInfo, sizeof(ProcInfo));

	/*LPCWSTR daughterProcess = L"C:\\daughterProc\\Debug\\daughterProc.exe";
	wcout << wstring(daughterProcess);
	cout<<""<<endl;*/

	wchar_t daughterProcess[100], t[5];
	wcscpy(daughterProcess, L"daughterProc.exe");
	swprintf_s(t, L"%d", number);
	wcscat(daughterProcess, t);

	
	/*LPWSTR command = CharToLPWSTR((num.c_str()));
	wcout << wstring(command);*/

	if (!CreateProcess(NULL, daughterProcess, NULL, NULL, FALSE, 0,
		NULL, NULL, &StartupInfo, &ProcInfo)) return 0;

	WaitForSingleObject(ProcInfo.hProcess, INFINITE);
	CloseHandle(ProcInfo.hProcess);
	CloseHandle(ProcInfo.hThread);

}

