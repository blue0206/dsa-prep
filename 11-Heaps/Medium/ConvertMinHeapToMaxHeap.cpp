/*
 * Problem: Convert Min Heap to Max Heap
 * Link:
 * https://www.naukri.com/code360/problems/convert-min-heap-to-max-heap_1381084?leftPanelTabValue=PROBLEM
 *
 * Approach:
 * The problem of converting a min-heap to a max-heap is equivalent to the
 * standard "build a max-heap from an array" problem. The most efficient way
 * to do this is by applying the `heapify` procedure to all non-leaf nodes.
 *
 * 1.  **Identify Non-Leaf Nodes:** In a 0-indexed array of size `n`, the nodes
 *     from index `(n/2) - 1` down to `0` are the non-leaf (parent) nodes.
 * 2.  **Heapify Down:** We iterate backwards from the last non-leaf node
 *     (`i = (n-2)/2`) to the root (`i = 0`). For each node, we call a
 *     `maxHeapifyDown` function. This function ensures that the subtree rooted
 *     at `i` satisfies the max-heap property by "sinking" the element at `i`
 *     down to its correct position.
 *
 * By starting from the last parent and moving up, we guarantee that when we
 * heapify a node, its children's subtrees are already max-heaps.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(logN)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> MinToMaxHeap(vector<int>& arr, int n);
void maxHeapifyDown(vector<int>& arr, int n, int index);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Input Array: [ ";
    for (int i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    vector<int> ans = MinToMaxHeap(nums, n);

    cout << "Result: [ ";
    for (int i : ans) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vector<int> MinToMaxHeap(vector<int>& arr, int n) {
  // The last non-leaf node is at index (n/2) - 1 or (n-2)/2.
  int lastParent = (n - 2) / 2;
  // Iterate backwards from the last non-leaf node to the root.
  for (int i = lastParent; i >= 0; i--) {
    // Apply the heapify-down procedure to ensure the max-heap property.
    maxHeapifyDown(arr, n, i);
  }

  return arr;
}

void maxHeapifyDown(vector<int>& arr, int n, int index) {  // Sift-down
  int greatest = index;
  int left = index * 2 + 1;
  int right = index * 2 + 2;

  if (left < n && arr[left] > arr[greatest]) {
    greatest = left;
  }
  if (right < n && arr[right] > arr[greatest]) {
    greatest = right;
  }

  // If the largest element is not the current node, swap and recurse.
  if (greatest != index) {
    swap(arr[index], arr[greatest]);
    maxHeapifyDown(arr, n, greatest);
  }
}
