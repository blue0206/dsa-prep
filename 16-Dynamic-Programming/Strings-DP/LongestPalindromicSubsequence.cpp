/*
 * Problem: Longest Palindromic Subsequence (LeetCode #516)
 * Link:
 * https://leetcode.com/problems/longest-palindromic-subsequence/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

/**
 * Approach: This problem can be cleverly reduced to the Longest Common
 *           Subsequence (LCS) problem. A palindrome reads the same forwards
 *           and backwards. Therefore, the longest palindromic subsequence of a
 *           string `s` is the LCS between `s` and its reverse. This memoization
 *           approach implements the standard recursive LCS solution.
 *
 * Time Complexity: O(N*N)
 * Space Complexity: O(N*N) for the DP table + O(N) for recursion stack.
 */
int memoizationApproach(string s);
int solve(vector<vector<int>>& dp, string& s1, string& s2, int i, int j);

/**
 * Approach: This is the tabulation (bottom-up) version of the LCS approach.
 *           It finds the LCS between the original string `s` and its reverse
 *           by building a 2D DP table, where `dp[i][j]` stores the length of
 *           the LCS between the first `i` characters of `s` and the first `j`
 *           characters of its reverse.
 *
 * Time Complexity: O(N*N)
 * Space Complexity: O(N*N)
 */
int tabulationApproach(string s);

/**
 * Approach: This is a space-optimized version of the tabulation approach. It
 *           also finds the LCS between the string and its reverse. To
 *           calculate the values for the current row, it only needs the
 *           results from the previous row. It uses two 1D arrays to store the
 *           previous and current row's results, reducing space from O(N*N) to
 *           O(N).
 *
 * Time Complexity: O(N*N)
 * Space Complexity: O(N)
 */
int optimalApproach(string s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string text;
    cin >> text;

    cout << "String: " << text << endl;

    cout << "LPS (Memoization): " << memoizationApproach(text) << endl;
    cout << "LPS (Tabulation): " << tabulationApproach(text) << endl;
    cout << "LPS (Optimal): " << optimalApproach(text) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(string s) {
  int n = s.length();

  string t = "";
  for (int i = n - 1; i >= 0; i--) t += s[i];

  vector<vector<int>> dp(n, vector<int>(n, -1));
  return solve(dp, s, t, n - 1, n - 1);
}

int solve(vector<vector<int>>& dp, string& s1, string& s2, int i, int j) {
  if (i < 0 || j < 0) return 0;
  if (dp[i][j] != -1) return dp[i][j];

  if (s1[i] == s2[j]) {
    dp[i][j] = solve(dp, s1, s2, i - 1, j - 1) + 1;
  } else {
    dp[i][j] = max(solve(dp, s1, s2, i - 1, j), solve(dp, s1, s2, i, j - 1));
  }

  return dp[i][j];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(string s) {
  int n = s.length();

  string t = "";
  for (int i = n - 1; i >= 0; i--) t += s[i];

  vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (s[i - 1] == t[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
      }
    }
  }

  return dp[n][n];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(string s) {
  int n = s.length();

  string t = "";
  for (int i = n - 1; i >= 0; i--) t += s[i];

  vector<int> lcs(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    vector<int> dp = lcs;
    for (int j = 1; j <= n; j++) {
      if (s[i - 1] == t[j - 1]) {
        lcs[j] = dp[j - 1] + 1;
      } else {
        lcs[j] = max(lcs[j - 1], dp[j]);
      }
    }
  }

  return lcs[n];
}
