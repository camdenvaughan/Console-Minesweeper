#pragma once

#include "Block.h"
#include <vector>


class Map
{
	int MapSize;
	int BombCount;

	std::vector<Block> blocks;
private:

	std::vector<Block> GenerateMap(int mapSize, int numberOfBombs);


public:
	Map(int mapSize, int bombCount);
	wchar_t GetSymbolOnBlock(int location) const;
};

