#pragma once

void InitGame(bool IsPlaying);

void Play(class Display* ScreenPtr, class Playspace* PlayBoxPtr, class Minefield* MinesPtr, class Player* PlayerPtr, struct GameData* GameStatePtr);

void ShowMenu(class Display* ScreenPtr);

void ShowRules(class Display* ScreenPtr, struct GameData* GameState);


