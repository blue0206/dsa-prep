/*
 * Problem: Burst Balloons (LeetCode #312)
 * Link: https://leetcode.com/problems/burst-balloons/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). This is a classic
 *           Partition DP problem where thinking in reverse is key. The
 *           function `solve(i, j)` finds the max coins from bursting all
 *           balloons in the range `(i, j)`.
 *           Instead of deciding which balloon to burst first, we decide which
 *           one to burst *last*. If we burst balloon `k` last in `(i, j)`, its
 *           neighbors will be `i` and `j`. The cost is
 *           `nums[i]*nums[k]*nums[j]` plus the max coins from the subproblems
 *           `(i, k)` and `(k, j)`.
 *
 * Time Complexity: O(N^3)
 * Space Complexity: O(N^2) for DP table + O(N) for recursion stack.
 */
int memoizationApproach(vector<int>& nums);
int solve(vector<vector<int>>& dp, const vector<int>& boundaries, int i, int j);

/**
 * Approach: This is the tabulation (bottom-up) version. We fill a 2D DP table
 *           where `dp[i][j]` stores the max coins for bursting balloons in the
 *           range `(i, j)`. The table is filled by iterating over chain
 *           lengths, from small to large, ensuring subproblems are solved
 *           before they are needed.
 *
 * Time Complexity: O(N^3)
 * Space Complexity: O(N^2)
 */
int tabulationApproach(vector<int>& nums);

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

    cout << "Maximum Coins (Memoization): " << memoizationApproach(nums)
         << endl;
    cout << "Maximum Coins (Tabulation): " << tabulationApproach(nums) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<int>& nums) {
  vector<int> boundaries = {1};
  boundaries.insert(boundaries.end(), nums.begin(), nums.end());
  boundaries.emplace_back(1);

  int n = boundaries.size();
  vector<vector<int>> dp(n, vector<int>(n, -1));
  return solve(dp, boundaries, 1, n - 1);
}

int solve(vector<vector<int>>& dp, vector<int>& boundaries, int i, int j) {
  if (i >= j) return 0;
  if (dp[i][j] != -1) return dp[i][j];

  int maxCoins = INT_MIN;
  for (int k = i; k < j; k++) {
    int coins = solve(dp, boundaries, i, k) + solve(dp, boundaries, k + 1, j) +
                (boundaries[i - 1] * boundaries[k] * boundaries[j]);
    maxCoins = max(maxCoins, coins);
  }

  dp[i][j] = maxCoins;
  return dp[i][j];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<int>& nums) {
  vector<int> boundaries = {1};
  boundaries.insert(boundaries.end(), nums.begin(), nums.end());
  boundaries.emplace_back(1);

  int n = boundaries.size();
  vector<vector<int>> dp(n, vector<int>(n, 0));
  for (int i = n - 1; i >= 1; i--) {
    for (int j = i + 1; j < n; j++) {
      int maxCoins = INT_MIN;
      for (int k = i; k < j; k++) {
        int coins = dp[i][k] + dp[k + 1][j] +
                    (boundaries[i - 1] * boundaries[k] * boundaries[j]);
        maxCoins = max(maxCoins, coins);
      }

      dp[i][j] = maxCoins;
    }
  }

  return dp[1][n - 1];
}
