/*
 * Problem: Minimum Falling Path Sum (LeetCode #931)
 * Link: https://leetcode.com/problems/minimum-falling-path-sum/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). The problem is to
 *           find the minimum path sum starting from any cell in the first row
 *           and ending in the last row. The recursive function `pathSum(r, c)`
 *           calculates the minimum falling path sum starting from cell (r, c).
 *           The result is the minimum of calling `pathSum` for all cells in
 *           the first row.
 *
 * Time Complexity: O(N*N)
 * Space Complexity: O(N*N) for the DP table + O(N) for recursion stack.
 */
int memoizationApproach(vector<vector<int>>& matrix);
int pathSum(vector<vector<int>>& matrix, vector<vector<int>>& dp, int n, int r,
            int c);

/**
 * Approach: This is a bottom-up DP approach (tabulation). We create a 2D DP
 *           table where `dp[i][j]` stores the minimum falling path sum ending
 *           at cell (i, j). We initialize the first row of `dp` with the first
 *           row of the matrix. Then, we iterate downwards, calculating each
 *           `dp[i][j]` based on the minimum of the three possible parent cells
 *           in the row above. The final answer is the minimum value in the
 *           last row of the DP table.
 *
 * Time Complexity: O(N*N)
 * Space Complexity: O(N*N)
 */
int tabulationApproach(vector<vector<int>>& matrix);

/**
 * Approach: This is a space-optimized version of the tabulation approach.
 *           To calculate the values for the current row `i`, we only need the
 *           values from the previous row `i-1`. We use a 1D array `dp` to
 *           store the previous row's results and a `temp` array to build the
 *           current row's results before updating `dp`.
 *
 * Time Complexity: O(N*N)
 * Space Complexity: O(N)
 */
int optimalApproach(vector<vector<int>>& matrix);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> grid[i][j];
      }
    }

    cout << "Grid: [ ";
    for (auto row : grid) {
      cout << "[ ";
      for (int val : row) {
        cout << val << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "Min Falling Path Sum (Memoization): " << memoizationApproach(grid)
         << endl;
    cout << "Min Falling Path Sum (Tabulation): " << tabulationApproach(grid)
         << endl;
    cout << "Min Falling Path Sum (Optimal): " << optimalApproach(grid) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<vector<int>>& matrix) {
  int n = matrix.size();

  vector<vector<int>> dp(n, vector<int>(n, -1));
  int minSum = INT_MAX;
  for (int i = 0; i < n; i++) {
    minSum = min(minSum, pathSum(matrix, dp, n, 0, i));
  }

  return minSum;
}

int pathSum(vector<vector<int>>& matrix, vector<vector<int>>& dp, int n, int r,
            int c) {
  if (c < 0 || c >= n) return INT_MAX;
  if (r == n - 1) return matrix[r][c];
  if (dp[r][c] != -1) return dp[r][c];

  int top = pathSum(matrix, dp, n, r + 1, c);
  int diagonal = min(pathSum(matrix, dp, n, r + 1, c - 1),
                     pathSum(matrix, dp, n, r + 1, c + 1));
  dp[r][c] = min(top, diagonal) + matrix[r][c];

  return dp[r][c];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<vector<int>>& matrix) {
  int n = matrix.size();
  if (n == 1) return matrix[0][0];

  vector<vector<int>> dp(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    dp[0][i] = matrix[0][i];
  }

  int minSum = INT_MAX;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int val = matrix[i][j];

      if (j == 0) {
        val += min(dp[i - 1][j], dp[i - 1][j + 1]);
      } else if (j == n - 1) {
        val += min(dp[i - 1][j], dp[i - 1][j - 1]);
      } else {
        val += min({dp[i - 1][j - 1], dp[i - 1][j], dp[i - 1][j + 1]});
      }

      dp[i][j] = val;
      if (i == n - 1) {
        minSum = min(minSum, dp[i][j]);
      }
    }
  }

  return minSum;
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(vector<vector<int>>& matrix) {
  int n = matrix.size();
  if (n == 1) return matrix[0][0];

  vector<int> dp = matrix.front();

  int minSum = INT_MAX;
  for (int i = 1; i < n; i++) {
    vector<int> temp = dp;
    for (int j = 0; j < n; j++) {
      int val = matrix[i][j];

      if (j == 0) {
        val += min(temp[j], temp[j + 1]);
      } else if (j == n - 1) {
        val += min(temp[j], temp[j - 1]);
      } else {
        val += min({temp[j - 1], temp[j], temp[j + 1]});
      }

      dp[j] = val;
      if (i == n - 1) {
        minSum = min(minSum, dp[j]);
      }
    }
  }

  return minSum;
}
