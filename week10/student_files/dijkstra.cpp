#include "dijkstra.h"
#include <queue>
#include <climits>

namespace dijkstra_algo {

std::map<std::string, int> dijkstra(const std::map<std::string, std::vector<Edge>>& graph,
                                   const std::string& start,
                                   std::map<std::string, std::string>& predecessors) {

    std::map<std::string, int> distances;
    std::map<std::string, bool> visited;
    std::priority_queue<std::pair<int, std::string>,
    std::vector<std::pair<int, std::string>>,
    std::greater<std::pair<int, std::string>>> pq;

    //#TODO:init
    for (const auto& pair : graph) {
        distances[XXXXXXXX]= X;
        visited[XXXXXXXXXX] = false;
        predecessors[XXXXXXXXX] = "";
    }

    distances[XXXXXXX] = 0;
    pq.push({0, XXXXXXXX});

    while (!pq.empty()) {
        
        std::string current = pq.top().second;
        pq.pop();

        if (visited[XXXXXX]) {
            continue;
        }
  
       ________________ = true;

        if (graph.find(current) != graph.end()) {
            for (const auto& edge : graph.at(current)) {

                // Check for negative edge weights
                if (edge.weight < XXXX) {
                    // TODO:
                    // Return an empty map to signal an error
                    //
                    return _____________;
                }

                if (distances[current] != _______________ + edge.weight < distances[_______]) {
                    //TODO:
                    __________________________________
                    ___________________________________;
                    ___________________________________;
                }
            }
        }
    }

    return distances;
}

} // namespace dijkstra_algo
