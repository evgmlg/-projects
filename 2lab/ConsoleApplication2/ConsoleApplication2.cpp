// ConsoleApplication2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>

void Light()
{
	INPUT inputs[6] = {};
	ZeroMemory(inputs, sizeof(inputs));

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = VK_NUMLOCK;
	
	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = VK_NUMLOCK;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	inputs[2].type = INPUT_KEYBOARD;
	inputs[2].ki.wVk = VK_CAPITAL;
	
	inputs[3].type = INPUT_KEYBOARD;
	inputs[3].ki.wVk = VK_CAPITAL;
	inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

	inputs[4].type = INPUT_KEYBOARD;
	inputs[4].ki.wVk = VK_SCROLL;

	inputs[5].type = INPUT_KEYBOARD;
	inputs[5].ki.wVk = VK_SCROLL;
	inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;

	UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
}

void ToogleKey(WORD vKey)
{
	INPUT inputs[2];
	ZeroMemory(inputs, sizeof(inputs));
	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = vKey;
	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = vKey;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
}

int main() {
	WORD keyChain[3] = { VK_NUMLOCK, VK_CAPITAL, VK_SCROLL };
	int n;
	std::cout << "Input time:";
	std::cin >> n;
	/*
	INPUT ti = { 0, 0 };
	ti.type = INPUT_KEYBOARD;
	ti.ki.wVk = VK_SCROLL;
	while (GetAsyncKeyState(VK_ESCAPE) == 0)
	{
		ti.ki.dwFlags = (ti.ki.dwFlags) ? 0 : KEYEVENTF_KEYUP;
		SendInput(1, &ti, sizeof(INPUT));
		Sleep(1000);
	}
	*/
	/*
	for (size_t i = 0; i < ARRAYSIZE(keyChain); i++)
	{
		WORD vKey = keyChain[i];
		if (GetKeyState(vKey) & 0x01) ToogleKey(vKey);
	}
	*/

	int light = 0;
	//WORD vKey;
	while (GetAsyncKeyState(VK_ESCAPE) == 0)
	{
		WORD vKey = keyChain[light];
		ToogleKey(vKey);
		Sleep(n);
		ToogleKey(vKey);
		light++;
		light %= ARRAYSIZE(keyChain);
	}

	/*
	INPUT inputs[ARRAYSIZE(keyChain) * 2];
	ZeroMemory(inputs, sizeof(inputs));

	int light = 0;

	while (GetAsyncKeyState(VK_ESCAPE) == 0)
	{
		for (size_t i = 0; i < ARRAYSIZE(keyChain); i++)
		{
			inputs[i].type = INPUT_KEYBOARD;
			inputs[i].ki.wVk = keyChain[i];
			//inputs[i].ki.dwFlags = (i == light) ? 0 : KEYEVENTF_KEYUP;
			inputs[i].ki.dwFlags = KEYEVENTF_KEYUP;
		}
		SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
		light++;
		light %= ARRAYSIZE(keyChain);
		Sleep(250);
	}
	*/

	return 0;
}

