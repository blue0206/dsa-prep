/*
 * Problem: Longest String Chain (LeetCode #1048)
 * Link: https://leetcode.com/problems/longest-string-chain/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). After sorting the
 *           words by length, the state `dp[i][pi+1]` stores the length of the
 *           longest chain from index `i` onwards, given that the previous
 *           word was at index `pi`. For each word, we choose to either include
 *           it in the chain (if it's a valid successor) or skip it.
 *
 * Time Complexity: O(N^2 * L) due to N^2 states and O(L) for comparison.
 * Space Complexity: O(N^2) for DP table + O(N) for recursion stack.
 */
int memoizationApproach(vector<string>& words);
int solve(vector<vector<int>>& dp, vector<string>& words, int pi, int i);

/**
 * Approach: This is the tabulation (bottom-up) version of the memoization
 *           approach. It uses a 2D DP table where `dp[i][pi+1]` represents
 *           the length of the longest chain starting from index `i` with the
 *           previous word being at index `pi`.
 *
 * Time Complexity: O(N^2 * L)
 * Space Complexity: O(N^2)
 */
int tabulationApproach(vector<string>& words);

/**
 * Approach: This is a space-optimized version of the 2D tabulation. Since
 *           `dp[i]` only depends on `dp[i+1]`, we can use two 1D arrays (`prev`
 *           and `dp`) to store the states for the previous and current rows,
 *           reducing space.
 *
 * Time Complexity: O(N^2 * L)
 * Space Complexity: O(N)
 */
int spaceOptimizedApproach(vector<string>& words);

/**
 * Approach: This is a more common O(N^2) DP approach. After sorting, a 1D DP
 *           array is used where `dp[i]` stores the length of the longest
 *           chain that *ends* with `words[i]`. To compute `dp[i]`, we check
 *           all previous words `words[j]` and if `words[i]` is a successor to
 *           `words[j]`, we update `dp[i] = max(dp[i], 1 + dp[j])`.
 *
 * Time Complexity: O(N^2 * L)
 * Space Complexity: O(N)
 */
int spaceOptimizedApproach2(vector<string>& words);

/**
 * Approach: This is a more optimal approach that uses a hash map. After
 *           sorting, it iterates through each word. For each word, it
 *           generates all possible predecessors by removing one character at a
 *           time. It then looks up the longest chain ending with that
 *           predecessor in the map and updates the chain length for the
 *           current word.
 *
 * Time Complexity: O(N * L^2) due to generating L predecessors of length L-1.
 * Space Complexity: O(N)
 */
int optimalApproach(vector<string>& words);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<string> words(n);
    for (int i = 0; i < n; i++) cin >> words[i];

    cout << "Words: [ ";
    for (string i : words) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "LSC (Memoization): " << memoizationApproach(words) << endl;
    cout << "LSC (Tabulation): " << tabulationApproach(words) << endl;
    cout << "LSC (Space-Optimized, Choice-Based): "
         << spaceOptimizedApproach(words) << endl;
    cout << "LSC (Space-Optimized, Ending-Based): "
         << spaceOptimizedApproach2(words) << endl;
    cout << "LSC (Optimal): " << optimalApproach(words) << endl;

    cout << endl;
  }

  return 0;
}

bool compare(string& a, string& b) {
  if (a.length() < b.length()) return compare(b, a);
  if (a.length() - b.length() != 1) return false;

  int ai = 0;
  int bi = 0;
  while (ai < a.length() && bi < b.length()) {
    if (a[ai] == b[bi]) {
      ai++;
      bi++;
    } else {
      ai++;
    }
  }

  return (ai - bi <= 1);
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(vector<string>& words) {
  int n = words.size();
  sort(words.begin(), words.end(),
       [](string& a, string& b) { return a.length() < b.length(); });

  vector<vector<int>> dp(n, vector<int>(n + 1, -1));
  return solve(dp, words, -1, 0);
}

int solve(vector<vector<int>>& dp, vector<string>& words, int pi, int i) {
  if (i == words.size()) return 0;
  if (dp[i][pi + 1] != -1) return dp[i][pi + 1];

  int len = solve(dp, words, pi, i + 1);  // Not take
  if (pi == -1 || compare(words[i], words[pi])) {
    len = max(len, solve(dp, words, i, i + 1) + 1);
  }

  dp[i][pi + 1] = len;
  return dp[i][pi + 1];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(vector<string>& words) {
  int n = words.size();
  sort(words.begin(), words.end(),
       [](string& a, string& b) { return a.length() < b.length(); });

  vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
  for (int i = n - 1; i >= 0; i--) {
    for (int pi = i - 1; pi >= -1; pi--) {
      dp[i][pi + 1] = dp[i + 1][pi + 1];

      if (pi == -1 || compare(words[i], words[pi])) {
        dp[i][pi + 1] = max(dp[i][pi + 1], dp[i + 1][i + 1] + 1);
      }
    }
  }

  return dp[0][0];
}

//---------------------------SPACE-OPTIMIZED APPROACH---------------------------
int spaceOptimizedApproach(vector<string>& words) {
  int n = words.size();
  sort(words.begin(), words.end(),
       [](string& a, string& b) { return a.length() < b.length(); });

  vector<int> dp(n + 1, 0);
  for (int i = n - 1; i >= 0; i--) {
    vector<int> prev = dp;

    for (int pi = i - 1; pi >= -1; pi--) {
      dp[pi + 1] = prev[pi + 1];

      if (pi == -1 || compare(words[i], words[pi])) {
        dp[pi + 1] = max(dp[pi + 1], prev[i + 1] + 1);
      }
    }
  }

  return dp[0];
}

//--------------------------SPACE-OPTIMIZED APPROACH 2--------------------------
int spaceOptimizedApproach2(vector<string>& words) {
  int n = words.size();
  sort(words.begin(), words.end(),
       [](string& a, string& b) { return a.length() < b.length(); });

  vector<int> dp(n, 1);
  int maxLen = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (dp[j] + 1 > dp[i] && compare(words[i], words[j])) {
        dp[i] = dp[j] + 1;
      }
    }

    maxLen = max(maxLen, dp[i]);
  }

  return maxLen;
}

//-----------------------------OPTIMAL APPROACH---------------------------------
int optimalApproach(vector<string>& words) {
  int n = words.size();
  sort(words.begin(), words.end(),
       [](string& a, string& b) { return a.length() < b.length(); });

  unordered_map<string, int>
      dp;  // Map word to the longest chain ending with it
  int maxLen = 1;
  for (int i = 0; i < n; i++) {
    dp[words[i]] = 1;
    for (int j = 0; j < words[i].length(); j++) {
      string predecessor = words[i].substr(0, j) + words[i].substr(j + 1);
      if (dp.count(predecessor)) {
        dp[words[i]] = max(dp[predecessor] + 1, dp[words[i]]);
      }
    }

    maxLen = max(maxLen, dp[words[i]]);
  }

  return maxLen;
}
