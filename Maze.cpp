#include "Maze.h"
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <set>

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

    std::set<std::tuple<int,int>> pathCells;
    auto tmp = path;
    while (!tmp.empty()) {
        pathCells.insert(tmp.top());
        tmp.pop();
    }

    for (int r = 0; r < grid.size(); ++r) {
        for (int c = 0; c < grid[0].size(); ++c) {
            std::tuple<int,int> cell{r,c};
            if (pathCells.count(cell)) {
                std::cout << "\033[31m* \033[0m"; // path in green
            } else if (grid[r][c] == 1) {
                std::cout << "\033[34m1 \033[0m"; // walls in blue
            } else {
                std::cout << "  "; // open space
            }
        }
        std::cout << '\n';
    }
}

/*
    top: row 0, search through cols for 0
    bottom: row maze.size() - 1, search through cols for 0
    left: search through row, col 0
    right: search through row, col is row.size() - 1
 */

void Maze::findEntryExit() {
    std::vector<std::tuple<int, int>> openings;

    for (int i = 0; i < grid[0].size(); ++i) {

        // top side
        if (grid[0][i] == 0) {
            openings.push_back({0, i});
        }

        // bottom side
        if (grid[grid.size() - 1][i] == 0) {
            openings.push_back({grid.size() - 1, i});
        }
    }

    for (int i = 0; i < grid.size(); ++i) {

        // right side
        if (grid[i][grid[0].size() - 1] == 0) {
            openings.push_back({i, grid[0].size() - 1});
        }

        // left side
        if (grid[i][0] == 0) {
            openings.push_back({i, 0});
        }
    }

    if (openings.size() == 2) {
        startCell = openings[0];
        targetCell = openings[1];
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
    // get<0> row, get<1> col
    if ((get<0>(cell) >= 0 && get<0>(cell) < grid.size()) && (get<1>(cell) >= 0 && get<1>(cell) < grid[0].size())) {
        return true;
    }

    return false;
}

std::tuple<int, int> Maze::nextNeighbor() {
    const std::tuple<int, int> current = path.top();

    // Fixed order: Down, right, up, left
    const std::tuple<int,int> adjacentCells[4] = {
            { std::get<0>(current) + 1, std::get<1>(current) },     // Down
            { std::get<0>(current),     std::get<1>(current) + 1 }, // Right
            { std::get<0>(current) - 1, std::get<1>(current) },     // Up
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
                std::cout << "Start cell: " << get<0>(startCell) << ", " << get<1>(startCell) << std::endl;
                std::cout << "Target cell: " << get<0>(targetCell) << ", " << get<1>(targetCell) << std::endl;
                printMaze();
                break;
            }
        }
    }

    if (path.empty()) {
        std::cout << "No solution is possible." << std::endl;
        std::cout << "Start cell: " << get<0>(startCell) << ", " << get<1>(startCell) << std::endl;
        std::cout << "Target cell: " << get<0>(targetCell) << ", " << get<1>(targetCell) << std::endl;
    }
}