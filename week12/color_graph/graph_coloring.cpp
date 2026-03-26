#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
class nodeData
{
public:
    nodeData(int x, int y) : node{x}, color{y} {};
    int node;
    int color;
};

// Function to perform graph coloring
void graphColoring(vector<vector<int>> &graph, int n)
{
    vector<int> result(n, -1); // Store color of each vertex
    result[0] = 0;            // Assign first color to the first vertex
    vector<bool> available(n, true); // Keep track of available colors
    vector<vector<nodeData>> adjList;
    // TODO Assign colors to remaining vertices
    // for(vector<int>& edge : graph)
    // {
    //     adjList[edge[0]].push_back(nodeData(edge[1], 0));
    //     adjList[edge[1]].push_back(nodeData(edge[0], 0));
    // }
    for(int i = 1; i < n; ++i)
    {
        for (size_t j = 0; j < graph[i].size(); ++j)
        {
            if(result[graph[i][j]] != -1)
                available[result[graph[i][j]]] = false;
        }
        for (int k = 0; k < n; ++k)
            if(available[k])
            {
                result[i] = k;
                break;
            }
        for (int g = 0; g < n; ++g)
            available[g] = true;
    }

    // Print the result
    cout << "Vertex\tColor" << endl;
    for (int u = 0; u < n; u++) {
        cout << u << "\t" << result[u] << endl;
    }

    // Print the total number of colors used
    cout << "Minimum number of colors required: "
         << (*max_element(result.begin(), result.end()) + 1) << endl;
}

int main() {
    // Example graph input
    int n = 5; // Number of vertices

    vector<vector<int>> graph(n);

    // Add edges
    //  vector<pair<int, int>> edges = {
    //      {0, 1}, {0, 2}, {1, 2}, {1, 3}, {2, 4}, {3, 4}};

    int numEdges;
    std::cout << "Enter the number of edges: ";
    std::cin >> numEdges;

    std::vector<std::pair<int, int>> edges;
    edges.reserve(numEdges); // Optional: reserves memory to optimize performance

    std::cout << "Enter each edge as two space-separated integers (e.g., '0 1'):\n";
    for (int i = 0; i < numEdges; ++i) {
        int u, v;
        std::cin >> u >> v;
        edges.emplace_back(u, v);
    }

    for (auto& edge : edges) {
        graph[edge.first].push_back(edge.second);
        graph[edge.second].push_back(edge.first);
    }

    // Perform graph coloring
    graphColoring(graph, n);

    return 0;
}