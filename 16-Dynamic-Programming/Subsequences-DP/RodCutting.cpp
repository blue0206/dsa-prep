/*
 * Problem: Rod Cutting Problem
 * Link:
 * https://www.naukri.com/code360/problems/rod-cutting-problem_800284?leftPanelTabValue=PROBLEM
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This problem is a classic example of the Unbounded Knapsack
 *           pattern. The rod length `n` is the knapsack capacity, the piece
 *           lengths `1, 2, ..., n` are the item weights, and the `price` array
 *           gives their values. This memoization approach uses a state
 *           `dp[i][n]` for the max price from a rod of length `n` using cuts of
 *           length `i+1` and greater.
 *
 * Time Complexity: O(N * N)
 * Space Complexity: O(N * N) for DP table + O(N) for recursion stack.
 */
int memoizationApproach(vector<int>& price, int n);
int solve(vector<vector<int>>& dp, vector<int>& price, int n, int i);

/**
 * Approach: This is a space-optimized bottom-up DP approach. It also models
 *           the problem as an Unbounded Knapsack. We use a 1D array `dp` where
 *           `dp[i]` stores the maximum price obtainable from a rod of length
 *           `i`. We iterate through each possible rod length `i` from 1 to `n`,
 *           and for each length, we try all possible cuts `j` to see if they
 *           yield a better price.
 *
 * Time Complexity: O(N * N)
 * Space Complexity: O(N)
 */
int tabulationApproach(vector<int>& price, int n);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> price(n);
    for (int i = 0; i < n; i++) cin >> price[i];

    cout << "Prices: [ ";
    for (int val : price) cout << val << " ";
    cout << "]" << endl;

    cout << "Result (Memoization): " << memoizationApproach(price, n) << endl;
    cout << "Result (Tabulation): " << tabulationApproach(price, n) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<int>& price, int n) {
  vector<vector<int>> dp(n, vector<int>(n + 1, -1));
  return solve(dp, price, n, 0);
}

int solve(vector<vector<int>>& dp, vector<int>& price, int n, int i) {
  if (i == price.size() || n == 0) return 0;
  if (dp[i][n] != -1) return dp[i][n];

  int include = 0;
  if (n >= i + 1) {
    include = solve(dp, price, n - i - 1, i) + price[i];
  }
  int exclude = solve(dp, price, n, i + 1);

  dp[i][n] = max(include, exclude);
  return dp[i][n];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<int>& price, int n) {
  vector<int> dp(n + 1, 0);

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < n; j++) {
      if (i >= j + 1) {
        int val = dp[i - j - 1] + price[j];
        dp[i] = max(dp[i], val);
      }
    }
  }

  return dp[n];
}
