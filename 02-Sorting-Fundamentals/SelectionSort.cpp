/*
 * SELECTION SORT
 *
 * Select minimum and swap the element with the one at the earliest index of
 * that round.
 * Therefore, in first round, we will swap the minimum element from 0 to n
 * (in an array of size n) with the element present at 0th index.
 * In second round, we will swap the minimum element from 1 to n
 * (in an array of size n) with the element present at 1st index.
 * We repeat this process till the second-last element as the last element is
 * already sorted.
 * Time Complexity: O(N^2)
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

void selectionSort(vector<int>& arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    int minIndex = i;

    for (int j = i + 1; j < n; j++) {
      if (arr[j] < arr[minIndex]) {
        minIndex = j;
      }
    }

    swap(arr[minIndex], arr[i]);
  }
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

    selectionSort(arr, n);

    cout << "Sorted array: ";
    printArr(arr);

    cout << endl;
  }

  return 0;
}
