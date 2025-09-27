/*
 * Problem: Jump Game (LeetCode #55)
 * Link: https://leetcode.com/problems/jump-game/description/
 *
 * Approach: This problem can be solved using a greedy approach. The core idea
 *           is to keep track of the maximum index that can be reached from the
 *           start.
 *
 *           1.  Initialize a variable `maxReach` to 0. This variable will
 *               store the farthest index we can currently reach.
 *           2.  Iterate through the array with an index `i`. At each step, we
 *               first check if the current index `i` is reachable. If `i` is
 *               greater than `maxReach`, it means we got stuck at a previous
 *               position and cannot proceed, so we return `false`.
 *           3.  If the current index `i` is reachable, we update `maxReach` by
 *               taking the maximum of its current value and `i + nums[i]` (the
 *               farthest we can jump from the current position).
 *           4.  If the loop completes, it means we were able to reach every
 *               index up to the end, so we return `true`.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool canJump(vector<int>& nums);

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

    cout << "Result: " << (canJump(nums) ? "True" : "False") << endl;
  }

  return 0;
}

bool canJump(const vector<int>& nums) {
  int maxReach = 0;
  for (int i = 0; i < nums.size(); i++) {
    // If the current index `i` is beyond our max reach, we can't get here.
    if (i > maxReach) {
      return false;
    }
    // Update the maximum reach based on the jump from the current index.
    maxReach = max(maxReach, i + nums[i]);
  }

  // If the loop completes, it means the last index was reachable.
  return true;
}
