/*
 * Problem: Palindrome Partitioning II (LeetCode #132)
 * Link: https://leetcode.com/problems/palindrome-partitioning-ii/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). This is a classic
 *           Partition DP problem. The function `solve(i)` finds the minimum
 *           number of partitions needed for the substring `s[i...]`.
 *           For each starting index `i`, we iterate through all possible end
 *           points `j`. If the substring `s[i...j]` is a palindrome, we
 *           consider it a valid partition and recursively call `solve(j+1)` to
 *           find the minimum partitions for the rest of the string. The result
 *           is `1 + solve(j+1)`. We take the minimum over all possible `j`.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N) for DP array + O(N) for recursion stack.
 */
int memoizationApproach(string s);
int solve(vector<int>& dp, string& s, int i);

/**
 * Approach: This is the tabulation (bottom-up) version. We fill a 1D DP array
 *           `dp` from right to left, where `dp[i]` stores the minimum number
 *           of partitions for the substring `s[i...]`. The base case is
 *           `dp[n] = 0`. The final answer is `dp[0] - 1`, as the number of
 *           cuts is one less than the number of partitions.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N)
 */
int tabulationApproach(string s);

bool checkPalindrome(string& s, int i, int j);
int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    cout << "Input String: " << s << endl;

    cout << "Minimum Cuts (Memoization): " << memoizationApproach(s) << endl;
    cout << "Minimum Cuts (Tabulation): " << tabulationApproach(s) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(string s) {
  int n = s.length();

  vector<int> dp(n, -1);
  return solve(dp, s, 0) - 1;
}

int solve(vector<int>& dp, string& s, int i) {
  if (i == s.length()) return 0;
  if (dp[i] != -1) return dp[i];

  int minCuts = INT_MAX;
  string temp = "";
  for (int j = i; j < s.length(); j++) {
    temp += s[j];
    if (checkPalindrome(temp, 0, temp.length() - 1)) {
      int cuts = solve(dp, s, j + 1) + 1;
      minCuts = min(cuts, minCuts);
    }
  }

  dp[i] = minCuts;
  return dp[i];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(string s) {
  int n = s.length();

  vector<int> dp(n + 1, 0);
  for (int i = n - 1; i >= 0; i--) {
    int minCuts = INT_MAX;
    string temp = "";
    for (int j = i; j < n; j++) {
      temp += s[j];
      if (checkPalindrome(temp, 0, temp.length() - 1)) {
        int cuts = 1 + dp[j + 1];
        minCuts = min(minCuts, cuts);
      }
    }
    dp[i] = minCuts;
  }

  return dp[0] - 1;
}

bool checkPalindrome(string& s, int i, int j) {
  while (i < j) {
    if (s[i] != s[j]) return false;
    i++;
    j--;
  }

  return true;
}
