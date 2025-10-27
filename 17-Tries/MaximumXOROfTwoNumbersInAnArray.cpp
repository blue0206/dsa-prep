/*
 * Problem: Maximum XOR of Two Numbers in an Array (LeetCode #421)
 * Link:
 * https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/description/
 *
 * Approach: This problem can be solved efficiently using a Trie where each
 *           number is stored as a 32-bit binary path.
 *           1.  **Trie Construction:** Insert all numbers from the input array
 *               into the Trie. Each number is represented as a path of 32
 *               nodes, one for each bit from MSB to LSB.
 *           2.  **Finding Max XOR:** For each number `num` in the array,
 *               traverse the Trie to find a counterpart that would maximize
 *               their XOR value. To do this, at each bit position, we greedily
 *               try to take the path corresponding to the opposite bit of
 *               `num`. If the opposite bit path doesn't exist, we must take
 *               the same bit path.
 *           3.  By following this greedy strategy for each number and keeping
 *               track of the maximum XOR found, we can find the overall answer.
 *
 * Time Complexity: O(N * 32)
 * Space Complexity: O(N * 32)
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
  bool endOfNumber;

  TrieNode() {
    children.assign(2, NULL);
    endOfNumber = false;
    num = 0;
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

    iter->endOfNumber = true;
    iter->num = num;
  }

  int maxXor(int num) {
    TrieNode* iter = root;

    for (int i = 31; i >= 0 && !iter->end(); i--) {
      int bit = (num & (1 << i)) != 0;
      iter = (iter->children[!bit] == NULL) ? iter->children[bit]
                                            : iter->children[!bit];
    }

    return (num) ^ (iter->num);
  }
};

int findMaximumXOR(vector<int>& nums);

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

    cout << "Maximum XOR: " << findMaximumXOR(nums) << endl;

    cout << endl;
  }

  return 0;
}

int findMaximumXOR(vector<int>& nums) {
  Trie* trie = new Trie();
  int maxXor = 0;
  for (int i : nums) {
    trie->insert(i);
    maxXor = max(maxXor, trie->maxXor(i));
  }

  return maxXor;
}
