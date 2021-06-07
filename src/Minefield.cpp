#include "Minefield.h"
#include <iostream>
#include <algorithm>
#include <ctime>


Minefield::Minefield(const int& PlaySpaceX, const int& PlaySpaceY, const int& PlayOffsetLeft, const int& PlayOffsetTop, const int& ScreenWidth, const int& BombCount) :
	PlaySpaceX(PlaySpaceX), PlaySpaceY(PlaySpaceY), PlayOffsetLeft(PlayOffsetLeft), PlayOffsetTop(PlayOffsetTop), ScreenWidth(ScreenWidth), BombCount(BombCount)
{
	Blocks.reserve(PlaySpaceX * PlaySpaceY);

	GenerateMinefield(PlaySpaceX * PlaySpaceY, BombCount, Blocks);
}

void Minefield::GenerateMinefield(int MapSize, int NumberOfBombs, std::vector<Block>& Blocks)
{
	for (int i = 0; i < MapSize; i++)
	{
		Blocks.emplace_back(Block(i < NumberOfBombs ? BlockState::Bomb : BlockState::Safe));
	}
	std::cout << std::endl;
	std::random_shuffle(Blocks.begin(), Blocks.end());
}

void Minefield::CheckSurroundingBlocks(int LocationX, int LocationY)
{
	//Blocks[LocationX * LocationY].State = BlockState::Clicked;

	//// Loop through 8 surrounding Blocks
	//for (int X = LocationX - 1; X < LocationX + 2; X++)
	//{
	//	for (int Y = LocationY - 1; Y < LocationY + 2; Y++)
	//	{
	//		// If the block has already been clicked (safe) or is outside the bounds of the play space, continue
	//		if (Blocks[X * Y].State == BlockState::Clicked || X < 0 || Y < 0 || X > PlaySpaceX || Y > PlaySpaceX)
	//			continue;
	//		// If the block is a bomb, increment the Adjacent BombCount
	//		if (Blocks[X * Y].State == BlockState::Bomb)
	//			Blocks[LocationX * LocationY].AddAdjacentBomb();
	//	}
	//}
	//// If the block contained no adjacent bombs, click and check the 8 surrounding blocks
	//if (Blocks[PlaySpaceToScreenConversion(LocationX, LocationY)].GetAdjacentBombs() == 0)
	//	for (int X = LocationX - 1; X < LocationX + 2; X++)
	//	{
	//		for (int Y = LocationY - 1; Y < LocationY + 2; Y++)
	//		{
	//			if (Blocks[X * Y].State == BlockState::Clicked || X < 0 || Y < 0 || X > PlaySpaceX || Y > PlaySpaceX)
	//				continue;
	//			CheckSurroundingBlocks(X, Y);
	//		}
	//	}
	//// Set the active symbol to show adjacent bombs
	//Blocks[PlaySpaceToScreenConversion(LocationX, LocationY)].ChangeSymbol(SymbolState::Number);
}

Block& Minefield::GetBlockAtLocation(const int& Location)
{
	return Blocks[Location];
}

Block Minefield::GetBlockAtLocation(const int& Location) const
{
	return Blocks[Location];
}