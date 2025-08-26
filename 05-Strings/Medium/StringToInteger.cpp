/*
 * Problem: String to Integer (atoi) (LeetCode #8)
 * Link: https://leetcode.com/problems/string-to-integer-atoi/description/
 *
 * Approach: The algorithm follows a set of explicit rules:
 *           1.  Read in and ignore any leading whitespace.
 *           2.  Check if the next character is '-' or '+'. Store the sign.
 *           3.  Read in the next characters until a non-digit character is
 *               found or the end of the string is reached.
 *           4.  Convert these digits into an integer.
 *           5.  During conversion, check for overflow. If the number exceeds
 *               `INT_MAX` or `INT_MIN`, clamp it to the respective limit.
 *           6.  Return the integer with the correct sign.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int myAtoi(string s);

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
  int i = 0;
  int n = s.length();
  int sign = 1;

  // 1. Escape whitespace.
  while (i < n && s[i] == ' ') i++;

  // 2. Set sign.
  if (i < n && (s[i] == '+' || s[i] == '-')) {
    sign = (s[i] == '-') ? -1 : 1;
    i++;
  }

  long long result = 0;
  while (i < n && isdigit(s[i])) {
    int digit = s[i] - '0';
    result = (result * 10) + digit;

    if (result * sign > INT_MAX) {
      return INT_MAX;
    }
    if (result * sign < INT_MIN) {
      return INT_MIN;
    }
    i++;
  }

  return (int)(sign * result);
}
