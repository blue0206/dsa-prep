/*
 * Problem: Find First and Last Position of Element in Sorted Array
 *          (LeetCode #34)
 *
 * Link:
 * https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This approach leverages the C++ Standard Template Library.
 *           - `std::lower_bound` is used to find the first position. It returns
 *             an iterator to the first element that is not less than the
 * target.
 *           - `std::upper_bound` is used to find the last position. It returns
 *             an iterator to the first element strictly greater than the
 *             target. The index before this (`- 1`) is the last occurrence.
 *           - A check is performed to ensure the element was actually found.
 *
 * Time Complexity: O(logN)
 * Space Complexity: O(1)
 */
vector<int> stlApproach(vector<int>& nums, int target);

/**
 * Approach: This approach uses two separate, custom binary searches.
 *           - `firstOccurrence`: A manual `lower_bound` implementation finds
 *             the smallest index `i` where `nums[i] >= target`.
 *           - `lastOccurrence`: A modified binary search finds the largest
 *             index `i` where `nums[i] <= target`.
 *           Both functions perform a final check to ensure the found index
 *           actually contains the target value.
 *
 * Time Complexity: O(logN)
 * Space Complexity: O(1)
 */
vector<int> customApproach(vector<int>& nums, int target);
int firstOccurrence(vector<int>& nums, int target);
int lastOccurrence(vector<int>& nums, int target);

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

    vector<int> stlAns = stlApproach(nums, target);
    vector<int> customAns = customApproach(nums, target);

    cout << "STL Approach: [ " << stlAns[0] << ", " << stlAns[1] << " ]"
         << endl;
    cout << "Custom Approach: [ " << customAns[0] << ", " << customAns[1]
         << " ]" << endl;

    cout << endl;
  }

  return 0;
}

//-------------------------------STL APPROACH-----------------------------------
vector<int> stlApproach(vector<int>& nums, int target) {
  int first = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
  int last = upper_bound(nums.begin(), nums.end(), target) - nums.begin() - 1;

  // If first doesn't point to target, then last won't either as element
  // doesn't exist.
  if (first == nums.size() || nums[first] != target) {
    return {-1, -1};
  }

  return {first, last};
}

//-------------------------------CUSTOM APPROACH--------------------------------
vector<int> customApproach(vector<int>& nums, int target) {
  return {firstOccurrence(nums, target), lastOccurrence(nums, target)};
}

int firstOccurrence(vector<int>& nums, int target) {
  int low = 0;
  int high = nums.size() - 1;
  int ans = -1;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (nums[mid] >= target) {
      ans = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  // If target is greater than all elements, ans would be -1
  // as it is never updated.
  if (ans == -1) return ans;

  // If ans index has the target element, we return ans
  // else we simply return -1.
  return nums[ans] == target ? ans : -1;
}

int lastOccurrence(vector<int>& nums, int target) {
  int low = 0;
  int high = nums.size() - 1;
  int ans = -1;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (nums[mid] <= target) {
      ans = mid;
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  // If target is smaller than all elements, ans would be -1
  // as it is never updated.
  if (ans == -1) return ans;

  // If ans index has the target element, we return ans
  // else we simply return -1.
  return nums[ans] == target ? ans : -1;
}
