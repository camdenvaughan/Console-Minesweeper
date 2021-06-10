#pragma once
class Input
{
public:
	Input() = delete;

	static bool RecieveInput(class Minefield* Mines, class Player* Player1, class Playspace* PlayBox, struct GameData* GameState);

	static bool MenuInput(int& PlayX, int& PlayY, int& BombCount);

	static void WaitForEnter();
};

