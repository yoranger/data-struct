#ifndef MATMUL_DIVIDE_CONQUER_H
#define MATMUL_DIVIDE_CONQUER_H

#include "matrix_utilities.h"

// Naive divide-and-conquer matrix multiplication (8 recursive multiplications).
MatrixInt64 matmulDivideConquer8(const MatrixInt64 &matrix_a,
                                 const MatrixInt64 &matrix_b);

#endif
