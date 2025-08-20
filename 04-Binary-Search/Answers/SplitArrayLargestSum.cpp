/*
 * Problem: Split Array Largest Sum (LeetCode #410)
 * Link: https://leetcode.com/problems/split-array-largest-sum/description/
 *
 * Approach: This is a classic "Binary Search on Answer" problem, structurally
 *           identical to "Painter's Partition" and "Book Allocation". We
 *           need to find the minimum possible value for the largest sum of any
 *           subarray after splitting the main array into `k` subarrays.
 *           1.  **Search Space:** The answer (the largest subarray sum) must
 *               be in a specific range. The minimum possible value is the
 *               largest single element in the array. The maximum is the sum
 *               of all elements (if k=1).
 *           2.  **Binary Search:** We binary search on this range of possible
 *               answers. For each `mid` value (a potential largest sum limit),
 *               we check if it's possible to split the array into `k` or fewer
 *               subarrays.
 *           3.  **Feasibility Check:** The `countSubarrays` function greedily
 *               determines the minimum number of subarrays required if no
 *               subarray's sum can exceed `mid`.
 *           4.  **Narrowing Down:** If the required subarrays are within our
 *               limit `k`, then `mid` is a possible answer, so we try for a
 *               better (smaller) one by searching left. Otherwise, `mid` is
 *               too restrictive, and we need to allow a larger sum by
 *               searching right.
 *
 * Time Complexity: O(N * log(S)), where S is the sum of all elements.
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int splitArray(vector<int>& nums, int k);
int countSubarrays(vector<int>& nums, int mid);

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

    cout << "Minimum Possible Maximum Subarray Sum: " << splitArray(nums, k)
         << endl;

    cout << endl;
  }

  return 0;
}

int splitArray(vector<int>& nums, int k) {
  // The search space for the answer is from the largest single element
  // to the sum of all elements.
  int low = 0;
  int high = 0;
  for (int i : nums) {
    if (i > low) low = i;
    high += i;
  }

  while (low <= high) {
    int mid = low + (high - low) / 2;

    int possibleSubarrays = countSubarrays(nums, mid);

    // If the number of subarrays required for this `mid` is within our limit,
    // it's a possible answer. Try to find an even smaller max sum.
    // Note that as we move to the right on our search space, the no. of
    // possible subarrays decreases and vice-versa for left.
    if (possibleSubarrays <= k) {
      high = mid - 1;
    } else {
      // Otherwise, the max sum `mid` is too small, we need to allow more.
      low = mid + 1;
    }
  }

  return low;
}

int countSubarrays(vector<int>& nums, int mid) {
  // Start with one subarray and a current sum of 0.
  int pSum = 0;
  int subarrays = 1;

  for (int i = 0; i < nums.size(); i++) {
    // If the current subarray can accommodate the next element without
    // exceeding the limit `mid`.
    if (pSum + nums[i] <= mid) {
      pSum += nums[i];
    } else {
      // Otherwise, a new subarray is required.
      subarrays++;
      pSum = nums[i];
    }
  }

  return subarrays;
}
