/*
 * Problem: Maximum Nesting Depth of the Parentheses (LeetCode #1614)
 * Link:
 * https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/description/
 *
 * Approach: The nesting depth at any point in a valid parentheses string is the
 *           number of open parentheses that have not yet been closed. We can
 *           track this by iterating through the string with a counter.
 *           - Initialize a `balance` counter and a `maxBalance` tracker to 0.
 *           - Iterate through each character of the string.
 *           - If the character is '(', increment `balance`.
 *           - If the character is ')', decrement `balance`.
 *           - After updating the balance for each character, update
 *             `maxBalance` with the maximum value `balance` has reached so far.
 *           - The final `maxBalance` is the answer.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int maxDepth(string s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    cout << "String: " << s << endl;

    cout << "Max Depth: " << maxDepth(s) << endl;

    cout << endl;
  }

  return 0;
}

int maxDepth(string s) {
  int maxBalance = 0;
  int balance = 0;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '(') {
      balance++;
    } else if (s[i] == ')') {
      balance--;
    }

    maxBalance = max(maxBalance, balance);
  }

  return maxBalance;
}
