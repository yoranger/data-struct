#include "matmul_divide_conquer.h"

#include <cstddef>
#include <stdexcept>

// Returns the smallest power of two that is >= n.
// Examples: nextPowerOfTwo(5) = 8, nextPowerOfTwo(8) = 8.
static std::size_t nextPowerOfTwo(std::size_t n) {
  std::size_t p = 1;
  while (p < n) {
    p *= 2;
  }
  return p;
}

// Recursive helper: Computes matrix_c += matrix_a * matrix_b for n x n
// submatrices. The submatrices are specified by their top-left corner offsets.
static void blockMatmulAdd(const MatrixInt64 &matrix_a,
                           std::size_t a_row_offset, std::size_t a_col_offset,
                           const MatrixInt64 &matrix_b,
                           std::size_t b_row_offset, std::size_t b_col_offset,
                           MatrixInt64 &matrix_c, std::size_t c_row_offset,
                           std::size_t c_col_offset, std::size_t n) {
  // TODO: Implement the base case (n == 1).

  // TODO: Compute h = n / 2, then make 8 recursive calls:
  // c11 += a11*b11; c11 += a12*b21
  // c12 += a11*b12; c12 += a12*b22
  // c21 += a21*b11; c21 += a22*b21
  // c22 += a21*b12; c22 += a22*b22
  //
  // Use offsets to specify quadrants. For example:
  // - a11 has offset (a_row_offset, a_col_offset)
  // - a12 has offset (a_row_offset, a_col_offset + h)
  // - a21 has offset (a_row_offset + h, a_col_offset)
  // - a22 has offset (a_row_offset + h, a_col_offset + h)
  if(n == 1)
  {
    matrix_c[c_row_offset][c_col_offset] += matrix_a[a_row_offset][a_col_offset] * matrix_b[b_row_offset][b_col_offset];
    return;
  }

  int h = n / 2;
  // C11 += A11*B11
  blockMatmulAdd(matrix_a, a_row_offset,       a_col_offset,
                 matrix_b, b_row_offset,       b_col_offset,
                 matrix_c, c_row_offset,       c_col_offset, h);

  // C11 += A12*B21
  blockMatmulAdd(matrix_a, a_row_offset,       a_col_offset + h,
                 matrix_b, b_row_offset + h,   b_col_offset,
                 matrix_c, c_row_offset,       c_col_offset, h);

  // C12 += A11*B12
  blockMatmulAdd(matrix_a, a_row_offset,       a_col_offset,
                 matrix_b, b_row_offset,       b_col_offset + h,
                 matrix_c, c_row_offset,       c_col_offset + h, h);

  // C12 += A12*B22
  blockMatmulAdd(matrix_a, a_row_offset,       a_col_offset + h,
                 matrix_b, b_row_offset + h,   b_col_offset + h,
                 matrix_c, c_row_offset,       c_col_offset + h, h);

  // C21 += A21*B11
  blockMatmulAdd(matrix_a, a_row_offset + h,   a_col_offset,
                 matrix_b, b_row_offset,       b_col_offset,
                 matrix_c, c_row_offset + h,   c_col_offset, h);

  // C21 += A22*B21
  blockMatmulAdd(matrix_a, a_row_offset + h,   a_col_offset + h,
                 matrix_b, b_row_offset + h,   b_col_offset,
                 matrix_c, c_row_offset + h,   c_col_offset, h);

  // C22 += A21*B12
  blockMatmulAdd(matrix_a, a_row_offset + h,   a_col_offset,
                 matrix_b, b_row_offset,       b_col_offset + h,
                 matrix_c, c_row_offset + h,   c_col_offset + h, h);

  // C22 += A22*B22
  blockMatmulAdd(matrix_a, a_row_offset + h,   a_col_offset + h,
                 matrix_b, b_row_offset + h,   b_col_offset + h,
                 matrix_c, c_row_offset + h,   c_col_offset + h, h);

}

MatrixInt64 matmulDivideConquer8(const MatrixInt64 &matrix_a,
                                 const MatrixInt64 &matrix_b) {
  const std::size_t n = matrix_a.size();
  if (n == 0) {
    throw std::invalid_argument(
        "matmulDivideConquer8 expects non-empty matrices");
  }
  if (matrix_b.size() != n) {
    throw std::invalid_argument(
        "matmulDivideConquer8 expects matrices of the same size");
  }
  for (std::size_t i = 0; i < n; ++i) {
    if (matrix_a[i].size() != n || matrix_b[i].size() != n) {
      throw std::invalid_argument(
          "matmulDivideConquer8 expects square matrices");
    }
  }
  const std::size_t padded_dim = nextPowerOfTwo(n);
  const MatrixInt64 *a_ptr = &matrix_a;
  const MatrixInt64 *b_ptr = &matrix_b;
  MatrixInt64 a_pad, b_pad;
  MatrixInt64 matrix_c(n, std::vector<std::int64_t>(n, 0));
  MatrixInt64 *c_ptr = &matrix_c;
  MatrixInt64 c_pad;
  if (padded_dim != n) {  // Pad to the next power of two.
    a_pad.assign(padded_dim, std::vector<std::int64_t>(padded_dim, 0));
    b_pad.assign(padded_dim, std::vector<std::int64_t>(padded_dim, 0));
    c_pad.assign(padded_dim, std::vector<std::int64_t>(padded_dim, 0));
    for (std::size_t i = 0; i < n; ++i) {
      for (std::size_t j = 0; j < n; ++j) {
        a_pad[i][j] = matrix_a[i][j];
        b_pad[i][j] = matrix_b[i][j];
      }
    }
    a_ptr = &a_pad;
    b_ptr = &b_pad;
    c_ptr = &c_pad;
  }
  blockMatmulAdd(*a_ptr, 0, 0, *b_ptr, 0, 0, *c_ptr, 0, 0, padded_dim);
  if (padded_dim != n) {  // Extract result from padded matrix.
    for (std::size_t i = 0; i < n; ++i) {
      for (std::size_t j = 0; j < n; ++j) {
        matrix_c[i][j] = c_pad[i][j];
      }
    }
  }
  return matrix_c;
}
