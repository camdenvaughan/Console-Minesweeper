#include "Display.h"
#include <Windows.h>

Display::Display(int screenWidth, int screenHeight) 
    : ScreenWidth(screenWidth), ScreenHeight(screenHeight), screen(new wchar_t[ScreenWidth * ScreenHeight])
{
    hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
}

void Display::AddWCharToArray(wchar_t c, int startingPos)
{
    if (startingPos > ScreenWidth * ScreenHeight)
    {
        const char* ErrorMessage = "Outside of bounds of Screen Array";
        for (int j = 0; ErrorMessage[j] != '\0'; j++)
        {
            screen[j] = ErrorMessage[j];
        }
    }
    screen[startingPos] = c;
}

void Display::AddStringToArray(const char* str, int startingPos)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (startingPos > ScreenWidth * ScreenHeight)
        {
            const char* ErrorMessage = "Outside of bounds of Screen Array";
            for (int j = 0; ErrorMessage[j] != '\0'; j++)
            {
                screen[j] = ErrorMessage[j];
            }
        }
        screen[startingPos++] = str[i];
    }

}

void Display::PrintArrayToScreen() const
{
    DWORD dwBytesWritten = 0;
    WriteConsoleOutputCharacter(hConsole, screen, ScreenWidth * ScreenHeight, { 0,0 }, &dwBytesWritten);
}

Display::~Display()
{
    delete[] screen;
}