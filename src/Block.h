#pragma once

enum class BlockState { Bomb, Safe, Clicked };
enum class SymbolState {Default, Flag, Number, Explode};

class Block
{
private:
	wchar_t ActiveSymbol = 0;

	int AdjacentBombs;

public:

	BlockState State;

public:

	Block(BlockState state);

	void ChangeSymbol(SymbolState interactionState);

	void AddAdjacentBomb();

	wchar_t GetActiveSymbol() const;

	int GetAdjacentBombs() const;
};

