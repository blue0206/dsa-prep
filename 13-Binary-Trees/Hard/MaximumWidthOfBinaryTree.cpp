/*
 * Problem: Maximum Width of Binary Tree (LeetCode #662)
 * Link: https://leetcode.com/problems/maximum-width-of-binary-tree/description/
 *
 * Approach: This problem is solved using a level-order traversal (BFS). The key
 *           idea is to assign an index to every node as if it were in a
 *           complete binary tree.
 *           - The root is at index 0.
 *           - A node at index `i` has its left child at `2*i + 1` and its right
 *             child at `2*i + 2`.
 *
 *           We use a queue to store pairs of `(TreeNode*, index)`. For each
 *           level, the width is the difference between the index of the
 *           rightmost node and the leftmost node, plus one. We keep track of
 *           the maximum width found across all levels.
 *
 *           `unsigned long long` is used for the index to prevent integer
 *           overflow, which can happen in deep or skewed trees.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(W), where W is the maximum number of nodes in any level.
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

int widthOfBinaryTree(const TreeNode* root);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    cout << "Width of Binary Tree: " << widthOfBinaryTree(root) << endl;
  }

  return 0;
}

int widthOfBinaryTree(const TreeNode* root) {
  if (root == NULL) return 0;

  queue<pair<const TreeNode*, unsigned long long>> q;
  q.push({root, 0});

  unsigned long long maxWidth = 0;
  while (!q.empty()) {
    int size = q.size();
    // Get the index of the first node at the current level.
    unsigned long long firstIndex = q.front().second;
    unsigned long long lastIndex = 0;

    for (int i = 0; i < size; i++) {
      auto [node, pos] = q.front();
      q.pop();

      // `pos` will be the index of the last node in the level on the last
      // iteration.
      lastIndex = pos;

      if (node->left) q.push({node->left, pos * 2LL + 1LL});
      if (node->right) q.push({node->right, pos * 2LL + 2LL});
    }
    // Update maxWidth with the width of the current level.
    maxWidth = max(maxWidth, lastIndex - firstIndex + 1);
  }

  return maxWidth;
}

// Helper function to build a tree from level-order input
TreeNode* buildTree(const string& str) {
  if (str.length() == 0 || str[0] == 'N') {
    return NULL;
  }
  vector<string> ip;
  stringstream ss(str);
  string word;
  while (ss >> word) {
    ip.push_back(word);
  }

  TreeNode* root = new TreeNode(stoi(ip[0]));
  queue<TreeNode*> q;
  q.push(root);

  int i = 1;
  while (!q.empty() && i < ip.size()) {
    TreeNode* currNode = q.front();
    q.pop();

    if (ip[i] != "-1") {
      currNode->left = new TreeNode(stoi(ip[i]));
      q.push(currNode->left);
    }
    i++;

    if (i < ip.size() && ip[i] != "-1") {
      currNode->right = new TreeNode(stoi(ip[i]));
      q.push(currNode->right);
    }
    i++;
  }
  return root;
}
