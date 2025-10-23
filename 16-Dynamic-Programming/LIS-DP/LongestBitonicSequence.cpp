/*
 * Problem: Longest Bitonic Sequence
 * Link:
 * https://www.naukri.com/code360/problems/longest-bitonic-sequence_1062688?leftPanelTabValue=PROBLEM
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization) with a 3D state:
 *           `dp[i][pi+1][descending]`.
 *           - `i`: current index.
 *           - `pi`: previous index in the subsequence.
 *           - `descending`: a boolean flag indicating if we are in the
 *             decreasing part of the sequence.
 *           The logic handles transitions for increasing, starting to decrease,
 *           and continuing to decrease.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N^2 * 2) for DP table + O(N) for recursion stack.
 */
int memoizationApproach(vector<int>& arr, int n);
int solve(vector<vector<vector<int>>>& dp, vector<int>& arr, bool descending,
          int pi, int i);

/**
 * Approach: This is the tabulation (bottom-up) version of the memoization
 *           approach. It uses a 3D DP table and iterates backwards to fill it
 *           based on the same recurrence relation.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N^2 * 2)
 */
int tabulationApproach(vector<int>& arr, int n);

/**
 * Approach: This is a space-optimized version of the 3D tabulation. Since
 *           `dp[i]` only depends on `dp[i+1]`, we can use two 2D arrays (`prev`
 *           and `dp`) to store the states for the previous and current rows,
 *           reducing space.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N * 2)
 */
int spaceOptimizedApproach(vector<int>& arr, int n);

/**
 * Approach: This is the most common and efficient O(N^2) approach. A bitonic
 *           sequence is an increasing sequence followed by a decreasing one.
 *           This can be seen as an LIS from the left and an LIS from the right
 *           (which is an LDS from the left) meeting at a peak.
 *           1. Calculate `lis[i]`: length of LIS ending at `i`.
 *           2. Calculate `lds[i]`: length of LIS starting at `i` (or LDS ending
 *              at `i`).
 *           3. The longest bitonic sequence is `max(lis[i] + lds[i] - 1)` for
 *              all `i`.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N)
 */
int optimalApproach(vector<int>& arr, int n);
vector<int> getLis(vector<int>& arr, int n);

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

    cout << "LBS (Memoization): " << memoizationApproach(nums, n) << endl;
    cout << "LBS (Tabulation): " << tabulationApproach(nums, n) << endl;
    cout << "LBS (Space-Optimized): " << spaceOptimizedApproach(nums, n)
         << endl;
    cout << "LBS (Optimal): " << optimalApproach(nums, n) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<int>& arr, int n) {
  vector<vector<vector<int>>> dp(
      n, vector<vector<int>>(n + 1, vector<int>(2, -1)));

  return solve(dp, arr, false, -1, 0);
}

int solve(vector<vector<vector<int>>>& dp, vector<int>& arr, bool descending,
          int pi, int i) {
  if (i == arr.size()) return 0;
  if (dp[i][pi + 1][descending] != -1) return dp[i][pi + 1][descending];

  // Not take arr[i]
  int len = solve(dp, arr, descending, pi, i + 1);

  if (!descending) {
    // Continue increasing part
    if (pi == -1 || arr[i] > arr[pi])
      len = max(len, solve(dp, arr, false, i, i + 1) + 1);
  }
  // Start or continue decreasing part
  if (pi != -1 && arr[i] < arr[pi]) {
    len = max(len, solve(dp, arr, false, i, i + 1) + 1);
  }

  dp[i][pi + 1][descending] = len;
  return dp[i][pi + 1][descending];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<int>& arr, int n) {
  vector<vector<vector<int>>> dp(n + 1,
                                 vector<vector<int>>(n + 1, vector<int>(2, 0)));

  for (int i = n - 1; i >= 0; i--) {
    for (int pi = i - 1; pi >= -1; pi--) {
      dp[i][pi + 1][0] = dp[i + 1][pi + 1][0];
      dp[i][pi + 1][1] = dp[i + 1][pi + 1][1];

      if (arr[i] > arr[pi]) {
        dp[i][pi + 1][0] = max(dp[i][pi + 1][0], dp[i + 1][i + 1][0] + 1);
      } else if (arr[i] < arr[pi]) {
        dp[i][pi + 1][0] = max(dp[i][pi + 1][0], dp[i + 1][i + 1][1] + 1);
        dp[i][pi + 1][1] = max(dp[i][pi + 1][1], dp[i + 1][i + 1][1] + 1);
      }
    }
  }

  return dp[0][0][0];
}

//---------------------------SPACE-OPTIMIZED APPROACH---------------------------
int spaceOptimizedApproach(vector<int>& arr, int n) {
  vector<vector<int>> dp(n + 1, vector<int>(2, 0));

  for (int i = n - 1; i >= 0; i--) {
    vector<vector<int>> prev = dp;

    for (int pi = i - 1; pi >= -1; pi--) {
      dp[pi + 1][0] = prev[pi + 1][0];
      dp[pi + 1][1] = prev[pi + 1][1];

      if (arr[i] > arr[pi]) {
        dp[pi + 1][0] = max(dp[pi + 1][0], prev[i + 1][0] + 1);
      } else if (arr[i] < arr[pi]) {
        dp[pi + 1][0] = max(dp[pi + 1][0], prev[i + 1][1] + 1);
        dp[pi + 1][1] = max(dp[pi + 1][1], prev[i + 1][1] + 1);
      }
    }
  }

  return dp[0][0];
}

//-----------------------------OPTIMAL APPROACH---------------------------------
int optimalApproach(vector<int>& arr, int n) {
  vector<int> rarr(arr.rbegin(), arr.rend());
  vector<int> lis = getLis(arr, n);
  vector<int> rLis = getLis(rarr, n);

  int maxLen = 1;
  for (int i = 0; i < n; i++) {
    int len = rLis[n - i - 1] + lis[i] - 1;
    maxLen = max(maxLen, len);
  }

  return maxLen;
}

vector<int> getLis(vector<int>& arr, int n) {
  vector<int> dp(n, 1);
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (arr[i] > arr[j] && dp[j] + 1 > dp[i]) {
        dp[i] = dp[j] + 1;
      }
    }
  }

  return dp;
}
