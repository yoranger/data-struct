#include "import_numbers_from_file.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static std::string trim(const std::string &s) {
  std::size_t first = 0;
  while (first < s.size() &&
         std::isspace(static_cast<unsigned char>(s[first]))) {
    ++first;
  }
  std::size_t last = s.size();
  while (last > first &&
         std::isspace(static_cast<unsigned char>(s[last - 1]))) {
    --last;
  }
  return s.substr(first, last - first);
}

std::vector<int> importNumbersFromFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Error: Could not open file: " << filename << "\n";
    return {};
  }

  std::vector<int> numbers;
  std::string chunk;
  std::size_t token_no = 0;

  while (std::getline(file, chunk, ',')) {
    ++token_no;

    // Windows line endings
    if (!chunk.empty() && chunk.back() == '\r') {
      chunk.pop_back();
    }

    const std::string token = trim(chunk);
    if (token.empty()) {
      if (file.eof()) {
        continue;
      }
      std::cerr << "Error: Empty value near comma (token " << token_no
                << ").\n";
      return {};
    }

    std::istringstream iss(token);
    int x;
    if (!(iss >> x)) {
      std::cerr << "Error: Invalid integer in token " << token_no << ": "
                << token << "\n";
      return {};
    }

    char extra;
    if (iss >> extra) {
      std::cerr << "Error: Trailing characters in token " << token_no << ": "
                << token << "\n";
      return {};
    }

    numbers.push_back(x);
  }

  return numbers;
}