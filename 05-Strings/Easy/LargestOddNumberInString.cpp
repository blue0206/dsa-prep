/*
 * Problem: Largest Odd Number in String (LeetCode #1903)
 * Link: https://leetcode.com/problems/largest-odd-number-in-string/description/
 *
 * Approach: The core property of an odd number is that its last digit must be
 *           odd. To find the largest odd number that is a prefix of the input
 *           string, we need to find the longest prefix that ends in an odd
 *           digit.
 *           This can be achieved by iterating through the string from right to
 *           left. The first odd digit we encounter from the right will be the
 *           last digit of our answer. The substring from the beginning of the
 *           string up to and including this digit is the largest possible odd
 *           number prefix. If no odd digits are found, no such prefix exists,
 *           and we return an empty string.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

string largestOddNumber(string num);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    cout << "String: " << s << endl;

    cout << "Largest Odd Number: " << largestOddNumber(s) << endl;

    cout << endl;
  }

  return 0;
}

string largestOddNumber(string num) {
  for (int i = num.length() - 1; i >= 0; i--) {
    int digit = num[i] - '0';
    if (digit & 1) {
      num.resize(i + 1);
      return num;
    }
  }

  return "";
}
