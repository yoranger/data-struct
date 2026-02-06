#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "import_numbers_from_file.h"
#include "merge_sort.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return EXIT_FAILURE;
  }

  const std::string filename = argv[1];
  std::vector<int> a = importNumbersFromFile(filename);
  if (!a.empty()) {
    mergeSort(a, 0, a.size() - 1);
  }

  for (std::size_t k = 0; k < a.size(); ++k) {
    if (k > 0) {
      std::cout << ", ";
    }
    std::cout << a[k];
  }
  std::cout << '\n';
  return EXIT_SUCCESS;
}