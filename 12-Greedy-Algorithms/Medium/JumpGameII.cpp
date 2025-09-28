/*
 * Problem: Jump Game II (LeetCode #45)
 * Link: https://leetcode.com/problems/jump-game-ii/description/
 *
 * Approach: This is a classic greedy problem that can be visualized as a
 *           level-order traversal (BFS) on the array indices. We want to find
 *           the minimum number of "jumps" (levels) to reach the end.
 *
 *           1.  **`jumps`**: Counts the number of jumps taken.
 *           2.  **`currentEnd`**: Marks the farthest index that can be reached
 *               with the current number of jumps. It's the end of the current
 *               "level" in our BFS.
 *           3.  **`maxReach`**: Tracks the farthest index we can possibly
 *               reach from any position within the current level.
 *
 *           We iterate through the array. At each position `i`, we update
 *           `maxReach`. When `i` reaches `currentEnd`, it signifies that we've
 *           exhausted all positions reachable with the current number of jumps.
 *           We must therefore take another jump, so we increment `jumps` and
 *           set the new `currentEnd` to the `maxReach` we've found so far.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int jump(const vector<int>& nums);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Nums: [ ";
    for (int i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Jumps: " << jump(nums) << endl;
  }

  return 0;
}

int jump(const vector<int>& nums) {
  if (nums.size() <= 1) return 0;

  int currentEnd = 0;
  int jumps = 0;
  int maxReach = 0;

  for (int i = 0; i < nums.size() - 1; i++) {
    // Update the farthest we can reach from the current level.
    maxReach = max(maxReach, i + nums[i]);

    if (i == currentEnd) {
      jumps++;
      currentEnd = maxReach;
    }
  }

  return jumps;
}
