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


void ShowMenu(bool IsPlaying)
{
    srand((unsigned int)time(NULL));
    // Create Screen Buffer

    const int ScreenWidth = 120;
    const int ScreenHeight = 30;

    const int OffsetTop = 5;
    const int OffsetLeft = 10;

    int PlaySpaceX = 10;
    int PlaySpaceY = 5;

    int BombCount = 5;

    Display Screen(ScreenWidth, ScreenHeight);
    Display* ScreenPtr = &Screen;
    ScreenPtr->FillScreenWithChar(' ');

    ScreenPtr->AddStringToArray("Welcome to MineSweeper", 0);
    ScreenPtr->AddStringToArray("======================", ScreenWidth);
    ScreenPtr->AddStringToArray("Choose A Difficulty", 3 * ScreenWidth);
    ScreenPtr->AddStringToArray("    1. Easy", 5 * ScreenWidth);
    ScreenPtr->AddStringToArray("    2. Medium", 6 * ScreenWidth);
    ScreenPtr->AddStringToArray("    3. Hard", 7 * ScreenWidth);

    ScreenPtr->MoveCursor(0, 29);

    ScreenPtr->PrintArrayToScreen();

    while (Input::MenuInput(PlaySpaceX, PlaySpaceY, BombCount));



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
    
    ScreenPtr->AddStringToArray("Good Luck!", 10 + 2 * ScreenWidth);

    // Set up Game State
    GameData GameState(PlayBoxPtr, BombCount);
    GameData* GameStatePtr = &GameState;

    Play(ScreenPtr, PlayBoxPtr, MinesPtr, PlayerPtr, GameStatePtr);
}

void Play(Display* ScreenPtr, Playspace* PlayBoxPtr, Minefield* MinesPtr, Player* PlayerPtr, GameData* GameStatePtr)
{
    while (GameStatePtr->IsGamePlaying(ScreenPtr))
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

    MinesPtr->ShowAllBombs();
    PlayBoxPtr->FillWithMinefield(MinesPtr);
    PlayBoxPtr->WritePlaySpaceToScreen(ScreenPtr);
    ScreenPtr->PrintArrayToScreen();
    Sleep(200);

    //bug
    Input::WaitForEnter();
}