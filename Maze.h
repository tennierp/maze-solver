#pragma once
#include <iostream>

class Maze {
public:
    void inputMazeFile(std::ifstream &inputFile);
    void printMaze();
    bool isEmpty();
    void searchForPath();
    static bool isValid();

private:
    void findEntryExit();

    std::vector<std::vector<int>> grid;
    std::vector<std::tuple<int, int>> visited;
    std::stack<std::tuple<int, int>> path;

    std::tuple<int, int> startCell;
    std::tuple<int, int> targetCell;
};