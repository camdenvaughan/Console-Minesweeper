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


public:
	Minefield(Playspace* PlayBox, const int& BombCount);

	void ShowAllBombs();

	void CheckSurroundingBlocks(int LocationX, int LocationY, struct GameData* GameState);

	Block& GetBlockAtLocation(const int& Location);

	Block GetBlockAtLocation(const int& Location)const;
};

