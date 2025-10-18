/*
 * Problem: Unbounded Knapsack
 * Link:
 * https://www.geeksforgeeks.org/problems/knapsack-with-duplicate-items4201/1
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). The state is defined
 *           by `dp[i][capacity]`, representing the maximum value that can be
 *           obtained from items `i` to `n-1` with the given `capacity`. For
 *           each item `i`, we have two choices:
 *           1. Don't pick item `i`: `solve(..., capacity, i + 1)`
 *           2. Pick item `i`: `val[i] + solve(..., capacity - wt[i], i)`. We
 *              stay at index `i` because we can pick the same item again.
 *
 * Time Complexity: O(N * capacity)
 * Space Complexity: O(N * capacity) for DP table + O(N + capacity) for
 * recursion stack.
 */
int memoizationApproach(vector<int>& val, vector<int>& wt, int capacity);
int solve(vector<vector<int>>& dp, vector<int>& val, vector<int>& wt,
          int capacity, int i);

/**
 * Approach: This is a space-optimized bottom-up DP approach (tabulation). We
 *           use a 1D array `dp` where `dp[i]` stores the maximum value for a
 *           knapsack of capacity `i`. We iterate through each capacity from 1
 *           to `W`, and for each capacity, we try to improve the result by
 *           including each available item.
 *
 * Time Complexity: O(N * capacity)
 * Space Complexity: O(capacity)
 */
int tabulationApproach(vector<int>& val, vector<int>& wt, int capacity);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, capacity;
    cin >> n >> capacity;

    vector<int> wt(n), vals(n);
    for (int i = 0; i < n; i++) cin >> wt[i];
    for (int i = 0; i < n; i++) cin >> vals[i];

    cout << "Capacity: " << capacity << endl;
    cout << "Weights: [ ";
    for (int val : wt) cout << val << " ";
    cout << "]" << endl;
    cout << "Value: [ ";
    for (int val : vals) cout << val << " ";
    cout << "]" << endl;

    cout << "Result (Memoization): " << memoizationApproach(vals, wt, capacity)
         << endl;
    cout << "Result (Tabulation): " << tabulationApproach(vals, wt, capacity)
         << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<int>& val, vector<int>& wt, int capacity) {
  int n = val.size();

  vector<vector<int>> dp(n, vector<int>(capacity + 1, -1));
  return solve(dp, val, wt, capacity, 0);
}

int solve(vector<vector<int>>& dp, vector<int>& val, vector<int>& wt,
          int capacity, int i) {
  if (i == val.size() || capacity == 0) return 0;
  if (dp[i][capacity] != -1) return dp[i][capacity];

  int p1 = 0;
  if (wt[i] <= capacity) {
    p1 = solve(dp, val, wt, capacity - wt[i], i) + val[i];
  }
  int p2 = solve(dp, val, wt, capacity, i + 1);

  dp[i][capacity] = max(p1, p2);
  return dp[i][capacity];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<int>& val, vector<int>& wt, int capacity) {
  int n = val.size();

  vector<int> dp(capacity + 1, 0);

  for (int i = 1; i <= capacity; i++) {
    for (int j = 0; j < wt.size(); j++) {
      if (i >= wt[j]) {
        int include = dp[i - wt[j]] + val[j];
        dp[i] = max(dp[i], include);
      }
    }
  }

  return dp[capacity];
}
