/*
 * Problem: Roman to Integer (LeetCode #13)
 * Link: https://leetcode.com/problems/roman-to-integer/description/
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/**
 * Approach: This approach iterates through the string from left to right. It
 *           looks at the next character to decide whether the current
 *           character's value should be added or subtracted. If the value of
 *           the current character is less than the value of the next one, it's
 *           a subtractive case (like 'IV' or 'IX'), so we subtract the current
 *           value. Otherwise, we add it.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int lookForwardApproach(string s);

/**
 * Approach: This approach also iterates from left to right. For each
 *           character, it checks if its value is greater than the previous
 *           character's value. If it is, it means we have a subtractive pair
 *           (like 'IV'). In this case, we add the current value but subtract
 *           the previous value twice (once to undo the initial addition and
 *           once for the actual subtraction). Otherwise, we just add the
 *           current value.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int lookBehindApproach(string s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    cout << "String: " << s << endl;

    cout << "Result (Look-Forward Approach): " << lookForwardApproach(s)
         << endl;
    cout << "Result (Look-Behind Approach): " << lookBehindApproach(s) << endl;

    cout << endl;
  }

  return 0;
}

int lookForwardApproach(string s) {
  unordered_map<char, int> romanMap = {{'I', 1},   {'V', 5},   {'X', 10},
                                       {'L', 50},  {'C', 100}, {'D', 500},
                                       {'M', 1000}};

  int val = 0;
  int n = s.length();
  for (int i = 0; i < n; i++) {
    // If the next character has a larger value, subtract the current one.
    if (i < n - 1 && romanMap[s[i]] < romanMap[s[i + 1]]) {
      val -= romanMap[s[i]];
    } else {
      // Otherwise, add the current value.
      val += romanMap[s[i]];
    }
  }

  return val;
}

int lookBehindApproach(string s) {
  unordered_map<char, int> romanMap = {{'I', 1},   {'V', 5},   {'X', 10},
                                       {'L', 50},  {'C', 100}, {'D', 500},
                                       {'M', 1000}};

  int val = 0;
  for (int i = 0; i < s.length(); i++) {
    // If this is not the first character and the current value is greater than
    // the previous, it's a subtractive case.
    if (i > 0 && romanMap[s[i]] > romanMap[s[i - 1]]) {
      // Add the current value, but subtract the previous value twice.
      // (Once to cancel the previous addition, once to actually subtract).
      val += (romanMap[s[i]] - (2 * romanMap[s[i - 1]]));
    } else {
      // Otherwise, just add the value.
      val += romanMap[s[i]];
    }
  }

  return val;
}
