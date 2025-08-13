/*
 * Problem: Upper Bound
 *
 * Statement: Given a sorted array of integers `nums` and a target value
 *            `target`, find the index of the first element that is strictly
 *            greater than the target. If no such element exists, return the
 *            index where it would be inserted, which is the size of the array.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This approach leverages the C++ Standard Template Library (STL)
 *           function `std::upper_bound`. This function performs a binary
 *           search internally and returns an iterator to the first element
 *           that is strictly greater than the target. Subtracting
 *           `nums.begin()` from this iterator gives the zero-based index.
 *
 * Time Complexity: O(logN)
 * Space Complexity: O(1)
 */
int stlApproach(const vector<int>& nums, int target);

/**
 * Approach: This problem is solved using a modified binary search. The goal is
 *           to find the smallest index `i` such that `nums[i] > target`.
 *           We maintain a search space with `low` and `high` pointers and an
 *           `ans` variable. If the middle element `nums[mid]` is less than or
 *           equal to the target, the answer must be in the right half
 *           (`low = mid + 1`). Otherwise, `mid` is a potential answer, so we
 *           store it in `ans` and try to find an even smaller index by
 *           searching in the left half (`high = mid - 1`).
 *
 * Time Complexity: O(logN)
 * Space Complexity: O(1)
 */
int upperBound(const vector<int>& nums, int target);

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

    cout << "Upper-Bound Index (STL): " << stlApproach(nums, target) << endl;
    cout << "Upper-Bound Index (Implementation): " << upperBound(nums, target)
         << endl;

    cout << endl;
  }

  return 0;
}

int stlApproach(const vector<int>& nums, int target) {
  // Returns index.
  return upper_bound(nums.begin(), nums.end(), target) - nums.begin();
}

int upperBound(const vector<int>& nums, int target) {
  int low = 0;
  int high = nums.size() - 1;
  int ans = nums.size();

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (nums[mid] <= target) {
      low = mid + 1;
    } else {
      ans = mid;
      high = mid - 1;
    }
  }

  return ans;
}
