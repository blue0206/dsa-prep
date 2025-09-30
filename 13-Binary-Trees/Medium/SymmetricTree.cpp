/*
 * Problem: Symmetric Tree (LeetCode #101)
 * Link: https://leetcode.com/problems/symmetric-tree/description/
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
 * Approach: This recursive solution checks for symmetry by comparing two
 *           subtrees at a time. A helper function `checkSymmetry` is used,
 *           which takes two nodes, `root1` and `root2`.
 *           1.  The base case: if either node is null, they must both be null
 *               to be symmetric.
 *           2.  The recursive step: The two nodes are symmetric if their values
 *               are equal, AND the left subtree of `root1` is symmetric to the
 *               right subtree of `root2`, AND the right subtree of `root1` is
 *               symmetric to the left subtree of `root2`.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(H), where H is the height of the tree.
 */
bool recursiveApproach(TreeNode* root);
bool checkSymmetry(TreeNode* root1, TreeNode* root2);

/**
 * Approach: This iterative solution uses two stacks to simulate the recursive
 *           comparison. One stack traces the left subtree, and the other
 *           traces the right subtree in a mirrored fashion.
 *           1.  Push the root's left and right children onto `st1` and `st2`.
 *           2.  In a loop, pop one node from each stack and compare them.
 *           3.  If they are not symmetric (one is null, values differ), return
 *               false.
 *           4.  To maintain the mirrored traversal, push children onto the
 *               stacks in opposite orders: `st1` gets `left` then `right`,
 *               while `st2` gets `right` then `left`.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(H), where H is the height of the tree.
 */
bool iterativeApproach(TreeNode* root);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    cout << "Result (Recursive Approach): "
         << (recursiveApproach(root) ? "True" : "False") << endl;
    cout << "Result (Iterative Approach): "
         << (iterativeApproach(root) ? "True" : "False") << endl;
  }

  return 0;
}

//------------------------------RECURSIVE APPROACH------------------------------
bool recursiveApproach(TreeNode* root) {
  if (root == NULL) return true;

  return checkSymmetry(root->left, root->right);
}

bool checkSymmetry(TreeNode* root1, TreeNode* root2) {
  if (root1 == NULL || root2 == NULL) return root1 == root2;

  bool left = checkSymmetry(root1->left, root2->right);
  bool right = checkSymmetry(root1->right, root2->left);

  return (root1->val == root2->val && left && right);
}

//------------------------------ITERATIVE APPROACH------------------------------
bool iterativeApproach(TreeNode* root) {
  if (root == NULL) return true;
  stack<TreeNode*> st1, st2;
  st1.push(root->left);
  st2.push(root->right);

  while (!st1.empty() || !st2.empty()) {
    if (st1.size() != st2.size()) return false;

    TreeNode* node1 = st1.top();
    st1.pop();
    TreeNode* node2 = st2.top();
    st2.pop();

    if (node1 == NULL || node2 == NULL) {
      if (node1 != node2) return false;
      continue;
    }
    if (node1->val != node2->val) return false;

    st1.push(node1->left);
    st1.push(node1->right);

    st2.push(node2->right);
    st2.push(node2->left);
  }

  return true;
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
