#include "matrix_utilities.h"

#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

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

static std::vector<std::int64_t> parseRowOfIntegers(const std::string &line,
                                                    int expected_count) {
  if (expected_count <= 0) {
    throw std::invalid_argument("expected_count must be positive");
  }
  std::vector<std::int64_t> values;
  values.reserve(static_cast<std::size_t>(expected_count));
  const bool has_comma = (line.find(',') != std::string::npos);
  if (has_comma) {
    std::string chunk;
    std::istringstream iss(line);
    while (std::getline(iss, chunk, ',')) {
      const std::string token = trim(chunk);
      if (token.empty()) {
        throw std::runtime_error("empty value near comma");
      }

      std::istringstream token_stream(token);
      std::int64_t x;
      if (!(token_stream >> x)) {
        throw std::runtime_error("invalid integer token: " + token);
      }
      char extra;
      if (token_stream >> extra) {
        throw std::runtime_error("trailing characters in token: " + token);
      }
      values.push_back(x);
    }
  } else {
    std::istringstream iss(line);
    std::int64_t x;
    while (iss >> x) {
      values.push_back(x);
    }
    char extra;
    if (iss >> extra) {
      throw std::runtime_error("invalid characters in row");
    }
  }
  if (static_cast<int>(values.size()) != expected_count) {
    throw std::runtime_error("expected " + std::to_string(expected_count) +
                             " values but got " +
                             std::to_string(values.size()));
  }
  return values;
}

int readDimension(std::istream &in) {
  std::string line;
  while (std::getline(in, line)) {
    // Windows line endings
    if (!line.empty() && line.back() == '\r') {
      line.pop_back();
    }

    // Strip inline comments.
    const std::size_t hash_pos = line.find('#');
    if (hash_pos != std::string::npos) {
      line = line.substr(0, hash_pos);
    }

    std::istringstream iss(line);
    int n = 0;
    if (iss >> n) {
      return n;
    }
  }
  return 0;
}

MatrixInt64 readMatrix(std::istream &in, int dimension) {
  if (dimension <= 0) {
    throw std::invalid_argument("dimension must be positive");
  }
  MatrixInt64 matrix(dimension, std::vector<std::int64_t>(dimension, 0));
  std::string line;
  int row = 0;
  while (row < dimension && std::getline(in, line)) {
    // Windows line endings
    if (!line.empty() && line.back() == '\r') {
      line.pop_back();
    }

    // Strip inline comments.
    const std::size_t hash_pos = line.find('#');
    if (hash_pos != std::string::npos) {
      line = line.substr(0, hash_pos);
    }

    const std::string line_data = trim(line);
    if (line_data.empty()) {
      continue;
    }
    const std::vector<std::int64_t> values =
        parseRowOfIntegers(line_data, dimension);
    for (int col = 0; col < dimension; ++col) {
      matrix[row][col] = values[col];
    }
    ++row;
  }
  if (row != dimension) {
    throw std::runtime_error("failed to read matrix: expected " +
                             std::to_string(dimension) + " rows");
  }
  return matrix;
}

void printMatrix(const MatrixInt64 &matrix) {
  for (const auto &row : matrix) {
    for (std::size_t j = 0; j < row.size(); ++j) {
      if (j > 0) {
        std::cout << ",";
      }
      std::cout << row[j];
    }
    std::cout << "\n";
  }
}

bool matricesEqual(const MatrixInt64 &matrix_a, const MatrixInt64 &matrix_b) {
  if (matrix_a.size() != matrix_b.size()) {
    return false;
  }
  if (matrix_a.empty()) {
    return true;
  }
  if (matrix_a[0].size() != matrix_b[0].size()) {
    return false;
  }
  for (std::size_t i = 0; i < matrix_a.size(); ++i) {
    if (matrix_a[i].size() != matrix_b[i].size()) {
      return false;
    }
    for (std::size_t j = 0; j < matrix_a[i].size(); ++j) {
      if (matrix_a[i][j] != matrix_b[i][j]) {
        return false;
      }
    }
  }
  return true;
}
