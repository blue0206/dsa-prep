/*
 * Problem: House Robber II (LeetCode #213)
 * Link: https://leetcode.com/problems/house-robber-ii/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This uses a bottom-up DP (tabulation) approach. The circular
 *           dependency is handled by breaking the problem into two linear
 *           subproblems:
 *           1. Max money from houses 0 to n-2 (excluding the last house).
 *           2. Max money from houses 1 to n-1 (excluding the first house).
 *           A helper function solves the standard linear House Robber problem
 *           on the given sub-array range `[low, high]` using a DP table. The
 *           final answer is the maximum of the two subproblem results.
 *
 * Time Complexity: O(N), as we run the linear scan twice.
 * Space Complexity: O(N) for the DP array.
 */
int tabulationApproach(vector<int>& nums);
int tabulation(vector<int>& nums, vector<int>& dp, int low, int high);

/**
 * Approach: This is a space-optimized version of the tabulation approach. It
 *           uses the same strategy of breaking the circular problem into two
 *           linear subproblems (houses 0 to n-2 and 1 to n-1).
 *           The helper function, however, solves the linear House Robber
 *           problem using only two variables to track the previous two states,
 *           achieving O(1) space for the subproblem calculation.
 *
 * Time Complexity: O(N), as we run the linear scan twice.
 * Space Complexity: O(1), as no extra space proportional to N is used.
 */
int optimalApproach(vector<int>& nums);
int optimal(vector<int>& nums, int low, int high);

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

    cout << "Maximum Amount (Tabulation): " << tabulationApproach(nums) << endl;
    cout << "Maximum Amount (Optimal): " << optimalApproach(nums) << endl;

    cout << endl;
  }

  return 0;
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<int>& nums) {
  int n = nums.size();
  if (n == 1) return nums[0];
  if (n == 2) return max(nums[0], nums[1]);

  vector<int> dp(n, -1);

  dp[0] = nums[0];
  dp[1] = max(nums[0], nums[1]);
  int score2 = tabulation(nums, dp, 0, n - 2);
  int score1 = tabulation(nums, dp, 1, n - 1);

  return max(score1, score2);
}

int tabulation(vector<int>& nums, vector<int>& dp, int low, int high) {
  dp[low + 1] = max(nums[low], nums[low + 1]);
  dp[low] = nums[low];
  for (int i = low + 2; i <= high; i++) {
    int prevScore = dp[i - 1];
    int currentScore = dp[i - 2] + nums[i];

    dp[i] = max(prevScore, currentScore);
  }

  return dp[high];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(vector<int>& nums) {
  int n = nums.size();
  if (n == 1) return nums[0];
  if (n == 2) return max(nums[0], nums[1]);

  int score2 = optimal(nums, 0, n - 2);
  int score1 = optimal(nums, 1, n - 1);

  return max(score1, score2);
}

int optimal(vector<int>& nums, int low, int high) {
  int prev1 = max(nums[low], nums[low + 1]);
  int prev2 = nums[low];
  for (int i = low + 2; i <= high; i++) {
    int prevScore = prev1;
    int currentScore = prev2 + nums[i];

    int maxScore = max(prevScore, currentScore);

    prev2 = prev1;
    prev1 = maxScore;
  }

  return prev1;
}
