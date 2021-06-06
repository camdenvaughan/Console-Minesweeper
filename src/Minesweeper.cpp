#include "Minesweeper.h"
#include "Minefield.h"
#include "Display.h"
#include "Block.h"
#include "Player.h"

#include <iostream>
#include <conio.h>
#include <ctime>
#include <map>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

void Menu()
{
    srand(time(NULL));

    std::cout << "Welcome to MineSweeper\n";
    std::cout << "======================\n\n";

    std::cout << "\nPress Enter to Generate start\n";
    // ***** ADD ***** dificulty choice
    std::cin.get();
    std::system("cls");
}

void Play()
{
    int ScreenWidth = 120;
    int ScreenHeight = 30;

    int OffsetTop = 5;
    int OffsetLeft = 10;

    int PlaySpaceX = 40;
    int PlaySpaceY = 10;

    // Create Screen Buffer
    Display display(ScreenWidth, ScreenHeight);

    // Create Minefield
    Minefield* Mines = new Minefield(PlaySpaceX, PlaySpaceY, OffsetLeft, OffsetTop, ScreenWidth, 25);

    // Create Player
    Player Player1(PlaySpaceX, PlaySpaceY);

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
                display.AddWCharToArray(Mines->GetBlockAtLocation(currentLoc).GetActiveSymbol(), currentLoc);
            }
        }

        // Convert Play Position to Play Space Position
        int PlayerPlaySpacePosition = (Player1.Location.Y + OffsetTop) * ScreenWidth + Player1.Location.X + OffsetLeft;

        // Place "Player" in Screen Array at current position
        display.AddWCharToArray(L'0', PlayerPlaySpacePosition);

        Sleep(100);

        // Print Sceen Array to screen
        display.PrintArrayToScreen();

        while (!RecieveInput(Mines, Player1, PlayerPlaySpacePosition))
        {
        }
    }
}

bool RecieveInput(Minefield* Mines, Player& Player1, int CurrentPos)
{
    bool Key[4];
    for (int k = 0; k < 4; k++)
        Key[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x26\x28"[k]))) != 0;
    if (Key[0])
    {
        Player1.Location.X++;
        return true;
    }
    if (Key[1])
    {
        Player1.Location.X--;
        return true;
    }
    if (Key[2])
    {
        Player1.Location.Y--;
        return true;
    }
    if (Key[3])
    {
        Player1.Location.Y++;
        return true;
    }
    return false;
}
