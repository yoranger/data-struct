#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <iostream>
#include <map>
#include <vector>
#include <climits>

namespace dijkstra_algo {

struct Edge {
    std::string to;
    int weight;
};

std::map<std::string, int> dijkstra(const std::map<std::string, std::vector<Edge>>& graph,
                                   const std::string& start,
                                   std::map<std::string, std::string>& predecessors);

} // namespace dijkstra_algo

#endif // DIJKSTRA_H