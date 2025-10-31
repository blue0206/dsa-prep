/*
 * Problem: The Two Sneaky Numbers of Digitville (LeetCode #3289)
 * Link:
 * https://leetcode.com/problems/the-two-sneaky-numbers-of-digitville/description/?envType=daily-question&envId=2025-10-31
 *
 * Approach: This problem is a variation of "Single Number III" and can be
 *           solved efficiently with bit manipulation. The core idea is to find
 *           the XOR sum of the symmetric difference between the given array
 *           and an expected "ideal" array.
 *           1.  **XOR Sum:** Calculate the XOR sum of all numbers in the input
 *               array against all numbers in the ideal set. The result of this
 *               operation will be `a ^ b`, where `a` and `b` are the two
 *               "sneaky" numbers we need to find.
 *           2.  **Differentiating Bit:** Find any set bit in this `a ^ b`
 *               result. This bit is guaranteed to be different in `a` and `b`.
 *           3.  **Partition and Isolate:** Partition both the input array and
 *               the ideal set into two groups based on this differentiating
 *               bit. By XORing all numbers within each partitioned group, we
 *               can cancel out all common numbers and isolate `a` and `b`.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
using ll = long long;

vector<int> getSneakyNumbers(vector<int>& nums);

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

    vector<int> ans = getSneakyNumbers(nums);

    cout << "Result: [" << ans[0] << ", " << ans[1] << "]" << endl;

    cout << endl;
  }

  return 0;
}

vector<int> getSneakyNumbers(vector<int>& nums) {
  int n = nums.size() - 3;

  int xorSum = 0;
  for (int i = 0; i < nums.size(); i++) {
    int extra = (i <= n) ? i : 0;
    xorSum ^= nums[i] ^ extra;
  }

  int diffBit = xorSum & (-xorSum);

  int a = 0, b = 0;
  for (int i = 0; i < nums.size(); i++) {
    int extra = (i <= n) ? i : 0;

    if (nums[i] & diffBit) {
      a ^= nums[i];
    } else {
      b ^= nums[i];
    }

    if (extra & diffBit) {
      a ^= extra;
    } else {
      b ^= extra;
    }
  }

  return {a, b};
}
