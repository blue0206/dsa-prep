/*
 * Problem: Postfix to Prefix
 * Link:
 * https://www.naukri.com/code360/problems/postfix-to-prefix_1788455?leftPanelTabValue=PROBLEM
 *
 * Approach: The conversion from a postfix expression to a prefix expression
 *           can be efficiently handled by scanning the postfix string from left
 *           to right and using a stack.
 *
 *           1.  **Scan Forwards:** Iterate through the postfix expression
 *               string from the first character to the last.
 *           2.  **Operand:** If the current character is an operand (a letter
 *               or a digit), push it onto a stack of strings.
 *           3.  **Operator:** If the current character is an operator, pop the
 *               top two operands from the stack (let's call them `op2` and
 *               `op1`). Form a new prefix string by concatenating the operator
 *               first, then `op1`, then `op2`: `operator + op1 + op2`. Push
 *               this new string back onto the stack.
 *           4.  **Result:** After the loop finishes, the stack will contain a
 *               single string, which is the final prefix expression.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

string postfixToPrefix(string &s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string exp;
    cin >> exp;

    cout << "Postfix Expression: " << exp << endl;

    cout << "Prefix Expression: " << postfixToPrefix(exp) << endl;

    cout << endl;
  }

  return 0;
}

string postfixToPrefix(string &s) {
  stack<string> operands;

  for (int i = 0; i < s.length(); i++) {
    // If the character is an operand, push it onto the stack.
    if (isalpha(s[i]) || isdigit(s[i])) {
      operands.push(string(1, s[i]));
    } else {
      // If the character is an operator, pop two operands.
      // Note: The first popped is operand2, the second is operand1.
      string op2 = operands.top();
      operands.pop();
      string op1 = operands.top();
      operands.pop();

      // Create a new prefix expression by concatenating the operator first,
      // followed by operand1 and operand2.
      string temp = s[i] + op1 + op2;
      operands.push(temp);
    }
  }

  // The final prefix expression is the only element left in the stack.
  string ans = "";
  while (!operands.empty()) {
    ans += operands.top();
    operands.pop();
  }

  return ans;
}
