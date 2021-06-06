#pragma once

#include <Windows.h>

class Display
{
private:
	int ScreenWidth, ScreenHeight;
	wchar_t* Screen;

	HANDLE HConsole;

public:
	Display(int ScreenWidth, int ScreenHeight);
	~Display();
	void FillScreenWithChar(wchar_t C);
	void AddWCharToArray(wchar_t C, int StartingPos);
	void AddStringToArray(const char* Message, int StartingPos);

	void PrintArrayToScreen();

};

