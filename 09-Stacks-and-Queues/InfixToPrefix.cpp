/*
 * Problem: Infix to Prefix
 * Link: https://www.geeksforgeeks.org/problems/infix-to-prefix-notation/1
 *
 * Approach: A straightforward way to convert from infix to prefix is to use a
 *           two-step process involving an intermediate postfix conversion.
 *
 *           1.  **Step 1: Infix to Postfix Conversion**
 *               -   The standard Shunting-yard algorithm is used to convert the
 *                   infix expression to its postfix equivalent.
 *               -   This involves using a stack to manage operators based on
 *                   their precedence. Special handling is included for the
 *                   right-associative exponentiation operator (`^`).
 *
 *           2.  **Step 2: Postfix to Prefix Conversion**
 *               -   The postfix string generated in the first step is then
 *                   converted to the final prefix expression.
 *               -   This is done by iterating through the postfix string from
 *                   left to right and using a stack. Operands are pushed onto
 *                   the stack. When an operator is encountered, two operands
 *                   are popped, combined into a prefix sub-expression
 *                   (`operator + op1 + op2`), and the result is pushed back.
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

string infixToPrefix(string &s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string exp;
    cin >> exp;

    cout << "Infix Expression: " << exp << endl;

    cout << "Prefix Expression: " << infixToPrefix(exp) << endl;

    cout << endl;
  }

  return 0;
}

string infixToPrefix(string &s) {
  unordered_map<char, int> mp;
  mp['('] = 0;
  mp['-'] = 1;
  mp['+'] = 1;
  mp['*'] = 2;
  mp['/'] = 2;
  mp['^'] = 3;

  // Step 1: Convert Infix to Postfix
  stack<char> op;
  string postfix = "";

  for (int i = 0; i < s.length(); i++) {
    if (isalpha(s[i]) || isdigit(s[i])) {
      postfix += s[i];
    } else if (s[i] == '(') {
      op.push(s[i]);
    } else if (s[i] == ')') {
      while (op.top() != '(') {
        postfix += op.top();
        op.pop();
      }
      op.pop();
    } else {
      if (op.empty() || mp[s[i]] > mp[op.top()]) {
        op.push(s[i]);
      } else {
        // Handle right-associative '^' separately.
        while ((mp[s[i]] < mp[op.top()]) ||
               (mp[s[i]] == mp[op.top()] && s[i] != '^')) {
          postfix += op.top();
          op.pop();

          if (op.empty()) break;
        }
        op.push(s[i]);
      }
    }
  }

  while (!op.empty()) {
    postfix += op.top();
    op.pop();
  }

  // Step 2: Convert Postfix to Prefix
  stack<string> operands;

  for (int i = 0; i < postfix.length(); i++) {
    if (isdigit(postfix[i]) || isalpha(postfix[i])) {
      operands.push(string(1, postfix[i]));
    } else {
      string op2 = operands.top();
      operands.pop();
      string op1 = operands.top();
      operands.pop();

      string temp = postfix[i] + op1 + op2;
      operands.push(temp);
    }
  }

  string ans = "";
  while (!operands.empty()) {
    ans += operands.top();
    operands.pop();
  }

  return ans;
}
