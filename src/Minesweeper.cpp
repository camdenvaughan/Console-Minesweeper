#include "Minesweeper.h"
#include "Minefield.h"
#include "Display.h"
#include "Block.h"
#include "Player.h"
#include "Playspace.h"
#include "Input.h"
#include "GameData.h"

#include <ctime>


void InitGame(bool IsPlaying)
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

    // Clear Screen
    Screen.FillScreenWithChar(' ');

    // Menu Message
    ShowMenu(&Screen);

    // Get Menu Input
    while (Input::MenuInput(PlaySpaceX, PlaySpaceY, BombCount));

    // --------Create GamePlay Objects-------- 

    // Create PlaySpace
    Playspace PlayBox(PlaySpaceX, PlaySpaceY, OffsetLeft, OffsetTop, ScreenWidth);

    // Create Minefield
    Minefield Mines(&PlayBox, BombCount);

    // Create Player
    Player Player1(PlaySpaceX, PlaySpaceY);

    // Fill Screen Array with .
    Screen.FillScreenWithChar(' ');
    
    Screen.AddStringToArray("Good Luck!", 10 + 2 * ScreenWidth);
    Screen.AddStringToArray("==========", 10 + 3 * ScreenWidth);

    // Set up Game State
    GameData GameState(&PlayBox, BombCount);

    // Start Game Loop
    Play(&Screen, &PlayBox, &Mines, &Player1, &GameState);
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

void ShowMenu(Display* ScreenPtr)
{
    ScreenPtr->AddStringToArray("Welcome to MineSweeper", 2 + ScreenPtr->ScreenWidth);
    ScreenPtr->AddStringToArray("======================", 2 + 2 * ScreenPtr->ScreenWidth);
    ScreenPtr->AddStringToArray("Choose A Difficulty", 2 + 5 * ScreenPtr->ScreenWidth);
    ScreenPtr->AddStringToArray("===================", 2 + 6 * ScreenPtr->ScreenWidth);
    ScreenPtr->AddStringToArray("    1. Easy", 2 + 7 * ScreenPtr->ScreenWidth);
    ScreenPtr->AddStringToArray("    2. Medium", 2 + 8 * ScreenPtr->ScreenWidth);
    ScreenPtr->AddStringToArray("    3. Hard", 2 + 9 * ScreenPtr->ScreenWidth);

    ScreenPtr->AddStringToArray("======================", 2 + 14 * ScreenPtr->ScreenWidth);
    ScreenPtr->AddStringToArray("Made By Camden Vaughan", 2 + 15 * ScreenPtr->ScreenWidth);
    ScreenPtr->AddStringToArray("www.CamdenVaughan.com", 2 + 16 * ScreenPtr->ScreenWidth);
    ScreenPtr->AddStringToArray("======================", 2 + 17 * ScreenPtr->ScreenWidth);

    // Move Cursor to Bottom Left
    ScreenPtr->MoveCursor(0, 29);

    // Print Screen
    ScreenPtr->PrintArrayToScreen();
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