/*
 * Problem: Balanced Binary Tree (LeetCode #110)
 * Link: https://leetcode.com/problems/balanced-binary-tree/description/
 *
 * Approach: This problem can be solved efficiently using a modified Depth-First
 *           Search (DFS). We need to check two conditions for every node:
 *           1. The height difference between its left and right subtrees is at
 *              most 1.
 *           2. Both its left and right subtrees are also balanced.
 *
 *           This naturally leads to a post-order traversal (Left, Right, Root)
 *           because we need the heights of the subtrees before we can check the
 *           current node.
 *
 *           The `checkHeightBalance` function returns the height of a subtree
 *           if it's balanced, or a special value `-1` if it's not. This allows
 *           us to propagate the "unbalanced" status up the recursion tree and
 *           stop early.
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

bool isBalanced(const TreeNode* root);
int checkHeightBalance(const TreeNode* root);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    cout << "Result: " << (isBalanced(root) ? "True" : "False") << endl;
  }

  return 0;
}

bool isBalanced(const TreeNode* root) {
  return (checkHeightBalance(root) == -1) ? false : true;
}

int checkHeightBalance(const TreeNode* root) {
  if (root == NULL) return 0;

  int leftHeight = checkHeightBalance(root->left);
  // If the left subtree is unbalanced, propagate the -1 up.
  if (leftHeight == -1) return -1;

  int rightHeight = checkHeightBalance(root->right);
  // If the right subtree is unbalanced, propagate the -1 up.
  if (rightHeight == -1) return -1;

  // Check if the current node is unbalanced.
  if (abs(leftHeight - rightHeight) > 1) return -1;

  // If balanced, return the height of the current subtree.
  return 1 + max(leftHeight, rightHeight);
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
