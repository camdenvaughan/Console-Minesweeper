#pragma once

struct Coords
{
	int X = 0, Y = 0;
};

class Player
{
private:

	int PlaySpaceX, PlaySpaceY;

public:

	Coords Location;

public:

	Player(int PlaySpaceX, int PlaySpaceY);
	void ClampPlayerLocation();