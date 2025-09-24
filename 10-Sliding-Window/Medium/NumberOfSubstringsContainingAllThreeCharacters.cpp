/*
 * Problem: Number of Substrings Containing All Three Characters
            (LeetCode #1358)
 * Link:
 * https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/description/
 *
 * Approach: This problem can be solved efficiently using a sliding window. The
 *           key insight is that once we find a valid substring `s[low...high]`
 *           that contains all three characters ('a', 'b', 'c'), any substring
 *           that starts at `low` and ends at or after `high` will also be
 *           valid.
 *
 *           1.  We use a sliding window with pointers `low` and `high`.
 *           2.  We expand the window by moving `high` and tracking character
 *               counts in a frequency map.
 *           3.  Once the window `[low, high]` is valid (contains 'a', 'b','c'),
 *               we know that any substring starting at `low` and ending at
 *               `high`, `high+1`, ..., `n-1` is also valid. There are
 *               `n - high` such substrings, so we add this to our count.
 *           4.  We then shrink the window by moving `low` to the right and
 *               repeat the process to find the next valid starting point.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int numberOfSubstrings(const string& s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    cout << "Input String: " << s << endl;

    cout << "Number of Substrings: " << numberOfSubstrings(s) << endl;
  }

  return 0;
}

int numberOfSubstrings(const string& s) {
  int n = s.length();

  int low = 0;
  int high = 0;
  int charMap[3] = {0};

  long long count = 0;
  while (high < n) {
    // Expand the window.
    charMap[s[high] - 'a']++;

    // Once the window is valid, calculate contributions and shrink.
    while (charMap[0] > 0 && charMap[1] > 0 && charMap[2] > 0) {
      // If s[low..high] is a valid substring, then any substring starting
      // at `low` and ending at `high` or later is also valid.
      // There are `n - high` such substrings.
      count += (n - high);

      // Shrink the window from the left to find the next valid configuration.
      charMap[s[low] - 'a']--;
      low++;
    }

    high++;
  }

  return count;
}
