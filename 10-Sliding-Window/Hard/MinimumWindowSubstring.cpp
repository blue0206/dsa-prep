/*
 * Problem: Minimum Window Substring (LeetCode #76)
 * Link: https://leetcode.com/problems/minimum-window-substring/description/
 *
 * Approach:
 *
 * This problem is solved using a sliding window approach with two pointers,
 * `low` and `high`. The goal is to find the smallest window in `s` that
 * contains all characters of `t`, including duplicates.
 *
 * 1.  **State Tracking:** We use a hash map (`tCounts`) to store the frequency
 *     of characters required by `t`. We also track `required`, the number of
 *     unique characters in `t`, and `formed`, the number of unique characters
 *     in the current window that meet their required frequency.
 * 2.  **Expansion:** The `high` pointer expands the window to the right. For
 *     each character `c` from `s`, we increment its count in our window map. If
 *     `c` is a required character and its count in the window now matches its
 *     required count in `t`, we increment `formed`.
 * 3.  **Contraction:** Once `formed == required`, the window is valid. We try
 *     to shrink it from the left by moving the `low` pointer. We update the
 *     minimum length found so far. When removing a character from the left, if
 *     it was a required character and its count drops below what's required,
 *     we decrement `formed`, making the window invalid and stopping the
 *     contraction.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

string minWindow(const string& s, const string& t);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s, t;
    cin >> s >> t;

    cout << "s: " << s << endl;
    cout << "t: " << t << endl;

    cout << "Min Window: " << minWindow(s, t) << endl;
  }

  return 0;
}

string minWindow(const string& s, const string& t) {
  if (t.length() > s.length() || t.empty()) {
    return "";
  }

  unordered_map<char, int> tCounts;
  for (char i : t) {
    tCounts[i]++;
  }

  unordered_map<char, int> windowCounts;
  int required = tCounts.size();
  int formed = 0;

  int minLength = INT_MAX;
  int minLow = -1;

  int low = 0;
  int high = 0;
  while (high < s.length()) {
    // Expand the window by adding the character at `high`.
    char charHigh = s[high];
    windowCounts[charHigh]++;

    // If the added character is required and its count now matches the
    // requirement.
    if (tCounts.count(charHigh) &&
        windowCounts[charHigh] == tCounts[charHigh]) {
      formed++;
    }

    // Contract the window from the left while it's still valid.
    while (low <= high && formed == required) {
      // Update the minimum window found so far.
      if (high - low + 1 < minLength) {
        minLow = low;
        minLength = high - low + 1;
      }

      // Remove the character at `low` from the window.
      char charLow = s[low];
      windowCounts[charLow]--;

      // If the removed character was required and its count now falls below the
      // requirement.
      if (tCounts.count(charLow) && windowCounts[charLow] < tCounts[charLow]) {
        formed--;
      }
      low++;
    }

    high++;
  }

  return minLength == INT_MAX ? "" : s.substr(minLow, minLength);
}
