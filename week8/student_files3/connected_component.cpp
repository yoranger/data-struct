#include "connected_component.h"
#include <vector>
#include <queue>

using namespace std;
    
int countComponents(int n, vector<vector<int>>& edges) 
{
    // write your code here, add comments to explain your logic and space & time complexity at each step
    vector<vector<int>> adjList(n);
    vector<bool> visited(n, false);
    int components = 0;
    for(vector<int>&edge : edges)
    {
        adjList[edge[0]].push_back(edge[1]);
        adjList[edge[1]].push_back(edge[0]);
    }
    for (int i = 0; i < n; ++i)
    {
        if(!visited[i])
        {
            ++components;
            queue<int> q;
            q.push(i);
            visited[i] = true;
            while(!q.empty())
            {
                int node = q.front();
                q.pop();
                for(int v : adjList[node])
                {
                    if(!visited[v])
                    {
                        q.push(v);
                        visited[v] = true;
                    }
                }
            }
        }
    }
    return components;
}