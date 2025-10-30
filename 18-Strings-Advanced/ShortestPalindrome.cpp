/*
 * Problem: Shortest Palindrome (LeetCode #214)
 * Link: https://leetcode.com/problems/shortest-palindrome/description/
 *
 * Approach: This problem can be solved efficiently using the KMP algorithm's
 *           LPS (Longest Proper Prefix which is also Suffix) array.
 *           1.  The goal is to find the longest prefix of the string `s` that
 *               is also a palindrome.
 *           2.  To do this, we create a temporary string `temp = s + '$' +
 *               reverse(s)`. The `$` is a separator to prevent matching the
 *               entire string.
 *           3.  We compute the LPS array for `temp`. The value at the last
 *               index of the LPS array, `lps.back()`, gives the length of the
 *               longest prefix of `s` that is also a palindrome.
 *           4.  The characters that need to be prepended are the reverse of the
 *               suffix of `s` that is not part of this longest palindromic
 *               prefix.
 *
 * Time Complexity: O(N), where N is the length of the string.
 * Space Complexity: O(N) for the temporary string and LPS array.
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

string shortestPalindrome(string s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    cout << "Input String: " << s << endl;

    cout << "Shortest Palindrome: " << shortestPalindrome(s) << endl;

    cout << endl;
  }

  return 0;
}

string shortestPalindrome(string s) {
  string revS = s;
  reverse(revS.begin(), revS.end());

  string temp = s + '$' + revS;
  vector<int> lps(temp.length(), 0);
  int i = 1, j = 0;
  while (i < temp.length()) {
    if (temp[i] == temp[j]) {
      lps[i] = j + 1;
      i++;
      j++;
    } else if (j > 0) {
      j = lps[j - 1];
    } else {
      i++;
    }
  }

  int idx = lps[temp.length() - 1];
  return (revS + s.substr(idx));
}
