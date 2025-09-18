/*
 * Problem: Infix to Postfix
 * Link:
 * https://www.naukri.com/code360/problems/day-23-:-infix-to-postfix-_1382146?leftPanelTabValue=PROBLEM
 *
 * Approach: This problem is solved using the Shunting-yard algorithm, which
 *           utilizes a stack to correctly order operators based on their
 *           precedence.
 *
 *           1.  **Initialization:** Create an empty stack for operators and an
 *               empty string for the postfix result. Use a map to define the
 *               precedence of each operator.
 *           2.  **Scan Expression:** Iterate through the infix expression.
 *               - **Operand:** If the character is an operand (a letter or
 *                 digit), append it directly to the result string.
 *               - **'(':** If it's an opening parenthesis, push it onto the
 *                 stack.
 *               - **')':** If it's a closing parenthesis, pop from the stack
 *                 and append to the result until an opening parenthesis is
 *                 found. Pop the opening parenthesis but do not append it.
 *               - **Operator:** If it's an operator, pop from the stack and
 *                 append to the result as long as the stack is not empty and
 *                 the operator at the top has a precedence greater than or
 *                 equal to the current operator. Then, push the current
 *                 operator onto the stack.
 *           3.  **Finalize:** After scanning the whole expression, pop any
 *               remaining operators from the stack and append them to the
 *               result.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

string infixToPostfix(string exp);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string exp;
    cin >> exp;

    cout << "Infix Expression: " << exp << endl;

    cout << "Postfix Expression: " << infixToPostfix(exp) << endl;

    cout << endl;
  }

  return 0;
}

string infixToPostfix(string exp) {
  unordered_map<char, int> mp;
  mp['('] = 0;
  mp['+'] = 1;
  mp['-'] = 1;
  mp['/'] = 2;
  mp['*'] = 2;
  mp['^'] = 3;
  string ans = "";
  stack<char> st;

  for (int i = 0; i < exp.length(); i++) {
    // If the character is an operand, add it to the result.
    if (isdigit(exp[i]) || isalpha(exp[i])) {
      ans += exp[i];
    } else if (exp[i] == '(') {
      // If it's an opening parenthesis, push it onto the stack.
      st.push(exp[i]);
    } else if (exp[i] == ')') {
      // If it's a closing parenthesis, pop and output from the stack
      // until an opening parenthesis is found.
      while (st.top() != '(') {
        ans += st.top();
        st.pop();
      }
      st.pop();  // Pop the opening parenthesis.
    } else {
      // An operator is encountered.
      if (st.empty() || mp[exp[i]] > mp[st.top()]) {
        // If stack is empty or incoming operator has higher precedence.
        st.push(exp[i]);
      } else {
        // Pop all operators from the stack that have a higher or equal
        // precedence than the current operator.
        while (!st.empty() && mp[st.top()] >= mp[exp[i]]) {
          ans += st.top();
          st.pop();
        }
        st.push(exp[i]);
      }
    }
  }

  // Pop all the remaining operators from the stack.
  while (!st.empty()) {
    ans += st.top();
    st.pop();
  }

  return ans;
}
