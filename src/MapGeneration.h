#pragma once
#include "Block.h"
#include <vector>


class MapGeneration
{
private:
	static void ShuffleMap(std::vector<Block>& blocks);
public:
	static std::vector<Block> GenerateMap(int mapSize, int numberOfBombs);
};

