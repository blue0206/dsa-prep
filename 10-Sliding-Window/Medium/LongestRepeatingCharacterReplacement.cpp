/*
 * Problem: Longest Repeating Character Replacement (LeetCode #424)
 * Link:
 * https://leetcode.com/problems/longest-repeating-character-replacement/description/
 *
 * Approach: This problem can be solved using an efficient sliding window
 *           approach. The goal is to find the longest window where the number
 *           of characters that need to be replaced is no more than `k`.
 *
 *           1.  **Window and State:** We use two pointers, `low` and `high`, to
 *               define the window. We also maintain a frequency map (`charMap`)
 *               for the characters (A-Z) and a variable `maxFq` to track the
 *               frequency of the most common character within the current
 *               window.
 *           2.  **Expansion:** The `high` pointer expands the window to the
 *               right. We update the frequency of `s[high]` and update `maxFq`.
 *           3.  **Condition Check & Contraction:** The key condition is
 *               `(window_size) - maxFq > k`. The number of characters that are
 *               *not* the most frequent one is `window_size - maxFq`. If this
 *               count exceeds `k`, the window is invalid. We shrink the window
 *               from the left by incrementing `low` and decrementing the count
 *               of the character at `s[low]`.
 *           4.  **Update Answer:** The window size `high - low + 1` is always a
 *               candidate for the maximum length. Since the window only grows
 *               or slides (maintaining its size), the final window size will
 *               represent the maximum length found.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int characterReplacement(const string& s, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;
    int k;
    cin >> k;

    cout << "Input String: " << s << endl;
    cout << "k: " << k << endl;

    cout << "Length of Longest Substring: " << characterReplacement(s, k)
         << endl;
  }

  return 0;
}

int characterReplacement(const string& s, int k) {
  int charMap[26] = {0};
  int low = 0;
  int high = 0;

  int maxLength = 0;
  int maxFq = 0;
  while (high < s.length()) {
    // Expand the window and update the frequency map and max frequency.
    charMap[s[high] - 'A']++;
    maxFq = max(maxFq, charMap[s[high] - 'A']);

    // The number of characters to replace is `window_size - maxFq`.
    // If this exceeds k, the window is invalid, so we shrink it.
    if ((high - low + 1) - maxFq > k) {
      charMap[s[low] - 'A']--;
      low++;
    }

    // The current window size is always a candidate for the max length.
    // Since the window only grows or slides, this will find the max.
    maxLength = max(maxLength, high - low + 1);

    // Move the high pointer to continue expanding.
    high++;
  }

  return maxLength;
}
