/*
 * Problem: Partition Array for Maximum Sum (LeetCode #1043)
 * Link:
 * https://leetcode.com/problems/partition-array-for-maximum-sum/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). This is a classic
 *           Partition DP problem. The function `solve(i)` finds the maximum
 *           sum for the subarray `arr[i...]`.
 *           For each starting index `i`, we iterate through all possible end
 *           points `j` (up to `k` elements away). For each partition
 *           `arr[i...j]`, we find its `maxVal`, calculate the partition's sum
 *           (`maxVal * length`), and add it to the result of the recursive call
 *           for the rest of the array, `solve(j+1)`.
 *
 * Time Complexity: O(N * K)
 * Space Complexity: O(N) for DP array + O(N) for recursion stack.
 */
int memoizationApproach(vector<int>& arr, int k);
int solve(vector<int>& dp, vector<int>& arr, int len, int i);

/**
 * Approach: This is the tabulation (bottom-up) version. We fill a 1D DP array
 *           `dp` from right to left, where `dp[i]` stores the maximum sum for
 *           the subarray `arr[i...]`. The base case is `dp[n] = 0`. The final
 *           answer is `dp[0]`.
 *
 * Time Complexity: O(N * K)
 * Space Complexity: O(N)
 */
int tabulationApproach(vector<int>& arr, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Maximum Subarray Length: " << k << endl;
    cout << "Input Array: [ ";
    for (int i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Maximum Sum (Memoization): " << memoizationApproach(nums, k)
         << endl;
    cout << "Maximum Sum (Tabulation): " << tabulationApproach(nums, k) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<int>& arr, int k) {
  int n = arr.size();

  vector<int> dp(n, -1);
  return solve(dp, arr, k, 0);
}

int solve(vector<int>& dp, vector<int>& arr, int len, int i) {
  if (i == arr.size()) return 0;
  if (dp[i] != -1) return dp[i];

  int maxSum = 0;
  int maxVal = 0;
  for (int j = i; j - i + 1 <= len && j < arr.size(); j++) {
    maxVal = max(maxVal, arr[j]);

    int sum = solve(dp, arr, len, j + 1) + (maxVal * (j - i + 1));
    maxSum = max(maxSum, sum);
  }

  dp[i] = maxSum;
  return dp[i];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<int>& arr, int k) {
  int n = arr.size();

  vector<int> dp(n + 1, 0);
  for (int i = n - 1; i >= 0; i--) {
    int maxSum = 0;
    int maxVal = 0;
    for (int j = i; j - i + 1 <= k && j < n; j++) {
      maxVal = max(maxVal, arr[j]);

      int sum = dp[j + 1] + (maxVal * (j - i + 1));
      maxSum = max(maxSum, sum);
    }

    dp[i] = maxSum;
  }

  return dp[0];
}
