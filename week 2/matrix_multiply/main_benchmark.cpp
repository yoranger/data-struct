#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

#include "matmul_divide_conquer.h"
#include "matmul_ijk.h"
#include "matrix_utilities.h"
#include "vega_lite_plot.h"

static MatrixInt64 randomMatrix(int n, std::mt19937 &rng) {
  std::uniform_int_distribution<std::int64_t> dist(-1000, 1000);
  MatrixInt64 matrix(n, std::vector<std::int64_t>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      matrix[i][j] = dist(rng);
    }
  }
  return matrix;
}

template <typename Fn>
static long long timeMicroseconds(Fn &&fn) {
  const auto start = std::chrono::steady_clock::now();
  fn();
  const auto stop = std::chrono::steady_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
      .count();
}

template <typename Fn>
static long long medianTimeMicroseconds(Fn &&fn, int trials) {
  if (trials <= 0) {
    throw std::invalid_argument("trials must be positive");
  }

  // Warmup (unmeasured) to reduce first-run effects.
  fn();
  std::vector<long long> times;
  times.reserve(static_cast<std::size_t>(trials));
  for (int t = 0; t < trials; ++t) {
    times.push_back(timeMicroseconds(fn));
  }
  std::sort(times.begin(), times.end());
  return times[static_cast<std::size_t>(trials / 2)];
}

static bool isPowerOfTwo(int n) {
  return n > 0 && (n & (n - 1)) == 0;
}

static std::vector<int> defaultSizesUpTo(int max_n) {
  if (max_n < 8) {
    max_n = 8;
  }
  std::vector<int> sizes;
  for (int n = 8; n <= max_n; n *= 2) {
    sizes.push_back(n);
  }
  return sizes;
}

int main(int argc, char **argv) {
  std::mt19937 rng(12345);
  const int trials = 7;

  // Keep sizes modest by default so this runs quickly everywhere.
  // You can override, e.g. `./benchmark 256`.
  int max_n = 64;
  if (argc >= 2) {
    try {
      max_n = std::stoi(argv[1]);
    } catch (const std::exception &) {
      std::cerr << "Usage: benchmark [max_n]\n";
      return EXIT_FAILURE;
    }
    if (!isPowerOfTwo(max_n) || max_n < 8) {
      std::cerr << "Error: max_n must be a power of two and >= 8\n";
      return EXIT_FAILURE;
    }
  }
  const std::vector<int> sizes = defaultSizesUpTo(max_n);
  std::vector<long long> ijk_times;
  std::vector<long long> dac_times;
  ijk_times.reserve(sizes.size());
  dac_times.reserve(sizes.size());
  std::cout << "Matrix multiplication benchmark (median of " << trials
            << " trials; times in microseconds).\n";
  std::cout << std::left << std::setw(8) << "n" << std::setw(22)
            << "Triple Loop (ijk)" << std::setw(26) << "8-Fold Block Recursion"
            << '\n';
  std::cout << std::string(56, '-') << '\n';
  for (int n : sizes) {
    const MatrixInt64 matrix_a = randomMatrix(n, rng);
    const MatrixInt64 matrix_b = randomMatrix(n, rng);
    MatrixInt64 matrix_c1;
    MatrixInt64 matrix_c2;
    const long long t_ijk = medianTimeMicroseconds(
        [&]() { matrix_c1 = matmulIJK(matrix_a, matrix_b); }, trials);
    const long long t_dac = medianTimeMicroseconds(
        [&]() { matrix_c2 = matmulDivideConquer8(matrix_a, matrix_b); },
        trials);
    if (!matricesEqual(matrix_c1, matrix_c2)) {
      std::cerr << "Warning: results differ for n=" << n << "\n";
    }
    ijk_times.push_back(t_ijk);
    dac_times.push_back(t_dac);
    std::cout << std::left << std::setw(8) << n << std::setw(22) << t_ijk
              << std::setw(26) << t_dac << '\n';
  }
  const std::string spec_json =
      generateVegaLiteSpecJson(sizes, ijk_times, dac_times);
  generateHtml(spec_json, "vega_lite_plot.html");
  std::cout << "\nWrote plot to vega_lite_plot.html\n";

  return EXIT_SUCCESS;
}
