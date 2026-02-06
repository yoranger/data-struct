#ifndef MATRIX_UTILITIES_H
#define MATRIX_UTILITIES_H

#include <cstdint>
#include <istream>
#include <vector>

using MatrixInt64 = std::vector<std::vector<std::int64_t>>;

int readDimension(std::istream &in);
MatrixInt64 readMatrix(std::istream &in, int dimension);
void printMatrix(const MatrixInt64 &matrix);
bool matricesEqual(const MatrixInt64 &matrix_a, const MatrixInt64 &matrix_b);

#endif
