/*
 * Problem: Isomorphic Strings (LeetCode #205)
 * Link: https://leetcode.com/problems/isomorphic-strings/description/
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/**
 * Approach: This approach uses two hash maps to ensure a bijective (one-to-one
 *           and onto) mapping between the characters of string `s` and `t`.
 *           One map `st` stores the mapping from `s` to `t`, and another map
 *           `ts` stores the mapping from `t` to `s`.
 *           We iterate through the strings. For each character `s[i]`, we
 *           ensure its mapping to `t[i]` is consistent. We also check the
 *           reverse mapping from `t[i]` to `s[i]` to prevent two different
 *           characters from `s` mapping to the same character in `t`.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(K), where K is the number of unique characters (at most
 * 256).
 */
bool hashMapApproach(string s, string t);

/**
 * Approach: Same as hashmap approach.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1), as the array sizes are fixed (256 for ASCII).
 */
bool hashArrayApproach(string s, string t);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s, t;
    cin >> s >> t;

    cout << "String s: " << s << endl;
    cout << "String t: " << t << endl;

    cout << "Result (Hash Map Approach): "
         << (hashMapApproach(s, t) ? "True" : "False") << endl;
    cout << "Result (Hash Array Approach): "
         << (hashArrayApproach(s, t) ? "True" : "False") << endl;

    cout << endl;
  }

  return 0;
}

bool hashMapApproach(string s, string t) {
  if (s.length() != t.length()) return false;

  unordered_map<char, char> st, ts;
  for (int i = 0; i < s.length(); i++) {
    if (st.find(s[i]) != st.end()) {
      if (t[i] != st[s[i]]) {
        return false;
      }
    } else {
      st[s[i]] = t[i];
    }

    if (ts.find(t[i]) != ts.end()) {
      if (s[i] != ts[t[i]]) {
        return false;
      }
    } else {
      ts[t[i]] = s[i];
    }
  }

  return true;
}

bool hashArrayApproach(string s, string t) {
  if (s.length() != t.length()) return false;

  int st[256] = {0};  // Stores last seen index of char in s
  int ts[256] = {0};  // Stores last seen index of char in t

  for (int i = 0; i < s.length(); i++) {
    if (st[s[i]] == 0) {
      st[s[i]] = t[i];
    } else if (st[s[i]] != t[i]) {
      return false;
    }

    if (ts[t[i]] == 0) {
      ts[t[i]] = s[i];
    } else if (ts[t[i]] != s[i]) {
      return false;
    }
  }

  return true;
}
