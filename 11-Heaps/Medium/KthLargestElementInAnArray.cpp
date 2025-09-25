/*
 * Problem: Kth Largest Element in an Array (LeetCode #215)
 * Link:
 * https://leetcode.com/problems/kth-largest-element-in-an-array/description/
 *
 * Approach:
 * This problem can be solved efficiently using a min-priority queue (min-heap)
 * of a fixed size `k`.
 *
 * 1.  **Min-Heap of Size K:** We maintain a min-heap that will store the `k`
 *     largest elements encountered so far.
 * 2.  **Iteration:** We iterate through each number in the input array. For
 *     each number, we push it into the min-heap. If the size of the heap
 *     exceeds `k`, we pop the smallest element (the root of the min-heap).
 * 3.  **Result:** After iterating through all the numbers, the heap contains
 *     the `k` largest elements of the entire array. The root of the min-heap
 *     (`pq.top()`) is the smallest of these `k` elements, which is exactly
 *     the k-th largest element.
 *
 * Time Complexity: O(N log K)
 * Space Complexity: O(K)
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int findKthLargest(const vector<int>& nums, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "k: " << k << endl;
    cout << "Input Array: [ ";
    for (int i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Kth Largest Element: " << findKthLargest(nums, k) << endl;

    cout << endl;
  }

  return 0;
}

int findKthLargest(const vector<int>& nums, int k) {
  // Create a min-heap.
  priority_queue<int, vector<int>, greater<int>> pq;

  for (int num : nums) {
    // Push the current element into the heap.
    pq.push(num);
    // If the heap size exceeds k, remove the smallest element.
    if (pq.size() > k) pq.pop();
  }

  // The top of the heap is the k-th largest element.
  return pq.top();
}
