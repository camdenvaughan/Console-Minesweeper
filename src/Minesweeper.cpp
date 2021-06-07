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
    srand((unsigned int)time(NULL));

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

    bool GameIsPlaying = true;

    // Create Screen Buffer
    Display Screen(ScreenWidth, ScreenHeight);
    Display* ScreenPtr = &Screen;

    // Create PlaySpace
    Playspace PlayBox(PlaySpaceX, PlaySpaceY, OffsetLeft, OffsetTop, ScreenWidth);
    Playspace* PlayBoxPtr = &PlayBox;

    // Create Minefield
    Minefield Mines(PlayBoxPtr, 25);
    Minefield* MinesPtr = &Mines;


    // Create Player
    Player Player1(PlaySpaceX, PlaySpaceY);
    Player* PlayerPtr = &Player1;

    // Fill Screen Array with .
    ScreenPtr->FillScreenWithChar(' ');

    while (GameIsPlaying)
    {

        PlayBoxPtr->FillWithMinefield(MinesPtr);

        // Place "Player" in Screen Array at current position
        PlayerPtr->ClampPlayerLocation();
        ScreenPtr->MoveCursor(PlayerPtr->Location.X + PlayBoxPtr->OffsetLeft, PlayerPtr->Location.Y + PlayBoxPtr->OffsetTop);

        // Add PlayBox to Screen Array
        PlayBoxPtr->WritePlaySpaceToScreen(ScreenPtr);


        // Print Sceen Array to screen
        ScreenPtr->PrintArrayToScreen();

        Sleep(300);
        while (RecieveInput(MinesPtr, PlayerPtr, PlayBoxPtr))
        {
        }
    }
}

bool RecieveInput(Minefield* Mines, Player* Player1, Playspace* PlayBox)
{
    if (GetAsyncKeyState(VK_RIGHT))
    {
        Player1->Location.X++;
        return false;
    }
    if (GetAsyncKeyState(VK_LEFT))
    {
        Player1->Location.X--;
        return false;
    }
    if (GetAsyncKeyState(VK_UP))
    {
        Player1->Location.Y--;
        return false;
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        Player1->Location.Y++;
        return false;
    }
    if (GetAsyncKeyState(VK_RETURN))
    {
        if (Mines->GetBlockAtLocation(PlayBox->CoordsToPlaySpace(Player1->Location.X, Player1->Location.Y)).IsFlagged)
            return true;
        // Click
        Mines->GetBlockAtLocation(PlayBox->CoordsToPlaySpace(Player1->Location.X, Player1->Location.Y)).ChangeSymbol(SymbolState::Number);
        
        return false;
    }
    if (GetAsyncKeyState(0x46))
    {
        if (Mines->GetBlockAtLocation(PlayBox->CoordsToPlaySpace(Player1->Location.X, Player1->Location.Y)).IsFlagged)
        {
            Mines->GetBlockAtLocation(PlayBox->CoordsToPlaySpace(Player1->Location.X, Player1->Location.Y)).IsFlagged = false;
            Mines->GetBlockAtLocation(PlayBox->CoordsToPlaySpace(Player1->Location.X, Player1->Location.Y)).ChangeSymbol(SymbolState::Default);
            return false;
        }
        else
        {
            Mines->GetBlockAtLocation(PlayBox->CoordsToPlaySpace(Player1->Location.X, Player1->Location.Y)).IsFlagged = true;
            Mines->GetBlockAtLocation(PlayBox->CoordsToPlaySpace(Player1->Location.X, Player1->Location.Y)).ChangeSymbol(SymbolState::Flag);
            return false;
        }
    }
    return true;
}
