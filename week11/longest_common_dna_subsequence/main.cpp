#include <iostream>
#include <fstream>
#include <string>
#include "longest_common_subsequence.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <filename>" << endl;
    return EXIT_FAILURE;
  }
  // 
  string test_filename = argv[1];
  ifstream file(test_filename);
  if (!file) {
    cerr << "Error opening file: " << test_filename << endl;
    return EXIT_FAILURE;
  }
// Read the two strings from the file and call longestCommonSubsequence

  string dna1, dna2;
  getline(file, dna1);
  getline(file, dna2);
  
  int length = longestCommonSubsequence(dna1, dna2);
  cout << length << '\n';
  return 0;
}
  
