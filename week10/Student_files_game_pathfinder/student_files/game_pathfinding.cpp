#include "game_pathfinding.h"

#include <climits>
#include <queue>
#include <vector>

using namespace std;

struct neighbours
{
    pair<int, int> coord;
    pair<int, int> parent;
    int distance = 0;
    int weight = INT_MAX;
};

int shortestPathCost(int rows, int cols, const vector<vector<int>> &terrain,
                       int start_r, int start_c, int target_r, int target_c) 
{
    int V = rows * cols;
    int E = (rows - 1) * cols + (cols - 1) * rows;

    //relax all edges V - 1 times
    for (int i = 1; i <= V; ++i)
    {
        for (int j = 0; )
    }

        // TODO: Implement Bellman-Ford algorithm
        //
        // Steps:
        // 1. Convert 2D positions to 1D indices: idx = row * cols + col
        // 2. Initialize distances: start cell = terrain[start_r][start_c], others =
        // INT_MAX
        // 3. Use Bellman-Ford (relaxation iterations)
        // 4. Handle 4-directional movement (up, down, left, right)
        // 5. Return the shortest path cost to target
        vector<vector<neighbours>> adjList;
        for (int i = 0; i < cols; ++i)
        {
            for (int j = 0; j < rows; ++j)
            {
                if ((i - 1) >= 0)
                    adjList[j * cols + i].emplace_back(pair<int, int>(i - 1, j), pair<int, int>(-1, -1), terrain[i][j]);
                if ((i + 1) < cols)
                    adjList[j * cols + i].emplace_back(pair<int, int>(i + 1, j), pair<int, int>(-1, -1), terrain[i][j]);
                if ((j - 1) >= 0)
                    adjList[j * cols + i].emplace_back(pair<int, int>(i, j - 1), pair<int, int>(-1, -1), terrain[i][j]);
                if ((j + 1) < rows)
                    adjList[j * cols + i].emplace_back(pair<int, int>(i, j + 1), pair<int, int>(-1, -1), terrain[i][j]);
            }
    }
    bool noChange = false;
    for (int i = 0; i <= cols; ++i)
    {
        
    }
        // Stub implementation - replace with your algorithm
        return 0;
}
