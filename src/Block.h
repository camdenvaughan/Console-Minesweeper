#pragma once
enum class BlockState { Bomb, Safe };
enum class InteractState {Default, Hover, Flag, ClickSafe, Explode};

class Block
{
private:
	char ActiveSymbol = 0;


	BlockState State;
public:
	Block(BlockState state);

	void PrintSymbol() const;

	void ChangeSymbol(InteractState interactionState);

	char GetActiveSymbol() const;
};

