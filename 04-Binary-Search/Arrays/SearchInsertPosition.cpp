/*
 * Problem: Search Insert Position (LeetCode #35)
 * Link: https://leetcode.com/problems/search-insert-position/description/
 *
 * Approach: The problem asks for the index of the target if it exists, or the
 *           index where it would be inserted to maintain order. This is
 *           precisely the definition of the "lower bound" algorithm.
 *
 *           The solution uses a modified binary search to find the smallest
 *           index `i` such that `nums[i] >= target`. If the target is found,
 *           this will be its first occurrence. If the target is not found,
 *           this will be the index of the first element greater than the
 *           target, which is the correct insertion point.
 *
 * Time Complexity: O(logN)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int searchInsert(vector<int>& nums, int target);

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

    cout << "Insert Position: " << searchInsert(nums, target) << endl;

    cout << endl;
  }

  return 0;
}

int searchInsert(vector<int>& nums, int target) {
  int low = 0;
  int high = nums.size() - 1;
  int ans = nums.size();

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (nums[mid] >= target) {
      ans = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return ans;
}
