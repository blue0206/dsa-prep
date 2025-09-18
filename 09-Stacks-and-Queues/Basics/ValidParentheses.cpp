/*
 * Problem: Valid Parentheses (LeetCode #20)
 * Link: https://leetcode.com/problems/valid-parentheses/description/
 *
 * Approach: This problem is a classic use case for a stack. The Last-In,
 *           First-Out (LIFO) nature of a stack is perfect for matching the
 *           most recently opened bracket with its corresponding closer.
 *
 *           1. Iterate through each character of the input string.
 *           2. If the character is an opening bracket ('(', '[', '{'), push it
 *              onto the stack.
 *           3. If the character is a closing bracket (')', ']', '}'), check if
 *              the stack is empty. If it is, there's no matching opener, so
 *              the string is invalid.
 *           4. If the stack is not empty, check if the top element is the
 *              corresponding opening bracket. If it is, pop the stack. If not,
 *              the brackets are mismatched, and the string is invalid.
 *           5. After the loop, if the stack is empty, all brackets were
 *              correctly matched and closed. If not, there are unclosed
 *              opening brackets, making the string invalid.
 *
 * Time Complexity: O(N), where N is the length of the string, as we iterate
 *                  through it once.
 * Space Complexity: O(N), as in the worst case (e.g., "((((...))))"), the
 *                   stack could hold all N characters.
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

bool isValid(string s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    cout << "Input: " << s << endl;

    cout << (isValid(s) ? "True" : "False") << endl;

    cout << endl;
  }

  return 0;
}

bool isValid(string s) {
  stack<char> st;

  for (int i = 0; i < s.length(); i++) {
    // If it's an opening bracket, push it onto the stack.
    if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
      st.push(s[i]);
    } else {
      // If it's a closing bracket but the stack is empty, it's invalid.
      if (st.empty()) return false;

      // Check if the closing bracket matches the last opening bracket.
      // This is a clever trick based on ASCII values:
      // ')' (41) - '(' (40) = 1
      // ']' (93) - '[' (91) = 2
      // '}' (125) - '{' (123) = 2
      int closingCharCode = s[i];
      int openingCharCode = st.top();
      if (closingCharCode - 2 == openingCharCode ||
          closingCharCode - 1 == openingCharCode) {
        st.pop();
      } else {
        return false;
      }
    }
  }

  return st.empty();
}
