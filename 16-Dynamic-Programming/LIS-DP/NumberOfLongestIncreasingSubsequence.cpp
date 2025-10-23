/*
 * Problem: Number of Longest Increasing Subsequence (LeetCode #673)
 * Link:
 * https://leetcode.com/problems/number-of-longest-increasing-subsequence/description/
 *
 * Approach: This solution builds upon the standard O(N^2) dynamic programming
 *           approach for finding the length of the Longest Increasing
 *           Subsequence (LIS).
 *           1.  Two DP arrays are used: `dp[i]` stores the length of the LIS
 *               ending at index `i`, and `counts[i]` stores the number of such
 *               subsequences.
 *           2.  When iterating, if `nums[i] > nums[j]`, we check if extending
 *               the LIS from `j` gives a longer sequence for `i` or an
 *               equally long one.
 *           3.  If it's longer (`dp[j] + 1 > dp[i]`), we update `dp[i]` and
 *               reset `counts[i]` to `counts[j]`.
 *           4.  If it's equally long (`dp[j] + 1 == dp[i]`), we add `counts[j]`
 *               to `counts[i]`.
 *           5.  Finally, we sum the counts for all indices `i` where `dp[i]`
 *               equals the overall maximum LIS length.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int findNumberOfLIS(vector<int>& nums);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Input Array: [ ";
    for (int i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Number of LIS: " << findNumberOfLIS(nums) << endl;

    cout << endl;
  }

  return 0;
}

int findNumberOfLIS(vector<int>& nums) {
  int n = nums.size();

  vector<int> dp(n, 1), counts(n, 1);
  int maxLen = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (nums[i] > nums[j]) {
        if (dp[j] + 1 == dp[i]) {
          counts[i] += counts[j];
        } else if (dp[j] + 1 > dp[i]) {
          dp[i] = dp[j] + 1;
          counts[i] = counts[j];
        }
      }
    }
    maxLen = max(maxLen, dp[i]);
  }

  int count = 0;
  for (int i = 0; i < n; i++) {
    if (dp[i] == maxLen) {
      count += counts[i];
    }
  }

  return count;
}
