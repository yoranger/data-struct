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

// Print array
void printArray(vector<int> &arr) {
  for (size_t j = 0; j < arr.size(); j++) {
    cout << " " << arr[j];
  }
}

// Print partial_array
void printPartialArray(vector<int> &arr, int low, int high) {
  for (int j = low; j <= high; j++) {
    cout << " " << arr[j];
  }
}

// Recursive function for Quick Sort. Uses partition()
void quickSort(vector<int> &arr, int low, int high) {
  //***** for debug do not remove *******
  cout << "\n-->";
  printPartialArray(arr, low, high);

  int new_pivot = partition(arr, low, high);
  if(low < new_pivot)
  {
    quickSort(arr, low, new_pivot - 1);
  }
  if(new_pivot < high)
  {
    quickSort(arr, new_pivot + 1, high);
  }

  // Insert recursion here:
}

int main() {
  int n;

  // Input array size
  cout << "Enter the number of elements: ";
  cin >> n;

  // Input array elements
  vector<int> arr(n);
  cout << "\nEnter the elements of the array: ";
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  // Find k-th smallest element
  quickSort(arr, 0, n - 1);

  // Output result
  cout << "\n==>";
  printArray(arr);
  cout << endl;

  return 0;
}
