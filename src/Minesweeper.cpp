#include "Minesweeper.h"
#include "Minefield.h"
#include "Display.h"
#include "Block.h"
#include "Player.h"
#include "Playspace.h"

#include <iostream>
#include <ctime>

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
    const int ScreenWidth = 120;
    const int ScreenHeight = 30;

    const int OffsetTop = 5;
    const int OffsetLeft = 10;

    const int PlaySpaceX = 40;
    const int PlaySpaceY = 10;

    // Create Screen Buffer
    Display Screen(ScreenWidth, ScreenHeight);

    // Create PlaySpace
    Playspace PlayBox = Playspace(PlaySpaceX, PlaySpaceY, OffsetLeft, OffsetTop, ScreenWidth);

    // Create Minefield
    Minefield Mines = Minefield(PlaySpaceX, PlaySpaceY, OffsetLeft, OffsetTop, ScreenWidth, 25);


    // Create Player
    Player Player1(PlaySpaceX, PlaySpaceY);

    // Fill Screen Array with .
    Screen.FillScreenWithChar(' ');

    while (1)
    {

        PlayBox.FillWithMinefield(Mines);

        // Place "Player" in Screen Array at current position
        Player1.ClampPlayerLocation();
        PlayBox.AddWCharToArray(L'0', Player1.Location.X + Player1.Location.Y * PlaySpaceX);

        // Add PlayBox to Screen Array
        PlayBox.WritePlaySpaceToScreen(Screen);

        Sleep(100);

        // Print Sceen Array to screen
        Screen.PrintArrayToScreen();

        while (!RecieveInput(Mines, Player1, PlayBox))
        {
        }
    }

}

bool RecieveInput(Minefield& Mines, Player& Player1, Playspace& PlayBox)
{
    if (GetAsyncKeyState(VK_RIGHT))
    {
        Player1.Location.X++;
        return true;
    }
    if (GetAsyncKeyState(VK_LEFT))
    {
        Player1.Location.X--;
        return true;
    }
    if (GetAsyncKeyState(VK_UP))
    {
        Player1.Location.Y--;
        return true;
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        Player1.Location.Y++;
        return true;
    }
    if (GetAsyncKeyState(VK_RETURN))
    {
        // Not Happening for some reason
        Mines.GetBlockAtLocation(PlayBox.CoordsToPlaySpace(Player1.Location.X, Player1.Location.Y)).ChangeSymbol(SymbolState::Explode);
        
        return true;
    }
    if (GetAsyncKeyState(0x46))
    {
        Mines.GetBlockAtLocation(PlayBox.CoordsToPlaySpace(Player1.Location.X, Player1.Location.Y)).ChangeSymbol(SymbolState::Flag);
        return true;
    }
    return false;
}
