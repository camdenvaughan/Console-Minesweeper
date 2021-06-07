#include "GameData.h"
#include "Playspace.h"

GameData::GameData(Playspace* PlayBox, const int& BombCount) 
	: TotalSafeSquares(PlayBox->PlaySpaceX* PlayBox->PlaySpaceY - BombCount) 
{}

bool GameData::IsGamePlaying()
{
	if (GameIsOver == true)
	{
		if (SafeSquaresClicked == TotalSafeSquares)
		{
			//Win State
			return false;
		}
		else
		{
			//Lost State
			return false;
		}
	}

}