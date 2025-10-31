/*
 * Problem: Count Palindromic Subsequences (LeetCode #2484)
 * Link:
 * https://leetcode.com/problems/count-palindromic-subsequences/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;
using ll = long long;
const ll M = 1e9 + 7;

/**
 * Approach: This is a top-down DP (memoization) approach. We need to find the
 *           number of subsequences of the form "xy.yx". We can iterate through
 *           all 100 possible pairs for `x` and `y`. For each pair, we use a
 *           recursive helper to count how many subsequences of `s` match the
 *           pattern `[x, y, ., y, x]`, where '.' can be any digit. The state
 *           `dp[i][size]` stores the number of ways to form the rest of the
 *           pattern from index `i` of the string, given that we have already
 *           matched `size` characters of the pattern.
 *
 * Time Complexity: O(100 * N * 5) = O(N)
 * Space Complexity: O(N * 5)
 */
int memoizationApproach(string s);
ll solve(vector<vector<ll>>& dp, vector<char>& pattern, string& s, int size,
         int i);

/**
 * Approach: This is an efficient approach using prefix and suffix counts. We
 *           iterate through the string, treating each character `s[i]` as the
 *           potential middle element of a palindrome "ab.ba".
 *           1.  Precompute `prefixPairs[i-1]`, which stores the count of all
 *               2-digit subsequences "ab" in the prefix `s[0...i-1]`.
 *           2.  Precompute `suffixPairs[i+1]`, which stores the count of all
 *               2-digit subsequences "ba" in the suffix `s[i+1...n-1]`.
 *           3.  For each middle index `i`, the total number of palindromes
 *               centered at `i` is the sum of `prefixPairs[i-1]["ab"] *
 *               suffixPairs[i+1]["ba"]` over all possible pairs "ab".
 *
 * Time Complexity: O(N * 100) = O(N)
 * Space Complexity: O(N * 100) = O(N)
 */
int prefixSuffixApproach(string s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    cout << "Input String: " << s << endl;

    cout << "Number of Palindromic Subsequences (Memoization): "
         << memoizationApproach(s) << endl;
    cout << "Number of Palindromic Subsequences (Prefix-Suffix): "
         << prefixSuffixApproach(s) << endl;

    cout << endl;
  }

  return 0;
}

//--------------------------------MEMOIZATION-----------------------------------
int memoizationApproach(string s) {
  int n = s.length();
  ll count = 0;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      char x = '0' + i;
      char y = '0' + j;
      vector<char> pattern = {x, y, '0', y, x};
      vector<vector<ll>> dp(n, vector<ll>(5, -1));
      count = ((count % M) + (solve(dp, pattern, s, 0, 0) % M)) % M;
    }
  }

  return count;
}

ll solve(vector<vector<ll>>& dp, vector<char>& pattern, string& s, int size,
         int i) {
  if (size == 5) return 1;
  if (i >= s.length()) return 0;
  if (dp[i][size] != -1) return dp[i][size];

  ll pick = 0;
  if (pattern[size] == s[i] || size == 2) {
    pick = solve(dp, pattern, s, size + 1, i + 1) % M;
  }

  ll notPick = solve(dp, pattern, s, size, i + 1) % M;

  dp[i][size] = ((pick + notPick) % M);
  return dp[i][size];
}

//-----------------------------PREFIX-SUFFIX APPROACH---------------------------
int prefixSuffixApproach(string s) {
  int n = s.length();

  ll prefixCounts[10] = {0};
  prefixCounts[s[0] - '0'] = 1;
  vector<vector<ll>> prefixPairs(n, vector<ll>(100, 0));
  for (int i = 1; i < n; i++) {
    int d = s[i] - '0';

    for (int j = 0; j < 10; j++) {
      for (int k = 0; k < 10; k++) {
        int pair = j * 10 + k;

        prefixPairs[i][pair] = prefixPairs[i - 1][pair];
        if (k == d) {
          prefixPairs[i][pair] =
              ((prefixPairs[i][pair] % M) + (prefixCounts[j] % M)) % M;
        }
      }
    }
    prefixCounts[d]++;
  }

  ll suffixCounts[10] = {0};
  suffixCounts[s[n - 1] - '0'] = 1;
  vector<vector<ll>> suffixPairs(n, vector<ll>(100, 0));
  for (int i = n - 2; i >= 0; i--) {
    int d = s[i] - '0';

    for (int j = 0; j < 10; j++) {
      for (int k = 0; k < 10; k++) {
        int pair = j * 10 + k;

        suffixPairs[i][pair] = suffixPairs[i + 1][pair];
        if (j == d) {
          suffixPairs[i][pair] =
              ((suffixPairs[i][pair] % M) + (suffixCounts[k] % M)) % M;
        }
      }
    }
    suffixCounts[d]++;
  }

  ll count = 0;
  for (int i = 2; i < n - 2; i++) {
    for (int j = 0; j < 10; j++) {
      for (int k = 0; k < 10; k++) {
        int pair1 = j * 10 + k;
        int pair2 = k * 10 + j;

        ll total = ((prefixPairs[i - 1][pair1] % M) *
                    (suffixPairs[i + 1][pair2] % M)) %
                   M;
        count = ((count % M) + (total % M)) % M;
      }
    }
  }

  return count;
}
