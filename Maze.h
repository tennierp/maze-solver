#pragma once
#include <iostream>
#include <stack>
#include <tuple>
#include <vector>

class Maze {
public:
    void inputMazeFile(std::ifstream &inputFile);
    void searchForPath();
    bool isVisited(std::tuple<int, int> cell);
    bool inBounds(std::tuple<int, int> cell);
    std::tuple<int, int> nextNeighbor();

private:
    void findEntryExit();
    void printMaze();

    std::vector<std::vector<int>> grid;
    std::vector<std::tuple<int, int>> visited;
    std::stack<std::tuple<int, int>> path;

    std::tuple<int, int> startCell;  // = {-1, -1}
    std::tuple<int, int> targetCell; // = {-1, -1};
};