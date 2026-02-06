#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#include "nlohmann_json.h"
#include "vega_lite_plot.h"

using namespace std;

// Utility function to print a vector.
void printVector(const std::vector<int> &a) {
  for (int x : a) {
    std::cout << ' ' << x;
  }
}

// Bubble sort in ascending order.
// * Use early-exit flag to stop once the array becomes sorted.
void bubbleSort(std::vector<int> &a) {
  // Replace with function from previous exercises.
}

int main() {
  int display_width = 12;

  int duration1;
  int duration2;
  int duration3;
  int total1;
  int total2;
  int total3;
  int dimension;

  vector<size_t> sizes;
  vector<long long> times1;
  vector<long long> times2;
  vector<long long> times3;

  cout << setw(display_width) << "Size";
  cout << setw(display_width) << "Time(Min)";
  cout << setw(display_width) << "Time(Typ)";
  cout << setw(display_width) << "Time(Max)";
  cout << endl;

  for (dimension = 400; dimension <= 25600; dimension *= 2) {
    // Random Generator Initialization.
    random_device rd;   // Seed
    mt19937 gen(rd());  // Random number generator
    uniform_real_distribution<> dis(-dimension,
                                    dimension);  // Distribution range

    total1 = 0;
    total2 = 0;
    total3 = 0;
    int iterations = (int)(25600 / dimension);
    vector<int> data1(dimension);
    vector<int> data2(dimension);
    vector<int> data3(dimension);

    for (int m = 0; m < iterations; m++) {
      for (int i = 0; i < dimension; i++) {
        data1[i] = i;
      }  // sorted
      for (int i = 0; i < dimension; i++) {
        data2[i] = dis(gen);
      }  // reversed
      for (int i = 0; i < dimension; i++) {
        data3[i] = dimension - i;
      }  // reversed
      chrono::time_point<chrono::high_resolution_clock> start1, start2, start3,
          end1, end2, end3;
      start1 = chrono::high_resolution_clock::now();
      bubbleSort(data1);
      end1 = chrono::high_resolution_clock::now();
      start2 = chrono::high_resolution_clock::now();
      bubbleSort(data2);
      end2 = chrono::high_resolution_clock::now();
      start3 = chrono::high_resolution_clock::now();
      bubbleSort(data3);
      end3 = chrono::high_resolution_clock::now();
      duration1 =
          chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
      duration2 =
          chrono::duration_cast<chrono::microseconds>(end2 - start2).count();
      duration3 =
          chrono::duration_cast<chrono::microseconds>(end3 - start3).count();
      total1 += duration1;
      total2 += duration2;
      total3 += duration3;
    }
    long long ave1 = (total1 * 1000L) / iterations;
    long long ave2 = (total2 * 1000L) / iterations;
    long long ave3 = (total3 * 1000L) / iterations;
    sizes.push_back(dimension);
    times1.push_back(ave1);
    times2.push_back(ave2);
    times3.push_back(ave3);
    cout << setw(display_width) << dimension;
    cout << setw(display_width) << ave1;
    cout << setw(display_width) << ave2;
    cout << setw(display_width) << ave3;
    cout << endl;
  }

  // Generate Vega-Lite JSON specification
  nlohmann::json spec = generate_vega_lite_spec(sizes, times1, times2, times3);

  // Generate HTML file
  generate_html(spec, "bubble_sort_timings.html");

  return 0;
}
