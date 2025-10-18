/*
 * Problem: Partitions with Given Difference
 * Link:
 * https://www.geeksforgeeks.org/problems/partitions-with-given-difference/1
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
const int m = 1e9 + 7;

/**
 * Approach: This problem can be reduced to "Count Subsets with Sum K".
 *           Let the two partitions be S1 and S2. We are given:
 *           1. sum(S1) - sum(S2) = d
 *           2. sum(S1) + sum(S2) = total_sum
 *           Adding these two equations gives: 2*sum(S1) = total_sum + d,
 *           so sum(S1) = (total_sum + d) / 2.
 *           Subtracting the first from the second gives:
 *           2*sum(S2) = total_sum - d, so sum(S2) = (total_sum - d) / 2.
 *           The problem is now to find the number of subsets that sum to a
 *           target of `(total_sum - d) / 2`. This is solved with memoization.
 *
 * Time Complexity: O(N * target)
 * Space Complexity: O(N * target) for DP table + O(N) for recursion stack.
 */
int memoizationApproach(vector<int>& arr, int d);
int solve(vector<int>& arr, vector<vector<int>>& dp, int target, int i);

/**
 * Approach: This is the tabulation (bottom-up) version. After reducing the
 *           problem to "Count Subsets with Sum K" with a target of
 *           `(total_sum - d) / 2`, we build a 2D DP table. `dp[i][j]` stores
 *           the number of subsets with sum `j` using the first `i` elements.
 *
 * Time Complexity: O(N * target)
 * Space Complexity: O(N * target)
 */
int tabulationApproach(vector<int>& arr, int d);

/**
 * Approach: This is the space-optimized version of the tabulation approach.
 *           It also solves the reduced "Count Subsets with Sum K" problem.
 *           To calculate the counts for the current element, it only needs
 *           the results from the previous state. It uses two 1D arrays to
 *           store the previous and current states of the DP table, reducing
 *           space from O(N * target) to O(target).
 *
 * Time Complexity: O(N * target)
 * Space Complexity: O(target)
 */
int optimalApproach(vector<int>& arr, int d);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, d;
    cin >> n >> d;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << "d: " << d << endl;
    cout << "Input Array: [ ";
    for (int val : arr) cout << val << " ";
    cout << "]" << endl;

    cout << "Result (Memoization): " << memoizationApproach(arr, d) << endl;
    cout << "Result (Tabulation): " << tabulationApproach(arr, d) << endl;
    cout << "Result (Optimal): " << optimalApproach(arr, d) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<int>& arr, int d) {
  int n = arr.size();

  int total = accumulate(arr.begin(), arr.end(), 0);
  if ((total - d) & 1) return 0;
  if (d > total) return 0;

  int target = (total - d) / 2;

  vector<vector<int>> dp(n, vector<int>(target + 1, -1));
  return solve(arr, dp, target, 0);
}

int solve(vector<int>& arr, vector<vector<int>>& dp, int target, int i) {
  if (target < 0) return 0;
  if (i == arr.size() - 1) {
    if (target == 0 && arr[i] == 0) return 2;
    if (target == 0 || target == arr[i]) return 1;
    return 0;
  }
  if (dp[i][target] != -1) return dp[i][target];

  int count1 = solve(arr, dp, target - arr[i], i + 1);
  int count2 = solve(arr, dp, target, i + 1);

  dp[i][target] = count1 + count2;
  return dp[i][target];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<int>& arr, int d) {
  int n = arr.size();

  int total = accumulate(arr.begin(), arr.end(), 0);
  if ((total - d) & 1) return 0;
  if (d > total) return 0;

  int target = (total - d) / 2;

  vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
  for (int i = 0; i <= n; i++) dp[i][0] = 1;

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= target; j++) {
      int exclude = dp[i - 1][j];
      int include = 0;
      if (j >= arr[i - 1]) {
        include = dp[i - 1][j - arr[i - 1]];
      }

      dp[i][j] = include + exclude;
    }
  }

  return dp[n][target];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(vector<int>& arr, int d) {
  int n = arr.size();

  int total = accumulate(arr.begin(), arr.end(), 0);
  if ((total - d) & 1) return 0;
  if (d > total) return 0;

  int target = (total - d) / 2;

  vector<int> counts(target + 1, 0);
  counts[0] = 1;

  for (int i = 1; i <= n; i++) {
    vector<int> dp = counts;
    for (int j = 0; j <= target; j++) {
      int exclude = dp[j];
      int include = 0;
      if (j >= arr[i - 1]) {
        include = dp[j - arr[i - 1]];
      }

      counts[j] = include + exclude;
    }
  }

  return counts[target];
}
