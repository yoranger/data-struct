#ifndef GAME_PATHFINDING_H
#define GAME_PATHFINDING_H

#include <vector>

// Function to find the shortest path cost from start to target in a game grid
// Parameters:
//   rows: number of rows in the grid
//   cols: number of columns in the grid
//   terrain: 2D vector where terrain[i][j] is the cost of cell (i, j)
//   start_r, start_c: starting position (row, column)
//   target_r, target_c: target position (row, column)
// Returns:
//   Minimum total cost to move from start to target (including start cell cost)
int shortestPathCost(int rows, int cols,
                     const std::vector<std::vector<int>> &terrain,
                     int start_r, int start_c,
                     int target_r, int target_c);

#endif  // GAME_PATHFINDING_H
