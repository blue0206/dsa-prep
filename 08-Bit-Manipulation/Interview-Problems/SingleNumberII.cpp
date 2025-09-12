/*
 * Problem: Single Number II (LeetCode #137)
 * Link: https://leetcode.com/problems/single-number-ii/description/
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This method works by considering the binary representation of the
 *           numbers. For each bit position from 0 to 31, it counts the total
 *           number of set bits (1s) across all numbers in the array. Since
 *           every number except one appears three times, the total count of set
 *           bits at any position will be a multiple of 3 if the single number
 *           has a 0 at that bit position. If the single number has a 1 at that
 *           bit position, the total count will be `3k + 1`. Therefore, by
 *           taking the count modulo 3 (`count % 3`), we can determine the
 *           corresponding bit of the single number. We reconstruct the single
 *           number bit by bit.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int bitsCountApproach(vector<int>& nums);

/**
 * Approach: This approach leverages sorting. After sorting the array, all
 *           numbers that appear three times will be grouped together (e.g., `a,
 *           a, a, b, b, b, ...`). The single number will break this pattern. We
 *           can iterate through the sorted array with a step of 3. If `nums[i]`
 *           is not equal to `nums[i+1]`, then `nums[i]` must be the single
 *           number. If the loop completes without finding such a number, it
 *           means the single number is the last element in the array.
 *
 * Time Complexity: O(N log N)
 * Space Complexity: O(1)
 */
int sortApproach(vector<int>& nums);

/**
 * Approach: This is a bit manipulation approach that finds the single number in
 *           linear time and constant space. It uses two variables, `ones` and
 *           `twos`. `ones` stores the bits that have appeared once so far, and
 *           `twos` stores the bits that have appeared twice.
 *           - When a number `x` appears for the 1st time, it's added to `ones`.
 *           - When `x` appears for the 2nd time, it's removed from `ones` and
 *             added to `twos`.
 *           - When `x` appears for the 3rd time, it's removed from `twos`.
 *           After iterating through all numbers, `ones` will hold the single
 *           number.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int optimalApproach(vector<int>& nums);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Input Array: [ ";
    for (int i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Result (Bits Count Approach): " << bitsCountApproach(nums) << endl;
    cout << "Result (Sort Approach): " << sortApproach(nums) << endl;
    cout << "Result (Optimal Approach): " << optimalApproach(nums) << endl;

    cout << endl;
  }

  return 0;
}

int bitsCountApproach(vector<int>& nums) {
  long long val = 1;
  int num = 0;

  for (int i = 0; i < 32; i++) {
    int count = 0;
    for (int j = 0; j < nums.size(); j++) {
      int shiftedNum = nums[j] >> i;
      count += (shiftedNum & 1);
    }

    num += (count % 3) ? val : 0;
    val *= 2LL;
  }

  return num;
}

int sortApproach(vector<int>& nums) {
  if (nums.size() == 1) {
    return nums[0];
  }

  sort(nums.begin(), nums.end());

  // Iterate in steps of 3 to check groups of numbers.
  for (int i = 0; i < nums.size() - 1; i += 3) {
    if (nums[i] != nums[i + 1]) {
      return nums[i];
    }
  }

  // The single number is the last element.
  return nums.back();
}

int optimalApproach(vector<int>& nums) {
  int ones = 0;
  int twos = 0;

  for (int i = 0; i < nums.size(); i++) {
    // A number will go in ones if it is NOT in twos.
    ones = (ones ^ nums[i]) & (~twos);
    // A number will go in twos if it is NOT in ones.
    twos = (twos ^ nums[i]) & (~ones);
  }

  return ones;
}
