/*
 * Problem: Set Mismatch (LeetCode #645)
 * Link: https://leetcode.com/problems/set-mismatch/description/
 */

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
using ll = long long;

/**
 * Approach: This approach uses a frequency counter. A `std::multiset` is used
 *           to store all numbers from the input array. We then iterate from 1
 *           to `n`. For each number `i`, we check its count in the multiset.
 *           - If the count is 0, `i` is the missing number.
 *           - If the count is greater than 1, `i` is the repeating number.
 *
 * Time Complexity: O(N logN)
 * Space Complexity: O(N)
 */
vector<int> bruteForceApproach(vector<int>& nums);

/**
 * Approach: This optimal approach uses mathematics to solve the problem
 *           without extra space. Let the repeating number be `x` and the
 *           missing number be `y`.
 *           1. Calculate the difference between the ideal sum (1 to n) and the
 *              actual sum of the array: `sum - prefixSum = y - x`.
 *           2. Calculate the difference between the ideal sum of squares and
 *              the actual sum of squares:
 *              `squareSum - prefixSquareSum = y^2 - x^2`.
 *           3. We now have two equations: `y - x` and `y^2 - x^2 = (y-x)(y+x)`.
 *              We can solve for `y + x`, and then solve the system of two
 *              linear equations to find `x` and `y`.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
vector<int> optimalApproach(vector<int>& nums);

int main() {
  int t;
  cin >> t;

  int cases = t;

  while (t--) {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    vector<int> bruteForceApproachAns = bruteForceApproach(nums);
    vector<int> optimalApproachAns = optimalApproach(nums);

    cout << "--------Test Case " << cases - t << "--------" << endl;

    cout << "Brute-Force Approach" << endl;
    cout << "Repeating Number: " << bruteForceApproachAns[0] << endl;
    cout << "Missing Number: " << bruteForceApproachAns[1] << endl;
    cout << endl;

    cout << "Optimal Approach" << endl;
    cout << "Repeating Number: " << optimalApproachAns[0] << endl;
    cout << "Missing Number: " << optimalApproachAns[1] << endl;

    cout << endl;
  }

  return 0;
}

vector<int> bruteForceApproach(vector<int>& nums) {
  multiset<int> ms;
  vector<int> ans = {-1, -1};

  for (auto i : nums) {
    ms.insert(i);
  }

  for (int i = 1; i <= nums.size(); i++) {
    int count = ms.count(i);
    if (count == 0) {
      ans[1] = i;
    } else if (count > 1) {
      ans[0] = i;
    }
    if (ans[0] != -1 && ans[1] != -1) break;
  }

  return ans;
}

vector<int> optimalApproach(vector<int>& nums) {
  ll n = nums.size();

  ll sum = (n * (n + 1)) / 2;
  ll squareSum = (n * (n + 1) * (2 * n + 1)) / 6;

  ll prefixSum = 0;
  ll prefixSquareSum = 0;
  for (int i = 0; i < nums.size(); i++) {
    prefixSum += nums[i];
    prefixSquareSum += ((ll)nums[i] * (ll)nums[i]);
  }

  ll diff = sum - prefixSum;  // missing - repeating
  ll valueSum = squareSum - prefixSquareSum;
  valueSum /= diff;  // missing + repeating

  ll missing = (diff + valueSum) / 2;
  ll repeating = valueSum - missing;

  return {(int)repeating, (int)missing};
}
