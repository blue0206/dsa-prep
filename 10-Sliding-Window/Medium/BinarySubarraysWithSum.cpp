/*
 * Problem: Binary Subarrays With Sum (LeetCode #930)
 * Link: https://leetcode.com/problems/binary-subarrays-with-sum/description/
 */
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * Approach: This clever approach uses the principle that the number of
 *           subarrays with a sum *exactly* equal to `goal` is the same as
 *           (number of subarrays with sum *at most* `goal`) -
 *           (number of subarrays with sum *at most* `goal - 1`).
 *
 *           A helper function, `countTillK`, uses a sliding window to count
 *           the number of subarrays with a sum at most `k`. For each valid
 *           window `[low, high]`, all subarrays ending at `high` also have a
 *           sum at most `k`. There are `high - low + 1` such subarrays.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int combinatorialApproach(const vector<int>& nums, int goal);
int countTillK(const vector<int>& nums, int k);

/**
 * Approach: This is a general-purpose solution for "Subarray Sum Equals K"
 *           problems. It uses a hash map to store the frequencies of prefix
 *           sums encountered so far.
 *
 *           As we iterate through the array, we calculate the current prefix
 *           sum `pSum`. If a previous prefix sum `pSum - goal` exists in the
 *           map, it means the subarray between that point and the current
 *           index sums to `goal`. We add the frequency of `pSum - goal` to our
 *           count.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
int hashMapApproach(const vector<int>& nums, int goal);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, goal;
    cin >> n >> goal;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Goal: " << goal << endl;

    cout << "Input Array: [ ";
    for (int i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Combinatorial Approach: " << combinatorialApproach(nums, goal)
         << endl;
    cout << "Hash-Map Approach: " << hashMapApproach(nums, goal) << endl;

    cout << endl;
  }

  return 0;
}

int hashMapApproach(const vector<int>& nums, int goal) {
  unordered_map<int, int> pSumHash;
  int pSum = 0;

  int count = 0;
  pSumHash[0] = 1;
  for (int i = 0; i < nums.size(); i++) {
    pSum += nums[i];

    if (pSumHash.find(pSum - goal) != pSumHash.end()) {
      count += pSumHash[pSum - goal];
    }
    pSumHash[pSum]++;
  }

  return count;
}

int combinatorialApproach(const vector<int>& nums, int goal) {
  int atMostK = countTillK(nums, goal);
  int lessThanK = countTillK(nums, goal - 1);

  return atMostK - lessThanK;
}

int countTillK(const vector<int>& nums, int k) {
  if (k < 0) return 0;

  int low = 0;
  int high = 0;

  int sum = 0;
  int count = 0;
  while (high < nums.size()) {
    sum += nums[high];

    while (sum > k) {
      sum -= nums[low];
      low++;
    }

    count += (high - low + 1);
    high++;
  }

  return count;
}
