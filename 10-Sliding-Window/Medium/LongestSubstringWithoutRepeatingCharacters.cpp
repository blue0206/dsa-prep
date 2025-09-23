/*
 * Problem: Longest Substring Without Repeating Characters (LeetCode #3)
 * Link:
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/description/
 *
 * Approach: This problem can be solved efficiently using a sliding window
 *           approach with two pointers, `low` and `high`.
 *           1.  **Window and State:** The pointers `low` and `high` define the
 *               current substring (window). A frequency map (`charMap`) is used
 *               to store the counts of characters within this window.
 *           2.  **Expansion:** The `high` pointer moves to the right, expanding
 *               the window and including a new character. The frequency of this
 *               new character is incremented in the map.
 *           3.  **Contraction:** After expansion, we check if the window is
 *               valid (i.e., if the new character is a duplicate).
 *               If `charMap[s[high]] > 1`, the window is invalid. We then
 *               shrink the window from the left by moving the `low` pointer to
 *               the right and decrementing the frequency of the character at
 *               `s[low]` until the window becomes valid again.
 *           4.  **Update Answer:** After each expansion and potential
 *               contraction, the window `[low, high]` is guaranteed to be
 *               valid. We update the `maxLength` with the size of this current
 *               valid window (`high - low + 1`).
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int lengthOfLongestSubstring(string s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    cout << "Input String: " << s << endl;

    cout << "Length of Longest Substring: " << lengthOfLongestSubstring(s)
         << endl;
  }

  return 0;
}

int lengthOfLongestSubstring(string s) {
  int low = 0;
  int high = 0;

  int charMap[256] = {0};
  int maxLength = 0;
  while (high < s.length()) {
    // Update State with s[high]
    charMap[s[high]]++;

    // Contraction Loop: Is window invalid?
    // (Yes, if the count of the new char is > 1)
    while (charMap[s[high]] > 1) {
      // Update State by removing s[low]
      charMap[s[low]]--;

      // Shrink
      low++;
    }

    // Update Answer (Window is now guaranteed to be valid).
    maxLength = max(maxLength, high - low + 1);

    // Expand
    high++;
  }

  return maxLength;
}
