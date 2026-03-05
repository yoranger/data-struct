#include "min_cost.h"

#include <vector>
#include <map>
// TODO: Add any necessary libraries here and in min_cost.h

using namespace std;

struct neighbour
{
	pair<int, int> coord;
	pair<int, int> parent;
	int distance = 0;
};

int distance(vector<int> &p1, vector<int> &p2)
{
	return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
}

int minCost(vector<vector<int>> &points)
{
	map<pair<int, int>, vector<neighbour>> adjList;
	map<pair<int, int>, bool> visited;
	vector<neighbour> availableEdge;
	int totalScore = 0;
	for (vector<int> point : points)
	{
		visited[pair<int, int>(point[0], point[1])] = false;
		for (vector<int> neighbour : points)
			if (point != neighbour)
				adjList[pair<int, int>(point[0], point[1])].emplace_back(pair<int, int>(neighbour[0], neighbour[1]), pair<int, int>(point[0], point[1]), distance(point, neighbour));
	}

	pair<int, int> current = adjList.begin()->first;
	visited[current] = true;
	while (true)
	{
		availableEdge.clear();
		for (pair<pair<int, int>, bool> node : visited)
		{
			if(node.second)
			{
				for(neighbour nb : adjList[node.first])
				{
					if(!visited[nb.coord])
						availableEdge.push_back(nb);
				}
			}
		}
		neighbour compare = availableEdge[0];
		for (int i = 1; i < availableEdge.size(); ++i)
		{
			if(compare.distance > availableEdge[i].distance)
				compare = availableEdge[i];
		}
		visited[compare.coord] = true;
		totalScore += compare.distance;
		bool allVisited = true;
		for(pair<pair<int, int>, bool> node : visited)
		{
			if(!node.second)
				allVisited = false;
		}
		if(allVisited)
			break;
	}
	return totalScore;
}
