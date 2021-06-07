#pragma once
class Input
{
public:
	static bool RecieveInput(class Minefield* Mines, class Player* Player1, class Playspace* PlayBox, struct GameData* GameState);

	static bool WaitForEnter();
};

