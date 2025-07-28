/*
 * MERGE SORT
 *
 * Divide the array and merge in sorted manner.
 * In this approach, we recursively keep dividing the array (via indices, array
 * remains untouched) until only one element remains, i.e., it is sorted.
 * After dividing we merge the halves in sorted manner.
 * In merge, we just create separate, temporary arrays representing left and
 * right halves and fill them with the sorted data, and then we fill the
 * main array with the data of halves in a sorted manner.
 *
 * Check out the image in this repo for visualization:
 * https://github.com/blue0206/dsa-prep/blob/main/02-Sorting-Fundamentals/merge-sort.png
 *
 * Time Complexity: O(N LogN)
 *                  O(Log_2 N) for mergeSort as array gets divided
 *                  into 2 halves. O(N) in the worst case for merge when the
 *                  main 2 halves of array (i.e., the top level) are merged.
 *                  Hence, we have O(N) * O(LogN) = O(N LogN).
 *
 * Space Complexity: O(N) as we create temporary arrays in merge step.
 */

#include <iostream>
#include <vector>

using namespace std;

void printArr(vector<int>& arr) {
  cout << "[ ";
  for (auto i : arr) {
    cout << i << " ";
  }
  cout << "]" << endl;
}

void merge(vector<int>& arr, int start, int mid, int end) {
  // Initialize the left half of main array with size and pointer.
  int leftSize = mid - start + 1;
  vector<int> leftArr(leftSize);
  int leftIndex = 0;

  // Initialize the right half of main array with size and pointer.
  int rightSize = end - mid;
  vector<int> rightArr(rightSize);
  int rightIndex = 0;

  // Populate the left and right arrays with their respective sorted data.
  for (int i = start; i <= mid; i++) {
    leftArr[leftIndex++] = arr[i];
  }
  for (int i = mid + 1; i <= end; i++) {
    rightArr[rightIndex++] = arr[i];
  }

  // Reset left and right array pointers and initialize main array pointer
  // for updating the main array in with sorted data.
  leftIndex = 0;
  rightIndex = 0;
  int mainIndex = start;

  // Update main array with sorted data until either one of the left or right
  // halves is exhausted.
  while (leftIndex < leftSize && rightIndex < rightSize) {
    if (leftArr[leftIndex] < rightArr[rightIndex]) {
      arr[mainIndex++] = leftArr[leftIndex++];
    } else {
      arr[mainIndex++] = rightArr[rightIndex++];
    }
  }

  // After previous loop, either one of the following loops will run.
  // Here we just directly update the data, as they halves already have elements
  // in sorted manner.
  while (leftIndex < leftSize) {
    arr[mainIndex++] = leftArr[leftIndex++];
  }
  while (rightIndex < rightSize) {
    arr[mainIndex++] = rightArr[rightIndex++];
  }
}

void mergeSort(vector<int>& arr, int start, int end) {
  // Base case is when there is a single element in array.
  // An array with a single element is already sorted and it is this which
  // gives us surety that the merge function always receives the left and
  // right halves in sorted manner.
  if (start >= end) return;

  int mid = start + (end - start) / 2;
  // Sort the left half.
  mergeSort(arr, start, mid);
  // Sort the right half.
  mergeSort(arr, mid + 1, end);
  // Merge the left and right halves in sorted manner.
  merge(arr, start, mid, end);
}

int main() {
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

    mergeSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    printArr(arr);

    cout << endl;
  }

  return 0;
}
