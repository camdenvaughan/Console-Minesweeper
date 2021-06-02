#include <iostream>
#include "MapGeneration.h"

int main()
{
    std::cout << "Welcome to MineSweeper\n";
    std::cout << "======================\n\n";

    int MapSize, Bombs;
    std::cout << "Enter Map Size\n";
    std::cin >> MapSize;
    std::cout << "Mape Size is : " << MapSize << std::endl;
    std::cout << "Enter Bomb Count\n";
    std::cin >> Bombs;
    std::cout << "Bomb count is : " << Bombs << std::endl;
    std::cout << "\nPress Enter to Generate Map\n";
    std::cin.get();

    // Generate Map
    MapGeneration::GenerateMap(MapSize, Bombs);
    std::cin.get();
}

