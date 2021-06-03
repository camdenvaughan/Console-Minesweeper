#include <iostream>
#include <Windows.h>
#include <ctime>

#include "Map.h"
#include "Display.h"

int main()
{
    srand(time(NULL));

    std::cout << "Welcome to MineSweeper\n";
    std::cout << "======================\n\n";

    //int MapSize, Bombs;
    //std::cout << "Enter Map Size\n";
    //std::cin >> MapSize;
    //std::cout << "Mape Size is : " << MapSize << std::endl;
    //std::cout << "Enter Bomb Count\n";
    //std::cin >> Bombs;
    //std::cout << "Bomb count is : " << Bombs << std::endl;
    //std::cout << "\nPress Enter to Generate Map\n";
    //std::cin.get();

    ////Generate Map

    std::cin.get();

    std::system("cls");
    // Display
    int ScreenWidth = 120;
    int ScreenHeight = 30;
    int currentPosX = 0;
    int currentPosY = 0;
    bool Key[4];

    int PlaySpaceX = 20;
    int PlaySpaceY = 20;

    

    // Create Screen Buffer
    Display display(ScreenWidth, ScreenHeight);

    // Create Map
    Map map(PlaySpaceX * PlaySpaceY, 15);

    while (1)
    {
        // Fill Screen Array with .
        for (int i = 0; i < ScreenWidth * ScreenHeight; i++)
            display.AddWCharToArray(L' ', i);

        // Fill Play Space with blocks
        int i = 0; // block reference
        for (int playX = 5; playX < PlaySpaceX; playX++)
        {
            for (int playY = 5; playY < PlaySpaceY; playY++)
            {
                display.AddWCharToArray(map.GetSymbolOnBlock(i++), (playY * ScreenWidth) + playX);
            }
        }
               
        // ** Find way to find which block is on a playspace **
            // find y, to get the row, then add the x
        // ** Find way to constrain player movement to playspace **


        // Place "Player" in Screen Array at current position
        display.AddWCharToArray(L'0', (currentPosY * ScreenWidth) + currentPosX);

        // Print Sceen Array to screen
        display.PrintArrayToScreen();

        //WriteConsoleOutputCharacter(hConsole, screen, ScreenWidth * ScreenHeight, { 0,0 }, &dwBytesWritten);
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
}

