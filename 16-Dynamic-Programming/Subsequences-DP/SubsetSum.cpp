/*
 * Problem: Subset Sum
 * Link: https://www.geeksforgeeks.org/problems/subset-sum-problem-1611555638/1
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). The state is defined
 *           by `dp[i][sum]`, which stores whether a subset with the given `sum`
 *           can be formed using elements from index `i` onwards. For each
 *           element, we have two choices: either include it in the subset or
 *           exclude it.
 *
 * Time Complexity: O(N * sum)
 * Space Complexity: O(N * sum) for the DP table + O(N) for recursion stack.
 */
bool memoizationApproach(vector<int>& arr, int sum);
bool findSum(const vector<int>& arr, vector<vector<int>>& dp, int sum, int i);

/**
 * Approach: This is a bottom-up DP approach (tabulation). We create a 2D DP
 *           table where `dp[i][j]` is true if a sum of `j` can be obtained
 *           using a subset of the first `i` elements of the array. The value
 *           is determined by the "pick vs. not-pick" logic based on the
 *           previous row's results.
 *
 * Time Complexity: O(N * sum)
 * Space Complexity: O(N * sum)
 */
bool tabulationApproach(vector<int>& arr, int sum);

/**
 * Approach: This is a space-optimized version of the tabulation approach.
 *           To compute the DP values for the current element, we only need the
 *           results from the previous element. We can use a single 1D array
 *           `dp` of size `sum+1` and update it in place.
 *
 * Time Complexity: O(N * sum)
 * Space Complexity: O(sum)
 */
bool optimalApproach(vector<int>& arr, int sum);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, sum;
    cin >> n >> sum;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << "Target: " << sum << endl;
    cout << "Input Array: [ ";
    for (int val : arr) cout << val << " ";
    cout << "]" << endl;

    cout << "Result (Memoization): " << memoizationApproach(arr, sum) << endl;
    cout << "Result (Tabulation): " << tabulationApproach(arr, sum) << endl;
    cout << "Result (Optimal): " << optimalApproach(arr, sum) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
bool memoizationApproach(vector<int>& arr, int sum) {
  vector<vector<int>> dp(arr.size(), vector<int>(sum + 1, -1));
  return (findSum(arr, dp, sum, 0));
}

bool findSum(vector<int>& arr, vector<vector<int>>& dp, int sum, int i) {
  if (sum == 0) return true;
  if (i == arr.size() || sum < 0) return false;
  if (dp[i][sum] != -1) return dp[i][sum];

  dp[i][sum] =
      findSum(arr, dp, sum - arr[i], i + 1) || findSum(arr, dp, sum, i + 1);
  return dp[i][sum];
}

//-----------------------------TABULATION APPROACH------------------------------
bool tabulationApproach(vector<int>& arr, int sum) {
  int n = arr.size();

  vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));
  for (int i = 0; i <= n; i++) dp[i][0] = true;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= sum; j++) {
      bool exclude = dp[i - 1][j];

      bool include = false;
      if (j >= arr[i - 1]) {
        include = dp[i - 1][j - arr[i - 1]];
      }

      dp[i][j] = include || exclude;
    }
  }

  return dp[n][sum];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
bool optimalApproach(vector<int>& arr, int sum) {
  int n = arr.size();

  vector<bool> dp(sum + 1, false);
  dp[0] = true;

  for (int i = 1; i <= n; i++) {
    vector<bool> temp = dp;
    for (int j = 1; j <= sum; j++) {
      int exclude = temp[j];

      int include = false;
      if (j >= arr[i - 1]) {
        include = temp[j - arr[i - 1]];
      }

      dp[j] = exclude || include;
    }
  }

  return dp[sum];
}
