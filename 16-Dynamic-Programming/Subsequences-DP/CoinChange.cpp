/*
 * Problem: Coin Change (LeetCode #322)
 * Link: https://leetcode.com/problems/coin-change/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). The state
 *           `dp[amount]` stores the minimum number of coins required to make
 *           that `amount`. The recursive function `solve(amount)` calculates
 *           this by trying every coin and recursively calling itself for the
 *           remaining amount (`amount - coin`).
 *           The minimum result among all coin choices is taken.
 *
 * Time Complexity: O(amount * N), where N is the number of coins.
 * Space Complexity: O(amount) for the DP array + O(amount) for recursion stack.
 */
int memoizationApproach(vector<int>& coins, int amount);
int solve(vector<int>& dp, vector<int>& coins, int amount);

/**
 * Approach: This is a bottom-up DP approach (tabulation). We create a 1D DP
 *           array where `dp[i]` stores the minimum number of coins to make
 *           amount `i`. We iterate from 1 to `amount`, and for each amount, we
 *           try every coin to see if it can lead to a better solution.
 *
 * Time Complexity: O(amount * N)
 * Space Complexity: O(amount)
 */
int tabulationApproach(vector<int>& coins, int amount);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, amount;
    cin >> n >> amount;

    vector<int> coins(n);
    for (int i = 0; i < n; i++) cin >> coins[i];

    cout << "Amount: " << amount << endl;
    cout << "Coins: [ ";
    for (int val : coins) cout << val << " ";
    cout << "]" << endl;

    cout << "Result (Memoization): " << memoizationApproach(coins, amount)
         << endl;
    cout << "Result (Tabulation): " << tabulationApproach(coins, amount)
         << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<int>& coins, int amount) {
  vector<int> dp(amount + 1, -1);
  int ans = solve(dp, coins, amount);

  if (ans >= INT_MAX - 1) return -1;
  return ans;
}

int solve(vector<int>& dp, vector<int>& coins, int amount) {
  if (amount < 0) return INT_MAX - 1;
  if (amount == 0) return 0;
  if (dp[amount] != -1) return dp[amount];

  int minCount = INT_MAX - 1;
  for (int i = 0; i < coins.size(); i++) {
    minCount = min(minCount, solve(dp, coins, amount - coins[i]) + 1);
  }

  dp[amount] = minCount;
  return dp[amount];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<int>& coins, int amount) {
  int INF = 1e9;
  vector<int> dp(amount + 1, INF);
  dp[0] = 0;

  for (int i = 1; i <= amount; i++) {
    for (int j = 0; j < coins.size(); j++) {
      int val = INF;
      if (coins[j] <= i) {
        val = dp[i - coins[j]] + 1;
      }

      dp[i] = min(dp[i], val);
    }
  }

  return (dp[amount] == INF) ? -1 : dp[amount];
}
