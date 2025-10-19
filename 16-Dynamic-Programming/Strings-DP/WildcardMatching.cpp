/*
 * Problem: Wildcard Matching (LeetCode #44)
 * Link: https://leetcode.com/problems/wildcard-matching/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). The state `dp[i][j]`
 *           stores whether `s[0...i]` matches `p[0...j]`. The recurrence is:
 *           - If `p[j] == '?'` or `s[i] == p[j]`, the match depends on the
 *             previous characters: `solve(i-1, j-1)`.
 *           - If `p[j] == '*'`, it can either match an empty sequence
 *             (`solve(i, j-1)`) or match one or more characters
 *             (`solve(i-1, j)`).
 *           - Otherwise, it's a mismatch.
 *
 * Time Complexity: O(N * M)
 * Space Complexity: O(N * M) for DP table + O(N + M) for recursion stack.
 */
bool memoizationApproach(string s, string p);
bool solve(vector<vector<int>>& dp, string& s, string& p, int i, int j);

/**
 * Approach: This is the tabulation (bottom-up) version. It builds a 2D DP
 *           table where `dp[i][j]` is true if the first `i` characters of `s`
 *           match the first `j` characters of `p`. The base cases handle empty
 *           strings and leading `*` characters in the pattern. The table is
 *           filled iteratively based on the same recurrence as memoization.
 *
 * Time Complexity: O(N * M)
 * Space Complexity: O(N * M)
 */
bool tabulationApproach(string s, string p);

/**
 * Approach: This is a space-optimized version of the tabulation approach.
 *           Since `dp[i]` only depends on `dp[i-1]`, we can use two 1D arrays
 *           (one for the previous row, one for the current) to reduce space.
 *           A `prev` array stores the state of the previous row `i-1` while
 *           the `dp` array is computed for the current row `i`.
 *
 * Time Complexity: O(N * M)
 * Space Complexity: O(M)
 */
bool optimalApproach(string s, string p);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string text1, text2;
    cin >> text1 >> text2;

    cout << "String 1: " << text1 << endl;
    cout << "String 2: " << text2 << endl;

    cout << "Result (Memoization): "
         << (memoizationApproach(text1, text2) ? "True" : "False") << endl;
    cout << "Result (Tabulation): "
         << (tabulationApproach(text1, text2) ? "True" : "False") << endl;
    cout << "Result (Optimal): "
         << (optimalApproach(text1, text2) ? "True" : "False") << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
bool memoizationApproach(string s, string p) {
  int n = s.length();
  int m = p.length();

  vector<vector<int>> dp(n, vector<int>(m, -1));
  return solve(dp, s, p, n - 1, m - 1);
}

bool solve(vector<vector<int>>& dp, string& s, string& p, int i, int j) {
  if (i < 0 && j < 0) return true;
  if (j < 0) return false;
  if (i < 0) {
    while (j >= 0) {
      if (p[j--] != '*') return false;
    }

    return true;
  }
  if (dp[i][j] != -1) return dp[i][j];

  if (s[i] == p[j] || p[j] == '?') {
    dp[i][j] = solve(dp, s, p, i - 1, j - 1);
  } else if (p[j] == '*') {
    dp[i][j] = solve(dp, s, p, i - 1, j) || solve(dp, s, p, i, j - 1);
  } else {
    dp[i][j] = false;
  }

  return dp[i][j];
}

//-----------------------------TABULATION APPROACH------------------------------
bool tabulationApproach(string s, string p) {
  int n = s.length();
  int m = p.length();

  vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
  for (int i = 0; i < m; i++) {
    if (p[i] != '*') break;
    dp[0][i + 1] = true;
  }

  dp[0][0] = true;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
        dp[i][j] = dp[i - 1][j - 1];
      } else if (p[j - 1] == '*') {
        dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
      }
    }
  }

  return dp[n][m];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
bool optimalApproach(string s, string p) {
  int n = s.length();
  int m = p.length();

  vector<bool> dp(m + 1, false);
  for (int i = 0; i < m; i++) {
    if (p[i] != '*') break;
    dp[i + 1] = true;
  }

  dp[0] = true;
  for (int i = 1; i <= n; i++) {
    vector<bool> prev = dp;
    dp[0] = false;
    for (int j = 1; j <= m; j++) {
      if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
        dp[j] = prev[j - 1];
      } else if (p[j - 1] == '*') {
        dp[j] = prev[j] || dp[j - 1];
      } else {
        dp[j] = false;
      }
    }
  }

  return dp[m];
}
