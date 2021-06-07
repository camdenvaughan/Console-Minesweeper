#include "Playspace.h"
#include "Display.h"
#include "Minefield.h"
#include "Block.h"

Playspace::Playspace(const int& PlaySpaceX, const int& PlaySpaceY, const int& OffsetLeft, const int& OffsetTop, const int& ScreenWidth)
	: PlaySpaceX(PlaySpaceX), PlaySpaceY(PlaySpaceY), OffsetLeft(OffsetLeft), OffsetTop(OffsetTop), ScreenWidth(ScreenWidth), PlaySpace(new wchar_t[PlaySpaceX * PlaySpaceY])
{

}

Playspace::Playspace() 
    : PlaySpaceX(10), PlaySpaceY(10), OffsetLeft(5), OffsetTop(5), ScreenWidth(50), PlaySpace(new wchar_t[PlaySpaceX * PlaySpaceY])
{}

Playspace::~Playspace()
{
    delete[] PlaySpace;
}

int Playspace::PlaySpaceToScreenSpace(const int& X, const int& Y) const
{
    return (X + OffsetLeft) + (Y + OffsetTop) * ScreenWidth;
}

int Playspace::CoordsToPlaySpace(const int& X, const int& Y) const
{
    return X + Y * PlaySpaceX;
}
void Playspace::AddWCharToArray(const wchar_t& C, const int& Position)
{
    PlaySpace[Position] = C;

}

void Playspace::WritePlaySpaceToScreen(Display& Screen)
{
    int i = 0;
    for (int playY = 0; playY < PlaySpaceY; playY++)
    {
        for (int playX = 0; playX < PlaySpaceX; playX++)
        {
            Screen.AddWCharToArray(PlaySpace[i++], PlaySpaceToScreenSpace(playX, playY));
        }
    }
}

void Playspace::FillWithMinefield(Minefield& Mines)
{
    for (int  i = 0; i < PlaySpaceX * PlaySpaceY; i++)
    {
        PlaySpace[i] = Mines.GetBlockAtLocation(i).GetActiveSymbol();
    }
}