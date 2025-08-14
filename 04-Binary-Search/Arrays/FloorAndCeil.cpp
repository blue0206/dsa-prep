/*
 * Problem: Floor and Ceil in Sorted Array
 * Statement: Given a sorted array of integers `nums` and a target value
 *            `target`, find the floor and ceil of the target in the array.
 *            - Floor: The largest element in the array that is less than or
 *              equal to the target.
 *            - Ceil: The smallest element in the array that is greater than or
 *              equal to the target.
 *            If floor or ceil do not exist, they should be represented by -1.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This approach uses the C++ Standard Template Library.
 *           - Ceil: `std::lower_bound` finds the first element `>= target`,
 *             which is the definition of ceil.
 *           - Floor: `std::upper_bound` finds the first element `> target`. The
 *             element just before it is the largest element `<= target`, which
 *             is the definition of floor.
 *           Edge cases for when the target is outside the bounds of the array
 *           elements are handled.
 *
 * Time Complexity: O(logN)
 * Space Complexity: O(1)
 */
void stlApproach(const vector<int>& nums, int target);

/**
 * Approach: This approach uses custom binary search implementations for both
 *           floor and ceil.
 *           - `ceil`: The implementation is identical to finding the lower
 *             bound. It searches for the smallest element `>= target`.
 *           - `floor`: The implementation uses binary search to find the
 *             largest element `<= target`. If an element `nums[mid]` is a
 *             candidate for the floor, we store its value and search for a
 *             potentially larger one in the right half.
 *
 * Time Complexity: O(logN)
 * Space Complexity: O(1)
 */
void floorAndCeil(const vector<int>& nums, int target);
int ceil(const vector<int>& nums, int target);
int floor(const vector<int>& nums, int target);

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

    cout << "Using STL: " << endl;
    stlApproach(nums, target);

    cout << "Custom Implementation: " << endl;
    floorAndCeil(nums, target);

    cout << endl;
  }

  return 0;
}

//---------------------------------Using STL------------------------------------
void stlApproach(const vector<int>& nums, int target) {
  int floor;
  int ceil;

  int ceilIndex = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
  if (ceilIndex == nums.size()) {
    ceil = -1;
  } else {
    ceil = nums[ceilIndex];
  }

  int floorIndex =
      upper_bound(nums.begin(), nums.end(), target) - nums.begin() - 1;
  if (floorIndex == -1) {
    floor = -1;
  } else {
    floor = nums[floorIndex];
  }

  cout << "Floor: " << floor << endl;
  cout << "Ceil: " << ceil << endl;
}

//----------------------------Custom Implementation-----------------------------
void floorAndCeil(const vector<int>& nums, int target) {
  cout << "Floor: " << floor(nums, target) << endl;
  cout << "Ceil: " << ceil(nums, target) << endl;
}

int ceil(const vector<int>& nums, int target) {
  int low = 0;
  int high = nums.size() - 1;
  int ans = -1;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (nums[mid] >= target) {
      ans = nums[mid];
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return ans;
}

int floor(const vector<int>& nums, int target) {
  int low = 0;
  int high = nums.size() - 1;
  int ans = -1;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (nums[mid] <= target) {
      ans = nums[mid];
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  return ans;
}
