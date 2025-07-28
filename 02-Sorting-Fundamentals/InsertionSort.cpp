/*
 * INSERTION SORT
 *
 * Select an element and place it in its correct position/order.
 * We assume the first element of the array to be already sorted and start with
 * the second element. We compare the second element with element of the sorted
 * part of array and swap if it is smaller.
 *
 * In each round, we take the first element of unsorted half and compare and
 * swap it starting from the last element of sorted half.
 *
 * For example, consider an array like this:
 * -Sorted-:-Unsorted-
 * [5        4 3 2 1]  Compare 4 with 5 and swap.
 * [4 5      3 2 1]    Compare 3 with 5, swap, then with 4 and swap.
 * [3 4 5    2 1]      Compare then swap 2 with 5, keep it up till it reaches
 * its right place. [2 3 4 5  1] [1 2 3 4 5] SORTED.
 *
 * Time Complexity: O(N^2) in worst and average case, O(N) in best case for
 *                  already sorted array.
 * Space Complexity: O(1)
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

void insertionSort(vector<int>& arr, int n) {
  for (int i = 1; i < n; i++) {
    for (int j = i; j > 0; j--) {
      if (arr[j] < arr[j - 1]) {
        swap(arr[j], arr[j - 1]);
      } else
        break;
    }
  }
}

void insertionSortRecursive(vector<int>& arr, int n, int targetIndex = 1) {
  if (targetIndex == n) return;

  for (int i = targetIndex; i > 0; i--) {
    if (arr[i] < arr[i - 1]) {
      swap(arr[i], arr[i - 1]);
    }
  }

  insertionSortRecursive(arr, n, targetIndex + 1);
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << "Initial array: ";
    printArr(arr);

    insertionSort(arr, n);
    // Uncomment the line below to use the recursive version.
    // insertionSortRecursive(arr, n);

    cout << "Sorted array: ";
    printArr(arr);

    cout << endl;
  }
}
