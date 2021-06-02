#include "MapGeneration.h"
#include <iostream>
#include <algorithm>
#include <ctime>

std::vector<Block> MapGeneration::GenerateMap(int mapSize, int numberOfBombs)
{
	std::vector<Block> blocks;
	blocks.reserve(mapSize);
	for (int i = 0; i < mapSize; i++)
	{
		blocks.emplace_back(Block(i < numberOfBombs ? BlockState::Bomb : BlockState::Safe));

	}
	std::cout << std::endl;
	ShuffleMap(blocks);
	return blocks;
}
void MapGeneration::ShuffleMap(std::vector<Block>& blocks)
{
	std::cout << std::endl;
	srand(time(NULL));
	std::random_shuffle(blocks.begin(), blocks.end());
	for (unsigned int i = 0; i < blocks.size(); i++)
	{
		blocks[i].PrintSymbol();
	}
	std::cout << std::endl;
}