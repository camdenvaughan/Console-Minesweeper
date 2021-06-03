#pragma once
enum class BlockState { Bomb, Safe };
enum class InteractState {Default, Hover, Flag, ClickSafe, Explode};

class Block
{
private:
	wchar_t ActiveSymbol = 0;


	BlockState State;
public:
	Block(BlockState state);



	void ChangeSymbol(InteractState interactionState);

	wchar_t GetActiveSymbol() const;
};

