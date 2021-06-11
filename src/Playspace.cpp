#include "Playspace.h"
#include "Display.h"
#include "Minefield.h"
#include "Block.h"

Playspace::Playspace(const int& PlaySpaceX, const int& PlaySpaceY, const int& OffsetLeft, const int& OffsetTop, const int& ScreenWidth)
	: PlaySpaceX(PlaySpaceX), PlaySpaceY(PlaySpaceY), OffsetLeft(OffsetLeft), OffsetTop(OffsetTop), ScreenWidth(ScreenWidth), PlaySpace(new wchar_t[PlaySpaceX * PlaySpaceY])
{}

Playspace::Playspace() 
    : PlaySpaceX(10), PlaySpaceY(10), OffsetLeft(5), OffsetTop(5), ScreenWidth(50), PlaySpace(new wchar_t[PlaySpaceX * PlaySpaceY])
{}

Playspace::~Playspace()
{
    delete[] PlaySpace;
}

// Converts Cordinates to the single dimensional array of the Display
int Playspace::PlaySpaceToScreenSpace(const int& X, const int& Y) const
{
    return (X + OffsetLeft) + (Y + OffsetTop) * ScreenWidth;
}

// Converts Cordinates to the single dimensional array of the Play Space
int Playspace::CoordsToPlaySpace(const int& X, const int& Y) const
{
    return X + Y * PlaySpaceX;
}

// Adds a WChar_T to the PlaySpaceArray
void Playspace::AddWCharToArray(const wchar_t& C, const int& Position)
{
    PlaySpace[Position] = C;

}

// Writes the Values of the PlaySpace Array to the Display + Adds a border
void Playspace::WritePlaySpaceToScreen(Display* Screen)
{
    // Border
    for (int X = 0; X < PlaySpaceX+2; X++)
    {
        Screen->AddWCharToArray(L'\u2588', (X + OffsetLeft - 1) + (OffsetTop - 1) * ScreenWidth);
    }
    for (int X = 0; X < PlaySpaceX + 2; X++)
    {
        Screen->AddWCharToArray(L'\u2588', (X + OffsetLeft - 1) + (PlaySpaceY + OffsetTop) * ScreenWidth);
    }
    for (int Y = 0; Y < PlaySpaceY; Y++)
    {
        Screen->AddWCharToArray(L'\u2588', (OffsetLeft - 1) + (Y + OffsetTop) * ScreenWidth);
    }
    for (int Y = 0; Y < PlaySpaceY; Y++)
    {
        Screen->AddWCharToArray(L'\u2588', (OffsetLeft + PlaySpaceX) + (Y + OffsetTop) * ScreenWidth);
    }

    // PlaySpace Content
    int i = 0;
    for (int playY = 0; playY < PlaySpaceY; playY++)
    {
        for (int playX = 0; playX < PlaySpaceX; playX++)
        {
            Screen->AddWCharToArray(PlaySpace[i++], PlaySpaceToScreenSpace(playX, playY));
        }
    }
}

// Fills the Playspace Array with the Minefield
void Playspace::FillWithMinefield(Minefield* Mines)
{
    for (int  i = 0; i < PlaySpaceX * PlaySpaceY; i++)
    {
        PlaySpace[i] = Mines->GetBlockAtLocation(i).GetActiveSymbol();
    }
}