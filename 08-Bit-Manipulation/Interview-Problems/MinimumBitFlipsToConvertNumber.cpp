/*
 * Problem: Minimum Bit Flips to Convert Number (LeetCode #2220)
 * Link:
 * https://leetcode.com/problems/minimum-bit-flips-to-convert-number/description/
 */
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * Approach: This method iterates through the bits of both numbers from right
 *           to left. In each step, it compares the least significant bit (LSB)
 *           of `start` and `goal`. If the bits are different, it means a flip
 *           is required, so a counter is incremented. Both numbers are then
 *           right-shifted to process the next pair of bits. The loop continues
 *           until both numbers become zero.
 *
 * Time Complexity: O(log N), where N is the larger of the two numbers. The
 *                  loop runs for as many bits as are in the number.
 * Space Complexity: O(1)
 */
int countApproach(int start, int goal);

/**
 * Approach: This optimal approach uses the XOR operator. The expression
 *           `start ^ goal` yields a number where each bit is 1 if the
 *           corresponding bits in `start` and `goal` differ, and 0 otherwise.
 *           The problem then reduces to counting the number of set bits (1s)
 *           in this resulting number, which is done efficiently using the
 *           `__builtin_popcount` intrinsic function.
 *
 * Time Complexity: O(1) (practically, as it maps to a hardware instruction).
 * Space Complexity: O(1)
 */
int optimalApproach(int start, int goal);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int start, goal;
    cin >> start >> goal;

    cout << "Start: " << start << endl;
    cout << "Goal: " << goal << endl;

    cout << "Count Approach: " << countApproach(start, goal) << endl;
    cout << "Optimal Approach: " << optimalApproach(start, goal) << endl;

    cout << endl;
  }

  return 0;
}

int countApproach(int start, int goal) {
  int count = 0;

  while (start != 0 || goal != 0) {
    if ((start & 1) != (goal & 1)) count++;

    start >>= 1;
    goal >>= 1;
  }

  return count;
}

int optimalApproach(int start, int goal) {
  int diff = start ^ goal;

  return __builtin_popcount(diff);
}
