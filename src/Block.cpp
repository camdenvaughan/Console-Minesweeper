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
		ActiveSymbol = L'O';
		break;
	case SymbolState::Flag:
		ActiveSymbol = L'2';
		break;
	case SymbolState::Number:
		if (AdjacentBombs == 0)
		{
			ActiveSymbol = L' ';
			break;
		}
		ActiveSymbol = WCharNumberIndex[AdjacentBombs];
		break;
	case SymbolState::Explode:
		ActiveSymbol = L'B';
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
