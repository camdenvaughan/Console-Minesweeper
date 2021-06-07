#pragma once

#include <vector>

class Playspace;
class Block;
class Minefield
{
private:
	Playspace* PlayBox;
	const int BombCount;
	std::vector<Block> Blocks;

private:
	void GenerateMinefield(int MapSize, int NumberOfBombs, std::vector<class Block>& Blocks);

	void CheckSurroundingBlocks(int LocationX, int LocationY);

public:
	Minefield(Playspace* PlayBox, const int& BombCount);
	Block& GetBlockAtLocation(const int& Location);
	Block GetBlockAtLocation(const int& Location)const;
};

