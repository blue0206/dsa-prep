/*
 * Problem: Longest Common Subsequence (LeetCode #1143)
 * Link: https://leetcode.com/problems/longest-common-subsequence/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). The state is defined
 *           by `dp[i][j]`, representing the length of the LCS for `text1[0..i]`
 *           and `text2[0..j]`. The recurrence relation is:
 *           - If `text1[i] == text2[j]`, LCS = `1 + solve(i-1, j-1)`.
 *           - Otherwise, LCS = `max(solve(i-1, j), solve(i, j-1))`.
 *
 * Time Complexity: O(N * M)
 * Space Complexity: O(N * M) for DP table + O(N + M) for recursion stack.
 */
int memoizationApproach(string text1, string text2);
int solve(vector<vector<int>>& dp, string& text1, string& text2, int i, int j);

/**
 * Approach: This is a bottom-up DP approach (tabulation). We create a 2D DP
 *           table where `dp[i][j]` stores the length of the LCS for the first
 *           `i` characters of `text1` and the first `j` characters of `text2`.
 *           The table is filled iteratively based on the same recurrence
 *           relation as the memoization approach.
 *
 * Time Complexity: O(N * M)
 * Space Complexity: O(N * M)
 */
int tabulationApproach(string text1, string text2);

/**
 * Approach: This is a space-optimized version of the tabulation approach. To
 *           calculate the values for the current row `i`, we only need the
 *           values from the previous row `i-1`. We can use two 1D arrays to
 *           store the previous and current row's results, reducing space from
 *           O(N*M) to O(M).
 *
 * Time Complexity: O(N * M)
 * Space Complexity: O(M)
 */
int optimalApproach(string text1, string text2);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string text1, text2;
    cin >> text1 >> text2;

    cout << "Text 1: " << text1 << endl;
    cout << "Text 2: " << text2 << endl;

    cout << "LCS (Memoization): " << memoizationApproach(text1, text2) << endl;
    cout << "LCS (Tabulation): " << tabulationApproach(text1, text2) << endl;
    cout << "LCS (Optimal): " << optimalApproach(text1, text2) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(string text1, string text2) {
  int n1 = text1.length();
  int n2 = text2.length();

  vector<vector<int>> dp(n1, vector<int>(n2, -1));
  return solve(dp, text1, text2, n1 - 1, n2 - 1);
}

int solve(vector<vector<int>>& dp, string& text1, string& text2, int i, int j) {
  if (i < 0 || j < 0) {
    return 0;
  }
  if (dp[i][j] != -1) return dp[i][j];

  if (text1[i] == text2[j]) {
    dp[i][j] = solve(dp, text1, text2, i - 1, j - 1) + 1;
  } else {
    dp[i][j] = max(solve(dp, text1, text2, i - 1, j),
                   solve(dp, text1, text2, i, j - 1));
  }

  return dp[i][j];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(string text1, string text2) {
  int n1 = text1.length();
  int n2 = text2.length();

  vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));

  for (int i = 1; i <= n1; i++) {
    for (int j = 1; j <= n2; j++) {
      if (text1[i - 1] == text2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  return dp[n1][n2];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(string text1, string text2) {
  int n = text1.length();
  int m = text2.length();

  vector<int> lcs(m + 1, 0);

  for (int i = 1; i <= n; i++) {
    vector<int> dp = lcs;
    for (int j = 1; j <= m; j++) {
      if (text1[i - 1] == text2[j - 1]) {
        lcs[j] = dp[j - 1] + 1;
      } else {
        lcs[j] = max(dp[j], lcs[j - 1]);
      }
    }
  }

  return lcs[m];
}
