/*
 * Problem: Find Minimum in Rotated Sorted Array (LeetCode #153)
 * Link:
 * https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/
 *
 * Approach: This problem is solved with a modified binary search. The goal is
 *           to find the "pivot" or "inflection point" where the rotation
 *           occurs, as the element at this point will be the minimum.
 *
 *           In each step, we identify which half of the current search space is
 *           sorted.
 *           - If the left half (`nums[low]` to `nums[mid]`) is sorted, the
 *             minimum in this portion is `nums[low]`. We take this as a
 *             potential answer and then search in the unsorted right half.
 *           - If the right half is sorted, the minimum in that portion is
 *             `nums[mid]`. We take this as a potential answer and search in the
 *             unsorted left half.
 *
 * Time Complexity: O(logN)
 * Space Complexity: O(1)
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
    // If the current search space is already sorted,
    // the first element is the minimum. We can stop here.
    if (nums[low] <= nums[high]) {
      ans = min(ans, nums[low]);
      break;
    }

    int mid = low + (high - low) / 2;

    // If left half is sorted, its minimum is nums[low].
    if (nums[low] <= nums[mid]) {
      ans = min(nums[low], ans);
      low = mid + 1;
    } else {  // Otherwise, the right half is sorted, and its minimum is at mid.
      ans = min(nums[mid], ans);
      high = mid - 1;
    }
  }

  return ans;
}
