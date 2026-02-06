#include "merge_sort.h"

#include <cstddef>
#include <vector>

static void merge(std::vector<int> &a, std::size_t l, std::size_t m,
                  std::size_t r) {
  const std::size_t n_left = m - l + 1;
  const std::size_t n_right = r - m;
  std::vector<int> left(n_left);
  std::vector<int> right(n_right);
  for (std::size_t j = 0; j < n_left; ++j) {
    left[j] = a[l + j];
  }
  for (std::size_t k = 0; k < n_right; ++k) {
    right[k] = a[m + 1 + k];
  }
  std::size_t i = l;
  std::size_t j = 0;
  std::size_t k = 0;
  while (j < n_left && k < n_right) {
    if (left[j] <= right[k]) {
      a[i] = left[j];
      ++j;
    } else {
      a[i] = right[k];
      ++k;
    }
    ++i;
  }
  while (j < n_left) {
    a[i] = left[j];
    ++i;
    ++j;
  }
  while (k < n_right) {
    a[i] = right[k];
    ++i;
    ++k;
  }
}

void mergeSort(std::vector<int> &a, std::size_t l, std::size_t r) {
  if (l >= r) {
    return;
  }
  const std::size_t m = l + (r - l) / 2;
  mergeSort(a, l, m);
  mergeSort(a, m + 1, r);
  merge(a, l, m, r);
}
