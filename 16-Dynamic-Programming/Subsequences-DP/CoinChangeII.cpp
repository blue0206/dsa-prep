/*
 * Problem: Coin Change II (LeetCode #518)
 * Link: https://leetcode.com/problems/coin-change-ii/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). The state is defined
 *           by `dp[i][amount]`, representing the number of ways to make the
 *           `amount` using coins from index `i` onwards. For each coin `i`, we
 *           have two choices:
 *           1. Don't use coin `i`: `solve(..., amount, i + 1)`
 *           2. Use coin `i`: `solve(..., amount - coins[i], i)` (stay at `i`
 *              as coins can be reused).
 *
 * Time Complexity: O(N * amount)
 * Space Complexity: O(N * amount) for DP table + O(N + amount) for recursion
 *                   stack.
 */
int memoizationApproach(vector<int>& coins, int amount);
int solve(vector<vector<int>>& dp, vector<int>& coins, int amount, int i);

/**
 * Approach: This is a space-optimized bottom-up DP approach. We use a 1D
 *           array `dp` where `dp[j]` stores the number of ways to make amount
 *           `j`. We iterate through each coin, and for each coin, we update
 *           the `dp` array for all amounts it can contribute to. The order of
 *           loops (outer for coins, inner for amount) is crucial for counting
 *           combinations.
 *
 * Time Complexity: O(N * amount)
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

    cout << "Result (Memoization): " << memoizationApproach(amount, coins)
         << endl;
    cout << "Result (Tabulation): " << tabulationApproach(amount, coins)
         << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(int amount, vector<int>& coins) {
  int n = coins.size();

  vector<vector<int>> dp(n, vector<int>(amount + 1, -1));
  return solve(dp, coins, amount, 0);
}

int solve(vector<vector<int>>& dp, vector<int>& coins, int amount, int i) {
  if (amount == 0) return 1;
  if (amount < 0 || i == coins.size()) return 0;
  if (dp[i][amount] != -1) return dp[i][amount];

  int count1 = solve(dp, coins, amount, i + 1);
  int count2 = solve(dp, coins, amount - coins[i], i);

  dp[i][amount] = count1 + count2;
  return dp[i][amount];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(int amount, vector<int>& coins) {
  int n = coins.size();

  vector<unsigned long long> dp(amount + 1, 0);
  dp[0] = 1;

  for (int i = 0; i < n; i++) {
    for (int j = coins[i]; j <= amount; j++) {
      dp[j] += dp[j - coins[i]];
    }
  }

  return dp[amount];
}
