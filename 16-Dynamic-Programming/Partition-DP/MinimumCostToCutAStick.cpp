/*
 * Problem: Minimum Cost to Cut a Stick (LeetCode #1547)
 * Link: https://leetcode.com/problems/minimum-cost-to-cut-a-stick/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). The problem is a
 *           classic Partition DP, similar to Matrix Chain Multiplication.
 *           1.  First, we add `0` and `n` to the `cuts` array and sort it. This
 *               gives us a `boundaries` array.
 *           2.  The function `solve(i, j)` finds the minimum cost to make all
 *               cuts between `boundaries[i-1]` and `boundaries[j]`.
 *           3.  We try every possible cut `k` (from `i` to `j-1`) as the first
 *               cut in this segment. The cost is the length of the current
 *               stick (`boundaries[j] - boundaries[i-1]`) plus the cost of
 *               the resulting subproblems `(i, k)` and `(k+1, j)`.
 *
 * Time Complexity: O(N^3)
 * Space Complexity: O(N^2) for DP table + O(N) for recursion stack.
 */
int memoizationApproach(int n, vector<int>& cuts);
int solve(vector<vector<int>>& dp, const vector<int>& boundaries, int i, int j);

/**
 * Approach: This is the tabulation (bottom-up) version. We fill a 2D DP table
 *           where `dp[i][j]` stores the minimum cost for the segment between
 *           `boundaries[i-1]` and `boundaries[j]`. The table is filled by
 *           iterating over segment lengths, from small to large.
 *
 * Time Complexity: O(N^3)
 * Space Complexity: O(N^2)
 */
int tabulationApproach(int n, vector<int>& cuts);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, m;
    cin >> n >> m;

    vector<int> nums(m);
    for (int i = 0; i < m; i++) cin >> nums[i];

    cout << "Stick Length: " << n << endl;
    cout << "Input Array: [ ";
    for (int i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Minimum Cost (Memoization): " << memoizationApproach(n, nums)
         << endl;
    cout << "Minimum Cost (Tabulation): " << tabulationApproach(n, nums)
         << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(int n, vector<int>& cuts) {
  vector<int> boundaries = cuts;
  boundaries.emplace_back(0);
  sort(boundaries.begin(), boundaries.end());
  boundaries.emplace_back(n);

  int m = boundaries.size();
  vector<vector<int>> dp(m, vector<int>(m, -1));
  return solve(dp, boundaries, 1, m - 1);
}

int solve(vector<vector<int>>& dp, vector<int>& boundaries, int i, int j) {
  if (i >= j) return 0;
  if (dp[i][j] != -1) return dp[i][j];

  int minCost = INT_MAX;
  int cutLength = boundaries[j] - boundaries[i - 1];
  for (int k = i; k < j; k++) {
    int cost = solve(dp, boundaries, i, k) + solve(dp, boundaries, k + 1, j) +
               cutLength;
    minCost = min(minCost, cost);
  }

  dp[i][j] = minCost;
  return dp[i][j];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(int n, vector<int>& cuts) {
  vector<int> boundaries = cuts;
  boundaries.emplace_back(0);
  sort(boundaries.begin(), boundaries.end());
  boundaries.emplace_back(n);

  int m = boundaries.size();
  vector<vector<int>> dp(m, vector<int>(m, 0));

  for (int i = m - 1; i >= 1; i--) {
    for (int j = i + 1; j < m; j++) {
      int minCost = INT_MAX;
      int cutLength = boundaries[j] - boundaries[i - 1];
      for (int k = i; k < j; k++) {
        int cost = dp[i][k] + dp[k + 1][j] + cutLength;
        minCost = min(minCost, cost);
      }

      dp[i][j] = minCost;
    }
  }

  return dp[1][m - 1];
}
