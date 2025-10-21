/*
 * Problem: Best Time to Buy and Sell Stock IV (LeetCode #188)
 * Link:
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution1 {
 public:
  /**
   * Approach: This is a top-down DP approach (memoization) using a 3D state:
   *           `dp[i][holding][transactions]`.
   *           - `i`: current day.
   *           - `holding`: 0 if not holding a stock, 1 if holding.
   *           - `transactions`: number of buys completed (from 0 to k).
   *           The state transitions handle the choice to buy, sell, or do
   *           nothing, constrained by the `transactions < k` limit for buying.
   *
   * Time Complexity: O(N * 2 * k)
   * Space Complexity: O(N * 2 * k) for DP table + O(N + k) for recursion stack.
   */
  int memoizationApproach(int k, vector<int>& prices) {
    int n = prices.size();

    vector<vector<vector<int>>> dp(
        n, vector<vector<int>>(2, vector<int>(k + 1, -1)));
    return solve(dp, prices, k, false, 0, 0);
  }

  int solve(vector<vector<vector<int>>>& dp, vector<int>& prices, int k,
            bool holding, int transactions, int i) {
    if (i == prices.size()) return 0;
    if (dp[i][holding][transactions] != -1) return dp[i][holding][transactions];

    if (holding) {
      int sellProfit =
          solve(dp, prices, k, false, transactions, i + 1) + prices[i];
      int holdProfit = solve(dp, prices, k, true, transactions, i + 1);

      dp[i][holding][transactions] = max(sellProfit, holdProfit);
    } else {
      int buyProfit = 0;
      if (transactions < k) {
        buyProfit =
            solve(dp, prices, k, true, transactions + 1, i + 1) - prices[i];
      }
      int dryProfit = solve(dp, prices, k, false, transactions, i + 1);

      dp[i][holding][transactions] = max(buyProfit, dryProfit);
    }

    return dp[i][holding][transactions];
  }

  /**
   * Approach: This is the tabulation (bottom-up) version of the 3D state
   *           approach. It iterates backwards from the last day, filling the
   *           `dp[i][holding][transactions]` table based on the values from
   *           the next day `i+1`.
   *
   * Time Complexity: O(N * 2 * k)
   * Space Complexity: O(N * 2 * k)
   */
  int tabulationApproach(int k, vector<int>& prices) {
    int n = prices.size();

    vector<vector<vector<int>>> dp(
        n + 1, vector<vector<int>>(2, vector<int>(k + 2, 0)));
    for (int i = n - 1; i >= 0; i--) {
      for (int j = 0; j <= k; j++) {
        dp[i][1][j] = max(dp[i + 1][0][j] + prices[i], dp[i + 1][1][j]);
        dp[i][0][j] = max(dp[i + 1][1][j + 1] - prices[i], dp[i + 1][0][j]);
      }
    }

    return dp[0][0][0];
  }

  /**
   * Approach: This is a space-optimized version of the 3D tabulation. Since
   *           `dp[i]` only depends on `dp[i+1]`, we can reduce space by using
   *           a 2D array to store the states for the previous day (`prev`)
   *           while calculating the current day's states (`dp`).
   *
   * Time Complexity: O(N * 2 * k)
   * Space Complexity: O(2 * k)
   */
  int optimalApproach(int k, vector<int>& prices) {
    int n = prices.size();

    vector<vector<int>> dp(2, vector<int>(k + 2, 0));
    for (int i = n - 1; i >= 0; i--) {
      vector<vector<int>> prev = dp;
      for (int j = 0; j <= k; j++) {
        dp[1][j] = max(prev[0][j] + prices[i], prev[1][j]);
        dp[0][j] = max(prev[1][j + 1] - prices[i], prev[0][j]);
      }
    }

    return dp[0][0];
  }
};

class Solution2 {
 public:
  /**
   * Approach: This memoization approach uses a 2D state `dp[i][t]`, where `t`
   *           is the transaction number (0 to 2k-1). This models the sequence
   *           of actions:
   *           - `t=0`: Can Buy 1, `t=1`: Can Sell 1
   *           - `t=2`: Can Buy 2, `t=3`: Can Sell 2, ...
   *           If `t` is even, we can buy; if odd, we can sell.
   *
   * Time Complexity: O(N * 2 * k)
   * Space Complexity: O(N * 2 * k) for DP table + O(N + k) for recursion stack.
   */
  int memoizationApproach(int k, vector<int>& prices) {
    int n = prices.size();

    vector<vector<int>> dp(n, vector<int>(2 * k + 1, -1));
    return solve(dp, prices, k, 0, 0);
  }

  int solve(vector<vector<int>>& dp, vector<int>& prices, int k, int t, int i) {
    if (i == prices.size() || t == 2 * k) return 0;
    if (dp[i][t] != -1) return dp[i][t];

    if (t % 2 == 0) {
      dp[i][t] = max(solve(dp, prices, k, t, i + 1),
                     solve(dp, prices, k, t + 1, i + 1) - prices[i]);
    } else {
      dp[i][t] = max(solve(dp, prices, k, t, i + 1),
                     solve(dp, prices, k, t + 1, i + 1) + prices[i]);
    }

    return dp[i][t];
  }

  /**
   * Approach: This is the tabulation (bottom-up) version of the transaction
   *           number approach. It iterates backwards from the last day,
   *           filling the `dp[i][t]` table based on the values from `dp[i+1]`.
   *
   * Time Complexity: O(N * 2 * k)
   * Space Complexity: O(N * 2 * k)
   */
  int tabulationApproach(int k, vector<int>& prices) {
    int n = prices.size();

    vector<vector<int>> dp(n + 1, vector<int>(2 * k + 2, 0));

    for (int i = n - 1; i >= 0; i--) {
      for (int t = 0; t <= 2 * k; t++) {
        if (t % 2 == 0) {
          dp[i][t] = max(dp[i + 1][t], dp[i + 1][t + 1] - prices[i]);
        } else {
          dp[i][t] = max(dp[i + 1][t], dp[i + 1][t + 1] + prices[i]);
        }
      }
    }

    return dp[0][0];
  }

  /**
   * Approach: This is a space-optimized version of the 2D tabulation. Since
   *           `dp[i]` only depends on `dp[i+1]`, we can use two 1D arrays
   *           (`prev` and `dp`) to store the states for the previous and
   *           current days. It also includes an optimization: if `k` is large
   *           enough to allow unlimited transactions, it solves that simpler
   *           problem instead.
   *
   * Time Complexity: O(N * 2 * k)
   * Space Complexity: O(2 * k)
   */
  int optimalApproach(int k, vector<int>& prices) {
    int n = prices.size();

    // Optimization for large k, the problem becomes same as LeetCode #122
    if (k >= n / 2) {  // infinite transactions
      int prev0 = 0;
      int prev1 = 0;
      for (int i = n - 1; i >= 0; i--) {
        int temp0 = prev0;
        int temp1 = prev1;
        prev0 = max(temp0, temp1 - prices[i]);
        prev1 = max(temp1, temp0 + prices[i]);
      }

      return prev0;
    }

    vector<int> dp(2 * k + 2, 0);
    for (int i = n - 1; i >= 0; i--) {
      vector<int> prev = dp;
      for (int t = 0; t <= 2 * k; t++) {
        if (t % 2 == 0) {
          dp[t] = max(prev[t], prev[t + 1] - prices[i]);
        } else {
          dp[t] = max(prev[t], prev[t + 1] + prices[i]);
        }
      }
    }

    return dp[0];
  }
};

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;

    vector<int> prices(n);
    for (int i = 0; i < n; i++) cin >> prices[i];

    cout << "Allowed Transactions: " << k << endl;
    cout << "Prices: [ ";
    for (int price : prices) {
      cout << price << " ";
    }
    cout << "]" << endl;

    cout << "First Approach:" << endl;
    Solution1 s1;
    cout << "Maximum Profit (Memoization): "
         << s1.memoizationApproach(k, prices) << endl;
    cout << "Maximum Profit (Tabulation): " << s1.tabulationApproach(k, prices)
         << endl;
    cout << "Maximum Profit (Optimal): " << s1.optimalApproach(k, prices)
         << endl;

    cout << "Second Approach:" << endl;
    Solution2 s2;
    cout << "Maximum Profit (Memoization): "
         << s2.memoizationApproach(k, prices) << endl;
    cout << "Maximum Profit (Tabulation): " << s2.tabulationApproach(k, prices)
         << endl;
    cout << "Maximum Profit (Optimal): " << s2.optimalApproach(k, prices)
         << endl;

    cout << endl;
  }

  return 0;
}
