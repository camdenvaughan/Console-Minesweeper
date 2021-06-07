#include "Player.h"
#include <Windows.h>


Player::Player(int PlaySpaceX, int PlaySpaceY) 
	: PlaySpaceX(PlaySpaceX), PlaySpaceY(PlaySpaceY)
{}

void Player::ClampPlayerLocation()
{
    // Clamp Y movement to Play Space
    if (Location.Y > PlaySpaceY - 1)
        Location.Y = PlaySpaceY - 1;
    if (Location.Y < 0)
        Location.Y = 0;

    // Clamp X movement to Play Space
    if (Location.X > PlaySpaceX- 1)
        Location.X = PlaySpaceX- 1;
    if (Location.X < 0)
        Location.X = 0;
}