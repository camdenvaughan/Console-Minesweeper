#pragma once


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

	void WritePlaySpaceToScreen(class Display& Screen);

	void FillWithMinefield(class Minefield& mines);

	void AddWCharToArray(const wchar_t& C, const int& Position);
};

