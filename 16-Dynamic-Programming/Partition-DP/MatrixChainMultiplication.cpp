/*
 * Problem: Matrix Chain Multiplication
 * Link:
 * https://www.geeksforgeeks.org/problems/matrix-chain-multiplication0303/1
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). This is a classic
 *           Partition DP problem. The function `solve(i, j)` finds the minimum
 *           operations to multiply matrices from index `i` to `j`. We try
 *           every possible partition point `k` between `i` and `j`. For each
 *           `k`, the cost is the sum of costs for the subproblems `(i, k)` and
 *           `(k+1, j)`, plus the cost of multiplying the two resulting
 *           matrices.
 *
 * Time Complexity: O(N^3)
 * Space Complexity: O(N^2) for DP table + O(N) for recursion stack.
 */
int memoizationApproach(vector<int>& arr);
int solve(vector<vector<int>>& dp, const vector<int>& arr, int i, int j);

/**
 * Approach: This is the tabulation (bottom-up) version. We fill a 2D DP table
 *           where `dp[i][j]` stores the minimum cost for the chain from `i` to
 *           `j`. The table is filled by iterating over chain lengths, from
 *           small to large, ensuring that subproblems are solved before they
 *           are needed.
 *
 * Time Complexity: O(N^3)
 * Space Complexity: O(N^2)
 */
int tabulationApproach(vector<int>& arr);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Input Array: [ ";
    for (int i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Minimum Operations (Memoization): " << memoizationApproach(nums)
         << endl;
    cout << "Minimum Operations (Tabulation): " << tabulationApproach(nums)
         << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<int>& arr) {
  int n = arr.size();

  vector<vector<int>> dp(n, vector<int>(n, -1));
  return solve(dp, arr, 1, n - 1);
}

int solve(vector<vector<int>>& dp, const vector<int>& arr, int i, int j) {
  if (i >= j) return 0;
  if (dp[i][j] != -1) return dp[i][j];

  int minOps = INT_MAX;
  for (int k = i; k < j; k++) {
    int ops = solve(dp, arr, i, k) + solve(dp, arr, k + 1, j) +
              (arr[i - 1] * arr[k] * arr[j]);
    minOps = min(minOps, ops);
  }

  dp[i][j] = minOps;
  return dp[i][j];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<int>& arr) {
  int n = arr.size();

  vector<vector<int>> dp(n, vector<int>(n, 0));
  for (int i = n - 1; i >= 1; i--) {
    for (int j = i + 1; j < n; j++) {
      int minOps = INT_MAX;
      for (int k = i; k < j; k++) {
        int ops = dp[i][k] + dp[k + 1][j] + (arr[i - 1] * arr[k] * arr[j]);
        minOps = min(minOps, ops);
      }
      dp[i][j] = minOps;
    }
  }

  return dp[1][n - 1];
}
