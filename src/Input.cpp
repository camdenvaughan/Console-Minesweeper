#include "Input.h"
#include "Minefield.h"
#include "Player.h"
#include "Playspace.h"
#include "Block.h"
#include "GameData.h"

#include <Windows.h>

#define F_KEY 0x46
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
        // Click
        if (Mines->GetBlockAtLocation(PlayBox->CoordsToPlaySpace(Player1->Location.X, Player1->Location.Y)).State == BlockState::Bomb)
        {
            GameState->GameIsOver = true;
            // Show All Bombs
            Mines->ShowAllBombs();
            // Set this Bomb to be uppercase X
            Mines->GetBlockAtLocation(PlayBox->CoordsToPlaySpace(Player1->Location.X, Player1->Location.Y)).ChangeSymbol(SymbolState::ExplodedBomb);
            return false;
        }

        // Sets State to clicked, checks the amount of blocks, and clicks any surrounding empty blocks
        Mines->CheckSurroundingBlocks(Player1->Location.X, Player1->Location.Y, GameState);

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

bool Input::WaitForEnter()
{
    if (GetAsyncKeyState(VK_RETURN))
        return false;
}
