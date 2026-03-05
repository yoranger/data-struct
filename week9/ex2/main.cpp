#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "min_cost.h"

using namespace std;

// Parse the input string to a vector of vectors
vector<vector<int>> parseEdges(const string &str) {
  vector<vector<int>> points;
  stringstream ss(str);
  char ch;
  int num;

  while (ss >> ch) {  // Read character by character
    if (ch == '[') {
      vector<int> point;
      while (ss >> num) {  // Read integers
        point.push_back(num);
        ss >> ch;  // Read ',' or ']'
        if (ch == ']')
          break;
      }
      if (!point.empty()) {
        points.push_back(point);
      }
    }
  }
  return points;
}

int main(int argc, char *argv[]) {
  // Check if filename argument is provided
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <filename>\n";
    return 1;
  }

  string filename = argv[1];  // Get filename from argument
  ifstream file(filename);    // Open file for reading
  if (!file) {
    cerr << "Error: Could not open file " << filename << ".\n";
    return 1;
  }

  string input;
  getline(file, input);  // Read the entire line from file
  file.close();
  // cout << "Input string: \n";
  // cout << input << endl;

  vector<vector<int>> points = parseEdges(input);

  // cout << "Parsed Vector: \n";
  // for (const auto& p : points) {
  //     cout << "[" << p[0] << ", " << p[1] << "]\n";
  // }

  // Call the function
  int result = minCost(points);
  cout << result << endl;
  return result;
}
