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
			Screen->AddStringToArray("YOU WIN!", 10 + 2 * Screen->ScreenWidth);
			Screen->AddStringToArray("========", 10 + 3 * Screen->ScreenWidth);
			Screen->AddStringToArray("Press Enter to continue!", 10 + 4 * Screen->ScreenWidth);
			return false;
		}
		else if (GameIsOver == true)
		{
			//Lost State
			Screen->AddStringToArray("You Lose...", 10 + 2 * Screen->ScreenWidth);
			Screen->AddStringToArray("===========", 10 + 3 * Screen->ScreenWidth);
			Screen->AddStringToArray("Press Enter to continue!", 10 + 4 * Screen->ScreenWidth);
			return false;
		}
		return true;
}