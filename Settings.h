#pragma once
#include <vector>

#include <fstream>
#include "json.hpp"

struct Settings 
{
    //int boardSize;
    //std::vector<int> shipSizes;
    //int numShips;
    //int numGuesses;

    //constexpr int opponentHistoryLimit = 10;

    int boardSize = 10;
    std::vector<int> shipSizes = { 5, 4, 3, 3, 2 };
    int numShips = 5;
    int numGuesses = 50;

    static Settings& getInstance() 
    {
        static Settings instance;
        return instance;
    }

private:
    Settings();
};
