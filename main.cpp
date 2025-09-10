#include <fstream>
#include "Maze.h"


int main(int argc, char* argv[]) {

    Maze maze;
    std::ifstream inputFile("/Users/parker/Desktop/maze-solver/maze.txt"); //argv[1]
    maze.inputMazeFile(inputFile);
    inputFile.close();

    maze.searchForPath();
    maze.printStack();

    return 0;
}