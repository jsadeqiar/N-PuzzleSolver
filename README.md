
# N-Puzzle Solver

A user friendly program to compute the solution (if possible) of an any sized N-Puzzle board.

# Description

This program utilizes Uniform Cost Search as well as A-Star search with two heuristics (Misplaced Tile and Euclidean Distance) in order to solve as well as compare the efficiency between the three algorithms. 

Users can input the size of the board (e.g. 3x3, 4x4, 5x5) as well as the initial state of the board which they want the program to start its evaluation at. The user will then be prompted to select one of the three search algorithms to compute the board to its solution. 

The solution will show the depth as well as the h-cost at every step from start to finish via backtracking to the original input.

# How to build

Ensure g++ -v (>=4.8) is installed then simply run the makefile.

The program can be run after with ```./program```

# Authors

[@jsadeqiar](https://github.com/jsadeqiar)