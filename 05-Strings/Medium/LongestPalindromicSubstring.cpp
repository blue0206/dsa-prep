/*
 * Problem: Longest Palindromic Substring (LeetCode #5)
 * Link:
 * https://leetcode.com/problems/longest-palindromic-substring/description/
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

/**
 * Approach: This method checks every possible substring to see if it's a
 *           palindrome. It uses two nested loops to generate all substrings
 *           and a helper function to check for palindromicity. To optimize,
 *           for each starting position `i`, it checks for the longest possible
 *           substring ending at `j` and works backwards. Once a palindrome is
 *           found, it breaks the inner loop since any shorter substring from
 *           `i` won't be the longest.
 *
 * Time Complexity: O(N^3)
 * Space Complexity: O(1)
 */
string bruteForceApproach(string s);
bool checkPalindrome(string& s, int low, int high);

/**
 * Approach: This is an optimized approach that considers each character (or
 *           pair of characters) as the center of a potential palindrome and
 *           expands outwards. It handles both odd-length (e.g., "aba") and
 *           even-length (e.g., "abba") palindromes. For each index `i`, it
 *           expands from `i` for odd lengths and from `i` and `i+1` for even
 *           lengths, keeping track of the longest palindrome found.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(1)
 */
string centerExpandApproach(string s);

/**
 * Note: Will be implemented once I learn DP (Step 16 of DSA Sheet).
 *
 * Approach:
 *
 * Time Complexity:
 * Space Complexity:
 */
string dpApproach(string s);

/**
 * Note: Will be implemented when I reach Step 18 of DSA Sheet.
 *
 * Approach: Manacher's Algorithm
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
string manachersApproach(string s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    cout << "String: " << s << endl;

    cout << "Result (Brute-Force Approach): " << bruteForceApproach(s) << endl;
    cout << "Result (Center-Expand Approach): " << centerExpandApproach(s)
         << endl;

    cout << endl;
  }

  return 0;
}

//-----------------------------BRUTE-FORCE APPROACH-----------------------------
string bruteForceApproach(string s) {
  int maxLength = 0;
  string ans = "";
  for (int i = 0; i < s.length(); i++) {
    for (int j = s.length() - 1; j >= i; j--) {
      if (checkPalindrome(s, i, j) && (j - i + 1) > maxLength) {
        maxLength = j - i + 1;
        ans = s.substr(i, maxLength);
        break;
      }
    }
  }

  return ans;
}

bool checkPalindrome(string& s, int low, int high) {
  while (low <= high) {
    if (s[low] != s[high]) return false;
    low++;
    high--;
  }

  return true;
}

//---------------------------CENTER-EXPAND APPROACH-----------------------------
string centerExpandApproach(string s) {
  string ans = "";
  int maxLength = 0;
  for (int i = 0; i < s.length(); i++) {
    int left = i;
    int right = i;
    while (left >= 0 && right < s.length() && s[left] == s[right]) {
      left--;
      right++;
    }
    if (right - left - 1 > maxLength) {
      maxLength = right - left - 1;
      ans = s.substr(left + 1, maxLength);
    }

    left = i;
    right = i + 1;
    while (left >= 0 && right < s.length() && s[left] == s[right]) {
      left--;
      right++;
    }
    if (right - left - 1 > maxLength) {
      maxLength = right - left - 1;
      ans = s.substr(left + 1, maxLength);
    }
  }

  return ans;
}
