#include <fstream>
#include "Maze.h"


int main(int argc, char* argv[]) {
    Maze maze;

    std::ifstream inputFile(argv[1]);
    maze.inputMazeFile(inputFile);
    inputFile.close();

    maze.searchForPath();
    maze.printMaze();

    return 0;
}