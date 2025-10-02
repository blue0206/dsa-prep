/*
 * Problem: Lowest Common Ancestor of a Binary Search Tree (LeetCode #235)
 * Link:
 * https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/description/
 *
 * Approach: This iterative solution leverages the properties of a Binary
 *           Search Tree (BST) to efficiently find the LCA. The LCA of two
 *           nodes `p` and `q` is the node where their paths from the root
 *           diverge.
 *           - Start at the root.
 *           - If the current node's value is greater than both `p` and `q`,
 *             the LCA must be in the left subtree.
 *           - If the current node's value is less than both `p` and `q`, the
 *             LCA must be in the right subtree.
 *           - Otherwise, the current node is the split point (or one of the
 *             nodes is the ancestor of the other). In this case, the current
 *             node is the LCA.
 *
 * Time Complexity: O(H), where H is the height of the tree.
 * Space Complexity: O(1)
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

TreeNode* lowestCommonAncestor(TreeNode* root, const TreeNode* p,
                               const TreeNode* q);

TreeNode* buildTree(const string& str);
TreeNode* findNode(TreeNode* root, int val);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);
  }

  return 0;
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
  TreeNode* iter = root;
  while (iter != NULL) {
    if (iter->val > p->val && iter->val > q->val) {
      iter = iter->left;
    } else if (iter->val < p->val && iter->val < q->val) {
      iter = iter->right;
    } else {
      return iter;
    }
  }

  return NULL;
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

// Helper function to find a node by its value in a BST
TreeNode* findNode(TreeNode* root, int val) {
  if (root == nullptr) return nullptr;
  if (root->val == val) return root;
  if (val < root->val) return findNode(root->left, val);
  return findNode(root->right, val);
}
