#include "connected_component.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
// #include <cassert>
using namespace std;

// Helper to parse edges from a string
vector<vector<int>> parseEdges(const string& edgesStr) {
    vector<vector<int>> edges;
    string temp;
    bool insideBracket = false;

    for (char c : edgesStr) {
        if (c == '[') {
            insideBracket = true;
            temp.clear();
        } else if (c == ']') {
            if (insideBracket && !temp.empty()) {
                stringstream ss(temp);
                vector<int> edge;
                int num;
                while (ss >> num) {
                    edge.push_back(num);
                    if (ss.peek() == ',') ss.ignore(); // Ignore commas
                }
                edges.push_back(edge);
            }
            insideBracket = false;
        } else if (insideBracket) {
            temp += c;
        }
    }
    return edges;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
      cerr << "Usage: " << argv[0] << " <filename>" << endl;
      return EXIT_FAILURE;
    }

    // Data import
    string filename = argv[1];
    ifstream testFile(filename);
    string line;

    if (!testFile) {
      cerr << "Error: Could not open file " << filename << endl;
      return 0;
    }

    // Read inputs
    int n;
    string edgesStr;
    vector<vector<int>> edges;

    if (getline(testFile, line)) {
        n = stoi(line); // Convert line to int
    }

    // Read edgesStr
    if (getline(testFile, edgesStr)) { 
        // cout << "Read line: " << edgesStr << endl; 
    } else {
        cerr << "Error: Could not read the line." << endl;
    }

    edges = parseEdges(edgesStr); 

    int result = countComponents(n, edges);

    // Output result
    cout << result << endl;

    return 0;
}