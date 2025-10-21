/*
 * Problem: Best Time to Buy and Sell Stock (LeetCode #121)
 * Link:
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). The state
 *           `dp[i][holding]` represents the maximum profit achievable from
 *           `prices[i]` to `prices[n-1]`, given whether we are currently
 *           `holding` a stock or not.
 *           - If `holding` is true (we own a stock):
 *             - We can either **sell** today: `prices[i] + solve(false, i + 1)`
 *               (gain `prices[i]`, then not holding).
 *             - Or **do nothing** (continue holding): `solve(true, i + 1)`.
 *             - We take the maximum of these two options.
 *           - If `holding` is false (we don't own a stock):
 *             - We can either **buy** today: `-prices[i] + solve(true, i + 1)`
 *               (spend `prices[i]`, then holding).
 *             - Or **do nothing** (continue not holding): `solve(false, i + 1)`
 *             - We take the maximum of these two options.
 *
 * Time Complexity: O(N * 2)
 * Space Complexity: O(N * 2) for DP table + O(N) for recursion stack.
 */
int memoizationApproach(vector<int>& prices);
int solve(vector<vector<int>>& dp, vector<int>& prices, bool holding, int i);

/**
 * Approach: This is a bottom-up DP approach (tabulation). We build a 2D DP
 *           table `dp[i][holding]`, where `dp[i][0]` is the maximum profit if
 *           we are not holding a stock on day `i`, and `dp[i][1]` is the
 *           maximum profit if we are holding a stock on day `i`. We iterate
 *           from the last day backwards.
 *           - `dp[i][0]` (not holding on day `i`): `max(dp[i+1][0], dp[i+1][1]
 *              + prices[i])` (don't buy on day `i`, or sell on day `i`).
 *           - `dp[i][1]` (holding on day `i`): `max(dp[i+1][1], dp[i+1][0] -
 *              prices[i])` (don't sell on day `i`, or buy on day `i`).
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N * 2)
 */
int tabulationApproach(vector<int>& prices);

/**
 * Approach: This is a space-optimized version of the tabulation approach.
 *           Since the current day's profit only depends on the next day's
 *           profits, we can reduce the space complexity to O(1) by using two
 *           variables:
 *           `notHold` (max profit if not holding) and `hold` (max profit if
 *            holding). We iterate from the last day backwards, updating these
 *            variables.
 *           - `new_notHold = max(old_notHold, old_hold + prices[i])`
 *           - `new_hold = max(old_hold, old_notHold - prices[i])`
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
  int n = prices.size();
  vector<vector<int>> dp(n, vector<int>(2, -1));

  return solve(dp, prices, false, 0);
}

int solve(vector<vector<int>>& dp, vector<int>& prices, bool holding, int i) {
  if (i == prices.size()) return 0;
  if (dp[i][holding] != -1) return dp[i][holding];

  if (holding) {
    int holdProfit = solve(dp, prices, true, i + 1);
    int sellProfit = prices[i];

    dp[i][holding] = max(holdProfit, sellProfit);
  } else {
    int dryProfit = solve(dp, prices, false, i + 1);
    int buyProfit = solve(dp, prices, true, i + 1) - prices[i];

    dp[i][holding] = max(dryProfit, buyProfit);
  }

  return dp[i][holding];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<int>& prices) {
  int n = prices.size();
  vector<vector<int>> dp(n + 1, vector<int>(2, 0));

  for (int i = n - 1; i >= 0; i--) {
    dp[i][0] = max(dp[i + 1][0], dp[i + 1][1] - prices[i]);
    dp[i][1] = max(dp[i + 1][1], prices[i]);
  }

  return dp[0][0];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(vector<int>& prices) {
  int n = prices.size();

  int hold = 0;
  int notHold = 0;
  for (int i = n - 1; i >= 0; i--) {
    notHold = max(notHold, hold - prices[i]);
    hold = max(hold, prices[i]);
  }

  return notHold;
}
