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

std::map<int, Block> Minefield::GenerateBlockMap()
{

	// Create Coordinate Keys for each block
	int i = 0; // block reference
	for (int playX = 0; playX < PlaySpaceX; playX++)
	{
		for (int playY = 0; playY < PlaySpaceY; playY++)
		{
			BlockMap[(playX + PlayOffsetLeft) + (playY + PlayOffsetTop) * ScreenWidth] = Blocks[i++];
		}
	}
	return BlockMap;
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

void Minefield::CheckSurroundingBlocks(int Location)
{
	//check 8 surrounding blocks
	//make sure they arent already visible

	//show the ones that arent bombs
	//get the ones at 0 to check
}

Block Minefield::GetBlockAtLocation(int Location)
{
	return BlockMap[Location];
}