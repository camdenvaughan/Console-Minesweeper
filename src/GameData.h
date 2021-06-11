#pragma once

struct GameData
{
private:
	const int TotalSafeSquares;
public:
	bool IsFirstClick = true;

	bool GameIsOver = false;

	bool AreRulesToggled = false;

	int SafeSquaresClicked = 0;

	GameData(class Playspace* PlayBox, const int& BombCount);
	bool IsGamePlaying(class Display* Screen);
};