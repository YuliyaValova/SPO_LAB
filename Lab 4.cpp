#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

const int mas_size = 20;
int mas[mas_size];

CRITICAL_SECTION cs;


void thr1() {
	srand(time_t(NULL));
	while (true) {
		Sleep(1000);
		EnterCriticalSection(&cs);
		for (int i = 0; i < mas_size; i++) {
			mas[i]+= rand() % 301 - 150;
		}
		LeaveCriticalSection(&cs);
	}
}

void thr2() {
	while (true) {
		Sleep(50);
		EnterCriticalSection(&cs);
		for (int i = 0; i < mas_size; i++) {
			if (mas[i] % 2 == 0) {
				mas[i] = 0;
			}
		}
		LeaveCriticalSection(&cs);
	}
}

int main() {
	InitializeCriticalSection(&cs);

	HANDLE  hThr1, hThr2;
	DWORD   IDThr1, IDThr2;

	hThr1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thr1, NULL, 0, &IDThr1);
	if (hThr1 == NULL) return GetLastError();

	hThr2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thr2, NULL, 0, &IDThr2);
	if (hThr2 == NULL) return GetLastError();

	while (true) {
		Sleep(1000);
		for (int i = 0; i < mas_size; i++) {
			cout << mas[i] << " ";
		}
		cout << endl;
	}

	DeleteCriticalSection(&cs);
	CloseHandle(hThr1);
	CloseHandle(hThr2);
	return 0;
}
