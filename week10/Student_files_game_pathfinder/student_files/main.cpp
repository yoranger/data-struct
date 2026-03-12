#include "game_pathfinding.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {
  int rows, cols;
  int start_r, start_c, target_r, target_c;

  // Read grid dimensions
  cin >> rows >> cols;

  // Read start and target positions
  cin >> start_r >> start_c >> target_r >> target_c;

  // Read terrain costs
  vector<vector<int>> terrain(rows, vector<int>(cols));
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      cin >> terrain[i][j];
    }
  }

  // Compute shortest path cost
  int result = shortestPathCost(rows, cols, terrain, start_r, start_c,
                                 target_r, target_c);

  // Output result
  cout << result << endl;

  return 0;
}
