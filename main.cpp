#include <fstream>
#include "Maze.h"


int main(int argc, char* argv[]) {
    Maze maze;
    std::ifstream inputFile(argv[1]); //argv[1] "/Users/parker/Desktop/maze-solver/maze_30x30.txt"
    maze.inputMazeFile(inputFile);
    inputFile.close();

    maze.searchForPath();
    return 0;
}