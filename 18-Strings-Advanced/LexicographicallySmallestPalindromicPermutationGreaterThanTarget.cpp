/*
 * Problem: Lexicographically Smallest Palindromic Permutation Greater Than
 *          Target (LeetCode #3734)
 * Link:
 * https://leetcode.com/problems/lexicographically-smallest-palindromic-permutation-greater-than-target/description/
 *
 * Approach: This problem is solved using a recursive backtracking algorithm.
 *           1.  **Feasibility Check:** First, count the character frequencies
 *               in the input string `s`. A palindromic permutation is only
 *               possible if at most one character has an odd count.
 *               If not, no such palindrome exists.
 *           2.  **Half-String Construction:** The problem is reduced to
 *               constructing the first half of the palindrome. The second half
 *               is its mirror image.
 *           3.  **Recursive Backtracking:** A recursive function `generate` is
 *               used to build this first half. It maintains a `greater` flag
 *               to track if the string being built is already
 *               lexicographically larger than the target's prefix.
 *               - If `greater` is false, it tries to match the target's
 *                 prefix or find the first character larger than the target's.
 *               - If `greater` is true, it greedily picks the smallest
 *                 available characters to complete the half-string.
 *           4.  **Palindrome Assembly:** Once a valid half-string is generated
 *               that results in a palindrome greater than the target, the full
 *               palindrome is constructed and returned.
 *
 * Time Complexity: O((N/2) * 26), where N is the length of the string. The
 *                  recursion depth is N/2, and at each level, we iterate up to
 *                  26 characters.
 * Space Complexity: O(N) for the recursion stack and storing the result.
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

string lexPalindromicPermutation(string s, string target);
bool generate(unordered_map<char, int>& halfCounts, string& s, string& target,
              int oddCount, char oddChar, string& res, bool greater);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s, target;
    cin >> s >> target;

    cout << "String: " << s << endl;
    cout << "Target: " << target << endl;

    cout << "Lexicographically Smallest Palindromic Permutation Greater Than "
            "Target: "
         << lexPalindromicPermutation(s, target) << endl;

    cout << endl;
  }

  return 0;
}

string lexPalindromicPermutation(string s, string target) {
  unordered_map<char, int> counts, halfCounts;
  for (char ch : s) {
    counts[ch]++;
  }
  int oddCount = 0;
  char oddChar = '.';
  for (char c = 'a'; c <= 'z'; c++) {
    halfCounts[c] = counts[c] / 2;
    if (counts[c] & 1) {
      oddCount++;
      oddChar = c;
    }
  }

  if (oddCount > 1) {
    return "";
  }

  string res = "";
  if (generate(halfCounts, s, target, oddCount, oddChar, res, false)) {
    return res;
  }

  return "";
}

bool generate(unordered_map<char, int>& halfCounts, string& s, string& target,
              int oddCount, char oddChar, string& res, bool greater) {
  if (res.length() == s.length() / 2) {
    string palindrome = res;
    string temp = res;
    reverse(temp.begin(), temp.end());
    if (oddCount == 1) palindrome += oddChar;
    palindrome += temp;

    if (palindrome > target) res = palindrome;
    return (palindrome > target);
  }

  int i = res.length();
  char ch = (greater) ? 'a' : target[i];
  while (ch <= 'z') {
    if (halfCounts[ch] > 0) {
      halfCounts[ch]--;
      res.push_back(ch);
      bool flag = (greater) ? greater : ch > target[i];
      if (generate(halfCounts, s, target, oddCount, oddChar, res, flag)) {
        return true;
      }
      halfCounts[ch]++;
      res.pop_back();
    }
    ch++;
  }

  return false;
}
