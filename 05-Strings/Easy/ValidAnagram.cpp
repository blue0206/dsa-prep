/*
 * Problem: Valid Anagram (LeetCode #242)
 * Link: https://leetcode.com/problems/valid-anagram/description/
 *
 * Approach: Two strings are anagrams if they contain the same characters with
 *           the same frequencies. This can be verified using a frequency map.
 *           1.  First, check if the lengths of the two strings are equal. If
 *               not, they cannot be anagrams.
 *           2.  Create an integer array `charMap` of size 26, initialized to
 *               zeros, to store the frequency of each lowercase English letter.
 *           3.  Iterate through both strings simultaneously. For each character
 *               in `s`, increment its corresponding count in `charMap`. For
 *               each character in `t`, decrement its count.
 *           4.  After the loop, if the strings are anagrams, `charMap` should
 *               contain all zeros. Iterate through `charMap` to verify this.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1), as the size of the frequency map is constant (26).
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

bool isAnagram(string s, string t);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s, t;
    cin >> s >> t;

    cout << "String s: " << s << endl;
    cout << "String t: " << t << endl;

    cout << "Result: " << (isAnagram(s, t) ? "True" : "False") << endl;

    cout << endl;
  }

  return 0;
}

bool isAnagram(string s, string t) {
  if (s.length() != t.length()) {
    return false;
  }

  int charMap[26] = {0};
  for (int i = 0; i < s.length(); i++) {
    charMap[s[i] - 'a']++;
    charMap[t[i] - 'a']--;
  }
  for (int i = 0; i < 26; i++) {
    if (charMap[i] != 0) {
      return false;
    }
  }

  return true;
}
