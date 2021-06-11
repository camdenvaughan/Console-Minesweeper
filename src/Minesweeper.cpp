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
    ScreenPtr->AddStringToArray("Welcome to MineSweeper", 2 + ScreenWidth);
    ScreenPtr->AddStringToArray("======================", 2 + 2 * ScreenWidth);
    ScreenPtr->AddStringToArray("Choose A Difficulty", 2 + 5 * ScreenWidth);
    ScreenPtr->AddStringToArray("===================", 2 + 6 * ScreenWidth);
    ScreenPtr->AddStringToArray("    1. Easy", 2 + 7 * ScreenWidth);
    ScreenPtr->AddStringToArray("    2. Medium", 2 + 8 * ScreenWidth);
    ScreenPtr->AddStringToArray("    3. Hard", 2 + 9 * ScreenWidth);

    ScreenPtr->AddStringToArray("======================", 2 + 14 * ScreenWidth);
    ScreenPtr->AddStringToArray("Made By Camden Vaughan", 2 + 15 * ScreenWidth);
    ScreenPtr->AddStringToArray("www.CamdenVaughan.com", 2 + 16 * ScreenWidth);
    ScreenPtr->AddStringToArray("======================", 2 + 17 * ScreenWidth);

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

        // Handles showing the rules
        ShowRules(ScreenPtr, GameStatePtr);

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

void ShowRules(Display* ScreenPtr, GameData* GameState)
{
    ScreenPtr->AddStringToArray("Press 'R' To Toggle Rules", 75 + 4 * ScreenPtr->ScreenWidth);
    ScreenPtr->AddStringToArray("=========================", 75 + 5 * ScreenPtr->ScreenWidth);
    if (GameState->AreRulesToggled)
    {
        ScreenPtr->AddStringToArray("Controls", 75 + 7 * ScreenPtr->ScreenWidth);
        ScreenPtr->AddStringToArray("========", 75 + 8 * ScreenPtr->ScreenWidth);
        ScreenPtr->AddStringToArray("- Use Arrow Keys To Navigate", 75 + 9 * ScreenPtr->ScreenWidth);
        ScreenPtr->AddStringToArray("- Press 'F' to Flag a Square", 75 + 10 * ScreenPtr->ScreenWidth);
        ScreenPtr->AddStringToArray("- Press 'Enter' to Click a Square", 75 + 11 * ScreenPtr->ScreenWidth);
        ScreenPtr->AddStringToArray("Objective", 75 + 13 * ScreenPtr->ScreenWidth);
        ScreenPtr->AddStringToArray("=========", 75 + 14 * ScreenPtr->ScreenWidth);
        ScreenPtr->AddStringToArray("- Click any square to start", 75 + 15 * ScreenPtr->ScreenWidth);
        ScreenPtr->AddStringToArray("- A number indicates how many Mines", 75 + 16 * ScreenPtr->ScreenWidth);
        ScreenPtr->AddStringToArray("  are in the surrounding 8 squares.", 75 + 17 * ScreenPtr->ScreenWidth);
        ScreenPtr->AddStringToArray("- Flag squares to help you keep track", 75 + 18 * ScreenPtr->ScreenWidth);
        ScreenPtr->AddStringToArray("  of spaces that might be bombs!", 75 + 19 * ScreenPtr->ScreenWidth);
        ScreenPtr->AddStringToArray("- Click all the safe squares to WIN!", 75 + 20 * ScreenPtr->ScreenWidth);
        ScreenPtr->AddStringToArray("- Click a bomb to lose...", 75 + 21 * ScreenPtr->ScreenWidth);
    }
}