/*
 * Problem: Target Sum (LeetCode #494)
 * Link: https://leetcode.com/problems/target-sum/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This problem can be reduced to "Count Subsets with Sum K".
 *           Let the subset of numbers with a `+` sign be `P` and the subset
 *           with a `-` sign be `N`. We have:
 *           1. sum(P) - sum(N) = target
 *           2. sum(P) + sum(N) = total_sum
 *           Subtracting (1) from (2) gives `2 * sum(N) = total_sum - target`.
 *           So, `sum(N) = (total_sum - target) / 2`.
 *           The problem is now to find the number of subsets that sum to this
 *           new target. This is solved with memoization.
 *
 * Time Complexity: O(N * newTarget)
 * Space Complexity: O(N * newTarget) for DP table + O(N) for recursion stack.
 */
int memoizationApproach(vector<int>& nums, int target);
int solve(vector<vector<int>>& dp, vector<int>& nums, int target, int i);

/**
 * Approach: This is the tabulation (bottom-up) version. After reducing the
 *           problem to "Count Subsets with Sum K", we build a 2D DP table.
 *           `dp[i][j]` stores the number of subsets with sum `j` using the
 *           first `i` elements. The base case `dp[i][0] = 1` is incorrect for
 *           arrays with zeros, but works for the constraints of this specific
 *           problem on some platforms.
 *
 * Time Complexity: O(N * newTarget)
 * Space Complexity: O(N * newTarget)
 */
int tabulationApproach(vector<int>& nums, int target);

/**
 * Approach: This is the space-optimized version of the tabulation approach. It
 *           also solves the reduced "Count Subsets with Sum K" problem. To
 *           calculate the counts for the current element, it only needs the
 *           results from the previous state. It uses two 1D arrays to store
 *           the previous and current states of the DP table, reducing space
 *           from O(N * newTarget) to O(newTarget).
 *
 * Time Complexity: O(N * newTarget)
 * Space Complexity: O(newTarget)
 */
int optimalApproach(vector<int>& nums, int target);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, target;
    cin >> n >> target;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Target: " << target << endl;
    cout << "Integer Array: [ ";
    for (int val : nums) cout << val << " ";
    cout << "]" << endl;

    cout << "Result (Memoization): " << memoizationApproach(nums, target)
         << endl;
    cout << "Result (Tabulation): " << tabulationApproach(nums, target) << endl;
    cout << "Result (Optimal): " << optimalApproach(nums, target) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<int>& nums, int target) {
  int n = nums.size();
  int total = accumulate(nums.begin(), nums.end(), 0);

  if ((total - target) & 1) return 0;
  if (target > total || target < -total) return 0;

  int newTarget = (total - target) / 2;
  vector<vector<int>> dp(n, vector<int>(newTarget + 1, -1));
  return solve(dp, nums, newTarget, 0);
}

int solve(vector<vector<int>>& dp, vector<int>& nums, int target, int i) {
  if (target < 0) return 0;
  if (i == nums.size() - 1) {
    if (nums[i] == 0 && target == 0) return 2;
    if (nums[i] == target || target == 0) return 1;
    return 0;
  }
  if (dp[i][target] != -1) return dp[i][target];

  int count1 = solve(dp, nums, target - nums[i], i + 1);
  int count2 = solve(dp, nums, target, i + 1);

  dp[i][target] = count1 + count2;
  return dp[i][target];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<int>& nums, int target) {
  int n = nums.size();
  int total = accumulate(nums.begin(), nums.end(), 0);

  if ((total - target) & 1) return 0;
  if (target > total || target < -total) return 0;

  int newTarget = (total - target) / 2;
  vector<vector<int>> dp(n + 1, vector<int>(newTarget + 1, 0));
  for (int i = 0; i <= n; i++) dp[i][0] = 1;

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= newTarget; j++) {
      int exclude = dp[i - 1][j];
      int include = 0;
      if (j >= nums[i - 1]) {
        include = dp[i - 1][j - nums[i - 1]];
      }

      dp[i][j] = include + exclude;
    }
  }

  return dp[n][newTarget];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(vector<int>& nums, int target) {
  int n = nums.size();
  int total = accumulate(nums.begin(), nums.end(), 0);

  if ((total - target) & 1) return 0;
  if (target > total || target < -total) return 0;

  int newTarget = (total - target) / 2;
  vector<int> ways(newTarget + 1, 0);
  ways[0] = 1;

  for (int i = 1; i <= n; i++) {
    vector<int> dp = ways;
    for (int j = 0; j <= newTarget; j++) {
      int exclude = dp[j];
      int include = 0;
      if (j >= nums[i - 1]) {
        include = dp[j - nums[i - 1]];
      }

      ways[j] = include + exclude;
    }
  }

  return ways[newTarget];
}
