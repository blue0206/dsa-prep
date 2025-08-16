/*
 * Problem: Kth Missing Positive Number (LeetCode #1539)
 * Link: https://leetcode.com/problems/kth-missing-positive-number/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This approach iterates through the array. The logic is that if we
 *           encounter a number `nums[i]` that is less than or equal to our
 *           current `k`, it means this number occupies a spot that a missing
 *           number would have taken. Therefore, the `k`-th missing number we
 *           are looking for must be further down the line. We compensate for
 *           this by incrementing `k`. After the loop, `k` will hold the value
 *           of the `k`-th missing positive number.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int bruteForceApproach(vector<int>& nums, int k);

/**
 * Approach: This optimal approach uses binary search. The core mathematical
 *           insight is that for any index `i`, the number of positive integers
 *           missing before `nums[i]` is `nums[i] - (i + 1)`.
 *           - **Why?** In a perfect array with no missing numbers (e.g.,
 *             `[1, 2, 3, 4, ...]`), the value at index `i` would be `i + 1`.
 *             The difference between the actual value `nums[i]` and the ideal
 *             value `i + 1` tells us exactly how many numbers are missing up
 *             to that point.
 *
 *           The binary search then finds the "partition point". We are looking
 *           for the boundary where the number of missing elements becomes
 *           greater than or equal to `k`.
 *           - If `nums[mid] - (mid + 1) < k`, there are not enough missing
 *             numbers yet, so the `k`-th missing number must be to the right.
 *           - Otherwise, the `k`-th missing number is at or before `nums[mid]`.
 *
 *           The loop terminates with `low` pointing to the first index where
 *           the number of missing elements is `>= k`. The final answer is
 *           `low + k`.
 *
 * Time Complexity: O(logN)
 * Space Complexity: O(1)
 */
int binarySearchApproach(vector<int>& nums, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Array: [ ";
    for (auto i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Brute-Force Approach: " << bruteForceApproach(nums, k) << endl;
    cout << "Binary Search Approach: " << binarySearchApproach(nums, k) << endl;

    cout << endl;
  }

  return 0;
}

int bruteForceApproach(vector<int>& nums, int k) {
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] <= k)
      k++;
    else
      break;
  }

  return k;
}

int binarySearchApproach(vector<int>& nums, int k) {
  int low = 0;
  int high = nums.size() - 1;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    int missingElement = nums[mid] - (mid + 1);

    if (missingElement < k) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  return low + k;  // Or high+k+1
}
