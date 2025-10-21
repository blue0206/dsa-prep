/*
 * Problem: Best Time to Buy and Sell Stock with Transaction Fee (LeetCode #714)
 * Link:
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). The state
 *           `dp[i][holding]` represents the maximum profit from day `i`
 *           onwards, given whether we currently hold a stock. The transaction
 *           fee is incorporated into the 'buy' action.
 *           - If not holding: We can either buy today (`-prices[i] - fee +
 *             solve(i+1, true)`) or do nothing (`solve(i+1, false)`).
 *           - If holding: We can either sell today (`prices[i] + solve(i+1,
 *             false)`) or do nothing (`solve(i+1, true)`).
 *
 * Time Complexity: O(N * 2)
 * Space Complexity: O(N * 2) for DP table + O(N) for recursion stack.
 */
int memoizationApproach(vector<int>& prices, int fee);
int solve(vector<vector<int>>& dp, vector<int>& prices, int fee, bool holding,
          int i);

/**
 * Approach: This is the tabulation (bottom-up) version. It builds a 2D DP
 *           table `dp[i][held]` and iterates backwards from the last day.
 *           - `dp[i][0]` (not holding): `max(dp[i+1][0], dp[i+1][1] - prices[i]
 *              - fee)`
 *           - `dp[i][1]` (holding): `max(dp[i+1][1], dp[i+1][0] + prices[i])`
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N * 2)
 */
int tabulationApproach(vector<int>& prices, int fee);

/**
 * Approach: This is a space-optimized version of tabulation. Since `dp[i]` only
 *           depends on `dp[i+1]`, we only need to store the values for the next
 *           day. We use two variables, `hold` and `notHold`, and update them as
 *           we iterate backwards.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int optimalApproach(vector<int>& prices, int fee);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, fee;
    cin >> n >> fee;

    vector<int> prices(n);
    for (int i = 0; i < n; i++) cin >> prices[i];

    cout << "Transaction Fee: " << fee << endl;
    cout << "Prices: [ ";
    for (int price : prices) {
      cout << price << " ";
    }
    cout << "]" << endl;

    cout << "Maximum Profit (Memoization): " << memoizationApproach(prices, fee)
         << endl;
    cout << "Maximum Profit (Tabulation): " << tabulationApproach(prices, fee)
         << endl;
    cout << "Maximum Profit (Optimal): " << optimalApproach(prices, fee)
         << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<int>& prices, int fee) {
  int n = prices.size();

  vector<vector<int>> dp(n, vector<int>(2, -1));
  return solve(dp, prices, fee, false, 0);
}

int solve(vector<vector<int>>& dp, vector<int>& prices, int fee, bool holding,
          int i) {
  if (i == prices.size()) return 0;
  if (dp[i][holding] != -1) return dp[i][holding];

  if (holding) {
    int holdProfit = solve(dp, prices, fee, true, i + 1);
    int sellProfit = solve(dp, prices, fee, false, i + 1) + prices[i];

    dp[i][holding] = max(holdProfit, sellProfit);
  } else {
    int dryProfit = solve(dp, prices, fee, false, i + 1);
    int buyProfit = solve(dp, prices, fee, true, i + 1) - prices[i] - fee;

    dp[i][holding] = max(dryProfit, buyProfit);
  }

  return dp[i][holding];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<int>& prices, int fee) {
  int n = prices.size();

  vector<vector<int>> dp(n + 1, vector<int>(2, 0));
  for (int i = n - 1; i >= 0; i--) {
    dp[i][0] = max(dp[i + 1][0], dp[i + 1][1] - prices[i] - fee);
    dp[i][1] = max(dp[i + 1][1], dp[i + 1][0] + prices[i]);
  }

  return dp[0][0];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(vector<int>& prices, int fee) {
  int n = prices.size();

  int hold = 0;
  int notHold = 0;
  for (int i = n - 1; i >= 0; i--) {
    int prevHold = hold;
    int prevNotHold = notHold;

    notHold = max(prevNotHold, prevHold - prices[i] - fee);
    hold = max(prevHold, prevNotHold + prices[i]);
  }

  return notHold;
}
