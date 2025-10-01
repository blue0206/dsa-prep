/*
 * Problem: Flatten Binary Tree to Linked List (LeetCode #114)
 * Link:
 * https://leetcode.com/problems/flatten-binary-tree-to-linked-list/description/
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
 * Approach: This recursive solution uses a post-order traversal (Right, Left,
 *           Root) to flatten the tree. A `prev` pointer is used to keep track
 *           of the previously processed node.
 *           1.  Recursively call on the right subtree.
 *           2.  Recursively call on the left subtree.
 *           3.  After the right and left subtrees have been flattened, process
 *               the current `root`. Set its `right` pointer to `prev` (the
 *               head of the already-flattened right part of the list) and its
 *               `left` pointer to `NULL`.
 *           4.  Update `prev` to be the current `root`.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(H), where H is the height of the tree.
 */
void recursiveApproach(TreeNode* root);

/**
 * Approach: This approach uses a modified Morris Traversal to achieve O(1)
 *           space complexity. It's a clever adaptation of the preorder
 *           traversal.
 *           - If the current node has a left child, find its inorder
 *             predecessor (the rightmost node of the left subtree).
 *           - Instead of just creating a temporary thread, we perform the
 *             rewiring: link the predecessor's right to the current node's
 *             right, then move the entire left subtree to become the current
 *             node's right.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
void morrisApproach(TreeNode* root);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    // Uncomment approach to be used.
    morrisApproach(root);
    // recursiveApproach(root);
  }

  return 0;
}

void morrisApproach(TreeNode* root) {
  TreeNode* iter = root;

  while (iter != NULL) {
    if (iter->left == NULL) {
      iter = iter->right;
    } else {
      TreeNode* prev = iter->left;
      while (prev->right != NULL && prev->right != iter) {
        prev = prev->right;
      }

      if (prev->right == NULL) {
        prev->right = iter;
        iter = iter->left;
      } else {
        prev->right = iter->right;
        iter->right = iter->left;
        iter->left = NULL;
        iter = prev->right;
      }
    }
  }
}

TreeNode* prevNode = NULL;
void recursiveApproach(TreeNode* root) {
  if (root == NULL) return;

  recursiveApproach(root->right);
  recursiveApproach(root->left);

  root->right = prevNode;
  root->left = NULL;
  prevNode = root;
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
