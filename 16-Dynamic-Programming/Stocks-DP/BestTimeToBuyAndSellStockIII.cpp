/*
 * Problem: Best Time to Buy and Sell Stock III (LeetCode #123)
 * Link:
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description/
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
   *           - `transactions`: number of buys completed (0, 1, or 2).
   *           The state transitions handle the choice to buy, sell, or do
   *           nothing, constrained by the `transactions < 2` limit for buying.
   *
   * Time Complexity: O(N * 2 * 3)
   * Space Complexity: O(N * 2 * 3) for DP table + O(N) for recursion stack.
   */
  int memoizationApproach(vector<int>& prices) {
    int n = prices.size();

    vector<vector<vector<int>>> dp(n,
                                   vector<vector<int>>(2, vector<int>(3, -1)));
    return solve(dp, prices, 0, false, 0);
  }

  int solve(vector<vector<vector<int>>>& dp, vector<int>& prices,
            int transactions, bool holding, int i) {
    if (i == prices.size()) return 0;
    if (dp[i][holding][transactions] != -1) return dp[i][holding][transactions];

    if (holding) {
      // Sell or not sell.
      int sellProfit =
          solve(dp, prices, transactions, false, i + 1) + prices[i];
      int notSellProfit = solve(dp, prices, transactions, true, i + 1);

      dp[i][holding][transactions] = max(sellProfit, notSellProfit);
    } else {
      // Buy or not buy
      int buyProfit = 0;
      if (transactions < 2) {
        buyProfit =
            solve(dp, prices, transactions + 1, true, i + 1) - prices[i];
      }
      int notBuyProfit = solve(dp, prices, transactions, false, i + 1);

      dp[i][holding][transactions] = max(buyProfit, notBuyProfit);
    }

    return dp[i][holding][transactions];
  }

  /**
   * Approach: This is the tabulation (bottom-up) version of the 3D state
   *           approach. It iterates backwards from the last day, filling the
   *           `dp[i][holding][transactions]` table based on the values from
   *           the next day `i+1`.
   *
   * Time Complexity: O(N * 2 * 3)
   * Space Complexity: O(N * 2 * 3)
   */
  int tabulationApproach(vector<int>& prices) {
    int n = prices.size();

    vector<vector<vector<int>>> dp(n + 1,
                                   vector<vector<int>>(2, vector<int>(3, 0)));
    for (int i = n - 1; i >= 0; i--) {
      for (int j = 0; j <= 2; j++) {
        dp[i][1][j] = max(dp[i + 1][0][j] + prices[i], dp[i + 1][1][j]);
        if (j < 2) {
          dp[i][0][j] = max(dp[i + 1][1][j + 1] - prices[i], dp[i + 1][0][j]);
        } else {
          dp[i][0][j] = dp[i + 1][0][j];
        }
      }
    }

    return dp[0][0][0];
  }

  /**
   * Approach: This is a space-optimized version of the 3D tabulation. Since
   *           `dp[i]` only depends on `dp[i+1]`, we can reduce space by using
   *           1D arrays to store the states for the previous day (`prev0`,
   *           `prev1`) while calculating the current day's states.
   *
   * Time Complexity: O(N)
   * Space Complexity: O(1)
   */
  int optimalApproach(vector<int>& prices) {
    int n = prices.size();

    vector<int> prev0(3, 0), prev1(3, 0);
    for (int i = n - 1; i >= 0; i--) {
      vector<int> dp0 = prev0;
      vector<int> dp1 = prev1;

      prev1[0] = max(dp0[0] + prices[i], dp1[0]);
      prev0[0] = max(dp1[1] - prices[i], dp0[0]);

      prev1[1] = max(dp0[1] + prices[i], dp1[1]);
      prev0[1] = max(dp1[2] - prices[i], dp0[1]);

      prev1[2] = max(dp0[2] + prices[i], dp1[2]);
      prev0[2] = dp0[2];
    }

    return prev0[0];
  }
};

class Solution2 {
 public:
  /**
   * Approach: This memoization approach uses a 2D state `dp[i][t]`, where `t`
   *           is the transaction number (0 to 3). This models the sequence of
   *           actions:
   *           - `t=0`: Can Buy 1
   *           - `t=1`: Can Sell 1
   *           - `t=2`: Can Buy 2
   *           - `t=3`: Can Sell 2
   *           If `t` is even, we can buy; if odd, we can sell.
   *
   * Time Complexity: O(N * 4)
   * Space Complexity: O(N * 4) for DP table + O(N) for recursion stack.
   */
  int memoizationApproach(vector<int>& prices) {
    vector<vector<int>> dp(prices.size(), vector<int>(4, -1));
    return solve(dp, prices, 0, 0);
  }

  int solve(vector<vector<int>>& dp, vector<int>& prices, int t, int i) {
    if (i == prices.size() || t == 4) return 0;
    if (dp[i][t] != -1) return dp[i][t];

    if (t % 2 == 0) {
      dp[i][t] = max(solve(dp, prices, t, i + 1),
                     solve(dp, prices, t + 1, i + 1) - prices[i]);
    } else {
      dp[i][t] = max(solve(dp, prices, t, i + 1),
                     solve(dp, prices, t + 1, i + 1) + prices[i]);
    }

    return dp[i][t];
  }

  /**
   * Approach: This is the tabulation (bottom-up) version of the transaction
   *           number approach. It iterates backwards from the last day,
   *           filling the `dp[i][t]` table based on the values from `dp[i+1]`.
   *
   * Time Complexity: O(N * 4)
   * Space Complexity: O(N * 5)
   */
  int tabulationApproach(vector<int>& prices) {
    int n = prices.size();

    vector<vector<int>> dp(n + 1, vector<int>(5, 0));
    for (int i = n - 1; i >= 0; i--) {
      for (int j = 0; j < 4; j++) {
        if (j % 2 == 0) {
          dp[i][j] = max(dp[i + 1][j], dp[i + 1][j + 1] - prices[i]);
        } else {
          dp[i][j] = max(dp[i + 1][j], dp[i + 1][j + 1] + prices[i]);
        }
      }
    }

    return dp[0][0];
  }

  /**
   * Approach: This is a space-optimized version of the 2D tabulation. Since
   *           `dp[i]` only depends on `dp[i+1]`, we can use two 1D arrays
   *           (`prev` and `dp`) to store the states for the previous and
   *           current days, reducing space complexity.
   *
   * Time Complexity: O(N * 4)
   * Space Complexity: O(1)
   */
  int optimalApproach(vector<int>& prices) {
    int n = prices.size();

    vector<int> dp(5, 0);
    for (int i = n - 1; i >= 0; i--) {
      vector<int> prev = dp;
      for (int j = 0; j < 4; j++) {
        if (j % 2 == 0) {
          dp[j] = max(prev[j], prev[j + 1] - prices[i]);
        } else {
          dp[j] = max(prev[j], prev[j + 1] + prices[i]);
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
    int n;
    cin >> n;

    vector<int> prices(n);
    for (int i = 0; i < n; i++) cin >> prices[i];

    cout << "Prices: [ ";
    for (int price : prices) {
      cout << price << " ";
    }
    cout << "]" << endl;

    cout << "First Approach:" << endl;
    Solution1 s1;
    cout << "Maximum Profit (Memoization): " << s1.memoizationApproach(prices)
         << endl;
    cout << "Maximum Profit (Tabulation): " << s1.tabulationApproach(prices)
         << endl;
    cout << "Maximum Profit (Optimal): " << s1.optimalApproach(prices) << endl;

    cout << "Second Approach:" << endl;
    Solution2 s2;
    cout << "Maximum Profit (Memoization): " << s2.memoizationApproach(prices)
         << endl;
    cout << "Maximum Profit (Tabulation): " << s2.tabulationApproach(prices)
         << endl;
    cout << "Maximum Profit (Optimal): " << s2.optimalApproach(prices) << endl;

    cout << endl;
  }

  return 0;
}
