#pragma once

class Minefield;
class Display;
class Playspace
{
private:
	wchar_t* PlaySpace;
public:
	const int PlaySpaceX, PlaySpaceY, OffsetLeft, OffsetTop, ScreenWidth;

	Playspace(const int& PlaySpaceX, const int& PlaySpaceY, const int& OffsetLeft, const int& OffsetTop, const int& ScreenWidth);
	Playspace();

	~Playspace();

	int PlaySpaceToScreenSpace(const int& X, const int& Y) const;

	int CoordsToPlaySpace(const int& X, const int& Y) const;

	void WritePlaySpaceToScreen(Display* Screen);

	void FillWithMinefield(Minefield* mines);

	void AddWCharToArray(const wchar_t& C, const int& Position);
};

