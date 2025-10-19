/*
 * Problem: Edit Distance (LeetCode #72)
 * Link: https://leetcode.com/problems/edit-distance/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). The state `dp[i][j]`
 *           stores the minimum operations to convert `word1[0...i]` to
 *           `word2[0...j]`. The recurrence relation is:
 *           - If `word1[i] == word2[j]`, no operation is needed, so the cost is
 *             `solve(i-1, j-1)`.
 *           - If they differ, we take the minimum of three operations:
 *             1. Insert: `1 + solve(i, j-1)`
 *             2. Delete: `1 + solve(i-1, j)`
 *             3. Replace: `1 + solve(i-1, j-1)`
 *
 * Time Complexity: O(N * M)
 * Space Complexity: O(N * M) for DP table + O(N + M) for recursion stack.
 */
int memoizationApproach(string word1, string word2);
int solve(vector<vector<int>>& dp, string& text1, string& text2, int i, int j);

/**
 * Approach: This is the tabulation (bottom-up) version. It builds a 2D DP
 *           table where `dp[i][j]` stores the minimum operations to convert
 *           the first `i` characters of `word1` to the first `j` characters of
 *           `word2`. The table is filled iteratively based on the same
 *           recurrence relation as the memoization approach.
 *
 * Time Complexity: O(N * M)
 * Space Complexity: O(N * M)
 */
int tabulationApproach(string word1, string word2);

/**
 * Approach: This is a space-optimized version of the tabulation approach.
 *           Since `dp[i]` only depends on `dp[i-1]`, we can use two 1D arrays
 *           (one for the previous row, one for the current) to reduce space.
 *
 * Time Complexity: O(N * M)
 * Space Complexity: O(M)
 */
int optimalApproach(string word1, string word2);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string text1, text2;
    cin >> text1 >> text2;

    cout << "String 1: " << text1 << endl;
    cout << "String 2: " << text2 << endl;

    cout << "Result (Memoization): " << memoizationApproach(text1, text2)
         << endl;
    cout << "Result (Tabulation): " << tabulationApproach(text1, text2) << endl;
    cout << "Result (Optimal): " << optimalApproach(text1, text2) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(string word1, string word2) {
  int n = word1.length();
  int m = word2.length();

  vector<vector<int>> dp(n, vector<int>(m, -1));
  return solve(dp, word1, word2, n - 1, m - 1);
}

int solve(vector<vector<int>>& dp, string& word1, string& word2, int i, int j) {
  if (i < 0) return j + 1;
  if (j < 0) return i + 1;
  if (dp[i][j] != -1) return dp[i][j];

  if (word1[i] == word2[j]) {
    dp[i][j] = solve(dp, word1, word2, i - 1, j - 1);
  } else {
    // Insert
    int count1 = solve(dp, word1, word2, i, j - 1) + 1;
    // Replace
    int count2 = solve(dp, word1, word2, i - 1, j - 1) + 1;
    // Delete
    int count3 = solve(dp, word1, word2, i - 1, j) + 1;

    dp[i][j] = min({count1, count2, count3});
  }

  return dp[i][j];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(string word1, string word2) {
  int n = word1.length();
  int m = word2.length();

  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
  for (int i = 0; i <= n; i++) dp[i][0] = i;
  for (int i = 0; i <= m; i++) dp[0][i] = i;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (word1[i - 1] == word2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        int replaceCost = dp[i - 1][j - 1] + 1;
        int deleteCost = dp[i - 1][j] + 1;
        int insertCost = dp[i][j - 1] + 1;

        dp[i][j] = min({replaceCost, deleteCost, insertCost});
      }
    }
  }

  return dp[n][m];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(string word1, string word2) {
  int n = word1.length();
  int m = word2.length();

  vector<int> dp1(m + 1, 0);
  for (int i = 0; i <= m; i++) dp1[i] = i;

  for (int i = 1; i <= n; i++) {
    vector<int> dp2 = dp1;
    dp1[0] = i;
    for (int j = 1; j <= m; j++) {
      if (word1[i - 1] == word2[j - 1]) {
        dp1[j] = dp2[j - 1];
      } else {
        int replaceCost = dp2[j - 1] + 1;
        int deleteCost = dp2[j] + 1;
        int insertCost = dp1[j - 1] + 1;

        dp1[j] = min({replaceCost, deleteCost, insertCost});
      }
    }
  }

  return dp1[m];
}
