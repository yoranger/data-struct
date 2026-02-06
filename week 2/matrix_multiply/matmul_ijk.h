#ifndef MATMUL_IJK_H
#define MATMUL_IJK_H

#include "matrix_utilities.h"

// Straightforward triple-loop matrix multiplication with loop order i-j-k.
MatrixInt64 matmulIJK(const MatrixInt64 &matrix_a, const MatrixInt64 &matrix_b);

#endif
