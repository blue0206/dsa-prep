/*
 * Problem: Longest Subarray with Sum K
 *
 * Description: For a given array, output the length of longest possible
 *              subarray that has a sum of K.
 *
 * Extra: Provide a solution for when an array has 0s and negatives as well.
 */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * Approach: Iterate through all possible subarrays, calculate their sum, and if
 *           the sum equals K, update the maximum length found so far.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(1)
 */
int approach1(vector<int>& nums, int k);

/**
 * Approach: This approach uses a hash map to store the cumulative prefix sum
 *           and its first corresponding index. We iterate through the array,
 *           calculating the prefix sum `pSum` at each index `i`. For a subarray
 *           to sum to `k`, there must be a previous prefix sum `pSum - k`. If
 *           we find `pSum - k` in our map at an index `j`, the subarray from
 *           `j+1` to `i` has a sum of `k`. We update our max length with
 *           `i - j`.
 *
 * This is the OPTIMAL approach for arrays with positives, negatives, and zeros.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
int approach2(vector<int>& nums, int k);

/**
 * Approach: This is a two-pointer/sliding window approach. We maintain a
 *           'window' using `start` and `end` pointers. We expand the window by
 *           moving `end` to the right, adding to the sum. If the sum exceeds
 *           `k`, we shrink the window from the left by moving `start` to the
 *           right, subtracting from the sum. Whenever the sum equals `k`, we
 *           update our maximum length.
 *
 * This is the OPTIMAL approach for arrays with non-negative numbers (positives
 * and zeros). It fails if the array contains negative numbers.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int approach3(vector<int>& nums, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Approach 1 (Brute-Force): " << approach1(nums, k) << endl;
    cout << "Approach 2: " << approach2(nums, k) << endl;
    cout << "Approach 3: " << approach3(nums, k) << endl;

    cout << endl;
  }

  return 0;
}

int approach1(vector<int>& nums, int k) {
  int maxLength = 0;

  for (int i = 0; i < nums.size(); i++) {
    // Initialize sum with value at index marking start of subarray.
    int sum = nums[i];
    for (int j = i + 1; j < nums.size(); j++) {
      sum += nums[j];
      if (sum == k && j - i + 1 > maxLength) {
        maxLength = j - i + 1;
      } else if (sum >= k) {
        break;
      }
    }
  }

  return maxLength;
}

int approach2(vector<int>& nums, int k) {
  unordered_map<int, int> pSumHash;
  int pSum = 0;
  int maxLength = 0;

  for (int i = 0; i < nums.size(); i++) {
    pSum += nums[i];
    if (pSum == k) {
      maxLength = i + 1;
    }
    if (pSumHash.find(pSum - k) != pSumHash.end()) {
      maxLength = max(maxLength, i - pSumHash[pSum - k]);
    }

    // Store prefix sum only if it's not already there to get the longest
    // subarray
    if (pSumHash.find(pSum) == pSumHash.end()) {
      pSumHash[pSum] = i;
    }
  }

  return maxLength;
}

int approach3(vector<int>& nums, int k) {
  int start = 0;
  int end = 0;
  int maxLength = 1;
  int sum = nums[0];

  while (end < nums.size()) {
    while (sum > k && start < end) {
      sum -= nums[start];
      start++;
    }

    if (sum == k) {
      maxLength = max(maxLength, end - start + 1);
    }
    end++;
    if (end < nums.size()) sum += nums[end];
  }

  return maxLength;
}
