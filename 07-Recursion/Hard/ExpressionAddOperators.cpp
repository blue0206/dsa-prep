/*
 * Problem: Expression Add Operators (LeetCode #282)
 * Link: https://leetcode.com/problems/expression-add-operators/description/
 *
 * Approach: This problem is solved with a recursive backtracking approach. The
 *           core idea is to iterate through the input number string,
 *           partitioning it into operands. At each partition point, we decide
 *           which operator (`+`, `-`, or `*`) to insert.
 *
 *           1. **Recursive Function:** The function `generateExpression` keeps
 *              track of the current `index` in the number string, the
 *              expression string `exp` built so far, the evaluated result
 *              `res`, and the value of the last operand `prevOperand`.
 *           2. **Operand Generation:** A `for` loop starting from the current
 *              `index` is used to generate all possible next operands. For
 *              example, if the remaining string is "123", the loop will first
 *              consider "1", then "12", then "123".
 *           3. **Handling Operators:**
 *              - **Addition (`+`):** The new result is `res + nextOperand`.
 *              - **Subtraction (`-`):** The new result is `res - nextOperand`.
 *              - **Multiplication (`*`):** This is the key challenge due to
 *                operator precedence. The new result is calculated as
 *                `(res - prevOperand) + (prevOperand * nextOperand)`.
 *           4. **Base Case:** When the `index` reaches the end of the number
 *              string, we check if the final `res` equals the `target`.
 *           5. **Pruning:** Numbers with leading zeros (like "05") are invalid.
 *
 * Time Complexity: O(N * 4^N)
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ll = long long;
using vs = vector<string>;

vs addOperators(string num, int target);
void generateExpression(vs& ans, string& num, string exp, ll target, int index,
                        ll res, ll prevOperand);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string num;
    cin >> num;

    int target;
    cin >> target;

    cout << "Num: " << num << endl;
    cout << "Target: " << target << endl;

    vs expressions = addOperators(num, target);

    cout << "Expressions: [ ";
    for (auto exp : expressions) {
      cout << exp << " ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vs addOperators(string num, int target) {
  vs ans;

  generateExpression(ans, num, "", (ll)target, 0, 0, 0);
  return ans;
}

void generateExpression(vs& ans, string& num, string exp, ll target, int index,
                        ll res, ll prevOperand) {
  if (index == num.length()) {
    if (res == target) {
      ans.emplace_back(exp);
    }
    return;
  }

  ll nextOperand = 0;
  string numStr = "";
  for (int i = index; i < num.length(); i++) {
    numStr += num[i];
    nextOperand = (nextOperand * 10LL) + (num[i] - '0');

    if (index == 0) {
      // First number in the expression, no operator before it.
      generateExpression(ans, num, exp + numStr, target, i + 1, nextOperand,
                         nextOperand);
    } else {
      // Add operator.
      generateExpression(ans, num, exp + "+" + numStr, target, i + 1,
                         res + nextOperand, nextOperand);

      // Subtract operator.
      generateExpression(ans, num, exp + "-" + numStr, target, i + 1,
                         res - nextOperand, -nextOperand);

      // Multiply operator.
      // To handle precedence, we undo the previous operation and apply the
      // multiplication: (res - prev) + (prev * curr)
      generateExpression(ans, num, exp + "*" + numStr, target, i + 1,
                         res - prevOperand + (prevOperand * nextOperand),
                         prevOperand * nextOperand);
    }

    // Pruning: If the number starts with '0', it can't be multi-digit.
    if (num[index] == '0') break;
  }
}
