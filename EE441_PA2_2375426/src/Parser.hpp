#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//Include stack and tile
#include "Stack.hpp"
#include "Tile.hpp"
bool parseFile(const std::string& NameBase, int turn, Stack<Tile>* tileStack) {

    std::string fileName = NameBase + std::to_string(turn) + ".txt";
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string tileStr;

        while (lineStream >> tileStr) {
            if (tileStr.size() != 2) {
                std::cerr << "Invalid tile format: " << tileStr << std::endl;
                continue;
            }
            char suit = tileStr[0];
            int number = tileStr[1] - '0'; // Convert character digit to int

            if ((suit == 'B' || suit == 'C' || suit == 'D') && (number >= 1 && number <= 9)) {
                tileStack->push_back(Tile(suit, number));
            }
            else {
                std::cerr << "Invalid tile: " << tileStr << std::endl;
            }
        }
    }

    file.close();
    return true;
}