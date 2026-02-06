#include <iostream>
#include <vector>

using namespace std;

// Utility function to print the heap
void printHeap(const vector<int> &heap) {
  for (int val : heap) {
    cout << " " << val;
  }
}

// Min-heapify the subtree rooted at index i in array of size n
void minHeapify(vector<int> &arr, int n, int i) {
  // **** Do not remove! for grading
  cout << " -->";
  printHeap(arr);
  cout << endl;

  int smallest = i;       // Assume root is smallest
  int left = 2 * i + 1;   // Left child index
  int right = 2 * i + 2;  // Right child index

  // TODO: Compare with the left child
  if(left < n && arr[smallest] > arr[left])
    smallest = left;
  // TODO: Compare with the right child
  if(right < n && arr[smallest] > arr[right])
    smallest = right;
  // TODO: If the smallest is not the current node, swap and recursively call
  if(i != smallest)
  {
    std::swap(arr[i], arr[smallest]);
    minHeapify(arr, n, smallest);
  }
}

// Example: build a min-heap from an array
void buildMinHeap(vector<int> &arr, int n) {
  // Start from last non-leaf node and heapify backwards
  for (int i = n / 2 - 1; i >= 0; i--) {
    minHeapify(arr, n, i);
  }
}

void heapSort(vector<int> &arr, int n) {
  // TODO: If the smallest is not the current node, swap and recursively call
  for (int i = n - 1; i > 0; --i)
  {
    std::swap(arr[i], arr[0]);
    minHeapify(arr, i, 0);
  }
}

// Example usage
int main() {
  int heap_size;

  // Input array size
  cout << "Enter the min heap size: ";
  cin >> heap_size;

  // Input array elements
  vector<int> min_heap(heap_size);
  cout << "\nEnter the elements of the min heap: ";
  for (int i = 0; i < heap_size; i++) {
    cin >> min_heap[i];
  }

  cout << "\nOriginal: ";
  printHeap(min_heap);

  buildMinHeap(min_heap, heap_size);
  cout << "Min-heap: ";
  printHeap(min_heap);

  heapSort(min_heap, heap_size);
  cout << "Sorted: ";
  printHeap(min_heap);
  cout << endl;

  return 0;
}
