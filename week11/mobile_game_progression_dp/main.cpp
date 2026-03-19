#include <iostream>
#include "mobile_game_progression_dp.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <number>" << endl;
    return EXIT_FAILURE;
  }

  string number = argv[1];
  int n;
  n = stoi(number);
  cout << calculateProgressionPathsDP(n) << '\n';

  return 0;
}