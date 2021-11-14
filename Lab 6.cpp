// Lab 6.cpp : 

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <ctime>

int n;
int mas[100];

HANDLE hSemaphore;

using namespace std;

int thr1() 
{
	srand(time(0));
	for (int i = 0; i < n; i++) {
		mas[i] = rand() % 501;
		cout << mas[i] << ' ';
		ReleaseSemaphore(hSemaphore, 1, NULL);
		Sleep(100);
	}
	cout << endl;
	return 0;
}

int thr2() 
{
	for (int i = 0; i < n; i++) {
		WaitForSingleObject(hSemaphore, INFINITE);
		if (abs(mas[i]) % 2 == 1)
		mas[i] = 1000;
		Sleep(150);
	}
	return 0;
}

int main()
{
	cout << "Input number of elements" << endl;
	cin >> n;
	// Создание семафора
	hSemaphore = CreateSemaphore(NULL, 0, n, L"MySemaphore");
	if (hSemaphore == NULL) cout << "Create semaphore failed" << GetLastError() << endl;
	HANDLE hThr1 = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)thr1, NULL, 0, NULL);
	if (hThr1 == NULL) return GetLastError();
	HANDLE hThr2 = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)thr2, NULL, 0, NULL);
	if (hThr2 == NULL) return GetLastError();
	WaitForSingleObject(hThr1, INFINITE);
	WaitForSingleObject(hThr2, INFINITE);
	// Закрытие семафора
	CloseHandle(hSemaphore);
	// Закрытие потоков
	CloseHandle(hThr1);
	CloseHandle(hThr2);
	for (int i = 0; i < n; i++)
		cout << mas[i] << ' ';
	cin.get();
	return 0;
}

