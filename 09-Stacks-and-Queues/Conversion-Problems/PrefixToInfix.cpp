/*
 * Problem: Prefix to Infix
 * Link:
 * https://www.naukri.com/code360/problems/prefix-to-infix_1215000?leftPanelTabValue=PROBLEM
 *
 * Approach: The conversion from a prefix expression to an infix expression can
 *           be efficiently handled by scanning the prefix string from right to
 *           left and using a stack.
 *
 *           1.  **Scan Backwards:** Iterate through the prefix expression
 *               string from the last character to the first.
 *           2.  **Operand:** If the current character is an operand (a letter
 *               or a digit), push it onto a stack of strings.
 *           3.  **Operator:** If the current character is an operator, pop the
 *               top two operands from the stack (let's call them `op1` and
 *               `op2`). Form a new string by concatenating them with the
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

string prefixToInfixConversion(string &s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string exp;
    cin >> exp;

    cout << "Prefix Expression: " << exp << endl;

    cout << "Infix Expression: " << prefixToInfixConversion(exp) << endl;

    cout << endl;
  }

  return 0;
}

string prefixToInfixConversion(string &s) {
  stack<string> operands;

  for (int i = s.length() - 1; i >= 0; i--) {
    // If the character is an operand, push it onto the stack.
    if (isalpha(s[i]) || isdigit(s[i])) {
      operands.push(string(1, s[i]));
    } else {
      // If the character is an operator, pop two operands.
      string op1 = operands.top();
      operands.pop();
      string op2 = operands.top();
      operands.pop();

      // Create a new infix expression by combining the operands and the
      // operator, enclosed in parentheses to maintain precedence.
      string exp = "(" + op1 + s[i] + op2 + ")";
      operands.push(exp);
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
