/*
 * Problem: Maximal Square (LeetCode #221)
 * Link: https://leetcode.com/problems/maximal-square/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This is a bottom-up DP approach (tabulation). We create a 2D DP
 *           table where `dp[i][j]` stores the side length of the largest
 *           square of '1's that has its bottom-right corner at
 *           `matrix[i-1][j-1]`. If `matrix[i-1][j-1]` is '1', the side length
 *           of the square is
 *           `1 + min(square_from_top, square_from_left, square_from_diagonal)`.
 *           This is because a square of side `k` requires squares of side `k-1`
 *           at its three adjacent neighbors.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N^2)
 */
int tabulationApproach(vector<int>& nums);

/**
 * Approach: This is a space-optimized version of the tabulation approach.
 *           To calculate the values for the current row `i`, we only need the
 *           values from the previous row `i-1`. We use a single 1D array `dp`
 *           to store the current row's results, while carefully preserving the
 *           previous row's diagonal element needed for the calculation.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(M), where M is the number of columns.
 */
int optimalApproach(vector<vector<char>>& matrix);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, m;
    cin >> n >> m;

    vector<vector<char>> matrix(n, vector<char>(m));
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) cin >> matrix[i][j];

    cout << "Matrix: [ ";
    for (auto row : matrix) {
      cout << "[ ";
      for (char c : row) {
        cout << c << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "Maximal Square (Tabulation): " << tabulationApproach(matrix)
         << endl;
    cout << "Maximal Square (Optimal): " << optimalApproach(matrix) << endl;

    cout << endl;
  }

  return 0;
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<vector<char>>& matrix) {
  int n = matrix.size();
  int m = matrix[0].size();

  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
  int maxSide = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (matrix[i - 1][j - 1] == '1') {
        dp[i][j] = 1 + min({dp[i - 1][j], dp[i - 1][j - 1], dp[i][j - 1]});
        maxSide = max(maxSide, dp[i][j]);
      }
    }
  }

  return (maxSide * maxSide);
}

//-----------------------------OPTIMAL APPROACH---------------------------------
int optimalApproach(vector<vector<char>>& matrix) {
  int n = matrix.size();
  int m = matrix[0].size();

  vector<int> dp(m + 1, 0);

  int maxSide = 0;
  for (int i = 1; i <= n; i++) {
    vector<int> prev = dp;
    for (int j = 1; j <= m; j++) {
      if (matrix[i - 1][j - 1] == '1') {
        dp[j] = 1 + min({prev[j], prev[j - 1], dp[j - 1]});
      } else {
        dp[j] = (matrix[i - 1][j - 1] == '1');
      }
      maxSide = max(maxSide, dp[j]);
    }
  }

  return (maxSide * maxSide);
}
