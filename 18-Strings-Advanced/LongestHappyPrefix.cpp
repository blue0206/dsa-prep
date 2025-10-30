/*
 * Problem: Longest Happy Prefix (LeetCode #1392)
 * Link: https://leetcode.com/problems/longest-happy-prefix/description/
 *
 * Approach: This problem is a direct application of the KMP algorithm's LPS
 *           (Longest Proper Prefix which is also Suffix) array.
 *           A "happy prefix" is a non-empty proper prefix that is also a
 *           suffix. The LPS array for a string `s` is defined such that
 *           `lps[i]` is the length of the longest proper prefix of `s[0...i]`
 *           that is also a suffix of `s[0...i]`.
 *           Therefore, the value at the last index, `lps[n-1]`, gives the
 *           exact length of the longest happy prefix for the entire string.
 *
 * Time Complexity: O(N), where N is the length of the string.
 * Space Complexity: O(N) for the LPS array.
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

string longestPrefix(string s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    cout << "Input String: " << s << endl;

    cout << "Longest Happy Prefix: " << longestPrefix(s) << endl;

    cout << endl;
  }

  return 0;
}

string longestPrefix(string s) {
  int n = s.length();

  vector<int> lps(n, 0);
  int i = 1, j = 0;
  while (i < n) {
    if (s[i] == s[j]) {
      lps[i] = j + 1;
      i++;
      j++;
    } else if (j > 0) {
      j = lps[j - 1];
    } else {
      i++;
    }
  }

  return s.substr(0, lps[n - 1]);
}
