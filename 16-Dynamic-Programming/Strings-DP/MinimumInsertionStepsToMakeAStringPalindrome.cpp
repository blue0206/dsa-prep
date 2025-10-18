/*
 * Problem: Minimum Insertion Steps to Make a String Palindrome (LeetCode #1312)
 * Link:
 * https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

/**
 * Approach: This problem can be reduced to finding the Longest Palindromic
 *           Subsequence (LPS). The characters already part of the LPS do not
 *           need insertions. The characters not in the LPS are the ones that
 *           need a matching character inserted to make the whole string a
 *           palindrome. Therefore, the number of insertions required is
 *           `n - length(LPS)`. The LPS is found by calculating the LCS of the
 *           string and its reverse. This is the memoization version.
 *
 * Time Complexity: O(N*N)
 * Space Complexity: O(N*N) for DP table + O(N) for recursion stack.
 */
int memoizationApproach(string s);
int solve(vector<vector<int>>& dp, string& s1, string& s2, int i, int j);

/**
 * Approach: This is the tabulation (bottom-up) version. It first finds the
 *           length of the Longest Palindromic Subsequence by calculating the
 *           LCS of the string and its reverse using a 2D DP table. The number
 *           of insertions is then `n - lcs_length`.
 *
 * Time Complexity: O(N*N)
 * Space Complexity: O(N*N)
 */
int tabulationApproach(string s);

/**
 * Approach: This is a space-optimized version of the tabulation approach. It
 *           also finds the LPS by calculating the LCS of the string and its
 *           reverse. It uses two 1D arrays to store the previous and current
 *           row's results during the LCS calculation, reducing space from
 *           O(N*N) to O(N). The final result is `n - lcs_length`.
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

    cout << "Result (Memoization): " << memoizationApproach(text) << endl;
    cout << "Result (Tabulation): " << tabulationApproach(text) << endl;
    cout << "Result (Optimal): " << optimalApproach(text) << endl;

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
  int lcs = solve(dp, s, t, n - 1, n - 1);
  return n - lcs;
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
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  return n - dp[n][n];
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
        lcs[j] = max(dp[j], lcs[j - 1]);
      }
    }
  }

  return n - lcs[n];
}
