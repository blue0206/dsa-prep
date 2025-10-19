/*
 * Problem: Distinct Subsequences (LeetCode #115)
 * Link: https://leetcode.com/problems/distinct-subsequences/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;
using ull = unsigned long long;

/**
 * Approach: This is a top-down DP approach (memoization). The state `dp[i][j]`
 *           stores the number of distinct subsequences of `t[0...j]` in
 *           `s[0...i]`. The recurrence relation is:
 *           - If `s[i] == t[j]`, we can either match `s[i]` with `t[j]` (adding
 *             `solve(i-1, j-1)` ways) or not match `s[i]`
 *             (adding `solve(i-1, j)` ways).
 *           - If `s[i] != t[j]`, we must skip `s[i]`, so the answer is
 *             `solve(i-1, j)`.
 *
 * Time Complexity: O(N * M)
 * Space Complexity: O(N * M) for DP table + O(N + M) for recursion stack.
 */
int memoizationApproach(string s, string t);
int solve(vector<vector<int>>& dp, string& text1, string& text2, int i, int j);

/**
 * Approach: This is the tabulation (bottom-up) version. It builds a 2D DP
 *           table where `dp[i][j]` stores the number of distinct subsequences
 *           of `t`'s first `j` characters within `s`'s first `i` characters.
 *           The base case `dp[i][0] = 1` signifies that an empty string can be
 *           formed in one way.
 *
 * Time Complexity: O(N * M)
 * Space Complexity: O(N * M)
 */
int tabulationApproach(string s, string t);

/**
 * Approach: This is a space-optimized version of the tabulation approach.
 *           Since `dp[i]` only depends on `dp[i-1]`, we can use a single 1D
 *           array. The inner loop must run backwards to use the values from
 *           the previous `i` iteration before they are updated in the current
 *           `i` iteration.
 *
 * Time Complexity: O(N * M)
 * Space Complexity: O(M)
 */
int optimalApproach(string s, string t);

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
int memoizationApproach(string s, string t) {
  int n = s.length();
  int m = t.length();

  vector<vector<int>> dp(n, vector<int>(m, -1));
  return solve(dp, s, t, n - 1, m - 1);
}

int solve(vector<vector<int>>& dp, string& s, string& t, int i, int j) {
  if (j < 0) return 1;
  if (i < 0) return 0;
  if (dp[i][j] != -1) return dp[i][j];

  if (s[i] == t[j]) {
    dp[i][j] = solve(dp, s, t, i - 1, j) + solve(dp, s, t, i - 1, j - 1);
  } else {
    dp[i][j] = solve(dp, s, t, i - 1, j);
  }

  return dp[i][j];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(string s, string t) {
  if (s.length() < t.length()) return 0;
  if (s == t) return 1;

  int n = s.length();
  int m = t.length();

  vector<vector<ull>> dp(n + 1, vector<ull>(m + 1, 0));
  // An empty string t is a subsequence of any string s in one way
  // (by choosing no characters from s).
  for (int i = 0; i <= n; i++) dp[i][0] = 1;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (s[i - 1] == t[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  return dp[n][m];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(string s, string t) {
  if (s.length() < t.length()) return 0;
  if (s == t) return 1;

  int n = s.length();
  int m = t.length();

  vector<ull> dp(m + 1, 0);
  dp[0] = 1;

  for (int i = 1; i <= n; i++) {
    ull prev = dp[0];
    for (int j = 1; j <= m; j++) {
      ull temp = dp[j];
      if (s[i - 1] == t[j - 1]) {
        dp[j] = prev + dp[j];
      }
      prev = temp;
    }
  }

  return dp[m];
}
