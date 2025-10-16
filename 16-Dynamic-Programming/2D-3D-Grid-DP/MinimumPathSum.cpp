/*
 * Problem: Minimum Path Sum (LeetCode #64)
 * Link: https://leetcode.com/problems/minimum-path-sum/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). The minimum path sum
 *           to reach cell (r, c) is the value of the cell itself plus the
 *           minimum of the path sums from the cell above (r-1, c) and the
 *           cell to the left (r, c-1). We use a recursive function and a 2D DP
 *           table to store results and avoid re-computation.
 *
 * Time Complexity: O(M * N)
 * Space Complexity: O(M * N) for the DP table + O(M + N) for recursion stack.
 */
int memoizationApproach(vector<vector<int>>& grid);
int minPath(vector<vector<int>>& grid, vector<vector<int>>& dp, int r, int c);

/**
 * Approach: This is a bottom-up DP approach (tabulation). We create a 2D DP
 *           table where `dp[i][j]` stores the minimum path sum to reach cell
 *           (i, j). We iterate through the grid, and for each cell, we
 *           calculate its value based on the previously computed values from
 *           the cells above and to the left.
 *
 * Time Complexity: O(M * N)
 * Space Complexity: O(M * N)
 */
int tabulationApproach(vector<vector<int>>& grid);

/**
 * Approach: This is a space-optimized version of the tabulation approach.
 *           To calculate the minimum path sums for the current row, we only
 *           need the results from the previous row. We can use a single 1D
 *           array to store the previous row's path sums and update it to
 *           compute the current row's sums.
 *
 * Time Complexity: O(M * N)
 * Space Complexity: O(N)
 */
int optimalApproach(vector<vector<int>>& grid);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int m, n;
    cin >> m >> n;

    vector<vector<int>> grid(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
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

    cout << "Min Path Sum (Memoization): " << memoizationApproach(grid) << endl;
    cout << "Min Path Sum (Tabulation): " << tabulationApproach(grid) << endl;
    cout << "Min Path Sum (Optimal): " << optimalApproach(grid) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<vector<int>>& grid) {
  vector<vector<int>> dp(grid.size(), vector<int>(grid[0].size(), -1));
  return minPath(grid, dp, grid.size() - 1, grid[0].size() - 1);
}

int minPath(vector<vector<int>>& grid, vector<vector<int>>& dp, int r, int c) {
  if (r < 0 || c < 0) return INT_MAX;
  if (r == 0 && c == 0) {
    return grid[r][c];
  }
  if (dp[r][c] != -1) return dp[r][c];

  dp[r][c] = min(minPath(grid, dp, r - 1, c), minPath(grid, dp, r, c - 1)) +
             grid[r][c];
  return dp[r][c];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<vector<int>>& grid) {
  vector<vector<int>> dp(grid.size(), vector<int>(grid[0].size(), -1));

  for (int r = 0; r < grid.size(); r++) {
    for (int c = 0; c < grid[0].size(); c++) {
      int val = grid[r][c];
      if (r - 1 >= 0 && c - 1 >= 0) {
        val += min(dp[r - 1][c], dp[r][c - 1]);
      } else if (r - 1 >= 0) {
        val += dp[r - 1][c];
      } else if (c - 1 >= 0) {
        val += dp[r][c - 1];
      }

      dp[r][c] = val;
    }
  }

  return dp[grid.size() - 1][grid[0].size() - 1];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(vector<vector<int>>& grid) {
  int n = grid[0].size();
  vector<int> dp(n, 0);

  dp[0] = grid[0][0];
  for (int i = 1; i < n; i++) {
    dp[i] = grid[0][i] + dp[i - 1];
  }

  for (int r = 1; r < grid.size(); r++) {
    int prev = INT_MAX;
    for (int c = 0; c < n; c++) {
      dp[c] = min(dp[c], prev) + grid[r][c];
      prev = dp[c];
    }
  }

  return dp[n - 1];
}
