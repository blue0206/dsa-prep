/*
 * Problem: Shortest Common Supersequence (LeetCode #1092)
 * Link:
 * https://leetcode.com/problems/shortest-common-supersequence/description/
 *
 * Approach: This solution builds upon the Longest Common Subsequence (LCS)
 *           problem. It uses a two-step dynamic programming approach:
 *           1.  **Build the LCS Table:** First, it computes the standard LCS DP
 *               table, where `dp[i][j]` stores the length of the LCS for
 *               `str1[0...i-1]` and `str2[0...j-1]`.
 *           2.  **Backtrack to Build Supersequence:** It then backtracks from
 *               `dp[n][m]`. If characters match, they are part of the LCS and
 *               are added once to the result. If they don't match, the
 *               non-common character is added, and the pointer moves in the
 *               direction of the larger subproblem's LCS length. This ensures
 *               all characters are included while keeping the result as short
 *               as possible.
 *
 * Time Complexity: O(N * M) for building the table and O(N + M) for
 * backtracking. Space Complexity: O(N * M) for the DP table.
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

string shortestCommonSupersequence(string str1, string str2);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string text1, text2;
    cin >> text1 >> text2;

    cout << "String 1: " << text1 << endl;
    cout << "String 2: " << text2 << endl;

    cout << "Shortest Common Supersequence: "
         << shortestCommonSupersequence(text1, text2) << endl;

    cout << endl;
  }

  return 0;
}

string shortestCommonSupersequence(string str1, string str2) {
  int n = str1.length();
  int m = str2.length();

  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (str1[i - 1] == str2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  string ans = "";
  int i = n;
  int j = m;
  while (i > 0 && j > 0) {
    if (str1[i - 1] == str2[j - 1]) {
      ans += str1[i - 1];
      i--;
      j--;
    } else if (dp[i - 1][j] >= dp[i][j - 1]) {
      ans += str1[i - 1];
      i--;
    } else {
      ans += str2[j - 1];
      j--;
    }
  }
  while (i != 0) {
    ans += str1[i - 1];
    i--;
  }
  while (j != 0) {
    ans += str2[j - 1];
    j--;
  }

  reverse(ans.begin(), ans.end());
  return ans;
}
