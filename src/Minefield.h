#pragma once

#include "Block.h"
#include <vector>



class Minefield
{
private:
	const int PlaySpaceX, PlaySpaceY, PlayOffsetTop, PlayOffsetLeft, ScreenWidth;
	const int BombCount;
	std::vector<Block> Blocks;

private:
	void GenerateMinefield(int MapSize, int NumberOfBombs, std::vector<Block>& Blocks);

	void CheckSurroundingBlocks(int LocationX, int LocationY);

public:
	Minefield(const int& PlaySpaceX, const int& PlaySpaceY, const int& PlayOffsetLeft, const int& PlayOffsetTop, const int& ScreenWidth, const int& BombCount);
	Block& GetBlockAtLocation(const int& Location);
	Block GetBlockAtLocation(const int& Location)const;
};

