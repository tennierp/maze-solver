#include <fstream>
#include <tuple>
#include <stack>
#include "Maze.h"


int main(int argc, char* argv[]) {

    Maze maze;
    std::ifstream inputFile("/Users/parker/Desktop/maze-solver/maze.txt"); //argv[1]
    maze.inputMazeFile(inputFile);
    inputFile.close();

    maze.printMaze();


//    while (!maze.isEmpty()) {
//
//    }

    return 0;
}

/*
    Push the start cell onto the stack
    While the stack is not empty do
        If the top cell has no unexplored adjacent cell then ---- From the current cell, is there at least one valid move left?
    Pop the stack
    Else
    Choose one unexplored adjacent cell
    Push that cell onto the stack
    Mark it as explored
    If this cell is the target then
    Exit the loop
    End If
    End While

    If the stack is empty then
    No path exists from the start cell to the target cell
    Else
    The stack now contains the path, in reverse order

    Order of searching for next cell: Down, Right, Up, Left

    adjacent cells:
    start (path.top()): [row, col]
    left: [row, col - 1]
    right: [row, col + 1]
    up: [row - 1, col]
    down: [row + 1, col]
 */