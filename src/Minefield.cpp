#include "Minefield.h"
#include "Block.h"
#include "Playspace.h"
#include "GameData.h"
#include <algorithm>
#include <ctime>


Minefield::Minefield(Playspace* PlayBox, const int& BombCount) 
	: PlayBox(PlayBox), BombCount(BombCount)
{
	Blocks.reserve(PlayBox->PlaySpaceX * PlayBox->PlaySpaceY);
	SafeBlockCoords.reserve(PlayBox->PlaySpaceX * PlayBox->PlaySpaceY - BombCount);

	GenerateMinefield();
}

// Creates the minefield
void Minefield::GenerateMinefield()
{
	for (int i = 0; i < PlayBox->PlaySpaceX * PlayBox->PlaySpaceY; i++)
	{
		Blocks.emplace_back(Block(i < BombCount ? BlockState::Bomb : BlockState::Safe));
	}
	std::random_shuffle(Blocks.begin(), Blocks.end());
}

// Counts up all the surrounding bombs
void Minefield::AddAdjacentBombs(const int& LocationX, const int& LocationY)
{
	// Loop through 8 surrounding Blocks
	for (int X = LocationX - 1; X < LocationX + 2; X++)
	{
		for (int Y = LocationY - 1; Y < LocationY + 2; Y++)
		{
			// If the block has already been clicked (safe) or is outside the bounds of the play space, continue
			if (X < 0 || Y < 0 || X > PlayBox->PlaySpaceX - 1 || Y > PlayBox->PlaySpaceY - 1)
			{

			}
			else if (Blocks[PlayBox->CoordsToPlaySpace(X, Y)].State == BlockState::Clicked)
			{

			}
			// If the block is a bomb, increment the Adjacent BombCount
			else
			{
				if (Blocks[PlayBox->CoordsToPlaySpace(X, Y)].State == BlockState::Bomb)
					Blocks[PlayBox->CoordsToPlaySpace(LocationX, LocationY)].AddAdjacentBomb();
			}
		}
	}
}

void Minefield::CheckSurroundingBlocks(const int& LocationX, const int& LocationY, GameData* GameState)
{
	// Set Block to Clicked and Increment the Safe Squares Clicked
	Blocks[PlayBox->CoordsToPlaySpace(LocationX, LocationY)].State = BlockState::Clicked;
	GameState->SafeSquaresClicked++;

	// Ensures that the first click has 0 surrounding bombs
	if (GameState->IsFirstClick)
	{
		AddAdjacentBombs(LocationX, LocationY);
		while (Blocks[PlayBox->CoordsToPlaySpace(LocationX, LocationY)].GetAdjacentBombs() != 0)
		{
			GenerateMinefield();
			AddAdjacentBombs(LocationX, LocationY);
		}
		GameState->IsFirstClick = false;
	}
	else
		AddAdjacentBombs(LocationX, LocationY);


	// If the block contained no adjacent bombs, click and check the 8 surrounding blocks
	if (Blocks[PlayBox->CoordsToPlaySpace(LocationX, LocationY)].GetAdjacentBombs() == 0)
		for (int X = LocationX - 1; X < LocationX + 2; X++)
		{
			for (int Y = LocationY - 1; Y < LocationY + 2; Y++)
			{
				if (X < 0 || Y < 0 || X > PlayBox->PlaySpaceX - 1 || Y > PlayBox->PlaySpaceY - 1)
					continue;
				else if (Blocks[PlayBox->CoordsToPlaySpace(X, Y)].State == BlockState::Clicked)
					continue;
				else if (Blocks[PlayBox->CoordsToPlaySpace(X, Y)].IsFlagged)
					continue;
				else
					CheckSurroundingBlocks(X, Y, GameState);
			}
		}
	// Set the active symbol to show adjacent bombs
	Blocks[PlayBox->CoordsToPlaySpace(LocationX, LocationY)].ChangeSymbol(SymbolState::Number);
}

// Returns a Mine given a coordinate
Block& Minefield::GetBlockAtLocation(const int& Location)
{
	return Blocks[Location];
}

// Const version of GetBlockAtLocation
Block Minefield::GetBlockAtLocation(const int& Location) const
{
	return Blocks[Location];
}

// Shows all the bombs upon losing
void Minefield::ShowAllBombs()
{
	for (int i = 0; i < Blocks.size(); i++)
	{
		if (Blocks[i].State == BlockState::Bomb)
		{
			if (Blocks[i].IsFlagged)
				Blocks[i].ChangeSymbol(SymbolState::FlaggedBomb);
			else
				Blocks[i].ChangeSymbol(SymbolState::UndetonatedBomb);
		}
	}

}