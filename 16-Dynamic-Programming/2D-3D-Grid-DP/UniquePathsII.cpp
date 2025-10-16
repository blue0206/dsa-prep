/*
 * Problem: Unique Paths II (LeetCode #63)
 * Link: https://leetcode.com/problems/unique-paths-ii/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). It's an extension of
 *           the standard Unique Paths problem. The recurrence relation is the
 *           same (paths to (r,c) = paths from (r+1,c) + paths from (r,c+1)),
 *           but with an added condition: if a cell contains an obstacle, the
 *           number of paths through it is 0.
 *
 * Time Complexity: O(M * N)
 * Space Complexity: O(M * N) for the DP table + O(M + N) for recursion stack.
 */
int memoizationApproach(vector<vector<int>>& obstacleGrid);
int findPaths(vector<vector<int>>& obstacleGrid, vector<vector<int>>& dp, int n,
              int m, int r, int c);

/**
 * Approach: This is a bottom-up DP approach (tabulation). We build a DP table
 *           where `dp[i][j]` stores the number of unique paths to reach cell
 *           (i, j). The logic is the same as Unique Paths I, but if
 *           `obstacleGrid[i][j]` is 1, we set `dp[i][j]` to 0.
 *
 * Time Complexity: O(M * N)
 * Space Complexity: O(M * N)
 */
int tabulationApproach(vector<vector<int>>& obstacleGrid);

/**
 * Approach: This is a space-optimized version of the tabulation approach.
 *           To calculate the paths for the current row, we only need the
 *           results from the previous row. We use a single 1D array to store
 *           the previous row's path counts and update it for each new row. If
 *           a cell in the current row has an obstacle, its path count is set
 *           to 0.
 *
 * Time Complexity: O(M * N)
 * Space Complexity: O(N)
 */
int optimalApproach(vector<vector<int>>& obstacleGrid);

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

    cout << "Unique Paths (Memoization): " << memoizationApproach(grid) << endl;
    cout << "Unique Paths (Tabulation): " << tabulationApproach(grid) << endl;
    cout << "Unique Paths (Optimal): " << optimalApproach(grid) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<vector<int>>& obstacleGrid) {
  int n = obstacleGrid.size();
  int m = obstacleGrid[0].size();
  if (obstacleGrid[n - 1][m - 1] == 1) return 0;

  vector<vector<int>> dp(n, vector<int>(m, -1));
  return findPaths(obstacleGrid, dp, n, m, 0, 0);
}

int findPaths(vector<vector<int>>& obstacleGrid, vector<vector<int>>& dp, int n,
              int m, int r, int c) {
  if (r >= n || c >= m || obstacleGrid[r][c]) return 0;
  if (r == n - 1 && c == m - 1) return 1;
  if (dp[r][c] != -1) return dp[r][c];

  dp[r][c] = findPaths(obstacleGrid, dp, n, m, r + 1, c) +
             findPaths(obstacleGrid, dp, n, m, r, c + 1);
  return dp[r][c];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<vector<int>>& obstacleGrid) {
  int n = obstacleGrid.size();
  int m = obstacleGrid[0].size();
  if (obstacleGrid[n - 1][m - 1] || obstacleGrid[0][0]) return 0;

  vector<vector<int>> dp(n, vector<int>(m, 0));

  dp[0][0] = 1;
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < m; c++) {
      if (obstacleGrid[r][c] != 1) {
        if (r - 1 >= 0) dp[r][c] += dp[r - 1][c];
        if (c - 1 >= 0) dp[r][c] += dp[r][c - 1];
      }
    }
  }

  return dp[n - 1][m - 1];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(vector<vector<int>>& obstacleGrid) {
  int n = obstacleGrid.size();
  int m = obstacleGrid[0].size();
  if (obstacleGrid[n - 1][m - 1] || obstacleGrid[0][0]) return 0;

  vector<int> dp(m, 0);
  for (int i = 0; i < m; i++) {
    if (obstacleGrid[0][i] != 1) {
      dp[i] = 1;
    } else {
      break;
    }
  }

  for (int r = 1; r < n; r++) {
    int prev = 0;
    for (int c = 0; c < m; c++) {
      if (obstacleGrid[r][c] != 1) {
        dp[c] += prev;
      } else {
        dp[c] = 0;
      }
      prev = dp[c];
    }
  }

  return dp[m - 1];
}
