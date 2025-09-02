/*
 * Problem: Generate All Binary Strings
 *
 * Statement: Given a number 'n', generate all binary strings of length 'n'.
 *
 * Approach: -----------------DECISION TREE MENTAL MODEL------------------------
 *           This problem is solved using a recursive backtracking approach that
 *           builds the binary strings character by character. The core idea is
 *           to model a decision tree where at each level, we decide which
 *           character ('0' or '1') to place at the current position.
 *
 *           1. The function `generateAllBinaryStrings` takes the string being
 *              built, its total length `n`, and the current index `i` to fill.
 *           2. **Base Case:** If the current index `i` equals `n`, it means we
 *              have successfully filled all positions. The complete string is
 *              printed, and the recursion returns.
 *           3. **Recursive Step:** For the current index `i`, we make two
 *              choices:
 *              a) Place '0' at `s[i]` and make a recursive call for the next
 *                 index, `i + 1`.
 *              b) Place '1' at `s[i]` and make another recursive call for
 *                 `i + 1`. This explores all 2^N possibilities.
 *
 * Time Complexity: O(2^N)
 * Space Complexity: O(N) for the recursion call stack depth.
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

void generateAllBinaryStrings(string& s, int n, int i);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    string s(n, ' ');
    generateAllBinaryStrings(s, n, 0);

    cout << endl;
  }

  return 0;
}

void generateAllBinaryStrings(string& s, int n, int i) {
  // Base Case: We have filled all positions from 0 to n-1.
  // The string is complete. Print it and stop this path.
  if (i == n) {
    cout << s << endl;
    return;
  }

  // --- The Recursive Step: Explore both choices for index i ---

  // Choice 1: Place '0' at index i
  s[i] = '0';
  // Recursively solve for the rest of the string starting from the next index.
  generateAllBinaryStrings(s, n, i + 1);

  // Choice 2: Place '1' at index i
  s[i] = '1';
  // Recursively solve for the rest of the string starting from the next index.
  generateAllBinaryStrings(s, n, i + 1);
}
