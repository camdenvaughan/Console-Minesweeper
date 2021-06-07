#pragma once

enum class BlockState { Bomb, Safe, Clicked };
enum class SymbolState {Default, Flag, Number, ExplodedBomb, FlaggedBomb, UndetonatedBomb};

class Block
{
private:
	wchar_t ActiveSymbol = 0;

	int AdjacentBombs = 0;

	wchar_t WCharNumberIndex[10] = { L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9' };

public:

	BlockState State;
	bool IsFlagged = false;
public:

	Block(BlockState state);

	void ChangeSymbol(SymbolState interactionState);

	void AddAdjacentBomb();

	wchar_t GetActiveSymbol() const;

	int GetAdjacentBombs() const;
};

