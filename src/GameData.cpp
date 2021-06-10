#include "GameData.h"
#include "Playspace.h"
#include "Display.h"

GameData::GameData(Playspace* PlayBox, const int& BombCount) 
	: TotalSafeSquares(PlayBox->PlaySpaceX* PlayBox->PlaySpaceY - BombCount) 
{}

bool GameData::IsGamePlaying(Display* Screen)
{
		if (SafeSquaresClicked == TotalSafeSquares)
		{
			//Win State
			Screen->AddStringToArray("YOU WIN!", 5 + Screen->ScreenWidth);
			Screen->AddStringToArray("Press 'Enter' to continue!", 5 + 3 * Screen->ScreenWidth);
			return false;
		}
		else if (GameIsOver == true)
		{
			//Lost State
			Screen->AddStringToArray("You Lose...", 5 + Screen->ScreenWidth);
			Screen->AddStringToArray("Press 'Enter' to continue!", 5 + 3 * Screen->ScreenWidth);
			return false;
		}
		return true;
}