/*
 * Problem: Longest Common Substring
 * Link:
 * https://www.naukri.com/code360/problems/longest-common-substring_1235207?leftPanelTabValue=PROBLEM
 *
 * Approach: This problem is a variation of the Longest Common Subsequence (LCS)
 *           problem. The key difference is that a substring must be
 *           contiguous. The DP state `dp[i][j]` represents the length of the
 *           common substring that *ends* at `str1[i-1]` and `str2[j-1]`.
 *           - If `str1[i-1] == str2[j-1]`, the common substring is extended:
 *             `dp[i][j] = 1 + dp[i-1][j-1]`.
 *           - If they don't match, the contiguous streak is broken, so
 * `dp[i][j]` is 0. The final answer is the maximum value found anywhere in the
 * DP table.
 *
 * Time Complexity: O(N * M)
 * Space Complexity: O(N * M)
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int lcs(string& str1, string& str2);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string text1, text2;
    cin >> text1 >> text2;

    cout << "Text 1: " << text1 << endl;
    cout << "Text 2: " << text2 << endl;

    cout << "Longest Common Substring: " << lcs(text1, text2) << endl;

    cout << endl;
  }

  return 0;
}

int lcs(string& str1, string& str2) {
  int n = str1.length();
  int m = str2.length();

  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

  int maxVal = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (str1[i - 1] == str2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
        maxVal = max(maxVal, dp[i][j]);
      }
    }
  }

  return maxVal;
}
