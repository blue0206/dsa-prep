/*
 * QUICK SORT
 *
 * Pick a pivot and place it at its correct place.
 *
 * Possible pivots: 1. First element in array.
 *                  2. Last element in array.
 *                  3. Mid/Median of the array.
 *                  4. Random element of array.
 *
 * Basically, after we pick a pivot, we move all the elements lesser than or
 * equal to pivot on its left and all the elements greater than pivot on its
 * right. And finally, we place the pivot at its correct place.
 * Once this is done, our array is successfully divided into left half, the
 * pivot, and the right half. Since our pivot is at its correct position, we
 * leave it as is. However, the left and right halves are still unsorted and
 * hence we recursively repeat the steps for both subarrays.
 *
 * Time Complexity: O(N^2) in worst case, O(N logN) in average and best case.
 * Space Complexity: O(N) in worst case, O(logN) in average and best case.
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

enum class PartitionMethod {
  FIRST_ELEMENT,    // Hoare
  LAST_ELEMENT,     // Lomuto
  RANDOM,           // Random pivot, uses Lomuto
  MEDIAN_OF_THREE,  // Median-of-three pivot, uses Lomuto
};

using namespace std;

void printArr(vector<int>& arr) {
  cout << "[ ";
  for (auto i : arr) {
    cout << i << " ";
  }
  cout << "]" << endl;
}

int partitionWithFirstElement(vector<int>& arr, int start, int end) {
  // Hoare Partition Scheme
  // We select first element as pivot.
  int pivot = arr[start];

  int low = start;
  int high = end;
  while (low < high) {
    // Move low pointer until an element greater than pivot is found.
    while (arr[low] <= pivot && low < end) low++;
    // Move high pointer until an element lesser than or equal to pivot is
    // found.
    while (arr[high] > pivot && high > start) high--;

    // If within bounds, swap them. As elements in low's domain must be lesser
    // than or equal to pivot and elements in high's domain must be greater than
    // pivot.
    if (low < high) {
      swap(arr[low], arr[high]);
    }
  }

  // Once swaps are done and all elements have been properly placed in left or
  // right of pivot, we move the pivot to its correct position, which in this
  // case is the high pointer's position (as it now points to an element equal
  // to or lesser than pivot based on how the while loop termination has been
  // set up.)
  swap(arr[start], arr[high]);
  return high;
}

int partitionWithLastElement(vector<int>& arr, int start, int end) {
  // Lomuto Partition Scheme.
  // We setup an index right before start index to serve as a boundary between
  // processed and unprocessed elements.
  // Then, we simply compare and swap (after incrementing the boundary index)
  // with the boundary index, going start to end-1 (all elements except pivot).
  // At the end, the position right after boundary index (i+1) is the true
  // position of pivot element, so we simply swap and return pivot index.
  // We can also use this method for partitioning with first element.
  int pivot = arr[end];
  int partitionIndex = start - 1;

  for (int i = start; i < end; i++) {
    if (arr[i] <= pivot) {
      swap(arr[++partitionIndex], arr[i]);
    }
  }

  swap(arr[++partitionIndex], arr[end]);
  return partitionIndex;
}

// Selects the first, middle, and last elements and determines the median value
// and further performs processing to place the median value at the last place
// in order to perform last index partitioning with lomuto scheme.
int partitionWithMedianElement(vector<int>& arr, int start, int end) {
  int mid = start + (end - start) / 2;

  // We first have to place first, middle, and last elements in ascending order
  // and pick the middle one afterwards, which is known as median.

  // Check if first element is greater than mid and if yes, swap to ensure
  // it has smaller element.
  if (arr[start] > arr[mid]) {
    swap(arr[start], arr[mid]);
  }

  // Check if first element is greater than end and if yes, swap. This ensures
  // that the first element is the smallest of all. (or equal).
  if (arr[start] > arr[end]) {
    swap(arr[start], arr[end]);
  }

  // Now we are only left with mid and last elements. Therefore, we ensure
  // that the element at mid is smaller than last element.
  if (arr[mid] > arr[end]) {
    swap(arr[mid], arr[end]);
  }

  // Since we have our median as mid element, we simply swap it with last
  // element to further perform last element partitioning.
  swap(arr[mid], arr[end]);

  return partitionWithLastElement(arr, start, end);
}

int partitionWithRandomElement(vector<int>& arr, int start, int end) {
  // Get a random pivot element.
  int pivotIndex = start + (rand() % (end - start + 1));

  // Swap pivot element with last element and continue with last element/Lomuto
  // partition.
  swap(arr[pivotIndex], arr[end]);
  return partitionWithLastElement(arr, start, end);
}

void quickSort(vector<int>& arr, int start, int end, PartitionMethod method) {
  if (start >= end) return;

  // Select pivot, place it in its correct location and get index of pivot.
  int pivotIndex;
  switch (method) {
    case PartitionMethod::FIRST_ELEMENT:
      pivotIndex = partitionWithFirstElement(arr, start, end);
      break;
    case PartitionMethod::LAST_ELEMENT:
      pivotIndex = partitionWithLastElement(arr, start, end);
      break;
    case PartitionMethod::RANDOM:
      pivotIndex = partitionWithRandomElement(arr, start, end);
      break;
    case PartitionMethod::MEDIAN_OF_THREE:
      pivotIndex = partitionWithMedianElement(arr, start, end);
      break;
  }

  // Sort the left subarray.
  quickSort(arr, start, pivotIndex - 1, method);
  // Sort the right subarray.
  quickSort(arr, pivotIndex + 1, end, method);
  // Note that pivot is excluded as it is already at its right place and hence,
  // sorted.
}

int main() {
  srand(time(NULL));

  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
      cin >> arr[i];
    }

    cout << "Initial array: ";
    printArr(arr);

    // Sort the array with strategy of choice.
    quickSort(arr, 0, n - 1, PartitionMethod::MEDIAN_OF_THREE);

    cout << "Sorted array: ";
    printArr(arr);

    cout << endl;
  }

  return 0;
}
