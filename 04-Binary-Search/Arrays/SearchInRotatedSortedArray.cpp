/*
 * Problem: Search in Rotated Sorted Array (LeetCode #33)
 * Link:
 * https://leetcode.com/problems/search-in-rotated-sorted-array/description/
 *
 * Approach: This problem is solved with a modified binary search. The key
 *           insight is that in a rotated sorted array, at any given point
 *           `mid`, at least one of the two halves (from `low` to `mid` or
 *           from `mid` to `high`) must be sorted.
 *           1. Identify the sorted half by comparing `nums[low]` with
 *              `nums[mid]`.
 *           2. If the left half (`nums[low]` to `nums[mid]`) is sorted, check
 *              if the target lies within this range. If it does, search in the
 *              left half; otherwise, search in the right.
 *           3. If the right half is sorted, do the same check for that half.
 *              This process eliminates half of the search space in each step.
 *
 * Time Complexity: O(logN)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int search(vector<int>& nums, int target);

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

    cout << "Index: " << search(nums, target) << endl;

    cout << endl;
  }

  return 0;
}

int search(vector<int>& nums, int target) {
  int low = 0;
  int high = nums.size() - 1;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (nums[mid] == target) return mid;

    // Check if left half is sorted.
    if (nums[low] <= nums[mid]) {
      // Check if answer is possibly present in range [low, mid].
      if (target >= nums[low] && target <= nums[mid]) {
        high = mid - 1;
      } else {
        low = mid + 1;
      }

      // If left half is not sorted, then right half will always be sorted.
    } else {
      // Check if answer is present in range [mid, high].
      if (target <= nums[high] && target >= nums[mid]) {
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }
  }

  return -1;
}
