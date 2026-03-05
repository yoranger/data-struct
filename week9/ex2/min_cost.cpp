#include "min_cost.h"

#include <vector>
#include <map>
// TODO: Add any necessary libraries here and in min_cost.h

using namespace std;

struct neighbour
{
  pair<int, int> coord;
  int distance = 0;
};

int distance(vector<int> &p1, vector<int> &p2) {
  return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
}

int minCost(vector<vector<int>> &points) 
{
  map<pair<int, int>, vector<neighbour>> adjList;
  map<pair<int, int>, bool> visited;
  for (vector<int> point : points)
  {
    visited[pair<int, int>(point[0], point[1])] = false;
    for(vector<int> neighbour : points)
      if(point != neighbour)
        adjList[pair<int, int>(point[0], point[1])].emplace_back(pair<int, int>(neighbour[0], neighbour[1]), distance(point, neighbour));
  }
  
  
  
}
