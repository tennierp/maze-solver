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

void Maze::findEntryExit() {
    for (int i = 0; i < grid.size(); ++i) {
        if (grid[i][0] == 0) {
            startCell = {i, 0};
        }

        if (grid[i][grid[0].size() - 1] == 0) {
            targetCell = {i, grid[0].size() - 1};
        }
    }
}

void Maze::searchForPath() {
    findEntryExit();
    path.push(startCell);

//    while (!path.empty()) {
//        if () // top cell has no unexplored adjacent cells
//    }

}

bool Maze::isValid() {

    return true; // just for warnings
}