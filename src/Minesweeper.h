#pragma once
#include <map>
#include "Minefield.h"
#include "Player.h"

void Menu();

void Play();

bool RecieveInput(Minefield* Mines, Player& Player1, int CurrentPos);

