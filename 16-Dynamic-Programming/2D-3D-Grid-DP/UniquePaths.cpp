/*
 * Problem: Unique Paths (LeetCode #62)
 * Link: https://leetcode.com/problems/unique-paths/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). The number of unique
 *           paths to reach the bottom-right corner from cell (r, c) is the sum
 *           of paths from the cell below (r+1, c) and the cell to the right
 *           (r, c+1). We use a DP table to store the results for each cell to
 *           avoid re-computation.
 *
 * Time Complexity: O(M * N)
 * Space Complexity: O(M * N) for DP table + O(M + N) for recursion stack.
 */
int memoizationApproach(int m, int n);
int findPaths(vector<vector<int>>& dp, int m, int n, int r, int c);

/**
 * Approach: This is a bottom-up DP approach (tabulation). We create a DP table
 *           where `dp[i][j]` stores the number of unique paths to reach cell
 *           (i, j). The value for each cell is the sum of the paths from the
 *           cell above (`dp[i-1][j]`) and the cell to the left (`dp[i][j-1]`).
 *
 * Time Complexity: O(M * N)
 * Space Complexity: O(M * N)
 */
int tabulationApproach(int m, int n);

/**
 * Approach: This is a space-optimized version of the tabulation approach.
 *           To calculate the values for the current row, we only need the
 *           values from the previous row. We can use a single 1D array `dp`
 *           to represent the previous row and update it in place to calculate
 *           the current row.
 *
 * Time Complexity: O(M * N)
 * Space Complexity: O(N)
 */
int optimalApproach(int m, int n);

/**
 * Approach: This is a purely mathematical approach. To get from the top-left
 *           to the bottom-right of an M x N grid, we must make a total of
 *           (M-1) down moves and (N-1) right moves. The total number of moves
 *           is (M+N-2). The problem is equivalent to finding the number of
 *           ways to choose (N-1) right moves out of (M+N-2) total moves, which
 *           is given by the binomial coefficient C(M+N-2, N-1).
 *
 * Time Complexity: O(min(M, N))
 * Space Complexity: O(1)
 */
int combinatorialApproach(int m, int n);
int nCr(int n, int r);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int m, n;
    cin >> m >> n;

    cout << "m: " << m << ", n: " << n << endl;

    cout << "Unique Paths (Memoization): " << memoizationApproach(m, n) << endl;
    cout << "Unique Paths (Tabulation): " << tabulationApproach(m, n) << endl;
    cout << "Unique Paths (Optimal): " << optimalApproach(m, n) << endl;
    cout << "Unique Paths (Combinatorial): " << combinatorialApproach(m, n)
         << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(int m, int n) {
  vector<vector<int>> dp(m, vector<int>(n, -1));
  return findPaths(dp, m, n, 0, 0);
}

int findPaths(vector<vector<int>>& dp, int m, int n, int r, int c) {
  if (r >= m || c >= n) return 0;
  if (r == m - 1 && c == n - 1) return 1;
  if (dp[r][c] != -1) return dp[r][c];

  dp[r][c] = findPaths(dp, m, n, r, c + 1) + findPaths(dp, m, n, r + 1, c);

  return dp[r][c];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(int m, int n) {
  vector<vector<int>> dp(m, vector<int>(n, 0));

  dp[0][0] = 1;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (i - 1 >= 0) dp[i][j] += dp[i - 1][j];
      if (j - 1 >= 0) dp[i][j] += dp[i][j - 1];
    }
  }

  return dp[m - 1][n - 1];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(int m, int n) {
  vector<int> dp(n, 1);

  for (int i = 1; i < m; i++) {
    int prev = 0;
    for (int j = 0; j < n; j++) {
      dp[j] += prev;
      prev = dp[j];
    }
  }

  return dp[n - 1];
}

//-------------------------COMBINATORIAL APPROACH-------------------------------
int combinatorialApproach(int m, int n) { return nCr(m + n - 2, n - 1); }

int nCr(int n, int r) {
  if (r > n) return 0;

  if (n - r < r) r = n - r;

  long long ans = 1;
  for (int i = 0; i < r; i++) {
    ans *= (long long)(n - i);
    ans /= (i + 1);
  }

  return (int)ans;
}
