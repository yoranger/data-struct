#include "import_numbers_from_file.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// This function reads decimal numbers in the file specified by the `filename`
// parameter and stores them in a double-precision floating-poing vector. It
// assumes that the file contains one number per line.
// If the file cannot be opened, or if a line contains a non-numeric value or
// a number out of range (i.e., too small or large to be represented by a
// `double`), an error message is printed to the standard error stream and an
// empty vector is returned.
vector<double> importNumbersFromFile(const string &filename) {
  ifstream file(filename);
  if (!file) {
    cerr << "Error: Could not open file " << filename << endl;
    return {};
  }

  // Convert input into a `double`
  vector<double> numbers;
  string line;
  while (getline(file, line)) {
    try {
      numbers.push_back(stod(line));
    } catch (const invalid_argument &e) {
      cerr << "Error: Non-numeric line encountered: " << line << endl;
      return {};
    } catch (const out_of_range &e) {
      cerr << "Error: Number out of range encountered: " << line << endl;
      return {};
    }
  }
  return numbers;
}