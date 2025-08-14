/*
 * Problem: Find Rotations in Rotated Sorted Array
 *
 * Statement: Find the number of rotations in a rotated and sorted array
 *            with UNIQUE elements.
 *
 * Follow Up: What if the array has duplicates?
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: The number of times a sorted array is rotated is equal to the
 *           index of its minimum element. This problem reduces to finding the
 *           index of the minimum element. We use a modified binary search where
 *           in each step, we identify the sorted half of the array. The minimum
 *           of that sorted half is a candidate for the overall minimum. The
 *           true minimum must lie in the unsorted half, so we continue our
 *           search there, keeping track of the index of the minimum element
 *           found so far.
 *
 * Time Complexity: O(logN)
 * Space Complexity: O(1)
 */
int findRotations(vector<int>& nums);

/**
 * Approach: When duplicates are allowed, the core logic remains the same, but
 *           we must handle an ambiguous case: `nums[low] == nums[mid] ==
 * nums[high]`. In this scenario, we cannot determine which half is sorted. To
 *           resolve this, we safely shrink the search space by incrementing
 *           `low` and decrementing `high` and then continue the binary search.
 *
 * Time Complexity: O(N) in the worst case, O(logN) on average.
 * Space Complexity: O(1)
 */
int followUp(vector<int>& nums);

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

    // Note that this one will output wrong answer for array with duplicates.
    cout << "Number of rotations (Unique Elements): " << findRotations(nums)
         << endl;

    // This one will always output the correct answer regardless of duplicates.
    cout << "Number of rotations (Duplicates): " << followUp(nums) << endl;

    cout << endl;
  }

  return 0;
}

int findRotations(vector<int>& nums) {
  int low = 0;
  int high = nums.size() - 1;
  // The number of rotations is equal to the index of minimum element.
  int ansIndex = 0;

  while (low <= high) {
    if (nums[low] <= nums[high]) {
      if (nums[low] < nums[ansIndex]) {
        ansIndex = low;
      }
      break;
    }

    int mid = low + (high - low) / 2;

    // Check if left half is sorted.
    if (nums[low] <= nums[mid]) {
      if (nums[low] < nums[ansIndex]) {
        ansIndex = low;
      }
      low = mid + 1;
    } else {  // If left half not sorted, right is definitely sorted.
      if (nums[mid] < nums[ansIndex]) {
        ansIndex = mid;
      }
      high = mid - 1;
    }
  }

  return ansIndex;
}

int followUp(vector<int>& nums) {
  int low = 0;
  int high = nums.size() - 1;
  // The number of rotations is equal to the index of minimum element.
  int ansIndex = 0;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    // Handle the condition that breaks the fact that if left half is not
    // sort, right half will always be sorted and vice-versa.
    if (nums[low] == nums[mid] && nums[mid] == nums[high]) {
      if (nums[low] < nums[ansIndex]) {
        ansIndex = low;
      }
      low++;
      high--;
      continue;
    }

    // Check if left half is sorted.
    if (nums[low] <= nums[mid]) {
      if (nums[low] < nums[ansIndex]) {
        ansIndex = low;
      }
      low = mid + 1;
    } else {  // If left half not sorted, right is definitely sorted.
      if (nums[mid] < nums[ansIndex]) {
        ansIndex = mid;
      }
      high = mid - 1;
    }
  }

  return ansIndex;
}
