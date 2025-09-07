/*
 * Problem: Palindrome Partitioning (LeetCode #131)
 * Link: https://leetcode.com/problems/palindrome-partitioning/description/
 *
 * Approach: This problem is solved using a classic recursive backtracking
 *           approach. The idea is to try every possible "cut" in the string.
 *           From a given starting index, we iterate forward, and if we find a
 *           substring that is a palindrome, we make that our first partition
 *           and then recursively solve the problem for the rest of the string.
 *
 *           1. The recursive function `partitionPalindrome` takes a `start`
 *              index, which indicates the beginning of the substring we are
 *              currently trying to partition.
 *           2. **Base Case:** If the `start` index reaches the end of the
 *              string, it means we have successfully partitioned the entire
 *              string into palindromes. We add the current partition to our
 *              answer.
 *           3. **Recursive Step:** We loop from `start` to the end of the
 *              string. For each index `i`, we check if the substring from
 *              `start` to `i` is a palindrome. If it is, we add it to our
 *              current partition and make a recursive call for the remaining
 *              part of the string, starting from `i + 1`. We then backtrack.
 *
 * Time Complexity: O(N * 2^N)
 * Space Complexity: O(N) - For the recursion call stack depth.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using vs = vector<string>;
using vvs = vector<vs>;

vvs partition(string s);
void partitionPalindrome(vvs& ans, vs& partition, string& s, int index);
bool isPalindrome(string& str, int low, int high);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    cout << "Input: " << s << endl;

    vvs ans = partition(s);

    cout << "Partitions: [ ";
    for (auto partition : ans) {
      cout << "[ ";
      for (auto str : partition) {
        cout << str << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vvs partition(string s) {
  vvs ans;
  vs partition;

  partitionPalindrome(ans, partition, s, 0);
  return ans;
}

void partitionPalindrome(vvs& ans, vs& partition, string& s, int index) {
  // Base Case: If we've reached the end of the string, we have found a valid
  // partition.
  if (index == s.length()) {
    ans.emplace_back(partition);
    return;
  }

  // Iterate through all possible "cut" points from the current index.
  for (int i = index; i < s.length(); i++) {
    // If the substring from the current index to `i` is a palindrome...
    if (isPalindrome(s, index, i)) {
      // ...add it to our current partition and recurse for the rest of the
      // string.
      partition.emplace_back(s.substr(index, i - index + 1));
      partitionPalindrome(ans, partition, s, i + 1);
      partition.pop_back();
    }
  }
}

bool isPalindrome(string& str, int low, int high) {
  while (low < high) {
    if (str[low] != str[high]) {
      return false;
    }
    low++;
    high--;
  }
  return true;
}
