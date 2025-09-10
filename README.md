# Project 1 -- Solving a maze
A C++ application that solves a maze using an iterative, stack-based backtracking algorithm. 
The maze will be provided as a file containing a grid of zeros and ones, where zeros represent 
open paths and ones represent walls. Your program will read the file, store the maze in a suitable
data structure (such as a vector of vectors), and then attempt to find a valid path from the 
entrance to the exit. If a path is found, the program will output the maze with the solution path 
identified. The output will display zeros for unused open cells, ones for walls, and a space 
character for the cells that are part of the path. Optionally, you may print the path in color 
using ANSI escape sequences.