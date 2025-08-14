/*
 * Problem: Find Peak Element (LeetCode #162)
 * Link: https://leetcode.com/problems/find-peak-element/description/
 *
 * Approach: This problem is solved using a modified binary search. The key
 *           insight is that we only need to find ANY peak, not a specific one.
 *           1.  Edge Cases: Handle arrays of size 1, and cases where the
 *               peak is at the first or last index. This simplifies the main
 *               loop by allowing the search space to be `[1, n-2]`.
 *           2.  Binary Search: At any `mid`, we check if it's a peak by
 *               comparing it to its neighbors.
 *           3.  Slope Logic: If `mid` is not a peak, we determine the
 *               "slope". If `nums[mid] < nums[mid+1]`, we are on an increasing
 *               slope, so a peak must exist to the right. We eliminate the
 *               left half. Otherwise, we are on a decreasing slope, and a peak
 *               must be at `mid` or to its left. We eliminate the right half.
 *
 * Time Complexity: O(logN)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int findPeakElement(vector<int>& nums);

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

    cout << "Peak Element: " << findPeakElement(nums) << endl;

    cout << endl;
  }

  return 0;
}

int findPeakElement(vector<int>& nums) {
  // Handle edge cases to prevent too many checks
  // to prevent runtime error.
  if (nums.size() == 1) return 0;
  if (nums[0] > nums[1]) return 0;
  if (nums.back() > nums[nums.size() - 2]) return nums.size() - 1;

  int low = 1;
  int high = nums.size() - 2;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    // Check if mid is the peak.
    if (nums[mid] > nums[mid + 1] && nums[mid] > nums[mid - 1]) {
      return mid;
    }

    // If we are on an increasing slope (nums[mid] < nums[mid+1]), a peak must
    // be on the right side.
    if (nums[mid] < nums[mid + 1]) {
      low = mid + 1;
    } else {
      // We are on a decreasing slope (nums[mid] > nums[mid+1]), so the peak
      // is either the current element or on the left side.
      high = mid - 1;
    }
  }

  return -1;
}
