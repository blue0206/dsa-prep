/*
 * Problem: Triangle (LeetCode #120)
 * Link: https://leetcode.com/problems/triangle/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). The minimum path sum
 *           to reach cell (r, i) is `triangle[r][i]` plus the minimum of the
 *           path sums from the two possible parent cells in the row above:
 *           (r-1, i) and (r-1, i-1). We use a recursive function and a 2D DP
 *           table to store results and avoid re-computation.
 *
 * Time Complexity: O(N^2), where N is the number of rows.
 * Space Complexity: O(N^2) for the DP table + O(N) for recursion stack.
 */
int memoizationApproach(vector<vector<int>>& triangle);
int pathSum(vector<vector<int>>& triangle, vector<vector<int>>& dp, int r,
            int i);

/**
 * Approach: This is a bottom-up DP approach (tabulation). We build a 2D DP
 *           table where `dp[i][j]` stores the minimum path sum to reach cell
 *           (i, j). We iterate from the top row downwards, calculating each
 *           cell's value based on the previously computed values from the row
 *           above. The final answer is the minimum value in the last row of
 *           the DP table.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N^2)
 */
int tabulationApproach(vector<vector<int>>& triangle);

/**
 * Approach: This is a space-optimized version that works from the bottom up.
 *           We use a single 1D array, initialized with the values of the last
 *           row of the triangle. We then iterate upwards, and for each row, we
 *           update the 1D array in place. `dp[j]` becomes the minimum path sum
 *           starting from `triangle[i][j]`. The final answer is in `dp[0]`.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N), where N is the number of rows.
 */
int optimalApproach(vector<vector<int>>& triangle);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<vector<int>> triangle(n);
    for (int i = 0; i < n; i++) {
      triangle[i].resize(i + 1);
      for (int j = 0; j <= i; j++) {
        cin >> triangle[i][j];
      }
    }

    cout << "Triangle: [ ";
    for (auto row : triangle) {
      cout << "[ ";
      for (int val : row) {
        cout << val << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "Min Path Sum (Memoization): " << memoizationApproach(triangle)
         << endl;
    cout << "Min Path Sum (Tabulation): " << tabulationApproach(triangle)
         << endl;
    cout << "Min Path Sum (Optimal): " << optimalApproach(triangle) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<vector<int>>& triangle) {
  int rows = triangle.size();
  vector<vector<int>> dp(rows);
  for (int i = 0; i < rows; i++) {
    int m = triangle[i].size();
    dp[i].assign(m, -1);
  }

  int minSum = INT_MAX;
  for (int i = 0; i < triangle[rows - 1].size(); i++) {
    minSum = min(minSum, pathSum(triangle, dp, rows - 1, i));
  }

  return minSum;
}

int pathSum(vector<vector<int>>& triangle, vector<vector<int>>& dp, int r,
            int i) {
  if (r < 0 || i < 0 || i >= triangle[r].size()) {
    return INT_MAX;
  }
  if (r == 0) {
    return triangle[0][0];
  }
  if (dp[r][i] != -1) return dp[r][i];

  dp[r][i] = min(pathSum(triangle, dp, r - 1, i),
                 pathSum(triangle, dp, r - 1, i - 1)) +
             triangle[r][i];
  return dp[r][i];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<vector<int>>& triangle) {
  int rows = triangle.size();
  if (rows == 1) return triangle[0][0];

  vector<vector<int>> dp(rows);
  for (int i = 0; i < rows; i++) {
    int m = triangle[i].size();
    dp[i].assign(m, -1);
  }

  dp[0][0] = triangle[0][0];
  int minSum = INT_MAX;
  for (int i = 1; i < rows; i++) {
    for (int j = 0; j < triangle[i].size(); j++) {
      int val = triangle[i][j];
      if (j == 0) {
        val += dp[i - 1][j];
      } else if (j == triangle[i].size() - 1) {
        val += dp[i - 1][j - 1];
      } else {
        val += min(dp[i - 1][j], dp[i - 1][j - 1]);
      }

      dp[i][j] = val;
      if (i == rows - 1) {
        minSum = min(minSum, dp[i][j]);
      }
    }
  }

  return minSum;
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(vector<vector<int>>& triangle) {
  int rows = triangle.size();
  if (rows == 1) return triangle[0][0];

  vector<int> dp = triangle.back();
  for (int i = rows - 2; i >= 0; i--) {
    for (int j = 0; j < triangle[i].size(); j++) {
      dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
    }
  }

  return dp[0];
}
