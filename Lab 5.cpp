// Lab 5.cpp : 
#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <time.h>

using namespace std;

int mas[3][10] = {};
const int kol = 10;

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void printArray(int i, int mas[10], char const status[10]) {
	cout << i+1<<" "<<status<< " array: " << endl;
	for (int i = 0; i < kol; i++) {
		cout << mas[i] << " ";
	}
	cout << endl;
}

void thr1() {
	 HANDLE hMutex;
	 hMutex = OpenMutex(SYNCHRONIZE, FALSE, L"Mutex");
	 if (hMutex == NULL) {
		 cout << GetLastError();
		 return;
	 }
	
	WaitForSingleObject(hMutex, INFINITE); //захват 

	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < kol; i++) {
			mas[j][i] = getRandomNumber(1,50);
		}
	
		printArray(j, mas[j], "old");
	}
	cout << endl;
	ReleaseMutex(hMutex); //освобождение
}

void thr2() {
	Sleep(100);
	HANDLE hMutex;
	hMutex = OpenMutex(SYNCHRONIZE, FALSE, L"Mutex");
	if (hMutex == NULL) {
		cout << GetLastError();
		return;
	}
	WaitForSingleObject(hMutex, INFINITE); //захват
	
	for (int j = 0; j < 3; j++) {
		int sum = 0;
		for (int i = 0; i < kol - 1; i++) {
			sum += mas[j][i];
		}
		mas[j][kol - 1] = sum;
		printArray(j, mas[j], "new");
	}
	cout << endl;
	ReleaseMutex(hMutex); //освобождение
}

int main() {
	srand(time(NULL));
	HANDLE hMutex;
	hMutex = CreateMutex(NULL, FALSE, L"Mutex");
	if (hMutex == NULL) {
		cout << GetLastError();
		return 1000;
	}

	HANDLE  hThr1, hThr2;
	DWORD   IDThr1, IDThr2;

	hThr1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thr1, NULL, 0, &IDThr1);
	if (hThr1 == NULL){
		cout<< GetLastError();
		return 999;
	}

	hThr2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thr2, NULL, 0, &IDThr2);
	if (hThr2 == NULL) {
		cout << GetLastError();
		return 998;
	}

	cin.get();
	// Закрытие мьютекса
	CloseHandle(hMutex);
	// Закрытие потоков
	CloseHandle(hThr1);
	CloseHandle(hThr2);

	return 0;
}
