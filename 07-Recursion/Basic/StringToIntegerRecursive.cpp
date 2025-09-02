/*
 * Problem: String to Integer (atoi) (LeetCode #8)
 * Link: https://leetcode.com/problems/string-to-integer-atoi/description/
 *
 * Approach: This solution separates the logic into a main parsing function and
 *           a recursive helper.
 *           1. The main function `myAtoi` handles the initial parsing: it
 *              skips leading whitespace, determines the sign, and skips any
 *              leading zeros.
 *           2. It then calls a recursive helper function `aToI` on the
 *              remaining part of the string.
 *           3. The `aToI` function recursively builds the number. The base case
 *              is reaching a non-digit character or the end of the string. In
 *              the recursive step, it processes the current digit and calls
 *              itself on the next character. It includes an overflow check.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N) due to recursion call stack
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int myAtoi(string s);
long long aToI(string& s, int index, long long currentAns);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string s;
    getline(cin, s);

    cout << "String: " << s << endl;

    cout << "Result: " << myAtoi(s) << endl;

    cout << endl;
  }

  return 0;
}

int myAtoi(string s) {
  int sign = 1;
  int index = 0;

  // 1. Skip whitespaces.
  while (index < s.length() && s[index] == ' ') index++;
  if (index == s.length()) {
    return 0;
  }

  // 2. Set sign.
  if (s[index] == '+' || s[index] == '-') {
    sign = (s[index] == '+') ? 1 : -1;
    index++;
  }

  // 3. Skip leading zeroes.
  while (index < s.length() && s[index] == '0') index++;
  if (index == s.length()) {
    return 0;
  }

  long long ans = aToI(s, index, 0) * sign;

  // Overflow check.
  if (ans >= INT_MAX) {
    return INT_MAX;
  } else if (ans <= INT_MIN) {
    return INT_MIN;
  }

  return (int)(ans);
}

long long aToI(string& s, int index, long long currentAns) {
  // Overflow check.
  if (currentAns > INT_MAX) return 1LL * INT_MAX + 1;  // +1 to handle INT_MIN

  // Base case.
  if (index >= s.length() || !isdigit(s[index])) {
    return currentAns;
  }

  // Extract digit and append to answer number.
  long long digit = s[index] - '0';
  long long ans = (currentAns * 10) + digit;
  return aToI(s, index + 1, ans);
}
