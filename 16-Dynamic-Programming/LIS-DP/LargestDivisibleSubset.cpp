/*
 * Problem: Largest Divisible Subset (LeetCode #368)
 * Link: https://leetcode.com/problems/largest-divisible-subset/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This approach is a variation of the O(N^2) LIS solution. After
 *           sorting the input array, it builds a 2D DP table where `dp[i][j+1]`
 *           is the length of the largest divisible subset (LDS) from index `i`
 *           onwards, with the previous element being at index `j`. After
 *           filling the table, it backtracks from the start to reconstruct the
 *           LDS.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N^2)
 */
vector<int> tabulationApproach(vector<int>& nums);

/**
 * Approach: This is a more common and space-efficient O(N^2) DP approach.
 *           After sorting, it uses `dp[i]` to store the length of the LDS
 *           ending at index `i`. A `prevIdx` array tracks the path. After
 *           filling both arrays, we find where the overall LDS ends and
 *           backtrack using `prevIdx` to reconstruct the sequence.
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

    cout << "LDS (Tabulation): ";
    print(tabulationAns);
    cout << "LDS (Optimal): ";
    print(optimalAns);

    cout << endl;
  }

  return 0;
}

//-----------------------------TABULATION APPROACH------------------------------
vector<int> tabulationApproach(vector<int>& nums) {
  int n = nums.size();
  sort(nums.begin(), nums.end());

  vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
  for (int i = n - 1; i >= 0; i--) {
    for (int pi = i - 1; pi >= -1; pi--) {
      dp[i][pi + 1] = dp[i + 1][pi + 1];

      if (pi == -1 || nums[i] % nums[pi] == 0) {
        dp[i][pi + 1] = max(dp[i][pi + 1], dp[i + 1][i + 1] + 1);
      }
    }
  }

  int i = 0;
  int pi = -1;
  vector<int> lds;
  while (i < n && pi < n) {
    if (dp[i][pi + 1] == dp[i + 1][pi + 1]) {
      i++;
    } else {
      lds.emplace_back(nums[i]);
      pi = i;
      i++;
    }
  }

  return lds;
}

//-----------------------------OPTIMAL APPROACH---------------------------------
vector<int> optimalApproach(vector<int>& nums) {
  int n = nums.size();
  sort(nums.begin(), nums.end());

  vector<int> dp(n, 0), prevIdx(n);
  prevIdx[0] = 0;

  int maxLen = 0;
  int lastIdx = 0;
  for (int i = 1; i < n; i++) {
    prevIdx[i] = i;
    for (int j = 0; j < i; j++) {
      if (nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i]) {
        dp[i] = dp[j] + 1;
        prevIdx[i] = j;
      }
    }
    if (dp[i] > maxLen) {
      maxLen = dp[i];
      lastIdx = i;
    }
  }

  vector<int> lds(maxLen + 1);
  int i = maxLen;
  lds[i--] = nums[lastIdx];
  while (prevIdx[lastIdx] != lastIdx) {
    lds[i--] = nums[prevIdx[lastIdx]];
    lastIdx = prevIdx[lastIdx];
  }

  return lds;
}
