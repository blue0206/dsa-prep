/*
 * Problem: Find Minimum in Rotated Sorted Array II (LeetCode #154)
 * Link:
 * https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/description/
 *
 * Approach: This approach adapts the binary search to find the minimum element
 *           in a rotated sorted array that may contain duplicates. The logic is
 *           similar to the unique-element version, but with a crucial addition
 *           to handle ambiguity.
 *           1. In each step, check for the ambiguous case:
 *              `nums[low] == nums[mid] == nums[high]`. If this is true, we
 *              cannot determine which half is sorted. We take `nums[low]` as a
 *              potential minimum and shrink the search space from both ends.
 *           2. Otherwise, we identify the sorted half, take its minimum as a
 *              potential answer, and search in the other (unsorted) half.
 *
 * Time Complexity: O(N) in the worst case, O(logN) on average.
 * Space Complexity: O(1)
 *
 * Follow up: This problem is similar to Find Minimum in Rotated Sorted Array,
 *            but nums may contain duplicates.
 *            Would this affect the runtime complexity? How and why?
 *
 * Answer:    The presence of duplicates affects the runtime complexity. The
 *            worst-case becomes O(N) because of the ambiguous case where
 *            `nums[low] == nums[mid] == nums[high]`, which forces a linear
 *            search step (`low++`, `high--`) instead of a binary one.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int findMin(vector<int>& nums);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Array: [ ";
    for (auto i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Minimum Element: " << findMin(nums) << endl;

    cout << endl;
  }

  return 0;
}

int findMin(vector<int>& nums) {
  int low = 0;
  int high = nums.size() - 1;
  int ans = INT_MAX;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    // Handle condition that breaks the fact that either left or right
    // half should always be sorted.
    if (nums[low] == nums[mid] && nums[mid] == nums[high]) {
      ans = min(ans, nums[low]);
      low++;
      high--;
      continue;
    }

    // Check if left half is sorted.
    if (nums[low] <= nums[mid]) {
      ans = min(ans, nums[low]);
      low = mid + 1;
    } else {  // If left half not sorted, right is definitely sorted.
      ans = min(ans, nums[mid]);
      high = mid - 1;
    }
  }

  return ans;
}
