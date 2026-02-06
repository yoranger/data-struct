#include <iostream>
#include <vector>

using namespace std;

// Utility function to print a vector.
void printVector(const std::vector<int> &a) {
  for (int x : a) {
    std::cout << ' ' << x;
  }
}

// Bubble sort in ascending order.
// Uses an early-exit flag to stop if the array becomes sorted before all
// passes.
void bubbleSort(std::vector<int> &a) {
  std::size_t n = a.size();
  if (n < 2)
    return;              // already sorted or empty
  bool swapped = false;  // Reset the flag at the start of each pass

  // After each pass, the largest element among the unsorted part
  // "bubbles up" to its correct position at the end.[web:28][web:30]
  for (std::size_t pass = 0; pass < n - 1; ++pass) {
    // **** do not remove, for gradescope ***
    cout << " -->";
    printVector(a);
    cout << endl;

    // To Do : implement and inner loop to "bubble up" next large number.
      for (size_t j = 0; j < n - pass - 1; ++j)
      {
        if(a[j] > a[j + 1])
        {
          std::swap(a[j], a[j + 1]);
          swapped = true;
        }
      }
      if(!swapped)
        break;
  }
}

int main() {
  int input_size;

  // Input array size
  cout << "Enter the input size: ";
  cin >> input_size;

  // Input array elements
  vector<int> arr(input_size);
  cout << "\nEnter the elements of the input: ";
  for (int i = 0; i < input_size; i++) {
    cin >> arr[i];
  }
  cout << endl;

  bubbleSort(arr);

  std::cout << "Sorted:";
  printVector(arr);
  cout << endl;

  return 0;
}
