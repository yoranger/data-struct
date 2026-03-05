#include "valid_path.h"
#include <vector>
#include <queue>
#include <stack>
#include <iostream>

using namespace std;

bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
    // int i = 0;
    // for(vector<int>& edge : edges)
    // {
    //     std::cout << i++ << std::endl;
    //     for(int& value : edge)
    //     {
    //         std::cout << value << ' ';
    //     }
    //     std::cout << std::endl;
    // }
    vector<vector<int>> adjList(n);
    vector<bool> vertices(n, false);
    queue<int> q;
    int current = 0;
    for(vector<int>&edge : edges)
    {
        adjList[edge[0]].push_back(edge[1]);
        adjList[edge[1]].push_back(edge[0]);
    }

    vertices[source] = true;
    q.push(source);
    while(!q.empty())
    {
        int node = q.front();
        q.pop();
        if(node == destination)
            return true;
        for(int v : adjList[node])
        {
            if(!vertices[v])
            {
                q.push(v);
                vertices[v] = true;
            }
        }
    }
    return false;
}