/*
 * BUBBLE SORT
 *
 * Select maximum and push it to the end via adjacent swaps.
 * In each round, we pick the maximum element of an array and push it to the
 * end. With each subsequent rounds, the range is reduced by ignoring the index
 * to which a maxima element was pushed to in previous round.
 *
 * For example, in first round for an array of size 'n', we consider the entire
 * array (0 to n-1) and push the maximum element to the index 'n-1'. In the next
 * round, we consider the array excluding the sorted part, i.e., 0 to n-2, as
 * n-1 is already sorted.
 *
 * In each round, we start from first index and pick two adjacent elements,
 * and if first element is larger than second, we swap them and move on to the
 * next index.
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

void bubbleSort(vector<int>& arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    bool swapped = false;

    // We only check until second last element as there is no (unsorted) element
    // adjacent to the last element of range.
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
        swapped = true;
      }
    }

    // If no swaps in a round, then the array is already sorted
    // and we break the loop.
    if (!swapped) break;
  }
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

    bubbleSort(arr, n);

    cout << "Sorted array: ";
    printArr(arr);

    cout << endl;
  }
}
