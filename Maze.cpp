#include "Maze.h"
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <set>
#include <string>

// Inputs the maze file to the grid, and checks if it cannot be open
void Maze::inputMazeFile(std::ifstream &inputFile) {
    if (!inputFile.is_open()) {
        std::cerr << "Error: file could not open!" << std::endl;
        return;
    }

    std::string line;

    while (std::getline(inputFile, line)) {
        std::vector<int> nums(line.begin(), line.end());
        for (int &n : nums) {
            n -= '0';
        }
        grid.push_back(std::move(nums));
    }
}

// Allows user to output the solution path, states no solution if path not found
void Maze::printMaze() {
    if (grid.empty() || path.empty()) {
        std::cout << "No solution is possible." << std::endl;
        return;
    }

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
                std::cout << "\033[31m* \033[0m"; // path in red + one space
            } else if (grid[r][c] == 1) {
                std::cout << "\033[34m1 \033[0m"; // walls in blue + one space
            } else {
                std::cout << "  "; // open cells in '  ' double space
            }
        }
        std::cout << '\n';
    }
}

// Searches the grid to find the startCell and targetCell
void Maze::findEntryExit() {
    std::vector<std::tuple<int, int>> openings;

    for (int i = 0; i < grid[0].size(); ++i) {

        // top side of maze grid
        if (grid[0][i] == 0) {
            openings.push_back({0, i});
        }

        // bottom side of maze grid
        if (grid[grid.size() - 1][i] == 0) {
            openings.push_back({grid.size() - 1, i});
        }
    }

    for (int i = 0; i < grid.size(); ++i) {

        // right side of maze grid
        if (grid[i][grid[0].size() - 1] == 0) {
            openings.push_back({i, grid[0].size() - 1});
        }

        // left side of maze grid
        if (grid[i][0] == 0) {
            openings.push_back({i, 0});
        }
    }

    // If the function finds 2 cells, make them the start and target cell
    if (openings.size() == 2) {
        startCell = openings[0];
        targetCell = openings[1];
    }
}

// Helper function to determine if the cell is in the visited member of the maze class
bool Maze::isVisited(std::tuple<int, int> cell) {
    for (auto &i : visited) {
        if (cell == i) {
            return true;
        }
    }
    return false;
}

// Checks the edges of the maze's grid to make sure the next move isn't out of bounds
bool Maze::inBounds(std::tuple<int, int> cell) {
    if ((get<0>(cell) >= 0 && get<0>(cell) < grid.size()) && (get<1>(cell) >= 0 && get<1>(cell) < grid[0].size())) {
        return true;
    }

    return false;
}

// Finds and returns the next safe move for the algorithm to move to
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

// Uses a Backtracking algorithm to find the start and exit points of any maze of 1's and 0's.
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
                break;
            }
        }
    }
}