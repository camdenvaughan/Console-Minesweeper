#include "Map.h"
#include <iostream>
#include <algorithm>
#include <ctime>


Map::Map(int mapSize, int bombCount) 
	: MapSize(mapSize), BombCount(bombCount)
{
	blocks.reserve(MapSize);
	GenerateMap(MapSize, BombCount);
}

std::vector<Block> Map::GenerateMap(int mapSize, int numberOfBombs)
{
	for (int i = 0; i < mapSize; i++)
	{
		blocks.emplace_back(Block(i < numberOfBombs ? BlockState::Bomb : BlockState::Safe));
	}
	std::cout << std::endl;
	std::random_shuffle(blocks.begin(), blocks.end());
	return blocks;
}

wchar_t Map::GetSymbolOnBlock(int location) const
{
	if (location < blocks.size())
		return blocks[location].GetActiveSymbol();
	else
		return 0;
}