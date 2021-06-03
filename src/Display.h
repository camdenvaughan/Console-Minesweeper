#pragma once

#include <Windows.h>

class Display
{
private:
	int ScreenWidth, ScreenHeight;
	wchar_t* screen;

	HANDLE hConsole;

public:
	Display(int screenWidth, int screenHeight);
	~Display();

	void AddWCharToArray(wchar_t c, int startingPos);
	void AddStringToArray(const char* str, int startingPos);

	void PrintArrayToScreen() const;
};

