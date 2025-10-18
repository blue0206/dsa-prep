/*
 * Problem: Partition Equal Subset Sum (LeetCode #416)
 * Link: https://leetcode.com/problems/partition-equal-subset-sum/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). The core idea is to
 *           try every possible subset. The recursive function explores two
 *           choices for each element: either include it in the current subset
 *           sum or not. The base case is reached when all elements have been
 *           considered. At that point, it checks if the sum of the constructed
 *           subset is equal to the sum of the remaining elements
 *           (`sum == total - sum`).
 *
 * Time Complexity: O(N * TotalSum)
 * Space Complexity: O(N * TotalSum) for the DP table + O(N) for recursion
 * stack.
 */
bool memoizationApproach(vector<int>& nums);
bool solve(vector<int>& nums, vector<vector<int>>& dp, int total, int sum,
           int i);

/**
 * Approach: This approach reduces the problem to the "Subset Sum" problem. A
 *           partition is possible only if the total sum of the array is even.
 *           If it is, the problem becomes: can we find a subset that sums up
 *           to `target = total_sum / 2`? This is solved using tabulation,
 *           where `dp[i][j]` is true if a sum of `j` can be made from the
 *           first `i` elements.
 *
 * Time Complexity: O(N * target)
 * Space Complexity: O(N * target)
 */
bool tabulationApproach(vector<int>& nums);

/**
 * Approach: This is a space-optimized version of the tabulation approach. It
 *           also reduces the problem to finding a subset with a sum of
 *           `target = total_sum / 2`. To calculate the results for the current
 *           element, it only needs the results from the previous state. It
 *           uses two 1D arrays to store the previous and current states of
 *           the DP table, reducing space from O(N * target) to O(target).
 *
 * Time Complexity: O(N * target)
 * Space Complexity: O(target)
 */
bool optimalApproach(vector<int>& nums);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << "Input Array: [ ";
    for (int val : arr) cout << val << " ";
    cout << "]" << endl;

    cout << "Result (Memoization): " << memoizationApproach(arr) << endl;
    cout << "Result (Tabulation): " << tabulationApproach(arr) << endl;
    cout << "Result (Optimal): " << optimalApproach(arr) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
bool memoizationApproach(vector<int>& nums) {
  int n = nums.size();

  int total = accumulate(nums.begin(), nums.end(), 0);
  if (total & 1) return false;

  vector<vector<int>> dp(n, vector<int>(total + 1, -1));
  return solve(nums, dp, total, 0, 0);
}

bool solve(vector<int>& nums, vector<vector<int>>& dp, int total, int sum,
           int i) {
  if (i == nums.size()) {
    return (sum == total - sum);
  }
  if (dp[i][sum] != -1) return dp[i][sum];

  dp[i][sum] = solve(nums, dp, total, sum, i + 1) ||
               solve(nums, dp, total, sum + nums[i], i + 1);
  return dp[i][sum];
}

//-----------------------------TABULATION APPROACH------------------------------
bool tabulationApproach(vector<int>& nums) {
  int n = nums.size();

  int total = accumulate(nums.begin(), nums.end(), 0);
  if (total & 1) return false;

  int target = total / 2;
  vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
  for (int i = 0; i <= n; i++) dp[i][0] = true;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= target; j++) {
      bool exclude = dp[i - 1][j];

      bool include = false;
      if (j >= nums[i - 1]) {
        include = dp[i - 1][j - nums[i - 1]];
      }

      dp[i][j] = include || exclude;
    }
  }

  return dp[n][target];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
bool optimalApproach(vector<int>& nums) {
  int n = nums.size();
  int total = accumulate(nums.begin(), nums.end(), 0);
  if (total & 1) return false;

  int target = total / 2;
  vector<bool> ans(target + 1, false);
  ans[0] = true;

  for (int i = 1; i <= n; i++) {
    vector<bool> dp = ans;
    for (int j = 1; j <= target; j++) {
      bool exclude = dp[j];
      bool include = false;
      if (j >= nums[i - 1]) {
        include = dp[j - nums[i - 1]];
      }

      ans[j] = include || exclude;
    }
  }

  return ans[target];
}
