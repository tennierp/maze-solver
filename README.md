## Project 1 - Maze Solver

## Student Information
Parker Tennier  
ID: 008768156  
https://github.com/tennierp/maze-solver

## Collaboration & Sources
Dr. Ali A. Kooshesh provided a clear maze backtracking algorithm in a pseudocode format,
I then used this information to create a c++ maze class that solves a maze input file and shows
the path, if one is found.

## Implementation Details
maze-solver is a c++ application that solves a maze input file given in ones and zeros using an iterative, stack-based backtracking algorithm.
The maze will be provided that file containing a grid of zeros and ones, where zeros represent open cells and ones will represent walls.
The program will read the file, store the maze in a grid, and then it will find a valid path from the start cell to the target cell,
it will tell you if the solution is not possible, or print the solution in a maze format where *'s will be the solution path through the maze,
1's will be the walls, and ' ' spaces will show the open cells that are now not needed.

## Testing & Status
The program will work on any size maze as long as it is in the correct format of 1's and 0's in a .txt file. 
The maze will print the solution path of the maze in your input file with the solution being the red *'s following 
your maze from the start to target points. If the maze does not have a start or an exit point, it will tell you that 
there is no solution possible for the maze you provided.