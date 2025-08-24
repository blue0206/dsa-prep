/*
 * Problem: Longest Common Prefix (LeetCode #14)
 * Link: https://leetcode.com/problems/longest-common-prefix/description/
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Approach: This method iterates through the strings, treating the first string
 *           as the initial common prefix. For each subsequent string, it
 *           shortens the prefix until it matches the beginning of that string.
 *           If the prefix ever becomes empty, it means there's no common
 *           prefix, so an empty string is returned.
 *
 * Time Complexity: O(S), where S is the sum of all characters in all strings.
 * Space Complexity: O(1)
 */
string horizontalScanningApproach(vector<string>& strs);

/**
 * Approach: This method compares characters column by column. It iterates from
 *           the first character to the last of the first string. For each
 *           character `i`, it checks if this character is the same across all
 *           strings in the `i`-th position. If a mismatch is found or a string
 *           is shorter than `i`, the prefix up to that point is the LCP.
 *
 * Time Complexity: O(S), where S is the sum of all characters. In the worst
 *                  case, M*N where M is # of strings, N is length of LCP.
 * Space Complexity: O(1)
 */
string verticalScanningApproach(vector<string>& strs);

/**
 * Approach: This clever approach relies on the fact that after lexicographical
 *           sorting, the LCP for the entire array will be the common prefix
 *           between the very first and the very last string. We sort the array
 *           and then just compare the first and last strings.
 *
 * Time Complexity: O(S * log(M)), where S is avg string length and M is # of
 *                  strings, dominated by sorting.
 * Space Complexity: O(log M) to O(M), depending on sort implementation.
 */
string sortingApproach(vector<string>& strs);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    vector<string> strs(n);
    for (int i = 0; i < n; i++) cin >> strs[i];

    cout << "Strings: [ ";
    for (auto i : strs) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Result (Horizontal Scanning Approach): "
         << horizontalScanningApproach(strs) << endl;
    cout << "Result (Vertical Scanning Approach): "
         << verticalScanningApproach(strs) << endl;
    cout << "Result (Sorting Approach): " << sortingApproach(strs) << endl;

    cout << endl;
  }

  return 0;
}

string horizontalScanningApproach(vector<string>& strs) {
  int minLengthIndex = 0;
  // Find the smallest string.
  for (int i = 1; i < strs.size(); i++) {
    if (strs[i].length() < strs[minLengthIndex].length()) {
      minLengthIndex = i;
    }
  }

  int cutoff =
      strs[minLengthIndex].length();  // Stores the prefix match cutoff length.

  // Compare prefix with all strings and adjust cutoff.
  for (int i = 0; i < strs.size(); i++) {
    int index = 0;
    while (index < strs[i].length() && index < strs[minLengthIndex].length()) {
      if (strs[i][index] != strs[minLengthIndex][index]) {
        cutoff = min(index, cutoff);
      }
      index++;
    }
  }

  // Return the string upto cutoff.
  string ans = "";
  for (int i = 0; i < cutoff; i++) {
    ans += strs[minLengthIndex][i];
  }

  return ans;
}

string verticalScanningApproach(vector<string>& strs) {
  for (int i = 0; i < strs[0].length(); i++) {
    for (int j = 1; j < strs.size(); j++) {
      if (strs[0][i] != strs[j][i]) {
        return strs[0].substr(0, i);
      }
    }
  }

  return strs[0];
}

string sortingApproach(vector<string>& strs) {
  sort(strs.begin(), strs.end());

  int index = 0;
  while (index < strs[0].length()) {
    if (strs[0][index] != strs[strs.size() - 1][index]) {
      break;
    }
    index++;
  }

  string ans = "";
  for (int i = 0; i < index; i++) {
    ans += strs[0][i];
  }
  return ans;
}
