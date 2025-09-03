/*
 * Problem: Generate Parentheses (LeetCode #22)
 * Link: https://leetcode.com/problems/generate-parentheses/description/
 *
 * Approach: This problem is solved using a recursive backtracking approach. We
 *           build the string of parentheses from left to right, character by
 *           character. The recursive function maintains a count of the
 *           remaining open (`lCount`) and close (`rCount`) parentheses we can
 *           place.
 *
 *           At each position, we have two potential choices:
 *           1. **Place '(':** We can place an opening parenthesis if we still
 *              have any left to place (`lCount > 0`).
 *           2. **Place ')':** We can place a closing parenthesis only if it
 *              doesn't create an invalid prefix. This is true if the number of
 *              closing parentheses we've placed is less than the number of
 *              opening ones, which translates to `rCount > lCount`.
 *
 * Time Complexity: O((4^n) / sqrt(n)) - The number of valid strings is the nth
 *                  Catalan number.
 * Space Complexity: O(n) - For the recursion call stack depth.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> generateParenthesis(int n);
void generateP(vector<string>& strs, string& s, int n, int i, int lCount,
               int rCount);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    cout << "n: " << n << endl;
    vector<string> strs = generateParenthesis(n);

    cout << "Valid Parenthesis: [ ";
    for (auto str : strs) {
      cout << str << " ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vector<string> generateParenthesis(int n) {
  vector<string> strs;
  string s(n * 2, ' ');

  generateP(strs, s, n * 2, 0, n, n);
  return strs;
}

void generateP(vector<string>& strs, string& s, int n, int i, int lCount,
               int rCount) {
  // Base Case: If the string is complete, we have found a valid combination.
  if (i == n) {
    strs.push_back(s);
    return;
  }

  // Choice 1: Place an opening parenthesis '('.
  // This is possible as long as we have open parentheses left to use.
  if (lCount > 0) {
    s[i] = '(';
    generateP(strs, s, n, i + 1, lCount - 1, rCount);
  }

  // Choice 2: Place a closing parenthesis ')'.
  // This is possible only if the number of closing parentheses does not exceed
  // the number of opening ones placed so far.
  if (rCount > lCount) {
    s[i] = ')';
    generateP(strs, s, n, i + 1, lCount, rCount - 1);
  }
}
