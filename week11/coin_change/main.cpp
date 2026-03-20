#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "coin_change.h"

using namespace std;

int main(int argc, char *argv[]) {
    // Check for the correct number of arguments
    if (argc != 2) {
      cerr << "Usage: " << argv[0] << " <filename>" << endl;
      return EXIT_FAILURE;
    }

    // Open the file
    string test_filename = argv[1];
    ifstream file(test_filename);
    if (!file) {
      cerr << "Error opening file: " << test_filename << endl;
      return EXIT_FAILURE;
    }

    // Read the amount from the file on the first line and the coin values on the second line
    int amount;
    file >> amount;
    vector<int> coins;
    int coin;
    while (file >> coin) {
      coins.push_back(coin);
    }
    file.close();
    
    // Call the coinChange function
    int result = coinChange(coins, amount);
    cout << result << '\n';

    return 0;
  }
    
  