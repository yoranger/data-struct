#include "dijkstra.h"
#include <queue>
#include <climits>

namespace dijkstra_algo {

std::map<std::string, int> dijkstra(const std::map<std::string, std::vector<Edge>>& graph,
                                   const std::string& start,
                                   std::map<std::string, std::string>& predecessors) {

    std::map<std::string, int> distances;
    std::map<std::string, bool> visited;
    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<std::pair<int, std::string>>> pq;

    //#TODO:init
    for (const auto& pair : graph) {
        distances[pair.first]= INT_MAX;
        visited[pair.first] = false;
        predecessors[pair.first] = "";
    }

    distances[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        
        std::string current = pq.top().second;
        pq.pop();

        if (visited[current]) {
            continue;
        }
  
       visited[current] = true;

        if (graph.find(current) != graph.end()) {
            for (const auto& edge : graph.at(current)) {

                // Check for negative edge weights
                if (edge.weight < 0) {
                    // TODO:
                    // Return an empty map to signal an error
                    //
                    return std::map<std::string, int>{};
                }

                if (distances[current] + edge.weight < distances[edge.to]) {
                    //TODO:
                    distances[edge.to] = distances[current] + edge.weight;
                    predecessors[edge.to] = current;
                    pq.emplace(distances[edge.to], edge.to);
                }
            }
        }
    }

    return distances;
}

} // namespace dijkstra_algo
