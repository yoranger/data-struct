#include <fstream>
#include <iostream>
#include <vector>

#include "image_segmentation.h"

using namespace std;

// Input format:
// First line: rows cols
// Next rows lines: each line has 'cols' integer pixel intensities.
int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <filename>\n";
    return 1;
  }

  string filename = argv[1];
  ifstream file(filename);
  if (!file) {
    cerr << "Error: Could not open file " << filename << ".\n";
    return 1;
  }

  int rows, cols;
  if (!(file >> rows >> cols)) {
    cerr << "Error: Failed to read rows and cols.\n";
    return 1;
  }

  vector<int> pixels;
  pixels.reserve(static_cast<size_t>(rows) * static_cast<size_t>(cols));

  int val;
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (!(file >> val)) {
        cerr << "Error: Not enough pixel values in file.\n";
        return 1;
      }
      pixels.push_back(val);
    }
  }

  file.close();

  int mst_cost = imageMSTCost(rows, cols, pixels);
  cout << mst_cost << endl;

  return 0;
}

