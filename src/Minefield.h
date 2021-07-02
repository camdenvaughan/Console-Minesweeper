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

	void AddAdjacentBombs(const int& LocationX, const int& LocationY);

public:

	bool BombsAreShown = false; // Debug

public:
	Minefield(Playspace* PlayBox, const int& BombCount);

	void GenerateMinefield();

	void ShowAllBombs();

	void CheckSurroundingBlocks(const int& LocationX, const int& LocationY, struct GameData* GameState);

	Block& GetBlockAtLocation(const int& Location);

	Block GetBlockAtLocation(const int& Location)const;
};

