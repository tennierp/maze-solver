#pragma once
#include <iostream>
#include <stack>
#include <tuple>
#include <vector>

class Maze {
public:
    void inputMazeFile(std::ifstream &inputFile);
    void searchForPath();
    void printMaze();
private:

    std::vector<std::vector<int>> grid;
    std::vector<std::tuple<int, int>> visited;
    std::stack<std::tuple<int, int>> path;
    std::tuple<int, int> startCell;
    std::tuple<int, int> targetCell;

    void findEntryExit();
    bool isVisited(std::tuple<int, int> cell);
    bool inBounds(std::tuple<int, int> cell);
    std::tuple<int, int> nextNeighbor();
};