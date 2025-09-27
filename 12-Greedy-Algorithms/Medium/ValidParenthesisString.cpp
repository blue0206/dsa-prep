/*
 * Problem: Valid Parenthesis String (LeetCode #678)
 * Link: https://leetcode.com/problems/valid-parenthesis-string/description/
 *
 * Approach: This problem can be solved with a greedy O(N) approach. The key
 *           idea is to keep track of the possible range of the balance of open
 *           parentheses. We use two counters: `low` and `high`.
 *
 *           - `low`: Represents the minimum possible number of open
 *             parentheses, treating every `*` as a closing parenthesis `)`.
 *           - `high`: Represents the maximum possible number of open
 *             parentheses, treating every `*` as an opening parenthesis `(`.
 *
 *           We iterate through the string:
 *           - If we see `(`, we increment both `low` and `high`.
 *           - If we see `)`, we decrement both `low` and `high`.
 *           - If we see `*`, it could be `(`, `)`, or empty. So, we decrement
 *             `low` and increment `high` to cover all possibilities.
 *           - `low` is always capped at 0, as we can't have a negative balance.
 *           - If `high` ever drops below 0, it's impossible to form a valid
 *             string.
 *           - Finally, the string is valid if and only if `low` is 0 at the
 *             end.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

bool checkValidString(string s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    cout << "String: " << s << endl;

    cout << "Result: " << (checkValidString(s) ? "True" : "False") << endl;
  }

  return 0;
}

bool checkValidString(string s) {
  int low = 0;
  int high = 0;

  for (char c : s) {
    if (c == '(') {
      low++;
      high++;
    } else if (c == ')') {
      low = max(0, low - 1);
      high--;
    } else {                  // c == '*'
      low = max(0, low - 1);  // Treat '*' as ')'
      high++;                 // Treat '*' as '('
    }

    // If high < 0, it means we have too many ')' even if all '*' are '('.
    if (high < 0) return false;
  }

  // At the end, low must be 0 to have a valid string.
  return low == 0;
}
