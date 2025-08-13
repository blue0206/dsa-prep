/*
 * Problem: Lower Bound
 *
 * Statement: Given a sorted array of integers `nums` and a target value
 *            `target`, find the index of the first element that is greater
 *            than or equal to the target. If no such element exists, return
 *            the index where it would be inserted, which is the size of the
 *            array.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This approach leverages the C++ Standard Template Library (STL)
 *           function `std::lower_bound`. This function performs a binary
 *           search internally and returns an iterator to the first element
 *           that is not less than the target. Subtracting `nums.begin()` from
 *           this iterator gives the zero-based index.
 *
 * Time Complexity: O(logN)
 * Space Complexity: O(1)
 */
int stlApproach(const vector<int>& nums, int target);

/**
 * Approach: This problem is solved using a modified binary search. The goal is
 *           to find the smallest index `i` such that `nums[i] >= target`.
 *           We maintain a search space with `low` and `high` pointers and an
 *           `ans` variable to store the best possible answer found so far.
 *           If the middle element `nums[mid]` is greater than or equal to the
 *           target, it is a potential answer. We store `mid` in `ans` and try
 *           to find an even smaller index by searching in the left half
 *           (`high = mid - 1`). Otherwise, the answer must be to the right
 *           (`low = mid + 1`).
 *
 * Time Complexity: O(logN)
 * Space Complexity: O(1)
 */
int lowerBound(const vector<int>& nums, int target);

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

    cout << "Lower-Bound Index (STL): " << stlApproach(nums, target) << endl;
    cout << "Lower-Bound Index (Implementation): " << lowerBound(nums, target)
         << endl;

    cout << endl;
  }

  return 0;
}

int stlApproach(const vector<int>& nums, int target) {
  // Returns index.
  return lower_bound(nums.begin(), nums.end(), target) - nums.begin();
}

int lowerBound(const vector<int>& nums, int target) {
  int low = 0;
  int high = nums.size() - 1;
  // Default answer if target is greater than all elements.
  int ans = nums.size();

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (nums[mid] >= target) {
      // This is a POTENTIAL answer.
      ans = mid;
      // Now, let's see if we can find an even better answer to the left.
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return ans;
}
