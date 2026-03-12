Game Pathfinding - Activity 3

This exercise requires you to implement Bellman-Ford algorithm
to find the shortest path in a 2D grid game with terrain costs.

Files:
- game_pathfinding.h: Header file with function declaration
- game_pathfinding.cpp: Implementation file (complete the TODO)
- main.cpp: Main program that reads input and calls your function
- makefile: Build configuration

Input Format:
- First line: rows cols
- Second line: start_r start_c target_r target_c
- Next rows lines: each line has cols integers (terrain costs)

Output:
- Single integer: minimum total cost from start to target

Example:
Input from test_0.txt:
3 4
0 0 2 3
1 5 2 1
3 1 4 2
1 2 1 3

This represents a 3x4 grid:
  0  1  2  3
0 1  5  2  1
1 3  1  4  2
2 1  2  1  3

Grid Layout:
(0,0): 1    (0,1): 5    (0,2): 2    (0,3): 1
(1,0): 3    (1,1): 1    (1,2): 4    (1,3): 2
(2,0): 1    (2,1): 2    (2,2): 1    (2,3): 3


Starting at (0,0) with cost 1, target at (2,3) with cost 3.


From the main file, Initial distances to all cells:
(0,0): 1 (0,1): INF (0,2): INF (0,3): INF (1,0): INF (1,1): INF (1,2): INF (1,3): INF (2,0): INF (2,1): INF (2,2): INF (2,3): INF

(0,0): 1 - This is the starting position. 
The initial distance is set to the terrain cost of the start cell (1).
All others: INF - "INF" means infinity (unreachable). 
At the start, we haven't explored any paths yet, so no other cells are reachable.


To build:
  make

To run with test file:
  ./game_pathfinding < test_0.txt

To clean:
  make clean
