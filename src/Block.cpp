#include "Block.h"
#include <iostream>

Block::Block(BlockState state) : State(state) 
{

	if (State == BlockState::Bomb)
		std::cout << "Q, ";
	else if (State == BlockState::Safe)
		std::cout << "#, ";
	else
		std::cout << "Error No State :/" << std::endl;
}

void Block::PrintSymbol() const
{
	if (State == BlockState::Bomb)
		std::cout << "Q, ";
	else if (State == BlockState::Safe)
		std::cout << "#, ";
	else
		std::cout << "no state :/" << std::endl;
}

void Block::ChangeSymbol(InteractState interactionState)
{
	switch (interactionState)
	{
	case InteractState::Default:
		ActiveSymbol = 'O';
		break;
	case InteractState::Hover:
		ActiveSymbol = '0';
		break;
	case InteractState::Flag:
		ActiveSymbol = 'P';
		break;
	case InteractState::ClickSafe:
		ActiveSymbol = '.';
		break;
	case InteractState::Explode:
		ActiveSymbol = 'B';
		break;
	default:
		break;
	}
}

char Block::GetActiveSymbol() const
{
	return ActiveSymbol;
}
