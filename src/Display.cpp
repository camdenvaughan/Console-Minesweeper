#include "Display.h"
#include <Windows.h>

Display::Display(int ScreenWidth, int ScreenHeight)
    : ScreenWidth(ScreenWidth), ScreenHeight(ScreenHeight), Screen(new wchar_t[ScreenWidth * ScreenHeight])
{
    // Create Screen Buffer
    HConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(HConsole);
}

// Fills the screen with a wchar_t
void Display::FillScreenWithChar(wchar_t C)
{
    for (int i = 0; i < ScreenWidth * ScreenHeight; i++)
        Screen[i] = C;
}

// Moves the cursor position
void Display::MoveCursor(int X, int Y)
{
    COORD CursorPoint;
    CursorPoint.X = X;
    CursorPoint.Y = Y;
    SetConsoleCursorPosition(HConsole, CursorPoint);
}

// Adds a single wchar_t to a position
void Display::AddWCharToArray(wchar_t c, int StartingPos)
{
    Screen[StartingPos] = c;
}


// Adds an entire string from a starting position
void Display::AddStringToArray(const char* Message, int StartingPos)
{
    for (int i = 0; Message[i] != '\0'; i++)
    {
        Screen[StartingPos++] = Message[i];
    }

}

// Prints the screen
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