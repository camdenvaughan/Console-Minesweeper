#include "Block.h"

Block::Block(BlockState state) 
	: State(state) 
{
	ChangeSymbol(SymbolState::Default);
}

// Handle Symbol Changes
void Block::ChangeSymbol(SymbolState interactionState)
{
	switch (interactionState)
	{
	case SymbolState::Default:
		ActiveSymbol = L'\uFFFD'; // Unicode for Question Mark Box
		break;
	case SymbolState::Flag:
		ActiveSymbol = L'F';
		break;
	case SymbolState::Number:
		if (AdjacentBombs == 0)
		{
			ActiveSymbol = L' ';
			break;
		}
		ActiveSymbol = WCharNumberIndex[AdjacentBombs];
		break;
	case SymbolState::ExplodedBomb:
		ActiveSymbol = L'X';
		break;
	case SymbolState::FlaggedBomb:
		ActiveSymbol = L'Y';
		break;
	case SymbolState::UndetonatedBomb:
		ActiveSymbol = L'x';
		break;
	default:
		break;
	}
}

// Increment Addjacent bombs
void Block::AddAdjacentBomb()
{
	AdjacentBombs++;
}

// Return Symbol
wchar_t Block::GetActiveSymbol() const
{
	return ActiveSymbol;
}

// Return Adjacent Bombs
int Block::GetAdjacentBombs() const
{
	return AdjacentBombs;
}
