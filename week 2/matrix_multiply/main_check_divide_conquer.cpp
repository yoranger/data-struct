#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "matmul_divide_conquer.h"
#include "matrix_utilities.h"

int main(int argc, char **argv) {
  enum ExitCode {
    ok = EXIT_SUCCESS,
    fail = 1,
    usage = 2,
    io = 3,
    bad_input = 4,
  };

  if (argc < 2) {
    std::cerr << "Usage: check_divide_conquer <input.txt>\n";
    return usage;
  }

  std::ifstream in(argv[1]);
  if (!in.is_open()) {
    std::cerr << "Error: could not open file " << argv[1] << "\n";
    return io;
  }

  try {
    const int n = readDimension(in);
    if (n <= 0) {
      std::cerr << "Error: invalid matrix dimension\n";
      return bad_input;
    }

    const MatrixInt64 matrix_a = readMatrix(in, n);
    const MatrixInt64 matrix_b = readMatrix(in, n);
    const MatrixInt64 matrix_expected = readMatrix(in, n);

    const MatrixInt64 matrix_c = matmulDivideConquer8(matrix_a, matrix_b);

    if (matricesEqual(matrix_c, matrix_expected)) {
      std::cout << "PASS\n";
      return ok;
    }

    std::cout << "FAIL\n";
    return fail;
  } catch (const std::exception &ex) {
    std::cerr << "Error: " << ex.what() << "\n";
    return bad_input;
  }
}
