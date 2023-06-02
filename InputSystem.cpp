#include "InputSystem.h"

#include "Settings.h"

#include <iostream>
#include <string>
#include <random>
#include <format>

void InputSystem::begin() const
{
    getchar();
}

void InputSystem::getUserMove(int& _row, int& _col) const
{
    //Move move;
    std::string input;
    std::string colStr;
    int row;

    while (true) 
    {
        //std::cout << "Enter your move (column letter followed by row number): ";
        //std::cout << "Your move: ";
        std::cin >> input;

        char colChar = input[0];

        int boardSize = Settings::getInstance().boardSize;
        char lastLetter = 'A' + boardSize;

        // Check if the column letter is valid
        if (colChar >= 'A' && colChar <= lastLetter) 
        {
            input = input.substr(1);
            
            // Try to convert row string to integer
            try {
                int row = std::stoi(input);

                // Check if the row number is valid
                if (row >= 0 && row <= 9) {
                    // Convert row number to index (assuming zero-based indexing)
                    _row = colChar - 'A';
                    _col = row;
                    return;
                }
                else {
                    std::cout << std::format("Invalid row number. Please enter a number between 1 and {}.", boardSize) << std::endl;
                }
            }
            catch (const std::invalid_argument& e) {
                std::cout << std::format("Invalid row number. Please enter a number between 1 and {}.", boardSize) << std::endl;
            }
        }
        else 
        {
            std::cout << std::format("Invalid column letter. Please enter a single letter between A and {}.", lastLetter) << std::endl;
        }
    }
}

void InputSystem::makeRandomMove(int& row, int& col) const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> rowDist(0, Settings::getInstance().boardSize - 1);
    std::uniform_int_distribution<int> colDist(0, Settings::getInstance().boardSize - 1);

    row = rowDist(gen);
    col = colDist(gen);
}
