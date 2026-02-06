#include "matmul_ijk.h"

#include <stdexcept>

MatrixInt64 matmulIJK(const MatrixInt64 &matrix_a,
                      const MatrixInt64 &matrix_b) {
  const std::size_t n = matrix_a.size();
  if (n == 0) {
    throw std::invalid_argument("matmulIJK expects non-empty matrices");
  }
  if (matrix_b.size() != n) {
    throw std::invalid_argument("matmulIJK expects matrices of the same size");
  }
  for (std::size_t i = 0; i < n; ++i) {
    if (matrix_a[i].size() != n || matrix_b[i].size() != n) {
      throw std::invalid_argument("matmulIJK expects square matrices");
    }
  }
  MatrixInt64 matrix_c(n, std::vector<std::int64_t>(n, 0));

  // TODO: Implement the triple loop (i-j-k order) to compute matrix_c.
  // Recall: C_ij = sum_{k=0}^{n-1} A_ik * B_kj
  for (int i = 0; i < matrix_a.size(); ++i)
    for (int j = 0; j < matrix_b[0].size(); ++j)
      for (int k = 0; k < matrix_b.size(); ++k)
        matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];

    return matrix_c;
}
