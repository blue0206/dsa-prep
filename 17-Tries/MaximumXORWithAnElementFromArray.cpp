/*
 * Problem: Maximum XOR With an Element From Array (LeetCode #1707)
 * Link:
 * https://leetcode.com/problems/maximum-xor-with-an-element-from-array/description/
 *
 * Approach: This problem requires finding the max XOR for several queries, each
 *           with a constraint. A naive approach would be too slow. The optimal
 *           solution uses offline processing with a Trie.
 *           1.  **Offline Processing:** Sort the `nums` array. Augment the
 *               `queries` with their original indices and sort them based on
 *               their limit `m`.
 *           2.  **Iterate and Build Trie:** Iterate through the sorted queries.
 *               For each query `(x, m)`, insert all numbers from `nums` that
 *               are `<= m` into a bitwise Trie. Since both `nums` and queries
 *               are sorted, we can do this efficiently with a single pointer
 *               for the `nums` array.
 *           3.  **Find Max XOR:** For each query, use the Trie to find the
 *               number that maximizes the XOR with `x`, using the standard
 *               greedy approach (always try to match with the opposite bit).
 *
 * Time Complexity: O(N*logN + Q*logQ + (N+Q)*32)
 * Space Complexity: O(N*32 + Q)
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

class TrieNode {
 public:
  vector<TrieNode*> children;
  int num;

  TrieNode() {
    children.assign(2, NULL);
    num = -1;
  }

  bool end() { return (children[0] == NULL && children[1] == NULL); }
};

class Trie {
 private:
  TrieNode* root;

 public:
  Trie() { root = new TrieNode(); }

  void insert(int num) {
    TrieNode* iter = root;

    for (int i = 31; i >= 0; i--) {
      int bit = (num & (1 << i)) != 0;

      if (iter->children[bit] == NULL) {
        iter->children[bit] = new TrieNode();
      }
      iter = iter->children[bit];
    }

    iter->num = num;
  }

  int getXor(int x) {
    TrieNode* iter = root;

    for (int i = 31; i >= 0 && !iter->end(); i--) {
      int bit = (x & (1 << i)) != 0;
      iter = (iter->children[!bit] == NULL) ? iter->children[bit]
                                            : iter->children[!bit];
    }

    return x ^ iter->num;
  }
};

vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, q;
    cin >> n >> q;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];
    vector<vector<int>> queries(q, vector<int>(2));
    for (int i = 0; i < q; i++) {
      cin >> queries[i][0] >> queries[i][1];
    }

    cout << "Input Nums: [ ";
    for (int i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    vector<int> ans = maximizeXor(nums, queries);

    for (int i = 0; i < q; i++) {
      cout << "Query " << i + 1 << ": " << ans[i] << endl;
    }

    cout << endl;
  }

  return 0;
}

vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
  int q = queries.size();
  vector<vector<int>> sortedQ = queries;
  for (int i = 0; i < q; i++) {
    sortedQ[i].emplace_back(i);
  }

  sort(sortedQ.begin(), sortedQ.end(),
       [](vector<int>& a, vector<int>& b) { return a[1] < b[1]; });
  sort(nums.begin(), nums.end());

  int numsIdx = 0;
  Trie* trie = new Trie();
  vector<int> ans(q, -1);
  for (int i = 0; i < q; i++) {
    int x = sortedQ[i][0];
    int m = sortedQ[i][1];
    int idx = sortedQ[i][2];

    if (m < nums[0]) continue;
    while (numsIdx < nums.size() && nums[numsIdx] <= m) {
      trie->insert(nums[numsIdx]);
      numsIdx++;
    }

    ans[idx] = trie->getXor(x);
  }

  return ans;
}
