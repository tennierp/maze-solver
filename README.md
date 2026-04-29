# Maze Solver (C++)

A C++ application that solves a maze using a stack-based backtracking algorithm.

The program reads a maze from a text file, finds a valid path from start to finish (if one exists), and outputs the solved maze with the path marked.

---

## Features
- Reads maze input from `.txt` file (0 = open path, 1 = wall)
- Uses iterative stack-based backtracking to find a solution
- Detects when no valid path exists
- Outputs solved maze with path visualization (`*`)

---

## How It Works
The maze is represented as a grid. The algorithm explores possible paths using a stack-based approach, backtracking when a dead end is reached.

---

## Build & Run (Windows)
g++ -std=c++20 main.cpp Maze.cpp -o maze  
.\maze.exe maze0-1_input.txt
