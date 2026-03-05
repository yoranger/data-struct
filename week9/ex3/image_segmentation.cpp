#include "image_segmentation.h"
#include <map>
#include "stdlib.h"
// TODO:
// Implement imageMSTCost using an MST algorithm (Prim's or Kruskal's).
// Hint:
//   - Treat each pixel as a node.
//   - Connect 4-neighbour pixels (up, down, left, right) with edge weights
//     equal to |intensity_u - intensity_v|.
//   - Run an MST algorithm on this graph and return the sum of weights of
//     all edges in the MST.
//
// You do NOT need to actually output the segmentation here; just compute
// the MST total "dissimilarity" cost of the image.

struct neighbours
{
    pair<int, int> coord;
    int distance = 0;
};

int calculateDist(int e1, int e2)
{
    return abs(e1 - e2);
}

int imageMSTCost(int rows, int cols, const vector<int> &pixels)
{
    // Replace this stub with your implementation.
    // For now, return 0 so the file compiles.
    (void)rows;
    (void)cols;
    (void)pixels;
    int totalScore = 0;
    map<pair<int, int>, vector<neighbours>> adjList;
    map<pair<int, int>, bool> visited;
	vector<neighbours> availableEdge;
    for (int i = 0; i < cols; ++i)
    {
        for (int j = 0; j < rows; ++j)
        {
            visited[pair<int, int>(i, j)] = false;
            if((i - 1) >= 0)
                adjList[pair<int, int>(i, j)].emplace_back(pair<int, int>(i - 1, j), calculateDist(pixels[j * cols + i], pixels[j * cols + i - 1]));
            if((i + 1) < cols)
                adjList[pair<int, int>(i, j)].emplace_back(pair<int, int>(i + 1, j), calculateDist(pixels[j * cols + i], pixels[j * cols + i + 1]));
            if((j - 1) >= 0)
                adjList[pair<int, int>(i, j)].emplace_back(pair<int, int>(i, j - 1), calculateDist(pixels[j * cols + i], pixels[(j - 1) * cols + i]));
            if((j + 1) < rows)
                adjList[pair<int, int>(i, j)].emplace_back(pair<int, int>(i, j + 1), calculateDist(pixels[j * cols + i], pixels[(j + 1) * cols + i]));
        }
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
				for(neighbours nb : adjList[node.first])
				{
					if(!visited[nb.coord])
						availableEdge.push_back(nb);
				}
			}
		}
		neighbours compare = availableEdge[0];
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
