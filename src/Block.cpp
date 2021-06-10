#include "Block.h"
#include <iostream>

Block::Block(BlockState state) 
	: State(state) 
{
	if (State == BlockState::Bomb)
		ChangeSymbol(SymbolState::Default);
	else
		ChangeSymbol(SymbolState::Default);
}

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

void Block::AddAdjacentBomb()
{
	AdjacentBombs++;
}

wchar_t Block::GetActiveSymbol() const
{
	return ActiveSymbol;
}

int Block::GetAdjacentBombs() const
{
	return AdjacentBombs;
}
