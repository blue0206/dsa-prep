/*
 * Problem: House Robber (LeetCode #198)
 * Link: https://leetcode.com/problems/house-robber/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down dynamic programming approach (memoization).
 *           For each house `i`, we have two choices: either rob it or skip it.
 *           - If we rob house `i`, we get `nums[i]` + max money from houses up
 * to `i-2`.
 *           - If we skip house `i`, we get the max money from houses up to
 * `i-1`. The result is the maximum of these two choices. We use a DP array to
 *           store results for subproblems.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N) for recursion stack and DP array.
 */
int memoizationApproach(vector<int>& nums);
int solve(const vector<int>& nums, vector<int>& dp, int i);

/**
 * Approach: This is a bottom-up dynamic programming approach (tabulation). We
 *           create a DP array where `dp[i]` stores the maximum amount that can
 *           be robbed from houses `0` to `i`. We fill this array iteratively
 *           using the same recurrence relation as the memoization approach.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
int tabulationApproach(vector<int>& nums);

/**
 * Approach: This is a space-optimized version of the tabulation approach.
 *           To calculate the max amount for house `i`, we only need the results
 *           for `i-1` and `i-2`. We can use two variables (`prev1`, `prev2`)
 *           instead of a full DP array to achieve O(1) space complexity.
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

    cout << "Money: [ ";
    for (int val : nums) {
      cout << val << " ";
    }
    cout << "]" << endl;

    cout << "Maximum Amount (Memoization): " << memoizationApproach(nums)
         << endl;
    cout << "Maximum Amount (Tabulation): " << tabulationApproach(nums) << endl;
    cout << "Maximum Amount (Optimal): " << optimalApproach(nums) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<int>& nums) {
  int n = nums.size();
  vector<int> dp(n, -1);

  return solve(nums, dp, n - 1);
}

int solve(vector<int>& nums, vector<int>& dp, int i) {
  if (i == 0) return nums[0];
  if (i == 1) return max(nums[0], nums[1]);
  if (dp[i] != -1) return dp[i];

  int prevScore = solve(nums, dp, i - 1);
  int currentScore = solve(nums, dp, i - 2) + nums[i];
  dp[i] = max(prevScore, currentScore);
  return dp[i];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<int>& nums) {
  int n = nums.size();
  if (n == 1) return nums[0];

  vector<int> dp(n, -1);

  dp[0] = nums[0];
  dp[1] = max(nums[0], nums[1]);
  for (int i = 2; i < n; i++) {
    int prevScore = dp[i - 1];
    int currentScore = dp[i - 2] + nums[i];

    dp[i] = max(prevScore, currentScore);
  }

  return dp[n - 1];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(vector<int>& nums) {
  int n = nums.size();
  if (n == 1) return nums[0];

  int prev1 = max(nums[0], nums[1]);
  int prev2 = nums[0];
  for (int i = 2; i < n; i++) {
    int prevScore = prev1;
    int currentScore = prev2 + nums[i];

    int maxScore = max(prevScore, currentScore);

    prev2 = prev1;
    prev1 = maxScore;
  }

  return prev1;
}
