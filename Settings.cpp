#include "Settings.h"

#include <fstream>
#include "json.hpp"

Settings::Settings() 
{
    //return;

    /*std::ifstream configFile("config.json");
    nlohmann::json config;
    configFile >> config;

    boardSize = config["boardSize"];
    shipSizes = config["shipSizes"].get<std::vector<int>>();
    numShips = config["numShips"];
    numGuesses = config["numGuesses"];*/
}