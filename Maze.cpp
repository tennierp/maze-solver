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
    if (grid.empty()) return;

    const int rows = static_cast<int>(grid.size());
    const int cols = static_cast<int>(grid[0].size());

    std::vector<std::vector<bool>> onPath(rows, std::vector<bool>(cols, false));

    // Unwind the stack copy to mark path cells
    while (!path.empty()) {
        auto [r, c] = path.top();
        path.pop();
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            onPath[r][c] = true;
        }
    }

    // Print: path '*' first, then walls(1) then open cells(0)
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (onPath[r][c]) {
                std::cout << "\033[32m*\033[0m ";
            } else if (grid[r][c] == 1) {
                std::cout << "\033[34m1\033[0m ";
            } else {
                std::cout << "\033[31m \033[0m ";
            }
        }
        std::cout << '\n';
    }
}

void Maze::printStack() {
    while (!path.empty()) {
        std::tuple<int, int> coord = path.top();
        std::cout << get<0>(coord) << ", " << get<1>(coord) << std::endl;
        path.pop();
    }
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

bool Maze::isVisited(std::tuple<int, int> cell) {
    for (auto &i : visited) {
        if (cell == i) {
            return true;
        }
    }

    return false;
}

bool Maze::inBounds(std::tuple<int, int> cell) {
    // row, col
    if ((get<0>(cell) >= 0 && get<0>(cell) < grid.size()) && (get<1>(cell) >= 0 && get<1>(cell) < grid[0].size())) {
        return true;
    }

    return false;
}

std::tuple<int, int> Maze::nextNeighbor() {
    const std::tuple<int, int> current = path.top();

    // Fixed order: Down, right, up, left
    const std::tuple<int,int> adjacentCells[4] = {
            { std::get<0>(current) + 1, std::get<1>(current) }, // Down
            { std::get<0>(current),     std::get<1>(current) + 1 }, // Right
            { std::get<0>(current) - 1, std::get<1>(current) }, // Up
            { std::get<0>(current),     std::get<1>(current) - 1 }  // Left
    };

    for (const auto &cell : adjacentCells) {
        if (inBounds(cell) && !isVisited(cell) && grid[get<0>(cell)][get<1>(cell)] == 0) {
                return cell;
        }
    }

    return std::tuple<int, int>{-1, -1};
}

void Maze::searchForPath() {
    findEntryExit();
    path.push(startCell);
    visited.push_back(startCell);

    while (!path.empty()) {
        std::tuple<int, int> neighbor = nextNeighbor();
        if (neighbor == std::make_tuple(-1, -1)) {
            path.pop();
        } else {
            path.push(neighbor);
            visited.push_back(neighbor);

            if (path.top() == targetCell) {
                std::cout << "Path Found!" << std::endl;
                break;
            }
        }
    }

    if (path.empty()) {
        std::cout << "No path exists." << std::endl;
    }
}