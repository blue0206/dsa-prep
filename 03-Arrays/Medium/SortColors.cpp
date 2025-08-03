/*
 * Problem: Sort Colors (LeetCode #75)
 * Link: https://leetcode.com/problems/sort-colors/description/
 *
 * Approach: ------------------Dutch National Flag Algorithm--------------------
 *           Initialize 3 pointers: low, mid, and high.
 *
 *           Everything before low index (0 to low-1) are 0s, everything from
 *           low index till mid-1 index are 1s (low to mid-1), everything from
 *           mid index till high index (mid to high) is unsorted area with
 *           0s/1s/2s, and lastly, everything after high till end are 2s.
 *
 *           At start, we treat the array from 0 to mid as sorted, from mid to
 *           high as unsorted, and again, from high to end as sorted.
 *
 *           Initially, the entire array is unsorted, i.e., low and mid are at
 *           index 0 and high at index n-1.

 *           There are 3 rules in this algorithm:
 *           1. If nums[mid] == 0: we swap the elements at low and mid and
 *                                 increment both of them.
 *           2. If nums[mid] == 1: we simply increment mid.
 *           3. If nums[mid] == 2: we swap the elements at high and mid and
 *                                 decrement ONLY high. This is because the
 *                                 element swapped from high is unknown and
 *                                 needs to be processed by mid.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void sortColors(vector<int>& nums) {
  int low = 0;
  int mid = 0;
  int high = nums.size() - 1;

  while (mid <= high) {
    if (nums[mid] == 0) {
      swap(nums[low], nums[mid]);
      low++;
      mid++;
    } else if (nums[mid] == 1) {
      mid++;
    } else {
      swap(nums[mid], nums[high]);
      high--;
    }
  }
}

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

    sortColors(nums);

    cout << "Sorted Array: [ ";
    for (auto i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;
  }

  return 0;
}
