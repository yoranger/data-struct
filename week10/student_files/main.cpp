
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype> // For isspace
#include <stdexcept> // For exceptions
#include <climits>

#include "dijkstra.h"

using namespace std;

// Helper function to trim leading and trailing whitespace
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (string::npos == first) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

vector<string> reconstructPath(const map<string, string>& predecessors, const string& start, const string& end) {
    vector<string> path;
    string current = end;

    while (current != "") {
        if (predecessors.find(current) == predecessors.end()) {
            cerr << "Error: Predecessor not found for vertex " << current << endl;
            return vector<string>();
        }
        path.push_back(current);
        current = predecessors.at(current);
    }

    if (path.back() != start) {
        return vector<string>();
    }

    reverse(path.begin(), path.end());
    return path;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    string filename = argv[1];
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    map<string, vector<dijkstra_algo::Edge>> graph;
    string line;
    string startVertex;
    bool startVertexFound = false;
    vector<string> allVertices;

    int lineNumber = 0; // Track line numbers for better error messages
    cout << "______________________________________ " << endl;
    cout << " Parsing file " << endl;
    while (getline(inputFile, line)) {
        lineNumber++;
        line = trim(line); // Trim whitespace

        // Skip empty lines and comment lines
        if (line.empty() || line[0] == '#') {
            continue;
        }

        stringstream ss(line);
        string from;
        string to;
        int weight;

        // Attempt to read from, to, and weight
        if (ss >> from >> to >> weight) {
            if (!startVertexFound) {
                startVertex = from;
                cout << "Starting Vertex: " << startVertex << endl;
                startVertexFound = true;
            }

            if (find(allVertices.begin(), allVertices.end(), from) == allVertices.end()) {
                allVertices.push_back(from);
            }
            if (find(allVertices.begin(), allVertices.end(), to) == allVertices.end()) {
                allVertices.push_back(to);
            }

            graph[from].push_back({to, weight});
        } else {
            // Handle the case where the line might only contain the starting vertex
            ss.clear(); // Clear error flags
            ss.str(line); // Reset the stringstream with the line
            if (ss >> from && !startVertexFound){
                startVertex = from;
                cout << "Starting Vertex: " << startVertex << endl;
                startVertexFound = true;
                if (find(allVertices.begin(), allVertices.end(), from) == allVertices.end()) {
                    allVertices.push_back(from);
                }
            } else if (!line.empty()) {
                cerr << "Error: Invalid line format at line " << lineNumber << ": \"" << line << "\"" << endl;
            }
        }
    }

    inputFile.close();

    // Print all vertices after parsing
    // cout << "\nParsed Vertices:\n";
    //for (const string& vertex : allVertices) {

    //    cout << "Vertex: " << vertex << endl;
    //}

    //for (const auto& vertex : allVertices) {
    //    if (graph.find(vertex) == graph.end()) {
    //        graph[vertex] = {};
    //    }
    //}

    cout << "______________________________________ " << endl;
    cout << " Print the graph's adjacency list " << endl;

    // Print the graph's adjacency list
    cout << "\nVertices in the graph:\n";
    for (const auto& pair : graph) {
        cout << "Vertex: " << pair.first << endl;
        for (const auto& edge : pair.second) {
            cout << "  Edge to: " << edge.to << " (weight: " << edge.weight << ")" << endl;
        }
    }
    cout << endl;

    //cout << "______________________printing verticies___________________________ " << endl;
    // Print all vertices after parsing
    //cout << "\nParsed Vertices:\n";
    //for (const string& vertex : allVertices) {
    //    cout << "Vertex: " << vertex << endl;
    //}

    //for (const auto& vertex : allVertices) {
    //    if (graph.find(vertex) == graph.end()) {
    //        graph[vertex] = {};
    //    }
    //}

    cout << "______________________________________ " << endl;
    cout << " Running Dijkstra's Algo " << endl;
    //return 0;

    map<string, string> predecessors;
    map<string, int> shortestDistances = dijkstra_algo::dijkstra(graph, startVertex, predecessors);

    if (shortestDistances.empty()) {
            cout << "Error: Negative edge weights found. Dijkstra's algorithm cannot handle them.\n" << endl;
            cout << "Exiting" << endl;
            return 1;
    }

    cout << "Shortest distances from vertex " << startVertex << ":\n";

    vector<string> vertexOrder;
    for (const auto& pair : shortestDistances) {
        vertexOrder.push_back(pair.first);
    }

    for (const string& vertex : vertexOrder) {
        cout << "Vertex " << vertex << ": ";
        if (shortestDistances[vertex] == INT_MAX) {
            cout << "Infinity\n";
        } else {
            cout << shortestDistances[vertex] << "\n";
            if (!predecessors.empty() && vertex != startVertex) {
                vector<string> path = reconstructPath(predecessors, startVertex, vertex);
                if (!path.empty()) {
                    cout << "  Path: ";
                    for (size_t i = 0; i < path.size(); ++i) {
                        cout << path[i];
                        if (i < path.size() - 1) {
                            cout << " -> ";
                        }
                    }
                    cout << endl;
                }
            }
        }
    }
    
    cout << "_________________________________________________________________ " << endl;
    return 0;
}