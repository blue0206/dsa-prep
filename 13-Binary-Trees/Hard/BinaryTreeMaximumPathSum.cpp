/*
 * Problem: Binary Tree Maximum Path Sum (LeetCode #124)
 * Link: https://leetcode.com/problems/binary-tree-maximum-path-sum/description/
 *
 * Approach: This problem is solved using a recursive Depth-First Search (DFS)
 *           with a post-order traversal pattern. For each node, we need to
 *           distinguish between two values:
 *
 *           1.  **The value to return upwards:** A node can only pass up a
 *               straight path to its parent (either `node->val + left_path` or
 *               `node->val + right_path`). It cannot pass up a path that bends
 *               (uses both left and right children). We return `node->val +
 *               max(left_path, right_path)`. We also use `max(0, ...)` to
 *               ignore negative paths from children.
 *           2.  **The value to update the global maximum with:** At any node,
 *               the maximum path sum that uses this node as the highest point
 *               (the "bend") is `node->val + left_path + right_path`. We
 *               maintain a global `maxSum` variable and update it with this
 *               potential maximum at every node.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(H), where H is the height of the tree.
 */
#include <algorithm>
#include <iostream>
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

int maxPathSum(const TreeNode* root);
int pathSum(const TreeNode* root, int& maxSum);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    cout << "Maximum Path Sum: " << maxPathSum(root) << endl;
  }

  return 0;
}

int maxPathSum(const TreeNode* root) {
  int maxSum = INT_MIN;
  pathSum(root, maxSum);

  return maxSum;
}

int pathSum(const TreeNode* root, int& maxSum) {
  if (root == NULL) return 0;

  // Recursively get the max path sum from left and right subtrees.
  // Ignore negative paths by taking max with 0.
  int leftSum = max(0, pathSum(root->left, maxSum));
  int rightSum = max(0, pathSum(root->right, maxSum));

  // Update the overall maximum path sum with the path that "bends" at the
  // current node.
  maxSum = max(maxSum, root->val + leftSum + rightSum);

  // Return the maximum path sum that can be extended upwards to the parent.
  // This path cannot "bend".
  return root->val + max(leftSum, rightSum);
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
