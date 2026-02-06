#include <iostream>
#include <vector>

using namespace std;

// Partition function based on QuickSort
int partition(vector<int> &arr, int low, int high) {
  int pivot = arr[high];
  int i = low;

  for (int j = low; j < high; j++) {
    if (arr[j] < pivot) {
      swap(arr[i], arr[j]);
      i++;
    }
  }
  swap(arr[i], arr[high]);
  return i;
}

// Print partial_array
void printPartialArray(vector<int> &arr, int low, int high) {
  for (int j = low; j <= high; j++) {
    cout << " " << arr[j];
  }
}

// Function to find the k-th smallest element
int kthSmallest(vector<int> &arr, int low, int high, int k) {
  if (low <= high) {
    //***** for debug do not remove *******
    cout << "\n-->";
    printPartialArray(arr, low, high);

    // Partition the array
    int pivot_index = partition(arr, low, high);
    // *** add recursion here. ***
    if(pivot_index == k - 1)
      return arr[pivot_index];
    else if(pivot_index < k - 1)
      return kthSmallest(arr, pivot_index + 1, high, k);
    else
      return kthSmallest(arr, low, pivot_index - 1, k);

    //return arr[pivot_index];
  }

  return -1;  // If k is out of bounds
}

int main() {
  int n, k;

  // Input array size
  cout << "Enter the number of elements: ";
  cin >> n;

  // Input array elements
  vector<int> arr(n);
  cout << "\nEnter the elements of the array: ";
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  // Input k
  cout << "\nEnter the value of k: ";
  cin >> k;

  if (k < 1 || k > n) {
    cout << "Invalid input. k must be between 1 and " << n << "." << endl;
    return 0;
  }

  // Find k-th smallest element
  int result = kthSmallest(arr, 0, n - 1, k);

  // Output result
  cout << "\nThe " << k
       << (k == 1   ? "st"
           : k == 2 ? "nd"
           : k == 3 ? "rd"
                    : "th")
       << " smallest element is: " << result << endl;

  return 0;
}
