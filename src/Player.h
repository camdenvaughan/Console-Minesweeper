#pragma once
struct Coords
{
	int X = 0, Y = 0;
};

class Player
{
private:

	int PlaySpaceX, PlaySpaceY;

	bool Key[4];

private:

	void ClampPlayerLocation();

public:

	Coords Location;
public:

	Player(int PlaySpaceX, int PlaySpaceY);

	bool RecieveInput();
};

