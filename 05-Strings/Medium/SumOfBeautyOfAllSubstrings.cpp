/*
 * Problem: Sum of Beauty of All Substrings (LeetCode #1781)
 * Link:
 * https://leetcode.com/problems/sum-of-beauty-of-all-substrings/description/
 *
 * Approach: This approach iterates through all possible substrings. The outer
 *           loop fixes the starting point `i`, and the inner loop expands the
 *           substring by moving the endpoint `j`. For each substring
 *           `s[i...j]`, we maintain a frequency map of its characters. We then
 *           find the maximum and minimum frequency among the characters
 *           present in that substring and add their difference (the "beauty")
 *           to the total sum.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int beautySum(string s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    cout << "String: " << s << endl;

    cout << "Sum: " << beautySum(s) << endl;

    cout << endl;
  }

  return 0;
}

int beautySum(string s) {
  int sum = 0;

  for (int i = 0; i < s.length(); i++) {
    int charMap[26] = {0};

    for (int j = i; j < s.length(); j++) {
      int code = s[j] - 'a';
      charMap[code]++;
      int maxF = INT_MIN;
      int minF = INT_MAX;
      for (int k = 0; k < 26; k++) {
        if (charMap[k] > maxF) maxF = charMap[k];
        if (charMap[k] > 0 && charMap[k] < minF) minF = charMap[k];
      }

      sum += (maxF - minF);
    }
  }

  return sum;
}
