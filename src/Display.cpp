#include "Display.h"
#include <Windows.h>

Display::Display(int ScreenWidth, int ScreenHeight)
    : ScreenWidth(ScreenWidth), ScreenHeight(ScreenHeight), Screen(new wchar_t[ScreenWidth * ScreenHeight])
{
    HConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(HConsole);
}

void Display::FillScreenWithChar(wchar_t C)
{
    for (int i = 0; i < ScreenWidth * ScreenHeight; i++)
        Screen[i] = C;
}

void Display::AddWCharToArray(wchar_t c, int StartingPos)
{
    if (StartingPos > ScreenWidth * ScreenHeight)
    {
        const char* ErrorMessage = "Outside of bounds of Screen Array";
        for (int j = 0; ErrorMessage[j] != '\0'; j++)
        {
            Screen[j] = ErrorMessage[j];
        }
    }
    Screen[StartingPos] = c;
}



void Display::AddStringToArray(const char* Message, int StartingPos)
{
    for (int i = 0; Message[i] != '\0'; i++)
    {
        if (StartingPos > ScreenWidth * ScreenHeight)
        {
            const char* ErrorMessage = "Outside of bounds of Screen Array";
            for (int j = 0; ErrorMessage[j] != '\0'; j++)
            {
                Screen[j] = ErrorMessage[j];
            }
        }
        Screen[StartingPos++] = Message[i];
    }

}

void Display::PrintArrayToScreen()
{
    DWORD dwBytesWritten = 0;
    WriteConsoleOutputCharacter(HConsole, Screen, ScreenWidth * ScreenHeight, { 0,0 }, &dwBytesWritten);
    
    //Clear Array
    this->FillScreenWithChar(' ');
}

Display::~Display()
{
    delete[] Screen;
}