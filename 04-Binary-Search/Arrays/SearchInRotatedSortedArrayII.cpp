/*
 * Problem: Search in Rotated Sorted Array II (LeetCode #81)
 * Link:
 * https://leetcode.com/problems/search-in-rotated-sorted-array-ii/description/
 *
 * Approach: This approach adapts the binary search for a rotated array to
 *           handle duplicates. The core logic remains to find the sorted half
 *           in each iteration. The key difference is handling the ambiguous
 *           case where `nums[low] == nums[mid] == nums[high]`. In this
 *           situation, we cannot determine which half is sorted, so we safely
 *           shrink the search space by moving both `low` and `high` pointers
 *           inward.
 *
 * Time Complexity: O(N) in the worst case, O(logN) on average.
 * Space Complexity: O(1)
 */
/*
 * Follow Up: This problem is similar to Search in Rotated Sorted Array,
 *            but nums may contain duplicates.
 *
 * Answer:    This affects the runtime complexity. The worst-case becomes O(N)
 *            because of the `nums[low] == nums[mid] == nums[high]` case, which
 *            forces a linear search step (`low++`, `high--`). For example,
 *            dry-run searching for 0 in [1,1,1,1,0,1,1,1,1,1,1].
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool search(vector<int>& nums, int target);

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

    if (search(nums, target)) {
      cout << "true" << endl;
    } else {
      cout << "false" << endl;
    }

    cout << endl;
  }

  return 0;
}

bool search(vector<int>& nums, int target) {
  int low = 0;
  int high = nums.size() - 1;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (nums[mid] == target) return true;

    // Handle the breaking condition.
    if (nums[low] == nums[mid] && nums[mid] == nums[high]) {
      low++;
      high--;
      continue;
    }

    if (nums[low] <= nums[mid]) {
      if (nums[low] <= target && nums[mid] >= target) {
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    } else {
      if (nums[high] >= target && nums[mid] <= target) {
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }
  }

  return false;
}
