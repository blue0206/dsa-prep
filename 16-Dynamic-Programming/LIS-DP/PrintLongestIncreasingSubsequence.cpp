/*
 * Problem: Print Longest Increasing Subsequence
 * Link:
 * https://www.naukri.com/code360/problems/printing-longest-increasing-subsequence_8360670?leftPanelTabValue=PROBLEM
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This approach first builds a 2D DP table similar to the standard
 *           O(N^2) LIS length calculation, where `dp[i][j+1]` is the length of
 *           the LIS from index `i` onwards, with the previous element being at
 *           index `j`. After filling the table, it backtracks from the start
 *           (`i=0, j=-1`) to reconstruct the LIS by following the path that
 *           yielded the maximum lengths.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N^2)
 */
vector<int> tabulationApproach(vector<int>& nums);

/**
 * Approach: This uses the more common O(N^2) DP approach where `dp[i]` stores
 *           the length of the LIS ending at index `i`. A second array,
 *           `prevIdx`, is used to store the index of the previous element in
 *           the LIS ending at `i`. After filling both arrays, we find the
 *           index where the overall LIS ends and backtrack using `prevIdx` to
 *           reconstruct the sequence.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N)
 */
vector<int> optimalApproach(vector<int>& nums);

void print(vector<int>& nums) {
  cout << "[ ";
  for (int i : nums) {
    cout << i << " ";
  }
  cout << "]" << endl;
}

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

    vector<int> tabulationAns = tabulationApproach(nums);
    vector<int> optimalAns = optimalApproach(nums);

    cout << "LIS (Tabulation): ";
    print(tabulationAns);
    cout << "LIS (Optimal): ";
    print(optimalAns);

    cout << endl;
  }

  return 0;
}

//-----------------------------TABULATION APPROACH------------------------------
vector<int> tabulationApproach(vector<int>& nums) {
  int n = nums.size();

  vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

  for (int i = n - 1; i >= 0; i--) {
    for (int j = i - 1; j >= -1; j--) {
      dp[i][j + 1] = dp[i + 1][j + 1];

      if (j == -1 || nums[i] > nums[j]) {
        dp[i][j + 1] = max(dp[i][j + 1], dp[i + 1][i + 1] + 1);
      }
    }
  }

  int i = 0;
  int j = -1;
  vector<int> ans;
  while (i < n && j < n) {
    if (dp[i + 1][j + 1] == dp[i][j + 1]) {
      i++;
    } else {
      ans.emplace_back(nums[i]);
      j = i;
      i++;
    }
  }

  return ans;
}

//-----------------------------OPTIMAL APPROACH---------------------------------
vector<int> optimalApproach(vector<int>& nums) {
  int n = nums.size();

  vector<int> dp(n, 0), prevIdx(n, 0);
  int maxLen = 0;
  int maxIdx = 0;
  for (int i = 1; i < n; i++) {
    prevIdx[i] = i;

    for (int j = 0; j < i; j++) {
      if (nums[i] > nums[j] && dp[j] + 1 > dp[i]) {
        dp[i] = dp[j] + 1;
        prevIdx[i] = j;
      }
    }

    if (dp[i] > maxLen) {
      maxLen = dp[i];
      maxIdx = i;
    }
  }

  vector<int> lis(maxLen + 1);
  int i = maxLen;
  lis[i--] = nums[maxIdx];
  while (prevIdx[maxIdx] != maxIdx) {
    lis[i--] = nums[prevIdx[maxIdx]];
    maxIdx = prevIdx[maxIdx];
  }

  return lis;
}
