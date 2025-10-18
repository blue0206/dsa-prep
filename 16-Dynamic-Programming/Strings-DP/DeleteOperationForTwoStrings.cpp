/*
 * Problem: Delete Operation for Two Strings (LeetCode #583)
 * Link:
 * https://leetcode.com/problems/delete-operation-for-two-strings/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

/**
 * Approach: This problem can be reduced to finding the Longest Common
 *           Subsequence (LCS). The characters in the LCS are the ones we want
 *           to keep. All other characters must be deleted.
 *           - Deletions from word1 = `word1.length() - lcs_length`
 *           - Deletions from word2 = `word2.length() - lcs_length`
 *           Total deletions =
 *           `word1.length() + word2.length() - 2 * lcs_length`.
 *           This approach finds the LCS length using memoization.
 *
 * Time Complexity: O(N * M)
 * Space Complexity: O(N * M) for DP table + O(N + M) for recursion stack.
 */
int memoizationApproach(string word1, string word2);
int solve(vector<vector<int>>& dp, string& word1, string& word2, int i, int j);

/**
 * Approach: This is a space-optimized tabulation approach. It also uses the
 *           LCS reduction. It calculates the length of the LCS iteratively
 *           using only two 1D arrays to store the previous and current row's
 *           results, reducing space complexity. The final answer is then
 *           calculated using the same formula as the memoization approach.
 *
 * Time Complexity: O(N * M)
 * Space Complexity: O(M)
 */
int tabulationApproach(string word1, string word2);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string text1, text2;
    cin >> text1 >> text2;

    cout << "Text 1: " << text1 << endl;
    cout << "Text 2: " << text2 << endl;

    cout << "Result (Memoization): " << memoizationApproach(text1, text2)
         << endl;
    cout << "Result (Tabulation): " << tabulationApproach(text1, text2) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(string word1, string word2) {
  int n = word1.length();
  int m = word2.length();

  vector<vector<int>> dp(n, vector<int>(m, -1));
  return (n + m) - 2 * solve(dp, word1, word2, n - 1, m - 1);
}

int solve(vector<vector<int>>& dp, string& word1, string& word2, int i, int j) {
  if (i < 0 || j < 0) return 0;
  if (dp[i][j] != -1) return dp[i][j];

  if (word1[i] == word2[j]) {
    dp[i][j] = solve(dp, word1, word2, i - 1, j - 1) + 1;
  } else {
    dp[i][j] = max(solve(dp, word1, word2, i - 1, j),
                   solve(dp, word1, word2, i, j - 1));
  }

  return dp[i][j];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(string word1, string word2) {
  int n = word1.length();
  int m = word2.length();

  vector<int> lcs(m + 1, 0);
  for (int i = 1; i <= n; i++) {
    vector<int> dp = lcs;
    for (int j = 1; j <= m; j++) {
      if (word1[i - 1] == word2[j - 1]) {
        lcs[j] = dp[j - 1] + 1;
      } else {
        lcs[j] = max(lcs[j - 1], dp[j]);
      }
    }
  }

  return (n + m - (2 * lcs[m]));
}
