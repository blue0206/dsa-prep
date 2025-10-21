/*
 * Problem: Best Time to Buy and Sell Stock with Cooldown (LeetCode #309)
 * Link:
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This is a generalized memoization approach for a variable cooldown.
 *           The state is `dp[i][holding][remCooldown]`, representing the max
 *           profit from day `i` onwards.
 *           - `holding`: Whether we currently own a stock.
 *           - `remCooldown`: Days remaining in the cooldown period.
 *           We can only buy if `remCooldown` is 0. When we sell, we reset the
 *           cooldown.
 *
 * Time Complexity: O(N * 2 * C)
 * Space Complexity: O(N * 2 * C) for DP table + O(N + C) for recursion stack.
 */
int memoizationApproach(vector<int>& prices);
int solve(vector<vector<vector<int>>>& dp, vector<int>& prices, int cooldown,
          int remCooldown, bool holding, int i);

/**
 * Approach: This is the tabulation version for a variable cooldown. It builds
 *           a 3D DP table `dp[i][holding][cooldown]` and iterates backwards.
 *           The state transitions are:
 *           - `dp[i][1][0]` (holding): `max(hold_yesterday, sell_today)`
 *           - `dp[i][0][0]` (can buy): `max(rest_yesterday, buy_today)`
 *           - `dp[i][0][c]` (in cooldown): `dp[i+1][0][c-1]` (must wait)
 *
 * Time Complexity: O(N * C)
 * Space Complexity: O(N * C)
 */
int tabulationApproach(vector<int>& prices);

/**
 * Approach: This is a space-optimized version of the variable cooldown
 *           tabulation. Since `dp[i]` only depends on `dp[i+1]`, we can use
 *           two 2D arrays (`prev` and `dp`) to store the states for the
 *           previous and current days, reducing space.
 *
 * Time Complexity: O(N * C)
 * Space Complexity: O(2 * C)
 */
int optimalApproach(vector<int>& prices);

/**
 * Approach: This is a highly optimized O(1) space solution for the specific
 *           problem with a fixed 1-day cooldown. It models a state machine
 *           with three states. We iterate backwards, updating the max profit
 *           for each state based on the profits from the next day.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int fixedCooldownApproach(vector<int>& prices);

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

    cout << "Variable Cooldown Solutions:" << endl;
    cout << "Maximum Profit (Memoization): " << memoizationApproach(prices)
         << endl;
    cout << "Maximum Profit (Tabulation): " << tabulationApproach(prices)
         << endl;
    cout << "Maximum Profit (Optimal): " << optimalApproach(prices) << endl;

    cout << "Fixed, 1-Day Cooldown Optimal Solution:" << endl;
    cout << "Maximum Profit: " << fixedCooldownApproach(prices) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<int>& prices) {
  int cooldown = 1;
  int n = prices.size();

  vector<vector<vector<int>>> dp(
      n, vector<vector<int>>(2, vector<int>(cooldown + 1, -1)));
  return solve(dp, prices, cooldown, 0, false, 0);
}

int solve(vector<vector<vector<int>>>& dp, vector<int>& prices, int cooldown,
          int remCooldown, bool holding, int i) {
  if (i == prices.size()) return 0;
  if (remCooldown < 0) remCooldown = 0;
  if (dp[i][holding][remCooldown] != -1) return dp[i][holding][remCooldown];

  if (holding) {
    int holdProfit = solve(dp, prices, cooldown, remCooldown, true, i + 1);
    int sellProfit =
        solve(dp, prices, cooldown, cooldown, false, i + 1) + prices[i];

    dp[i][holding][remCooldown] = max(holdProfit, sellProfit);
  } else {
    int dryProfit = solve(dp, prices, cooldown, remCooldown - 1, false, i + 1);
    int buyProfit = 0;
    if (remCooldown == 0) {
      buyProfit =
          solve(dp, prices, cooldown, remCooldown, true, i + 1) - prices[i];
    }

    dp[i][holding][remCooldown] = max(dryProfit, buyProfit);
  }

  return dp[i][holding][remCooldown];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<int>& prices) {
  int cooldown = 1;
  int n = prices.size();

  vector<vector<vector<int>>> dp(
      n + 1, vector<vector<int>>(2, vector<int>(cooldown + 1, 0)));
  for (int i = n - 1; i >= 0; i--) {
    dp[i][1][0] = max(dp[i + 1][1][0], dp[i + 1][0][cooldown] + prices[i]);
    dp[i][0][0] = max(dp[i + 1][0][0], dp[i + 1][1][0] - prices[i]);

    for (int c = 1; c <= cooldown; c++) {
      dp[i][0][c] = dp[i + 1][0][c - 1];
    }
  }

  return dp[0][0][0];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(vector<int>& prices) {
  int cooldown = 1;
  int n = prices.size();

  vector<vector<int>> dp(2, vector<int>(cooldown + 1, 0));
  for (int i = n - 1; i >= 0; i--) {
    vector<vector<int>> prev = dp;

    dp[1][0] = max(prev[1][0], prev[0][cooldown] + prices[i]);
    dp[0][0] = max(prev[0][0], prev[1][0] - prices[i]);
    for (int c = 1; c <= cooldown; c++) {
      dp[0][c] = prev[0][c - 1];
    }
  }

  return dp[0][0];
}

//-------------------OPTIMAL APPROACH (FIXED, 1-DAY COOLDOWN)-------------------
int fixedCooldownApproach(vector<int>& prices) {
  int n = prices.size();

  int hold = 0;
  int canBuy = 0;
  int justSold = 0;
  for (int i = n - 1; i >= 0; i--) {
    int prevHold = hold;

    hold = max(hold, justSold + prices[i]);
    justSold = canBuy;
    canBuy = max(canBuy, prevHold - prices[i]);
  }

  return max(canBuy, justSold);
}
