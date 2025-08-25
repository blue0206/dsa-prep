/*
 * Problem: Rotate String (LeetCode #796)
 * Link: https://leetcode.com/problems/rotate-string/description/
 *
 * Approach: This problem can be solved with a clever string manipulation trick.
 *           If string `goal` is a rotation of string `s`, then `goal` must be
 *           a substring of `s` concatenated with itself (`s + s`).
 *           For example, if s = "abcde", then s+s = "abcdeabcde". Any rotation
 *           of "abcde" (like "cdeab") will be a substring of "abcdeabcde".
 *           The first step is to check if the lengths are equal. If they are,
 *           we perform the concatenation and search.
 *
 * Time Complexity: O(N^2) in the worst case for string find.
 * Space Complexity: O(N) for the concatenated string.
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

bool rotateString(string s, string goal);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s, goal;
    cin >> s >> goal;

    cout << "String s: " << s << endl;
    cout << "String goal: " << goal << endl;

    cout << "Result: " << (rotateString(s, goal) ? "True" : "False") << endl;

    cout << endl;
  }

  return 0;
}

bool rotateString(string s, string goal) {
  if (s.length() != goal.length() || s.empty()) {
    return false;
  }

  s += s;

  if (s.find(goal) == string::npos) {
    return false;
  }

  return true;
}
