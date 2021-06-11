#include "Minesweeper.h"
#include "Minefield.h"
#include "Display.h"
#include "Block.h"
#include "Player.h"
#include "Playspace.h"
#include "Input.h"
#include "GameData.h"

#include <ctime>


void ShowMenu(bool IsPlaying)
{
    srand((unsigned int)time(NULL));

    // Initialize Variables
    const int ScreenWidth = 120;
    const int ScreenHeight = 30;

    const int OffsetTop = 8;
    const int OffsetLeft = 10;

    int PlaySpaceX = 10;
    int PlaySpaceY = 5;

    int BombCount = 5;

    // Create Screen Buffer
    Display Screen(ScreenWidth, ScreenHeight);
    Display* ScreenPtr = &Screen;

    // Clear Screen
    ScreenPtr->FillScreenWithChar(' ');

    // Menu Message
    ScreenPtr->AddStringToArray("Welcome to MineSweeper", 0);
    ScreenPtr->AddStringToArray("======================", ScreenWidth);
    ScreenPtr->AddStringToArray("Choose A Difficulty", 3 * ScreenWidth);
    ScreenPtr->AddStringToArray("    1. Easy", 5 * ScreenWidth);
    ScreenPtr->AddStringToArray("    2. Medium", 6 * ScreenWidth);
    ScreenPtr->AddStringToArray("    3. Hard", 7 * ScreenWidth);

    // Move Cursor to Bottom Left
    ScreenPtr->MoveCursor(0, 29);

    // Print Screen
    ScreenPtr->PrintArrayToScreen();

    // Get Menu Input
    while (Input::MenuInput(PlaySpaceX, PlaySpaceY, BombCount));

    // --------Create GamePlay Objects-------- 

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
    ScreenPtr->AddStringToArray("==========", 10 + 3 * ScreenWidth);

    // Set up Game State
    GameData GameState(PlayBoxPtr, BombCount);
    GameData* GameStatePtr = &GameState;

    // Start Game Loop
    Play(ScreenPtr, PlayBoxPtr, MinesPtr, PlayerPtr, GameStatePtr);
}

void Play(Display* ScreenPtr, Playspace* PlayBoxPtr, Minefield* MinesPtr, Player* PlayerPtr, GameData* GameStatePtr)
{
    while (GameStatePtr->IsGamePlaying(ScreenPtr))
    {
        // Add Current Minefield to the PlayBox
        PlayBoxPtr->FillWithMinefield(MinesPtr);

        // Place "Player" in Screen Array at current position
        PlayerPtr->ClampPlayerLocation();
        ScreenPtr->MoveCursor(PlayerPtr->Location.X + PlayBoxPtr->OffsetLeft, PlayerPtr->Location.Y + PlayBoxPtr->OffsetTop);

        // Add PlayBox to Screen Array
        PlayBoxPtr->WritePlaySpaceToScreen(ScreenPtr);


        // Print Sceen Array to screen
        ScreenPtr->PrintArrayToScreen();

        // Sleep to minimize repeated inputs
        Sleep(250);

        // Get Input
        while (Input::RecieveInput(MinesPtr, PlayerPtr, PlayBoxPtr, GameStatePtr));
    }

    PlayBoxPtr->FillWithMinefield(MinesPtr);
    PlayBoxPtr->WritePlaySpaceToScreen(ScreenPtr);
    ScreenPtr->PrintArrayToScreen();
    Sleep(200);

    // Pause before restarting
    Input::WaitForEnter();
}