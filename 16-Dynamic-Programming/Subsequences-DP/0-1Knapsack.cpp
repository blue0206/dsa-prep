/*
 * Problem: 0 1 Knapsack
 * Link:
 * https://www.naukri.com/code360/problems/0-1-knapsack_920542?leftPanelTabValue=PROBLEM
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
const int m = 1e9 + 7;

/**
 * Approach: This is a top-down DP approach (memoization). The state is defined
 *           by `dp[i][maxW]`, representing the maximum value that can be
 *           obtained from items `i` to `n-1` with a remaining knapsack
 *           capacity of `maxW`. For each item, we have two choices:
 *           1. Pick the item: `value[i] + solve(..., maxW - weight[i], i + 1)`
 *           2. Don't pick the item: `solve(..., maxW, i + 1)`
 *
 * Time Complexity: O(N * maxWeight)
 * Space Complexity: O(N * maxWeight) for DP table + O(N) for recursion stack.
 */
int memoizationApproach(vector<int> weight, vector<int> value, int n,
                        int maxWeight);
int solve(vector<vector<int>>& dp, vector<int>& weight, vector<int>& value,
          int maxW, int i);

/**
 * Approach: This is a bottom-up DP approach (tabulation). We create a 2D DP
 *           table where `dp[i][j]` stores the maximum value that can be
 *           achieved using the first `i` items with a knapsack capacity of `j`.
 *           The value for each cell is calculated based on the "pick vs.
 *           not-pick" logic using results from the previous row.
 *
 * Time Complexity: O(N * maxWeight)
 * Space Complexity: O(N * maxWeight)
 */
int tabulationApproach(vector<int> weight, vector<int> value, int n,
                       int maxWeight);

/**
 * Approach: This is a space-optimized version of the tabulation approach. To
 *           calculate the values for the current item, we only need the
 *           results from the previous state. It uses two 1D arrays to store
 *           the previous and current states of the DP table, reducing space
 *           from O(N * maxWeight) to O(maxWeight).
 *
 * Time Complexity: O(N * maxWeight)
 * Space Complexity: O(maxWeight)
 */
int optimalApproach(vector<int> weight, vector<int> value, int n,
                    int maxWeight);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, maxWeight;
    cin >> n >> maxWeight;

    vector<int> wt(n), vals(n);
    for (int i = 0; i < n; i++) cin >> wt[i];
    for (int i = 0; i < n; i++) cin >> vals[i];

    cout << "Max Weight: " << maxWeight << endl;
    cout << "Weights: [ ";
    for (int val : wt) cout << val << " ";
    cout << "]" << endl;
    cout << "Value: [ ";
    for (int val : vals) cout << val << " ";
    cout << "]" << endl;

    cout << "Result (Memoization): "
         << memoizationApproach(wt, vals, n, maxWeight) << endl;
    cout << "Result (Tabulation): "
         << tabulationApproach(wt, vals, n, maxWeight) << endl;
    cout << "Result (Optimal): " << optimalApproach(wt, vals, n, maxWeight)
         << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<int> weight, vector<int> value, int n,
                        int maxWeight) {
  vector<vector<int>> dp(n, vector<int>(maxWeight + 1, -1));

  return solve(dp, weight, value, maxWeight, 0);
}

int solve(vector<vector<int>>& dp, vector<int>& weight, vector<int>& value,
          int maxW, int i) {
  if (i == value.size()) {
    return 0;
  }
  if (dp[i][maxW] != -1) return dp[i][maxW];

  int val1 = 0;
  if (maxW >= weight[i]) {
    val1 = solve(dp, weight, value, maxW - weight[i], i + 1) + value[i];
  }
  int val2 = solve(dp, weight, value, maxW, i + 1);

  dp[i][maxW] = max(val1, val2);
  return dp[i][maxW];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<int> weight, vector<int> value, int n,
                       int maxWeight) {
  vector<vector<int>> dp(n + 1, vector<int>(maxWeight + 1, 0));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= maxWeight; j++) {
      int exclude = dp[i - 1][j];
      int include = 0;
      if (j >= weight[i - 1]) {
        include = dp[i - 1][j - weight[i - 1]] + value[i - 1];
      }

      dp[i][j] = max(include, exclude);
    }
  }

  return dp[n][maxWeight];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(vector<int> weight, vector<int> value, int n,
                    int maxWeight) {
  vector<int> val(maxWeight + 1, 0);

  for (int i = 1; i <= n; i++) {
    vector<int> dp = val;
    for (int j = 1; j <= maxWeight; j++) {
      int exclude = dp[j];
      int include = 0;
      if (j >= weight[i - 1]) {
        include = dp[j - weight[i - 1]] + value[i - 1];
      }

      val[j] = max(include, exclude);
    }
  }

  return val[maxWeight];
}
