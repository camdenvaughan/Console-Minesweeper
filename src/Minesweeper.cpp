#include "Minesweeper.h"
#include "Minefield.h"
#include "Display.h"
#include "Block.h"
#include "Player.h"
#include "Playspace.h"
#include "Input.h"
#include "GameData.h"

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

    const int PlaySpaceX = 10;
    const int PlaySpaceY = 5;

    const int BombCount = 10;

    // Create Screen Buffer
    Display Screen(ScreenWidth, ScreenHeight);
    Display* ScreenPtr = &Screen;

    // Create PlaySpace
    Playspace PlayBox(PlaySpaceX, PlaySpaceY, OffsetLeft, OffsetTop, ScreenWidth);
    Playspace* PlayBoxPtr = &PlayBox;

    // Create Minefield
    Minefield Mines(PlayBoxPtr, BombCount);
    Minefield* MinesPtr = &Mines;

    // Create Player
    Player Player1(PlaySpaceX, PlaySpaceY);
    Player* PlayerPtr = &Player1;

    // Fill Screen Array with .
    ScreenPtr->FillScreenWithChar(' ');

    // Set up Game State
    GameData GameState(PlayBoxPtr, BombCount);
    GameData* GameStatePtr = &GameState;
    while (GameStatePtr->IsGamePlaying())
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
        while (Input::RecieveInput(MinesPtr, PlayerPtr, PlayBoxPtr, GameStatePtr))
        {
        }
    }
    PlayBoxPtr->FillWithMinefield(MinesPtr);
    PlayBoxPtr->WritePlaySpaceToScreen(ScreenPtr);
    ScreenPtr->PrintArrayToScreen();

    while (Input::WaitForEnter())
    { }
}