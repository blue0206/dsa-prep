/*
 * Problem: Cherry Pickup II (LeetCode #1463)
 * Link: https://leetcode.com/problems/cherry-pickup-ii/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). Since both robots
 *           move down one row at a time, their states can be synchronized by
 *           the current row `r`. The DP state is defined by `dp[r][c1][c2]`,
 *           representing the maximum cherries collected when robot 1 is at
 *           (r, c1) and robot 2 is at (r, c2). The function recursively
 *           explores all 9 possible next moves for the pair of robots and
 *           maximizes the result.
 *
 * Time Complexity: O(N * M * M * 9) ~ O(N * M^2)
 * Space Complexity: O(N * M * M) for the DP table + O(N) for recursion stack.
 */
int memoizationApproach(vector<vector<int>>& grid);
int solve(vector<vector<int>>& grid, vector<vector<vector<int>>>& dp, int n,
          int m, int r, int c1, int c2);

/**
 * Approach: This is a bottom-up DP approach (tabulation). We create a 3D DP
 *           table `dp[r][c1][c2]` and fill it from the last row up to the
 *           first. The base case is the last row of the grid. For each cell
 *           (r, c1, c2), we calculate the max cherries by considering all 9
 *           possible previous states from the row below (r+1).
 *
 * Time Complexity: O(N * M * M * 9) ~ O(N * M^2)
 * Space Complexity: O(N * M * M)
 */
int tabulationApproach(vector<vector<int>>& grid);

/**
 * Approach: This is a space-optimized version of the tabulation approach.
 *           To calculate the DP values for the current row `r`, we only need
 *           the values from the row below, `r+1`. We can reduce the 3D DP
 *           table to two 2D tables: one for the previous row's results (`temp`)
 *           and one for the current row's results (`dp`). This reduces the
 *           space complexity significantly.
 *
 * Time Complexity: O(N * M * M * 9) ~ O(N * M^2)
 * Space Complexity: O(M * M)
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

    cout << "Max Cherries (Memoization): " << memoizationApproach(grid) << endl;
    cout << "Max Cherries (Tabulation): " << tabulationApproach(grid) << endl;
    cout << "Max Cherries (Optimal): " << optimalApproach(grid) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<vector<int>>& grid) {
  int n = grid.size();
  int m = grid[0].size();

  vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, -1)));
  return solve(grid, dp, n, m, 0, 0, m - 1);
}

int solve(vector<vector<int>>& grid, vector<vector<vector<int>>>& dp, int n,
          int m, int r, int c1, int c2) {
  if (r == n - 1) {
    if (c1 == c2) return grid[r][c1];
    return grid[r][c1] + grid[r][c2];
  }
  if (dp[r][c1][c2] != -1) return dp[r][c1][c2];

  int cherries = (c1 == c2) ? grid[r][c1] : grid[r][c1] + grid[r][c2];
  int maxSum = 0;

  int dx[9] = {0, 0, 0, -1, -1, -1, 1, 1, 1};
  int dy[9] = {1, 0, -1, 1, 0, -1, 1, 0, -1};
  for (int i = 0; i < 9; i++) {
    int nc1 = c1 + dx[i];
    int nc2 = c2 + dy[i];

    if (nc1 >= 0 && nc1 < m && nc2 >= 0 && nc2 < m) {
      int sum = solve(grid, dp, n, m, r + 1, nc1, nc2);
      maxSum = max(maxSum, sum);
    }
  }

  dp[r][c1][c2] = maxSum + cherries;
  return dp[r][c1][c2];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<vector<int>>& grid) {
  int n = grid.size();
  int m = grid[0].size();

  vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, 0)));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      if (i == j) {
        dp[n - 1][i][j] = grid[n - 1][i];
      } else {
        dp[n - 1][i][j] = grid[n - 1][i] + grid[n - 1][j];
      }
    }
  }

  int dx[9] = {0, 0, 0, -1, -1, -1, 1, 1, 1};
  int dy[9] = {1, 0, -1, 1, 0, -1, 1, 0, -1};
  for (int r = n - 2; r >= 0; r--) {
    for (int c1 = 0; c1 < m; c1++) {
      for (int c2 = 0; c2 < m; c2++) {
        int val = grid[r][c1];
        if (c1 != c2) {
          val += grid[r][c2];
        }

        int maxSum = 0;
        for (int k = 0; k < 9; k++) {
          int nc1 = c1 + dx[k];
          int nc2 = c2 + dy[k];

          if (nc1 >= 0 && nc1 < m && nc2 >= 0 && nc2 < m) {
            int sum = dp[r + 1][nc1][nc2];
            maxSum = max(maxSum, sum);
          }
        }

        dp[r][c1][c2] = maxSum + val;
      }
    }
  }

  return dp[0][0][m - 1];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(vector<vector<int>>& grid) {
  int n = grid.size();
  int m = grid[0].size();

  vector<vector<int>> dp(m, vector<int>(m, 0));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      if (i == j) {
        dp[i][j] = grid[n - 1][i];
      } else {
        dp[i][j] = grid[n - 1][i] + grid[n - 1][j];
      }
    }
  }

  int dx[9] = {0, 0, 0, -1, -1, -1, 1, 1, 1};
  int dy[9] = {1, 0, -1, 1, 0, -1, 1, 0, -1};
  for (int r = n - 2; r >= 0; r--) {
    vector<vector<int>> temp = dp;

    for (int c1 = 0; c1 < m; c1++) {
      for (int c2 = 0; c2 < m; c2++) {
        int val = grid[r][c1];
        if (c1 != c2) {
          val += grid[r][c2];
        }

        int maxSum = 0;
        for (int k = 0; k < 9; k++) {
          int nc1 = c1 + dx[k];
          int nc2 = c2 + dy[k];

          if (nc1 >= 0 && nc1 < m && nc2 >= 0 && nc2 < m) {
            int sum = temp[nc1][nc2];
            maxSum = max(maxSum, sum);
          }
        }

        dp[c1][c2] = maxSum + val;
      }
    }
  }

  return dp[0][m - 1];
}
