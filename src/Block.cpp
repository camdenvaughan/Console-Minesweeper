#include "Block.h"
#include <iostream>

Block::Block(BlockState state) : State(state) 
{
	if (state == BlockState::Safe)
		ChangeSymbol(InteractState::Default);
	else
		ChangeSymbol(InteractState::Explode);
}

void Block::ChangeSymbol(InteractState interactionState)
{
	switch (interactionState)
	{
	case InteractState::Default:
		ActiveSymbol = L'O';
		break;
	case InteractState::Hover:
		ActiveSymbol = L'0';
		break;
	case InteractState::Flag:
		ActiveSymbol = L'P';
		break;
	case InteractState::ClickSafe:
		ActiveSymbol = L'.';
		break;
	case InteractState::Explode:
		ActiveSymbol = L'B';
		break;
	default:
		break;
	}
}

wchar_t Block::GetActiveSymbol() const
{
	return ActiveSymbol;
}
