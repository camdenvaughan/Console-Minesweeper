#pragma once

struct GameData
{
private:
	const int TotalSafeSquares;
public:

	bool GameIsOver = false;

	int SafeSquaresClicked = 0;

	GameData(class Playspace* PlayBox, const int& BombCount);
	bool IsGamePlaying();
};