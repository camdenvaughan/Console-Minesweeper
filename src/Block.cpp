#include "Block.h"
#include <iostream>

Block::Block(BlockState state) 
	: State(state) 
{
		ChangeSymbol(SymbolState::Default);
}

void Block::ChangeSymbol(SymbolState interactionState)
{
	switch (interactionState)
	{
	case SymbolState::Default:
		ActiveSymbol = L'#';
		break;
	case SymbolState::Flag:
		ActiveSymbol = L'P';
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
