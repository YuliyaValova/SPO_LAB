// Lab 3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <cstring>

using namespace std;

int value1 = 0, value2 = 0, value3 = 0;
HANDLE hTh01, hTh02, hTh03;

void thread01() 
{
	while (true) {
		value1++; Sleep(21);
	}
}

void thread02() 
{
	while (true) {
		value2++; Sleep(1);
	}
}

void thread03() 
{
	while (true) {
		value3++; Sleep(12);
	}
}

int max_value(int a, int b) {
	return a > b ? a : b;
}

int main()
{
	cout << "Input 'q' to stop and 'v' to find max value" << endl;

	DWORD IDTh01;
	hTh01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread01,
		NULL, 0, &IDTh01);
	DWORD IDTh02;
	hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread02,
		NULL, 0, &IDTh02);
	DWORD IDTh03;
	hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread03,
		NULL, 0, &IDTh03);
	char key = getchar();
	while (key != 'q') {
		if (key == 'v') {
			cout << value1 << ' ' << value2 << ' ' << value3 << endl;
			cout << "Max: " << max_value(value1, max_value(value2, value3)) << endl;
			key = getchar();
		}
		else
			key = getchar();
	}
	CloseHandle(hTh01);
	CloseHandle(hTh02);
	CloseHandle(hTh03);
	return 0;
}
