#pragma once

#include "Block.h"
#include <vector>
#include <map>


class Minefield
{
private:

	static void GenerateMinefield(int MapSize, int NumberOfBombs, std::vector<Block>& Blocks);

public:

	static std::map<int, Block> GenerateBlockMap(int PlaySpaceX, int PlaySpaceY, int BombCount, int PlayOffsetLeft, int PlayOffsetTop, int ScreenWidth);
};

