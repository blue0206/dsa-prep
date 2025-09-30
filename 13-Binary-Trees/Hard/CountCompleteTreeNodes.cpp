/*
 * Problem: Count Complete Tree Nodes (LeetCode #222)
 * Link: https://leetcode.com/problems/count-complete-tree-nodes/description/
 *
 * Approach: This solution leverages the properties of a complete binary tree to
 *           achieve a time complexity better than O(N).
 *
 *           For any node in the tree, we calculate the height of its leftmost
 *           path and its rightmost path.
 *           1.  If `leftHeight == rightHeight`, it means the subtree rooted at
 *               the current node is a **perfect** binary tree. In this case,
 *               we can calculate the number of nodes directly using the
 *               formula `2^height - 1` and stop the recursion for this branch.
 *           2.  If `leftHeight != rightHeight`, the subtree is complete but not
 *               perfect. We don't have a shortcut, so we fall back to the
 *               standard recursive formula: `1 + countNodes(left) +
 *               countNodes(right)`.
 *
 *           This optimization ensures that we only traverse a single path down
 *           the tree at each step, leading to a logarithmic time complexity.
 *
 * Time Complexity: O((log N)^2)
 * Space Complexity: O(log N) for the recursion stack.
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

int countNodes(const TreeNode* root);
int getLeftHeight(const TreeNode* root);
int getRightHeight(const TreeNode* root);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    cout << "Number of Nodes in Complete Binary Tree: " << countNodes(root)
         << endl;
  }

  return 0;
}

int countNodes(const TreeNode* root) {
  if (root == NULL) return 0;

  int leftHeight = getLeftHeight(root);
  int rightHeight = getRightHeight(root);

  // If the subtree is a perfect binary tree, calculate nodes with the formula.
  if (leftHeight == rightHeight) {
    return (1 << leftHeight) - 1;  // 2^h - 1
  } else {
    // Otherwise, recursively count nodes in left and right subtrees.
    return 1 + countNodes(root->left) + countNodes(root->right);
  }
}

int getLeftHeight(const TreeNode* root) {
  const TreeNode* iter = root;
  int ht = 0;
  while (iter != NULL) {
    ht++;
    iter = iter->left;
  }
  return ht;
}

int getRightHeight(const TreeNode* root) {
  const TreeNode* iter = root;
  int ht = 0;
  while (iter != NULL) {
    ht++;
    iter = iter->right;
  }
  return ht;
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
