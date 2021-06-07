#pragma once
#include "Minefield.h"
#include "Display.h"

class Playspace
{
private:
	const int PlaySpaceX, PlaySpaceY, OffsetLeft, OffsetTop, ScreenWidth;
	wchar_t* PlaySpace;

public:
	Playspace(const int& PlaySpaceX, const int& PlaySpaceY, const int& OffsetLeft, const int& OffsetTop, const int& ScreenWidth);
	~Playspace();
	int PlaySpaceToScreenSpace(const int& X, const int& Y) const;
	int CoordsToPlaySpace(const int& X, const int& Y) const;
	void WritePlaySpaceToScreen(Display& Screen);
	void FillWithMinefield(Minefield& Mines);
	void AddWCharToArray(const wchar_t& C, const int& Position);
};

