/*
 * Problem: Minimum Add to Make Parentheses Valid (LeetCode #921)
 * Link:
 * https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/description/
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

/**
 * Approach: This approach uses a stack to keep track of open parentheses.
 *           - When an opening parenthesis `(` is encountered, it's pushed
 *             onto the stack.
 *           - When a closing parenthesis `)` is seen, we check the stack. If
 *             the stack is not empty, we pop an opening parenthesis, forming a
 *             valid pair. If the stack is empty, it means this closing
 *             parenthesis is unmatched, and we need to add one opening
 *             parenthesis.
 *           - After iterating, any remaining parentheses on the stack are
 *             unmatched, and we need to add a closing one for each.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N) in the worst case (e.g., "(((").
 */
int stackApproach(string& s);

/**
 * Approach: This is a constant-space greedy approach. We use two counters:
 *           `openBal` for unmatched open parentheses and `closeBal` for
 *           unmatched close parentheses.
 *           - When we see `(`, we increment `openBal`.
 *           - When we see `)`, if `openBal > 0`, we can match it by
 *             decrementing `openBal`. If `openBal` is 0, this `)` is unmatched,
 *             so we increment `closeBal`.
 *           - The total additions needed is the sum of `openBal` and
 *             `closeBal`.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int optimalApproach(string& s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    cout << "Input String: " << s << endl;
    cout << "Minimum Add (Stack): " << stackApproach(s) << endl;
    cout << "Minimum Add (Optimal): " << optimalApproach(s) << endl;

    cout << endl;
  }

  return 0;
}

int stackApproach(const string& s) {
  int ans = 0;
  stack<char> st;
  for (char ch : s) {
    if (ch == '(') {
      st.push(ch);
    } else {
      if (st.empty())
        ans++;
      else
        st.pop();
    }
  }

  return ans + st.size();
}

int optimalApproach(const string& s) {
  int closeBal = 0;
  int openBal = 0;
  for (char ch : s) {
    if (ch == '(') {
      openBal++;
    } else {
      if (openBal == 0)
        closeBal++;
      else
        openBal--;
    }
  }

  return closeBal + openBal;
}
