/*
 * Problem: Remove Outermost Parentheses (LeetCode #1021)
 * Link: https://leetcode.com/problems/remove-outermost-parentheses/description/
 *
 * Approach: We can solve this by iterating through the string and keeping
 *           track of the balance of open parentheses. A primitive
 *           decomposition starts when the balance is 0 and ends when it returns
 *           to 0. We want to include characters only when they are "inside" a
 *           primitive string.
 *           - When we see an opening parenthesis '(', we first check if the
 *             balance is > 0. If it is, we are inside a primitive string, so we
 *             add it to our result. Then, we increment the balance.
 *           - When we see a closing parenthesis ')', we first decrement the
 *             balance. Then, we check if the balance is > 0. If it is, we are
 *             still inside, so we add it to our result.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N) (for the result string)
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

string removeOuterParentheses(string s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    cout << "String: " << s << endl;

    cout << "Result: " << removeOuterParentheses(s) << endl;

    cout << endl;
  }

  return 0;
}

string removeOuterParentheses(string s) {
  int balance = 0;
  string ans = "";

  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '(') {
      if (balance > 0) {
        ans += s[i];
      }
      balance++;
    } else {
      balance--;
      if (balance > 0) {
        ans += s[i];
      }
    }
  }

  return ans;
}
