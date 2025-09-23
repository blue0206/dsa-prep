/*
 * Problem: Max Consecutive Ones III (LeetCode #1004)
 * Link: https://leetcode.com/problems/max-consecutive-ones-iii/
 *
 * Approach: This problem can be solved using a sliding window approach.
 *           The goal is to find the longest subarray containing at most `k`
 *           zeros.
 *
 *           1.  **Window and State:** We use two pointers, `low` and `high`, to
 *               define the current window. We maintain a `flips` counter, which
 *               tracks the number of zeros within the current window.
 *           2.  **Expansion:** The `high` pointer moves to the right, expanding
 *               the window. If `nums[high]` is a `0`, we increment `flips`.
 *           3.  **Contraction:** If `flips` exceeds `k` (meaning the window has
 *               too many zeros), we need to shrink the window from the left.
 *               We move the `low` pointer to the right. If `nums[low]` was a
 *               `0`, we decrement `flips`. This continues until `flips` is
 *               less than or equal to `k`.
 *           4.  **Update Answer:** After each expansion and potential
 *               contraction, the window `[low, high]` is guaranteed to be
 *               valid. We update `maxLength` with the current window size
 *               (`high - low + 1`).
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int longestOnes(const vector<int>& nums, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "k: " << k << endl;

    cout << "Input Array: [ ";
    for (int i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Maximum Consecutive Ones: " << longestOnes(nums, k) << endl;
  }

  return 0;
}

int longestOnes(const vector<int>& nums, int k) {
  int low = 0;
  int high = 0;

  int flips = 0;
  int maxLength = 0;
  while (high < nums.size()) {
    // Expand the window: If the current element is 0, increment flips.
    if (nums[high] == 0) flips++;

    // Contract the window: If flips exceed k, shrink the window from the left.
    while (flips > k) {
      // If the element leaving the window was 0, decrement flips.
      if (nums[low] == 0) flips--;
      low++;
    }

    // Update the maximum length of the valid window.
    maxLength = max(maxLength, high - low + 1);

    // Move the high pointer to expand the window.
    high++;
  }

  return maxLength;
}
