/*
 * Problem: Frog Jump
 * Link: https://www.geeksforgeeks.org/problems/geek-jump/1
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down dynamic programming approach (memoization).
 *           The minimum energy to reach stone `i` is the minimum of the energy
 *           from `i-1` and `i-2`. We define a recursive relation and use a DP
 *           array to store the results of subproblems to avoid re-computation.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N) for recursion stack and DP array.
 */
int memoizationApproach(vector<int>& height);
int solve(const vector<int>& height, vector<int>& dp, int i);

/**
 * Approach: This is a bottom-up dynamic programming approach (tabulation). We
 *           create a DP array `dp` where `dp[i]` stores the minimum energy to
 *           reach stone `i`. We fill this array iteratively from the base case
 *           `dp[0] = 0`.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
int tabulationApproach(vector<int>& height);

/**
 * Approach: This is a space-optimized version of the tabulation approach.
 *           To calculate the energy for the current stone `i`, we only need
 *           the results for the previous two stones (`i-1` and `i-2`). We can
 *           therefore use two variables (`prev1`, `prev2`) instead of a full
 *           DP array, reducing space complexity to O(1).
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int optimalApproach(vector<int>& height);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> height(n);
    for (int i = 0; i < n; i++) cin >> height[i];

    cout << "Heights: [ ";
    for (int val : height) {
      cout << val << " ";
    }
    cout << "]" << endl;

    cout << "Minimum Cost (Memoization): " << memoizationApproach(height)
         << endl;
    cout << "Minimum Cost (Tabulation): " << tabulationApproach(height) << endl;
    cout << "Minimum Cost (Optimal): " << optimalApproach(height) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<int>& height) {
  vector<int> dp(height.size(), -1);

  return solve(height, dp, dp.size() - 1);
}

int solve(vector<int>& height, vector<int>& dp, int i) {
  if (i == 0) return 0;
  if (i == 1) return abs(height[1] - height[0]);
  if (dp[i] != -1) return dp[i];

  int cost1 = solve(height, dp, i - 1) + abs(height[i] - height[i - 1]);
  int cost2 = solve(height, dp, i - 2) + abs(height[i] - height[i - 2]);

  dp[i] = min(cost1, cost2);
  return dp[i];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<int>& height) {
  int n = height.size();
  if (n == 1) return 0;

  vector<int> dp(n, -1);

  dp[0] = 0;
  dp[1] = abs(height[1] - height[0]);
  for (int i = 2; i < n; i++) {
    int cost1 = dp[i - 1] + abs(height[i] - height[i - 1]);
    int cost2 = dp[i - 2] + abs(height[i] - height[i - 2]);

    dp[i] = min(cost1, cost2);
  }

  return dp[n - 1];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(vector<int>& height) {
  int n = height.size();
  if (n == 1) return 0;

  int prev1 = abs(height[1] - height[0]);
  int prev2 = 0;
  for (int i = 2; i < n; i++) {
    int cost1 = prev1 + abs(height[i] - height[i - 1]);
    int cost2 = prev2 + abs(height[i] - height[i - 2]);

    int minCost = min(cost1, cost2);

    prev2 = prev1;
    prev1 = minCost;
  }

  return prev1;
}
