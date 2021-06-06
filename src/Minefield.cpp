#include "Minefield.h"
#include <iostream>
#include <algorithm>
#include <ctime>


std::map<int, Block> Minefield::GenerateBlockMap(int PlaySpaceX, int PlaySpaceY, int BombCount, int PlayOffsetLeft, int PlayOffsetTop, int ScreenWidth)
{
	std::vector<Block> blocks;
	blocks.reserve(PlaySpaceX * PlaySpaceY);

	GenerateMinefield(PlaySpaceX * PlaySpaceY, BombCount, blocks);

	// Initialize Map
	std::map<int, Block> BlockMap;

	// Create Coordinate Keys for each block
	int i = 0; // block reference
	for (int playX = 0; playX < PlaySpaceX; playX++)
	{
		for (int playY = 0; playY < PlaySpaceY; playY++)
		{
			BlockMap[(playX + PlayOffsetLeft) + (playY + PlayOffsetTop) * ScreenWidth] = blocks[i++];
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