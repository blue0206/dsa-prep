/*
 * Problem: Count All Substrings
 *
 * Statement: Given a string `s`, count the total number of non-empty
 *            substrings.
 *
 * Approach: The number of substrings in a string of length `n` can be
 *           calculated using a simple combinatorial formula.
 *           - There are `n` substrings of length 1.
 *           - There are `n-1` substrings of length 2.
 *           - ...
 *           - There is 1 substring of length `n`.
 *           The total is the sum of the first `n` natural numbers:
 *           `1 + 2 + ... + n`, which is equal to `n * (n + 1) / 2`.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int countSubstrings(string s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    cout << "String: " << s << endl;

    cout << "Result: " << countSubstrings(s) << endl;

    cout << endl;
  }

  return 0;
}

int countSubstrings(string s) {
  int n = s.length();
  return (n * (n + 1)) / 2;
}
