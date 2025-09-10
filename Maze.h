#pragma once
#include <iostream>

class Maze {
public:
    void inputMazeFile(std::ifstream &inputFile);
    void printMaze();
    bool isEmpty();

private:
    std::vector<std::vector<int>> grid;
    std::vector<std::tuple<int, int>> visited;
    std::stack<std::tuple<int, int>> path;
};