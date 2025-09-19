/*
 * Problem: Postfix to Infix
 * Link:
 * https://www.naukri.com/code360/problems/postfix-to-infix_8382386?leftPanelTabValue=PROBLEM
 *
 * Approach: The conversion from a postfix expression to an infix expression
 *           can be efficiently handled by scanning the postfix string from left
 *           to right and using a stack.
 *
 *           1.  **Scan Forwards:** Iterate through the postfix expression
 *               string from the first character to the last.
 *           2.  **Operand:** If the current character is an operand (a letter
 *               or a digit), push it onto a stack of strings.
 *           3.  **Operator:** If the current character is an operator, pop the
 *               top two operands from the stack (let's call them `op2` and
 *               `op1`). Form a new infix string by concatenating them with the
 *               operator in between and enclosing them in parentheses:
 *               `"(" + op1 + operator + op2 + ")"`. Push this new string back
 *               onto the stack.
 *           4.  **Result:** After the loop finishes, the stack will contain a
 *               single string, which is the final infix expression.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

string postToInfix(string postfix);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string exp;
    cin >> exp;

    cout << "Postfix Expression: " << exp << endl;

    cout << "Infix Expression: " << postToInfix(exp) << endl;

    cout << endl;
  }

  return 0;
}

string postToInfix(string postfix) {
  stack<string> operands;

  for (int i = 0; i < postfix.length(); i++) {
    // If the character is an operand, push it onto the stack.
    if (isalpha(postfix[i]) || isdigit(postfix[i])) {
      operands.push(string(1, postfix[i]));
    } else {
      // If the character is an operator, pop two operands.
      // Note: The first popped is operand2, the second is operand1.
      string op2 = operands.top();
      operands.pop();
      string op1 = operands.top();
      operands.pop();

      // Create a new infix expression by combining the operands and the
      // operator, enclosed in parentheses to maintain precedence.
      string temp = "(" + op1 + postfix[i] + op2 + ")";
      operands.push(temp);
    }
  }

  // The final infix expression is the only element left in the stack.
  string ans = "";
  while (!operands.empty()) {
    ans += operands.top();
    operands.pop();
  }

  return ans;
}
