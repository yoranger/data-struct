#include "valid_path.h"
#include <vector>
#include <queue>
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
    vector<vector<int>> adjList;
    for(vector<int>&edge : edges)
    {
        adjList[edge[0]].push_back(edge[1]);
        adjList[edge[1]].push_back(edge[0]);
    }
    
}