/*
 * Problem: Count Square Submatrices with All Ones (LeetCode #1277)
 * Link:
 * https://leetcode.com/problems/count-square-submatrices-with-all-ones/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This is a bottom-up DP approach (tabulation). The logic is very
 *           similar to the "Maximal Square" problem. We create a 2D DP table
 *           where `dp[i][j]` stores the side length of the largest square of
 *           '1's that has its bottom-right corner at `matrix[i-1][j-1]`.
 *           The key difference is that a value of `k` in `dp[i][j]` means
 *           there are `k` squares ending at that cell (of sizes 1x1, 2x2,
 *           ..., kxk). Therefore, we sum up all values in the DP table to get
 *           the total count.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N^2)
 */
int tabulationApproach(vector<vector<int>>& matrix);

/**
 * Approach: This is a space-optimized version of the tabulation approach.
 *           To calculate the values for the current row, we only need the
 *           values from the previous row. We use a single 1D array `dp` to
 *           store the current row's results.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(M), where M is the number of columns.
 */
int optimalApproach(vector<vector<int>>& matrix);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int m, n;
    cin >> m >> n;

    vector<vector<int>> matrix(m, vector<int>(n));
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++) cin >> matrix[i][j];

    cout << "Matrix: [ ";
    for (auto row : matrix) {
      cout << "[ ";
      for (int i : row) {
        cout << i << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "Submatrices (Tabulation): " << tabulationApproach(matrix) << endl;
    cout << "Submatrices (Optimal): " << optimalApproach(matrix) << endl;

    cout << endl;
  }

  return 0;
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<vector<int>>& matrix) {
  int m = matrix.size();
  int n = matrix[0].size();

  vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
  int count = 0;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (matrix[i - 1][j - 1]) {
        dp[i][j] = 1 + min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
        count += dp[i][j];
      }
    }
  }

  return count;
}

//-----------------------------OPTIMAL APPROACH---------------------------------
int optimalApproach(vector<vector<int>>& matrix) {
  int m = matrix.size();
  int n = matrix[0].size();

  vector<int> dp(n + 1, 0);
  int count = 0;
  for (int i = 1; i <= m; i++) {
    vector<int> prev = dp;
    for (int j = 1; j <= n; j++) {
      if (matrix[i - 1][j - 1]) {
        dp[j] = 1 + min({prev[j - 1], prev[j], dp[j - 1]});
        count += dp[j];
      } else {
        dp[j] = 0;
      }
    }
  }

  return count;
}
