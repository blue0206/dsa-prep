/*
 * Problem: Print Longest Common Subsequence
 * Link:
 * https://www.naukri.com/code360/problems/print-longest-common-subsequence_8416383?leftPanelTabValue=PROBLEM
 *
 * Approach: This solution uses a two-step dynamic programming approach.
 *           1.  **Build the DP Table:** First, it computes the lengths of the
 *               LCS for all prefixes of the two strings using tabulation.
 *               The `dp[i][j]` table stores the length of the LCS for
 *               `s1[0...i-1]` and `s2[0...j-1]`.
 *           2.  **Backtrack to Reconstruct:** After the table is filled, it
 *               backtracks from `dp[n][m]` to build the LCS string. If the
 *               characters `s1[i-1]` and `s2[j-1]` match, they are part of the
 *               LCS, and we move diagonally. Otherwise, we move in the
 *               direction of the larger value in the DP table (up or left).
 *
 * Time Complexity: O(N * M) for building the table and O(N + M) for
 *                  backtracking.
 * Space Complexity: O(N * M) for the DP table.
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

string findLCS(int n, int m, string& s1, string& s2);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string text1, text2;
    cin >> text1 >> text2;

    cout << "Text 1: " << text1 << endl;
    cout << "Text 2: " << text2 << endl;

    cout << "LCS: " << findLCS(text1.length(), text2.length(), text1, text2)
         << endl;

    cout << endl;
  }

  return 0;
}

string findLCS(int n, int m, string& s1, string& s2) {
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (s1[i - 1] == s2[j - 1]) {
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
    if (s1[i - 1] == s2[j - 1]) {
      ans += s1[i - 1];
      i--;
      j--;
    } else if (dp[i - 1][j] >= dp[i][j - 1]) {
      i--;
    } else {
      j--;
    }
  }
  reverse(ans.begin(), ans.end());

  return ans;
}
