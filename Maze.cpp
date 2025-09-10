#include "Maze.h"
#include <iostream>
#include <fstream>

void Maze::inputMazeFile(std::ifstream &inputFile) {
    if (!inputFile.is_open()) {
        std::cerr << "Error: file could not open!" << std::endl;
        return;
    }

    std::string line;

    while (getline(inputFile, line)) {
        std::vector<int> nums;
        for (char c : line) {
            nums.push_back(static_cast<int>(c - '0'));
        }
        grid.push_back(nums);
    }
}

void Maze::printMaze() {
    for (const auto &i : grid) {
        for (const auto &j : i) {
            if (j == 0) {
                std::cout << "\033[31m0 \033[0m";
            } else {
                std::cout << "\033[34m1 \033[0m";
            }
        }
        std::cout << std::endl;
    }
}

bool Maze::isEmpty() {
    return path.empty();
}