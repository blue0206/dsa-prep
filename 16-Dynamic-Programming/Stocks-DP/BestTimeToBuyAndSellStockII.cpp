/*
 * Problem: Best Time to Buy and Sell Stock II (LeetCode #122)
 * Link:
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). The state
 *           `dp[i][held]` represents the maximum profit from day `i` onwards,
 *           given whether we currently hold a stock (`held` = true) or not
 *           (`held` = false).
 *           - If not holding: We can either buy today (`-prices[i] + solve(i+1,
 *             true)`) or do nothing (`solve(i+1, false)`).
 *           - If holding: We can either sell today (`prices[i] + solve(i+1,
 *             false)`) or do nothing (`solve(i+1, true)`). The base case is at
 *             the end of the prices array, where profit is 0.
 *
 * Time Complexity: O(N * 2)
 * Space Complexity: O(N * 2) for DP table + O(N) for recursion stack.
 */
int memoizationApproach(vector<int>& prices);
int solve(vector<vector<int>>& dp, vector<int>& prices, bool held, int i);

/**
 * Approach: This is a bottom-up DP approach (tabulation). We build a 2D DP
 *           table `dp[i][held]` and iterate backwards from the last day.
 *           - `dp[i][0]` (not holding): `max(dp[i+1][0], dp[i+1][1] -
 *             prices[i])` (rest, or buy today).
 *           - `dp[i][1]` (holding): `max(dp[i+1][1], dp[i+1][0] + prices[i])`
 *             (rest, or sell today).
 *           The answer is `dp[0][0]`, the max profit starting from day 0
 *           without a stock.
 *
 * Time Complexity: O(N * 2) ~ O(N)
 * Space Complexity: O(N * 2) ~ O(N)
 */
int tabulationApproach(vector<int>& prices);

/**
 * Approach: This is a space-optimized version of tabulation. Since `dp[i]` only
 *           depends on `dp[i+1]`, we only need to store the values for the next
 *           day. We use two variables, `hold` and `notHold`, and update them as
 *           we iterate backwards.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int optimalApproach(vector<int>& prices);

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

    cout << "Maximum Profit (Memoization): " << memoizationApproach(prices)
         << endl;
    cout << "Maximum Profit (Tabulation): " << tabulationApproach(prices)
         << endl;
    cout << "Maximum Profit (Optimal): " << optimalApproach(prices) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<int>& prices) {
  vector<vector<int>> dp(prices.size(), vector<int>(2, -1));
  return solve(dp, prices, false, 0);
}

int solve(vector<vector<int>>& dp, vector<int>& prices, bool held, int i) {
  if (i == prices.size()) return 0;
  if (dp[i][held] != -1) return dp[i][held];

  if (!held) {
    // Buy or not buy.
    dp[i][held] = max(solve(dp, prices, true, i + 1) - prices[i],
                      solve(dp, prices, false, i + 1));
  } else {
    // Sell or not sell.
    dp[i][held] = max(solve(dp, prices, false, i + 1) + prices[i],
                      solve(dp, prices, true, i + 1));
  }

  return dp[i][held];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<int>& prices) {
  int n = prices.size();

  vector<vector<int>> dp(n + 1, vector<int>(2, 0));
  for (int i = n - 1; i >= 0; i--) {
    dp[i][0] = max(dp[i + 1][0], dp[i + 1][1] - prices[i]);
    dp[i][1] = max(dp[i + 1][1], dp[i + 1][0] + prices[i]);
  }

  return dp[0][0];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(vector<int>& prices) {
  int notHold = 0;
  int hold = 0;
  for (int i = prices.size() - 1; i >= 0; i--) {
    int prevHold = hold;

    hold = max(hold, notHold + prices[i]);
    notHold = max(notHold, prevHold - prices[i]);
  }

  return notHold;
}
