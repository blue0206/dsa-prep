/*
 * Problem: Longest Increasing Subsequence (LeetCode #300)
 * Link:
 * https://leetcode.com/problems/longest-increasing-subsequence/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). The state
 *           `dp[i][prevIdx+1]` stores the length of the LIS from index `i`
 *           onwards, given that the previous element included in the LIS was at
 *           index `prevIdx`. For each element, we have two choices: either
 *           include it (if it's greater than the previous element) or not.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N^2) for DP table + O(N) for recursion stack.
 */
int memoizationApproach(vector<int>& nums);
int solve(vector<vector<int>>& dp, const vector<int>& nums, int prevIdx, int i);

/**
 * Approach: This is the tabulation (bottom-up) version of the memoization
 *           approach. It uses a 2D DP table where `dp[i][j+1]` represents the
 *           length of the LIS starting from index `i` with the previous
 *           element being at index `j`. The table is filled by iterating
 *           backwards.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N^2)
 */
int tabulationApproach(vector<int>& nums);

/**
 * Approach: This is a space-optimized version of the 2D tabulation. Since
 *           `dp[i]` only depends on `dp[i+1]`, we can use two 1D arrays (`prev`
 *           and `dp`) to store the states for the previous and current rows,
 *           reducing space.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N)
 */
int spaceOptimizedApproach(vector<int>& nums);

/**
 * Approach: This is a more common and intuitive O(N^2) DP approach. A 1D DP
 *           array is used where `dp[i]` stores the length of the LIS that
 *           *ends* at index `i`. To compute `dp[i]`, we look at all previous
 *           elements `j < i` and if `nums[i] > nums[j]`, we can potentially
 *           extend the LIS ending at `j`. So, `dp[i] = 1 + max(dp[j])`.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N)
 */
int spaceOptimizedApproach2(vector<int>& nums);

/**
 * Approach: This is the most optimal solution using patience sorting and
 *           binary search. It maintains a `tails` vector, where `tails[i]` is
 *           the smallest tail of all increasing subsequences of length `i+1`.
 *           When processing a new number, we either extend the longest current
 *           subsequence or use binary search (`lower_bound`) to find the
 *           smallest tail that is greater than or equal to the current number
 *           and replace it, creating a new potential LIS of the same length
 *           but with a smaller tail.
 *
 * Time Complexity: O(N log N)
 * Space Complexity: O(N)
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

    cout << "LIS (Memoization): " << memoizationApproach(nums) << endl;
    cout << "LIS (Tabulation): " << tabulationApproach(nums) << endl;
    cout << "LIS (Space-Optimized, Choice-Based): "
         << spaceOptimizedApproach(nums) << endl;
    cout << "LIS (Space-Optimized, Ending-Based): "
         << spaceOptimizedApproach2(nums) << endl;
    cout << "LIS (Optimal): " << optimalApproach(nums) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<int>& nums) {
  int n = nums.size();

  vector<vector<int>> dp(n, vector<int>(n + 1, -1));
  return solve(dp, nums, -1, 0);
}

int solve(vector<vector<int>>& dp, const vector<int>& nums, int prevIdx,
          int i) {
  if (i == nums.size()) return 0;
  if (dp[i][prevIdx + 1] != -1) return dp[i][prevIdx + 1];

  int lis1 = solve(dp, nums, prevIdx, i + 1);
  int lis2 = 0;

  if (prevIdx == -1 || nums[i] > nums[prevIdx]) {
    lis2 = solve(dp, nums, i, i + 1) + 1;
  }

  dp[i][prevIdx + 1] = max(lis1, lis2);
  return dp[i][prevIdx + 1];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<int>& nums) {
  int n = nums.size();

  vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
  for (int i = n - 1; i >= 0; i--) {
    for (int j = i - 1; j >= -1; j--) {
      dp[i][j + 1] = dp[i + 1][j + 1];

      if (j == -1 || nums[i] > nums[j]) {
        dp[i][j + 1] = max(dp[i][j + 1], dp[i + 1][i + 1] + 1);
      }
    }
  }

  return dp[0][0];
}

//---------------------------SPACE-OPTIMIZED APPROACH---------------------------
int spaceOptimizedApproach(vector<int>& nums) {
  int n = nums.size();

  vector<int> dp(n + 1, 0);
  for (int i = n - 1; i >= 0; i--) {
    vector<int> prev = dp;

    for (int j = i - 1; j >= -1; j--) {
      dp[j + 1] = prev[j + 1];

      if (j == -1 || nums[i] > nums[j]) {
        dp[j + 1] = max(dp[j + 1], prev[i + 1] + 1);
      }
    }
  }

  return dp[0];
}

//--------------------------SPACE-OPTIMIZED APPROACH 2--------------------------
int spaceOptimizedApproach2(vector<int>& nums) {
  int n = nums.size();

  vector<int> dp(n, 1);
  int lis = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (nums[i] > nums[j]) {
        dp[i] = max(dp[i], dp[j] + 1);
        lis = max(lis, dp[i]);
      }
    }
  }

  return lis;
}

//-----------------------------OPTIMAL APPROACH---------------------------------
int optimalApproach(vector<int>& nums) {
  int n = nums.size();

  vector<int> tails;
  for (int i = 0; i < n; i++) {
    if (tails.empty() || tails.back() < nums[i]) {
      tails.emplace_back(nums[i]);
    } else {
      auto it = lower_bound(tails.begin(), tails.end(), nums[i]);
      int idx = distance(tails.begin(), it);
      tails[idx] = nums[i];
    }
  }

  return tails.size();
}
