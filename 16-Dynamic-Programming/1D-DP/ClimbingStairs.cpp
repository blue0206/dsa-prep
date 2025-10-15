/*
 * Problem: Climbing Stairs (LeetCode #70)
 * Link: https://leetcode.com/problems/climbing-stairs/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down dynamic programming approach. The number of ways
 *           to reach step `n` is the sum of ways to reach `n-1` and `n-2`. We
 *           use a recursive function and a DP array (memoization) to store the
 *           results for subproblems to avoid re-computation.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N) for recursion stack and DP array.
 */
int memoizationApproach(int n);
int solve(vector<int>& dp, int n);

/**
 * Approach: This is a bottom-up dynamic programming approach. We create a DP
 *           array and fill it iteratively. `dp[i]` stores the number of ways
 *           to reach step `i`. The value of `dp[i]` is calculated from the
 *           previously computed values `dp[i-1]` and `dp[i-2]`.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
int tabulationApproach(int n);

/**
 * Approach: This is a space-optimized version of the tabulation approach.
 *           Since we only need the previous two values (`i-1` and `i-2`) to
 *           calculate the current value (`i`), we can get rid of the DP array
 *           and use two variables (`prev1`, `prev2`) to store the last two
 *           results. This reduces the space complexity to constant.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int optimalApproach(int n);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    cout << "n: " << n << endl;

    cout << "Number of Ways (Memoization): " << memoizationApproach(n) << endl;
    cout << "Number of Ways (Tabulation): " << tabulationApproach(n) << endl;
    cout << "Number of Ways (Optimal): " << optimalApproach(n) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(int n) {
  vector<int> dp(n + 1, -1);

  return solve(dp, n);
}

int solve(vector<int>& dp, int n) {
  if (n <= 2) return n;
  if (dp[n] != -1) return dp[n];

  dp[n] = solve(dp, n - 1) + solve(dp, n - 2);
  return dp[n];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(int n) {
  if (n <= 3) return n;
  vector<int> dp(n + 1, -1);

  dp[2] = 2;
  dp[3] = 3;
  for (int i = 4; i <= n; i++) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }

  return dp[n];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(int n) {
  if (n <= 3) return n;

  int prev1 = 3;
  int prev2 = 2;
  for (int i = 4; i <= n; i++) {
    int num = prev1 + prev2;
    prev2 = prev1;
    prev1 = num;
  }

  return prev1;
}
