/*
 * Problem: Generate Binary Strings Without Adjacent Zeros (LeetCode #3211)
 * Link:
 * https://leetcode.com/problems/generate-binary-strings-without-adjacent-zeros/description/
 *
 * Approach: This problem is a variation of generating all binary strings, but
 *           with the constraint that no two zeros can be adjacent. We use a
 *           recursive backtracking approach.
 *
 *           The recursive function `generateBS` builds the string position by
 *           position. It takes an extra parameter, `prevChar`, to know what
 *           character was placed at the previous index.
 *
 *           1. **Base Case:** If the current index `i` reaches the desired
 *              length `n`, the string is valid and complete. Add it to the
 *              result and return.
 *           2. **Recursive Step:** At index `i`, we have two choices:
 *              a) Place '0': A '0' can only be placed if the `prevChar` was not
 *                 '0'. If this condition is met, we make a recursive call for
 *                 `i+1` after placing a '0'.
 *              b) Place '1': A '1' can follow any character, so we always make
 *                 a recursive call for `i+1` after placing a '1'.
 *
 * Time Complexity: O(2^N) - A loose upper bound. The number of valid strings
 *                  grows according to the Fibonacci sequence.
 * Space Complexity: O(N) - For the recursion call stack depth.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> validStrings(int n);
void generateBS(vector<string>& strs, string& s, int n, int i, char prevChar);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    cout << "n: " << n << endl;
    vector<string> strs = validStrings(n);

    cout << "Valid Binary Strings: [ ";
    for (auto str : strs) {
      cout << str << " ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vector<string> validStrings(int n) {
  vector<string> strs;
  string s(n, ' ');

  generateBS(strs, s, n, 0, ' ');
  return strs;
}

void generateBS(vector<string>& strs, string& s, int n, int i, char prevChar) {
  // Base Case: If we have filled the string up to length n, it's a valid
  // string.
  if (i == n) {
    strs.push_back(s);
    return;
  }

  // Choice 1: Place '0'.
  // This is only allowed if the previous character was not '0'.
  if (prevChar != '0') {
    s[i] = '0';
    generateBS(strs, s, n, i + 1, '0');
  }

  // Choice 2: Place '1'.
  // This is always allowed.
  s[i] = '1';
  generateBS(strs, s, n, i + 1, '1');
}
