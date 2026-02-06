#include "bstree.h"
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <set>
#include <vector>

// Function to generate random keys
std::vector<double> generateRandomKeys(size_t size) {
  std::vector<double> keys(size);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  for (size_t i = 0; i < size; ++i) {
    keys[i] = dist(gen);
  }
  return keys;
}

// Function to measure the time taken to insert keys into a container
template <typename Container>
void insertKeys(Container &container, const std::vector<double> &keys) {
  for (const double &key : keys) {
    container.insert(key);
  }
}

// Function to measure the time taken to search for keys in a BSTree
double measureSearchTime(const BSTree &bst, const std::vector<double> &keys) {
  auto start = std::chrono::high_resolution_clock::now();
  for (const double &key : keys) {
    bst.search(key);
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  return duration.count();
}

// Function to measure the time taken to search for keys in a std::set
double measureSearchTime(const std::set<double> &std_set,
                         const std::vector<double> &keys) {
  auto start = std::chrono::high_resolution_clock::now();
  for (const double &key : keys) {
    std_set.find(key);
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  return duration.count();
}

int main() {
  std::vector<size_t> key_sizes = {1000, 2000, 5000, 10000, 20000, 50000};

  // Output header
  std::cout << std::setw(10) << "Key Size" << std::setw(25)
            << "BSTree Random (s)" << std::setw(25) << "std::set Random (s)"
            << std::setw(25) << "BSTree Sorted (s)" << std::setw(25)
            << "std::set Sorted (s)" << std::endl;

  // Vectors to store the results for plotting
  std::vector<double> bst_search_times_random;
  std::vector<double> std_set_search_times_random;
  std::vector<double> bst_search_times_sorted;
  std::vector<double> std_set_search_times_sorted;

  for (size_t size : key_sizes) {
    std::vector<double> random_keys = generateRandomKeys(size);
    std::vector<double> sorted_keys = random_keys;
    std::sort(sorted_keys.begin(), sorted_keys.end());

    // Containers
    BSTree bst;
    std::set<double> std_set;

    // Insert keys into containers
    insertKeys(bst, random_keys);
    insertKeys(std_set, random_keys);

    // Measure search time for random keys
    double bst_search_time_random = measureSearchTime(bst, random_keys);
    double std_set_search_time_random = measureSearchTime(std_set, random_keys);

    // Clear containers
    bst = BSTree();
    std_set.clear();

    // Insert keys into containers again for sorted keys
    insertKeys(bst, sorted_keys);
    insertKeys(std_set, sorted_keys);

    // Measure search time for sorted keys
    double bst_search_time_sorted = measureSearchTime(bst, sorted_keys);
    double std_set_search_time_sorted = measureSearchTime(std_set, sorted_keys);

    // Store the results for plotting
    bst_search_times_random.push_back(bst_search_time_random);
    std_set_search_times_random.push_back(std_set_search_time_random);
    bst_search_times_sorted.push_back(bst_search_time_sorted);
    std_set_search_times_sorted.push_back(std_set_search_time_sorted);

    // Print results to console
    std::cout << std::setw(10) << size << std::setw(25)
              << bst_search_time_random << std::setw(25)
              << std_set_search_time_random << std::setw(25)
              << bst_search_time_sorted << std::setw(25)
              << std_set_search_time_sorted << std::endl;
  }

  return 0;
}