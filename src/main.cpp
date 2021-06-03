#include <iostream>
#include "MapGeneration.h"
#include <Windows.h>

int main()
{
    std::cout << "Welcome to MineSweeper\n";
    std::cout << "======================\n\n";

    int MapSize, Bombs;
    std::cout << "Enter Map Size\n";
    std::cin >> MapSize;
    std::cout << "Mape Size is : " << MapSize << std::endl;
    std::cout << "Enter Bomb Count\n";
    std::cin >> Bombs;
    std::cout << "Bomb count is : " << Bombs << std::endl;
    std::cout << "\nPress Enter to Generate Map\n";
    std::cin.get();

    //Generate Map
    MapGeneration::GenerateMap(MapSize, Bombs);
    std::cin.get();

    std::system("cls");
    // Display
    int ScreenWidth = 120;
    int ScreenHeight = 40;
    int currentPosX = 0;
    int currentPosY = 0;
    bool Key[4];

    // Create Screen Buffer
    wchar_t* screen = new wchar_t[ScreenWidth * ScreenHeight];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    while (1)
    {
        // Fill Screen Array with .
        for (int i = 0; i < ScreenWidth * ScreenHeight; i++) 
            screen[i] = L'.';

        // Place "Player" in Screen Array at current position
        screen[(currentPosY * ScreenWidth) + currentPosX] = L'0';

        // Print Sceen Array to screen
        WriteConsoleOutputCharacter(hConsole, screen, ScreenWidth * ScreenHeight, { 0,0 }, &dwBytesWritten);
        while (1)
        {
            // Input

            // Set Keys (x27 = right, x25 = left, x26 = up, x28 = down
            for (int k = 0; k < 4; k++)
                Key[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x26\x28"[k]))) != 0;
            if (Key[0])
            {
                currentPosX++;
                Sleep(100);
                break;
            }
            if (Key[1])
            {
                currentPosX--;
                Sleep(100);
                break;
            }
            if (Key[2])
            {
                currentPosY--;
                Sleep(100);
                break;
            }
            if (Key[3])
            {
                currentPosY++;
                Sleep(100);
                break;
            }
        }
    }
    delete screen;
}

