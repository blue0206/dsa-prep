/*
 * Problem: Count Subsets with Sum K
 * Link:
 * https://www.naukri.com/code360/problems/count-subsets-with-sum-k_3952532?leftPanelTabValue=PROBLEM
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
const int m = 1e9 + 7;

/**
 * Approach: This is a top-down DP approach (memoization). The logic is based
 *           on the "pick vs. not-pick" strategy. The function `solve(k, i)`
 *           calculates the number of subsets that sum to `k` using elements
 *           from index `i` onwards. For each element `arr[i]`, the total count
 *           is the sum of counts from two choices:
 *           1. Pick `arr[i]`: Recursively find counts for sum `k - arr[i]`.
 *           2. Don't pick `arr[i]`: Recursively find counts for sum `k`.
 *
 * Time Complexity: O(N * K)
 * Space Complexity: O(N * K) for the DP table + O(N) for recursion stack.
 */
int memoizationApproach(vector<int>& arr, int k);
int solve(vector<int>& arr, vector<vector<int>>& dp, int k, int i);

/**
 * Approach: This is a bottom-up DP approach (tabulation). We create a 2D DP
 *           table where `dp[i][j]` stores the number of subsets that sum to `j`
 *           using the first `i` elements. The value for each cell is
 *           calculated based on the "pick vs. not-pick" logic using results
 *           from the previous row.
 *
 * Time Complexity: O(N * K)
 * Space Complexity: O(N * K)
 */
int tabulationApproach(vector<int>& arr, int k);

/**
 * Approach: This is a space-optimized version of the tabulation approach. To
 *           calculate the counts for the current element, it only needs the
 *           results from the previous state. It uses two 1D arrays to store
 *           the previous and current states of the DP table, reducing space
 *           from O(N * K) to O(K).
 *
 * Time Complexity: O(N * K)
 * Space Complexity: O(K)
 */
int optimalApproach(vector<int>& arr, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << "k: " << k << endl;
    cout << "Input Array: [ ";
    for (int val : arr) cout << val << " ";
    cout << "]" << endl;

    cout << "Result (Memoization): " << memoizationApproach(arr, k) << endl;
    cout << "Result (Tabulation): " << tabulationApproach(arr, k) << endl;
    cout << "Result (Optimal): " << optimalApproach(arr, k) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<int>& arr, int k) {
  int n = arr.size();

  vector<vector<int>> dp(n, vector<int>(k + 1, -1));
  return solve(arr, dp, k, 0);
}

int solve(vector<int>& arr, vector<vector<int>>& dp, int k, int i) {
  if (k == 0) {
    return 1;
  }
  if (i >= arr.size() || k < 0) return 0;
  if (dp[i][k] != -1) return dp[i][k];

  int count1 = solve(arr, dp, k - arr[i], i + 1) % m;
  int count2 = solve(arr, dp, k, i + 1) % m;

  dp[i][k] = (count1 + count2) % m;
  return dp[i][k];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<int>& arr, int k) {
  int n = arr.size();

  vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
  dp[0][0] = 1;

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= k; j++) {
      int exclude = dp[i - 1][j] % m;
      int include = 0;
      if (j >= arr[i - 1]) {
        include = dp[i - 1][j - arr[i - 1]] % m;
      }

      dp[i][j] = (include + exclude) % m;
    }
  }

  return dp[n][k];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(vector<int>& arr, int k) {
  int n = arr.size();

  vector<int> ways(k + 1, 0);
  ways[0] = 1;

  for (int i = 1; i <= n; i++) {
    vector<int> dp = ways;
    for (int j = 0; j <= k; j++) {
      int exclude = dp[j] % m;
      int include = 0;
      if (j >= arr[i - 1]) {
        include = dp[j - arr[i - 1]] % m;
      }

      ways[j] = (include + exclude) % m;
    }
  }

  return ways[k];
}
