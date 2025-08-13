/*
 * Problem: Binary Search (LeetCode #704)
 * Link: https://leetcode.com/problems/binary-search/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This is the standard iterative binary search algorithm. It uses two
 *           pointers, `low` and `high`, to maintain a search space. In each
 *           step, it calculates the middle index `mid` and compares the
 *           element at `mid` with the target. If they match, the index is
 *           returned. If the middle element is smaller than the target, the
 *           search continues in the right half (`low = mid + 1`). Otherwise,
 *           the search continues in the left half (`high = mid - 1`).
 *
 * Time Complexity: O(logN)
 * Space Complexity: O(1)
 */
int iterativeBS(const vector<int>& nums, int target);

/**
 * Approach: This is the recursive implementation of binary search. A helper
 *           function takes the array, target, and the current `low` and `high`
 *           bounds. The base case for the recursion is when `low` exceeds
 *           `high`, indicating the element is not found. Otherwise, it finds
 *           the middle element and recursively calls itself on either the left
 *           or right half of the current search space.
 *
 * Time Complexity: O(logN)
 * Space Complexity: O(logN) due to recursion stack depth.
 */
int recursiveBS(const vector<int>& nums, int target);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, target;
    cin >> n >> target;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Array: [ ";
    for (auto i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Target Index (Iterative Approach): " << iterativeBS(nums, target)
         << endl;
    cout << "Target Index (Recursive Approach): " << recursiveBS(nums, target)
         << endl;

    cout << endl;
  }

  return 0;
}

int iterativeBS(const vector<int>& nums, int target) {
  int low = 0;
  int high = nums.size() - 1;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (nums[mid] == target) {
      return mid;
    } else if (nums[mid] < target) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  return -1;
}

//-----------------------------RECURSIVE APPROACH-------------------------------
int bs(const vector<int>& nums, int target, int low, int high) {
  if (low > high) {
    return -1;
  }

  int mid = low + (high - low) / 2;

  if (nums[mid] == target) {
    return mid;
  } else if (nums[mid] < target) {
    return bs(nums, target, mid + 1, high);
  } else {
    return bs(nums, target, low, mid - 1);
  }
}

int recursiveBS(const vector<int>& nums, int target) {
  return bs(nums, target, 0, nums.size() - 1);
}
