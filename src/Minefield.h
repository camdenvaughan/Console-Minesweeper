#pragma once

#include "Block.h"
#include <vector>
#include <map>


class Minefield
{
private:
	const int PlaySpaceX, PlaySpaceY;
	const int PlayOffsetLeft, PlayOffsetTop, ScreenWidth;
	const int BombCount;
	std::vector<Block> Blocks;
	std::map<int, Block> BlockMap;

private:
	void GenerateMinefield(int MapSize, int NumberOfBombs, std::vector<Block>& Blocks);

	std::map<int, Block> GenerateBlockMap();
	void CheckSurroundingBlocks(int Location);

public:
	Minefield(const int& PlaySpaceX, const int& PlaySpaceY, const int& PlayOffsetLeft, const int& PlayOffsetTop, const int& ScreenWidth, const int& BombCount);
	Block GetBlockAtLocation(int Location);
};

