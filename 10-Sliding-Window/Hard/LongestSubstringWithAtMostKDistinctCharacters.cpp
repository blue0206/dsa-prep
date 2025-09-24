/*
 * Problem: Longest Substring with At Most K Distinct Characters
 * Link:
 * https://www.naukri.com/code360/problems/distinct-characters_2221410?leftPanelTabValue=PROBLEM
 *
 * Approach: This problem is a classic application of the sliding window
 *           technique. The goal is to find the longest substring (window) that
 *           contains at most `k` distinct characters.
 *
 *           1.  **Window and State:** We use two pointers, `low` and `high`, to
 *               define the current window. We also use a frequency map
 *               (`charMap`) to store counts of characters in the window and a
 *               `distinctCount` variable to track the number of unique
 *               characters.
 *           2.  **Expansion:** The `high` pointer moves to the right, expanding
 *               the window. When a new character is encountered for the first
 *               time (`charMap[char] == 0`), we increment `distinctCount`.
 *           3.  **Contraction:** If `distinctCount` exceeds `k`, the window is
 *               invalid. We shrink it from the left by moving the `low`
 *               pointer. When a character's count becomes zero after
 *               decrementing, we decrement `distinctCount`.
 *           4.  **Update Answer:** After each step, the window is valid, and we
 *               update `maxLen` with the current window size
 *               (`high - low + 1`).
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int kDistinctChars(const string& s, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int k;
    cin >> k;

    string s;
    cin >> s;

    cout << "k: " << k << endl;
    cout << "Input String: " << s << endl;

    cout << "Length of Longest Substring: " << kDistinctChars(s, k) << endl;
  }

  return 0;
}

int kDistinctChars(const string& s, int k) {
  unordered_map<char, int> charMap;

  int maxLen = 0;
  int low = 0;
  int high = 0;
  while (high < s.length()) {
    // Expand the window by including the character at `high`.
    charMap[s[high]]++;

    // If the number of distinct characters exceeds k, shrink the window.
    while (charMap.size() > k) {
      // Decrement the count of the character at `low`.
      charMap[s[low]]--;
      // If the count becomes zero, erase it from the map.
      if (charMap[s[low]] == 0) {
        charMap.erase(s[low]);
      }
      // Move the left pointer to shrink the window.
      low++;
    }

    // Update the maximum length with the size of the current valid window.
    maxLen = max(maxLen, high - low + 1);

    // Move the right pointer to continue expanding.
    high++;
  }

  return maxLen;
}
