/*
 * Problem: Maximum Depth of Binary Tree (LeetCode #104)
 * Link: https://leetcode.com/problems/maximum-depth-of-binary-tree/description/
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

/**
 * Approach: This is a level-order traversal (BFS) approach. We traverse the
 *           tree level by level, using a queue to keep track of nodes. We
 *           simply count how many levels we traverse until the queue is empty.
 *           This count is the maximum depth of the tree.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(W), where W is the maximum width of the tree.
 */
int bfsApproach(const TreeNode* root);

/**
 * Approach: This is a classic recursive Depth-First Search (DFS) solution. The
 *           depth of a tree is defined by the longest path from the root to a
 *           leaf. Recursively, the depth of a node is `1 + max(depth of left
 *           subtree, depth of right subtree)`. The base case is a null node,
 *           which has a depth of 0.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(H), where H is the height of the tree (for the recursion
 *                   stack).
 */
int dfsApproach(const TreeNode* root);

TreeNode* buildTree(const string& str);
void printTree(const vector<int>& tree);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    cout << "Max Depth (BFS): " << bfsApproach(root) << endl;
    cout << "Max Depth (DFS): " << dfsApproach(root) << endl;

    cout << endl;
  }

  return 0;
}

//-------------------------------BFS APPROACH-----------------------------------
int bfsApproach(const TreeNode* root) {
  if (root == NULL) return 0;

  queue<TreeNode*> q;
  q.push(const_cast<TreeNode*>(root));
  int height = 0;
  while (!q.empty()) {
    int size = q.size();

    for (int i = 0; i < size; i++) {
      TreeNode* node = q.front();
      q.pop();

      if (node->left != NULL) q.push(node->left);
      if (node->right != NULL) q.push(node->right);
    }
    height++;
  }

  return height;
}

//-------------------------------DFS APPROACH-----------------------------------
int dfsApproach(const TreeNode* root) {
  // Base case: A null node has a depth of 0.
  if (root == NULL) return 0;

  // Recursively find the depth of the left and right subtrees.
  int leftDepth = dfsApproach(root->left);
  int rightDepth = dfsApproach(root->right);
  // The depth of the tree is 1 (for the current node) + the max of subtree
  // depths.
  return 1 + max(leftDepth, rightDepth);
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

// Helper function to print the traversal result
void printTree(const vector<int>& tree) {
  cout << "[ ";
  for (int val : tree) {
    cout << val << " ";
  }
  cout << "]" << endl;
}
