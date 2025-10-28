/*
 * Problem: Repeated String Match (LeetCode #686)
 * Link: https://leetcode.com/problems/repeated-string-match/description/
 *
 * Approach: The core idea is to build a string `temp` by repeating string `a`
 *           just enough times so that its length is greater than or equal to
 *           string `b`. Let this require `k` repetitions.
 *           - If `b` is a substring of `a` repeated `k` times, then `k` is a
 *             potential answer.
 *           - If not, `b` might still be a substring if it spans across the
 *             concatenation boundary. For example, if `a = "abcd"` and `b =
 *             "cdab"`. This can be checked by repeating `a` one more time
 *             (`k+1` times) and searching again.
 *           - If `b` is not found even after `k+1` repetitions, it's
 *             impossible to form, so we return -1.
 *
 * Time Complexity: O(M * N), where N is the length of `a` and M is the length
 *                  of `b`.
 * Space Complexity: O(M + N) for the temporary string.
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

int repeatedStringMatch(string a, string b);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string a, b;
    cin >> a >> b;

    cout << "String A: " << a << endl;
    cout << "String B: " << b << endl;

    cout << "Minimum Repeats: " << repeatedStringMatch(a, b) << endl;

    cout << endl;
  }

  return 0;
}

int repeatedStringMatch(string a, string b) {
  int count = 0;
  string temp = "";
  while (temp.length() < b.length()) {
    temp += a;
    count++;
  }

  if (temp.find(b) != string::npos) return count;
  temp += a;
  if (temp.find(b) != string::npos) return count + 1;
  return -1;
}
