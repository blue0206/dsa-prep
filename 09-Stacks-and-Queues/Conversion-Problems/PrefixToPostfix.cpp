/*
 * Problem: Prefix to Postfix
 * Link:
 * https://www.naukri.com/code360/problems/convert-prefix-to-postfix_8391014?leftPanelTabValue=PROBLEM
 *
 * Approach: The conversion from a prefix expression to a postfix expression
 *           can be efficiently handled by scanning the prefix string from right
 *           to left and using a stack.
 *
 *           1.  **Scan Backwards:** Iterate through the prefix expression
 * string from the last character to the first.
 *           2.  **Operand:** If the current character is an operand (a letter
 * or a digit), push it onto a stack of strings.
 *           3.  **Operator:** If the current character is an operator, pop the
 *               top two operands from the stack (let's call them `op1` and
 *               `op2`). Form a new postfix string by concatenating them with
 *               the operator at the end: `op1 + op2 + operator`. Push this new
 *               string back onto the stack.
 *           4.  **Result:** After the loop finishes, the stack will contain a
 *               single string, which is the final postfix expression.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

string preToPost(string s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string exp;
    cin >> exp;

    cout << "Prefix Expression: " << exp << endl;

    cout << "Postfix Expression: " << preToPost(exp) << endl;

    cout << endl;
  }

  return 0;
}

string preToPost(string s) {
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

      // Create a new postfix expression by concatenating the operands first,
      // followed by the operator.
      string temp = op1 + op2 + s[i];
      operands.push(temp);
    }
  }

  // The final postfix expression is the only element left in the stack.
  string ans = "";
  while (!operands.empty()) {
    ans += operands.top();
    operands.pop();
  }

  return ans;
}
