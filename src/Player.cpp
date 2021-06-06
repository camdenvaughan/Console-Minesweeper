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
    if (Location.X > PlaySpaceX - 1)
        Location.X = PlaySpaceX - 1;
    if (Location.X < 0)
        Location.X = 0;
}

bool Player::RecieveInput()
{
    for (int k = 0; k < 4; k++)
        Key[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x26\x28"[k]))) != 0;
    if (Key[0])
    {
        Location.X++;
        return true;
    }
    if (Key[1])
    {
        Location.X--;
        return true;
    }
    if (Key[2])
    {
        Location.Y--;
        return true;
    }
    if (Key[3])
    {
        Location.Y++;
        return true;
    }
    return false;
}