/*
 * Problem: Reverse Pairs (LeetCode #493)
 * Link: https://leetcode.com/problems/reverse-pairs/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

/**
 * Approach: Use two nested loops. The outer loop iterates from `i = 0` to
 *           `n-1`, and the inner loop iterates from `j = i+1` to `n-1`. For
 *           each pair `(i, j)`, check if `nums[i] > 2 * nums[j]`. If the
 *           condition is met, increment a counter. The multiplication should
 *           use 64-bit integers to prevent overflow.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(1)
 */
int bruteForceApproach(vector<int> nums);

/**
 * Approach: This approach uses a modified Merge Sort algorithm. The core idea
 *           is that the total number of reverse pairs is the sum of pairs
 *           within the left half, pairs within the right half, and pairs that
 *           cross the two halves. The first two are found by recursive calls.
 *           The cross-pairs are counted efficiently during the merge step.
 *           Before merging, for each element in the sorted left half, we count
 *           how many elements in the sorted right half satisfy the condition.
 *
 * Time Complexity: O(N logN)
 * Space Complexity: O(N)
 */
int optimalApproach(vector<int> nums);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Brute-Force Approach: " << bruteForceApproach(nums) << endl;
    cout << "Optimal Approach: " << optimalApproach(nums) << endl;

    cout << endl;
  }

  return 0;
}

int bruteForceApproach(vector<int> nums) {
  int count = 0;

  for (int i = 0; i < nums.size(); i++) {
    for (int j = i + 1; j < nums.size(); j++) {
      long long value = (long long)nums[j] * 2;
      if (nums[i] > value) count++;
    }
  }

  return count;
}

//-----------------------------OPTIMAL APPROACH---------------------------------
int countPairs(vector<int>& nums, int start, int mid, int end) {
  int count = 0;
  int index = mid + 1;
  for (int i = start; i <= mid; i++) {
    while (index <= end && nums[i] > (ll)nums[index] * 2) {
      index++;
    }
    count += (index - (mid + 1));
  }
  return count;
}

int mergeAndCount(vector<int>& nums, int start, int mid, int end) {
  // Count the number of inversion pairs from both subarrays
  // with 'i' in left and 'j' in right.
  int count = countPairs(nums, start, mid, end);

  // Temporary array to store left half of
  // main array [start, mid]
  int leftSize = mid - start + 1;
  vector<int> leftNums(leftSize);
  int leftIndex = 0;

  // Temporary array to store right half of
  // main array (mid, end]
  int rightSize = end - mid;
  vector<int> rightNums(rightSize);
  int rightIndex = 0;

  // Populate left and right temporary subarrays.
  for (int i = start; i <= mid; i++) {
    leftNums[leftIndex++] = nums[i];
  }
  for (int i = mid + 1; i <= end; i++) {
    rightNums[rightIndex++] = nums[i];
  }

  // Merge the two temnporary arrays into the main array in
  // sorted manner.
  leftIndex = 0;
  rightIndex = 0;
  int index = start;
  while (leftIndex < leftSize && rightIndex < rightSize) {
    if (rightNums[rightIndex] < leftNums[leftIndex]) {
      nums[index++] = rightNums[rightIndex++];
    } else {
      nums[index++] = leftNums[leftIndex++];
    }
  }

  // Fill leftover elements.
  while (leftIndex < leftSize) {
    nums[index++] = leftNums[leftIndex++];
  }
  while (rightIndex < rightSize) {
    nums[index++] = rightNums[rightIndex++];
  }

  return count;
}

int mergeSortAndCount(vector<int>& nums, int start, int end) {
  if (start >= end) return 0;

  int mid = start + (end - start) / 2;
  // count = pairs from left subarray + pairs from right subarray + pairs from
  // both subarrays.
  int count = 0;
  count += mergeSortAndCount(nums, start, mid);
  count += mergeSortAndCount(nums, mid + 1, end);
  count += mergeAndCount(nums, start, mid, end);
  return count;
}

int optimalApproach(vector<int> nums) {
  return mergeSortAndCount(nums, 0, nums.size() - 1);
}
