/*
 * Problem: Single Number III (LeetCode #260)
 * Link: https://leetcode.com/problems/single-number-iii/description/
 *
 * Approach: This problem is solved in two main passes using bit manipulation.
 *           1. **First Pass (XOR all numbers):** XORing all numbers in the
 *              array gives us the XOR sum of the two unique numbers, let's
 *              call them `a` and `b`. The result is `aXorB = a ^ b`.
 *           2. **Find a Differentiating Bit:** Since `a` and `b` are
 *              different, `aXorB` will have at least one bit set to 1. We need
 *              to find any one of these set bits. A common trick to find the
 *              rightmost set bit is `diffBit = aXorB & (-aXorB)`. This
 * `diffBit` will be a number with only one bit set.
 *           3. **Second Pass (Partition and XOR):** We iterate through the
 *              original array again. We use `diffBit` to partition the numbers
 *              into two groups:
 *              - Group 1: Numbers where the `diffBit` is set (`num & diffBit`).
 *              - Group 2: Numbers where the `diffBit` is not set.
 *              The unique number `a` will be in one group, and `b` will be in
 *              the other. All duplicate numbers will be paired up within their
 *              respective groups. By XORing all numbers in each group, we can
 *              isolate `a` and `b`.
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

vector<int> singleNumber(vector<int>& nums);

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

    vector<int> ans = singleNumber(nums);

    cout << "Result: [" << ans[0] << ", " << ans[1] << "]" << endl;

    cout << endl;
  }

  return 0;
}

vector<int> singleNumber(vector<int>& nums) {
  ll aXorB = 0;
  for (int i = 0; i < nums.size(); i++) {
    aXorB ^= nums[i];
  }

  ll diffBit = aXorB & (-aXorB);

  int a = 0;
  int b = 0;
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] & diffBit) {
      a ^= nums[i];
    } else {
      b ^= nums[i];
    }
  }

  return {a, b};
}
