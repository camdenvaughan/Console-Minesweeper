#include <iostream>
#include <Windows.h>
#include <ctime>
#include <map>

#include "Minefield.h"
#include "Display.h"
#include "Block.h"

int main()
{

    srand(time(NULL));

    std::cout << "Welcome to MineSweeper\n";
    std::cout << "======================\n\n";

    std::cout << "\nPress Enter to Generate start\n";
    // ***** ADD ***** dificulty choice
    std::cin.get();
    std::system("cls");



    //*** Possibly extract to a Game loop file
    
    // Display
    int ScreenWidth = 120;
    int ScreenHeight = 30;
    int CurrentPosX = 0;
    int CurrentPosY = 0;
    bool Key[4];

    int OffsetTop = 5;
    int OffsetLeft = 10;

    int PlaySpaceX = 40;
    int PlaySpaceY = 10;

    // Create Screen Buffer
    Display display(ScreenWidth, ScreenHeight);

    // Create Minefield
    std::map<int, Block> BlockMap = Minefield::GenerateBlockMap(PlaySpaceX, PlaySpaceY, 15, OffsetLeft, OffsetTop, ScreenWidth);

    // Fill Screen Array with .
    display.FillScreenWithChar(' ');

    while (1)
    {
        // Fill Play Space with blocks
        int i = 0; // block reference
        for (int playX = 0; playX < PlaySpaceX; playX++)
        {
            for (int playY = 0; playY < PlaySpaceY; playY++)
            {
                int currentLoc = (playX + OffsetLeft) + (playY + OffsetTop) * ScreenWidth;
                display.AddWCharToArray(BlockMap[currentLoc].GetActiveSymbol(), currentLoc);
            }
        }
        // Convert Play Position to Play Space Position
        // 
        if (CurrentPosY > PlaySpaceY - 1)
            CurrentPosY = PlaySpaceY - 1;
        if (CurrentPosY < 0)
            CurrentPosY = 0;

        if (CurrentPosX > PlaySpaceX - 1)
            CurrentPosX = PlaySpaceX -1;
        if (CurrentPosX < 0)
            CurrentPosX = 0;
        int PlayerPlaySpacePosition = (CurrentPosY + OffsetTop) * ScreenWidth + CurrentPosX + OffsetLeft;

        // Place "Player" in Screen Array at current position
        display.AddWCharToArray(L'0', PlayerPlaySpacePosition);
        Sleep(100);
        // Print Sceen Array to screen
        display.PrintArrayToScreen();

        while (1)
        {
            // Input

            // Set Keys (x27 = right, x25 = left, x26 = up, x28 = down
            for (int k = 0; k < 4; k++)
                Key[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x26\x28"[k]))) != 0;
            if (Key[0])
            {
                CurrentPosX++;
                //Sleep(100);
                break;
            }
            if (Key[1])
            {
                CurrentPosX--;
                //Sleep(100);
                break;
            }
            if (Key[2])
            {
                CurrentPosY--;
                //Sleep(100);
                break;
            }
            if (Key[3])
            {
                CurrentPosY++;
                //Sleep(100);
                break;
            }
        }
    }
}

