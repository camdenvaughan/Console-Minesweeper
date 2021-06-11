#include "Input.h"
#include "Minefield.h"
#include "Player.h"
#include "Playspace.h"
#include "Block.h"
#include "GameData.h"

#include <Windows.h>

#define F_KEY 0x46
#define ONE_KEY 0x31
#define TWO_KEY 0x32
#define THREE_KEY 0x33
#define FOUR_KEY 0x34

bool Input::RecieveInput(Minefield* Mines, Player* Player1, Playspace* PlayBox, GameData* GameState)
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
        if (Mines->GetBlockAtLocation(PlayBox->CoordsToPlaySpace(Player1->Location.X, Player1->Location.Y)).State == BlockState::Clicked)
            return true;
        // Click
        if (Mines->GetBlockAtLocation(PlayBox->CoordsToPlaySpace(Player1->Location.X, Player1->Location.Y)).State == BlockState::Bomb)
        {
            if (GameState->IsFirstClick)
            {
                // Swap a bomb with a safe square
                while (Mines->GetBlockAtLocation(PlayBox->CoordsToPlaySpace(Player1->Location.X, Player1->Location.Y)).State == BlockState::Bomb)
                {
                    Mines->GenerateMinefield();
                }
                Mines->CheckSurroundingBlocks(Player1->Location.X, Player1->Location.Y, GameState);
                GameState->IsFirstClick = false;
                return false;
            }
            GameState->GameIsOver = true;
            // Show All Bombs
            Mines->ShowAllBombs();
            // Set this Bomb to be uppercase X
            Mines->GetBlockAtLocation(PlayBox->CoordsToPlaySpace(Player1->Location.X, Player1->Location.Y)).ChangeSymbol(SymbolState::ExplodedBomb);
            return false;
        }
        // Sets State to clicked, checks the amount of blocks, and clicks any surrounding empty blocks
        Mines->CheckSurroundingBlocks(Player1->Location.X, Player1->Location.Y, GameState);
        GameState->IsFirstClick = false;

        return false;
    }
    if (GetAsyncKeyState(F_KEY)) // F Key
    {
        if (Mines->GetBlockAtLocation(PlayBox->CoordsToPlaySpace(Player1->Location.X, Player1->Location.Y)).State == BlockState::Clicked)
            return false;
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

bool Input::MenuInput(int& PlayX, int& PlayY, int& BombCount)
{
    if (GetAsyncKeyState(ONE_KEY) || GetAsyncKeyState(VK_NUMPAD1))
    {
        PlayX = 9;
        PlayY = 9;
        BombCount = 10;
        return false;
    }
    if (GetAsyncKeyState(TWO_KEY) || GetAsyncKeyState(VK_NUMPAD2))
    {
        PlayX = 16;
        PlayY = 16;
        BombCount = 45;
        return false;
    }
    if (GetAsyncKeyState(THREE_KEY) || GetAsyncKeyState(VK_NUMPAD3))
    {
        PlayX = 30;
        PlayY = 16;
        BombCount = 99;
        return false;
    }
    if (GetAsyncKeyState(FOUR_KEY) ||GetAsyncKeyState(VK_NUMPAD4))
    {
        return true;
    }
    return true;
}

void Input::WaitForEnter()
{
    bool EnterWasNotPressed = true;
    while (EnterWasNotPressed)
    {
        if (GetAsyncKeyState(VK_RETURN))
            EnterWasNotPressed = false;
    }
}
