/*
 * Problem: Count and Say (LeetCode #38)
 * Link: https://leetcode.com/problems/count-and-say/description/
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

/**
 * Approach: This is a recursive solution. The base case is when `n` is 1,
 *           returning "1". For any other `n`, it makes a recursive call to get
 *           the `(n-1)th` term and then passes that result to a helper
 *           function `generateString` to produce the `nth` term.
 *
 * Time Complexity: O(N * L), where N is the input number and L is the average
 *                  length of the generated strings.
 * Space Complexity: O(L_max), where L_max is the length of the longest string.
 */
string recursiveApproach(int n);

/**
 * Approach: This is an iterative solution. It starts with the first term "1"
 *           and then loops from 2 to `n`. In each iteration, it generates the
 *           next term in the sequence by calling the `generateString` helper
 *           on the current term.
 *
 * Time Complexity: O(N * L), where N is the input number and L is the average
 *                  length of the generated strings.
 * Space Complexity: O(L_max), where L_max is the length of the longest string.
 */
string iterativeApproach(int n);

string generateString(string& s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    cout << "n: " << n << endl;
    cout << "Count and Say (Recursive): " << recursiveApproach(n) << endl;
    cout << "Count and Say (Iterative): " << iterativeApproach(n) << endl;

    cout << endl;
  }

  return 0;
}

//------------------------------RECURSIVE APPROACH------------------------------
string recursiveApproach(int n) {
  if (n == 1) {
    return "1";
  }

  string s = recursiveApproach(n - 1);
  return generateString(s);
}

//------------------------------ITERATIVE APPROACH------------------------------
string iterativeApproach(int n) {
  string s = "1";
  for (int i = 2; i <= n; i++) {
    s = generateString(s);
  }

  return s;
}

//-----------------------------------HELPER-------------------------------------
string generateString(string& s) {
  string res = "";
  int low = 0;
  int high = 0;
  while (high < s.length()) {
    high++;

    if (high >= s.length() || s[low] != s[high]) {
      int val = high - low;
      res += to_string(val);
      res += s[low];
      low = high;
    }
  }
  return res;
}
