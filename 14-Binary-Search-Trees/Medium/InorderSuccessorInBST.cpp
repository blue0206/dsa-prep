/*
 * Problem: Inorder Successor in BST
 * Link: https://www.geeksforgeeks.org/problems/inorder-successor-in-bst/1
 *
 * Approach: The inorder successor of a node `x` is the next node in the
 *           inorder traversal. There are two cases:
 *           1.  **Node `x` has a right child:** The successor is the minimum
 *               value in the right subtree of `x`. This is found by going to
 *               the right child and then traversing as far left as possible.
 *           2.  **Node `x` has no right child:** The successor is one of `x`'s
 *               ancestors. We traverse the tree from the root. While searching
 *               for `x`, we keep track of the last node where we took a left
 *               turn. This node is the successor because `x` lies in its left
 *               subtree, making it the next node to be visited in an inorder
 *               sequence.
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

int inOrderSuccessor(TreeNode* root, TreeNode* x);

TreeNode* findNode(TreeNode* root, int val);
TreeNode* buildTree(const string& str);
void printInorder(TreeNode* root);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    int val;
    cin >> val;
    cin.ignore();

    TreeNode* x = findNode(root, val);
    int successorVal = inOrderSuccessor(root, x);

    cout << "Inorder successor of " << val << ": "
         << ((successorVal == -1) ? "None" : to_string(successorVal)) << endl;
  }

  return 0;
}

int inOrderSuccessor(TreeNode* root, TreeNode* x) {
  if (x == NULL) return -1;

  if (x->right != NULL) {
    TreeNode* successor = x->right;
    while (successor->left != NULL) {
      successor = successor->left;
    }

    return successor->val;
  }

  TreeNode* parent = NULL;
  TreeNode* iter = root;
  while (iter != NULL && iter->val != x->val) {
    if (iter->val < x->val) {
      iter = iter->right;
    } else {
      parent = iter;
      iter = iter->left;
    }
  }

  return (parent == NULL) ? -1 : parent->val;
}

// Helper function to find a node by its value in a BST
TreeNode* findNode(TreeNode* root, int val) {
  if (root == nullptr) return nullptr;
  if (root->val == val) return root;
  if (val < root->val)
    return findNode(root->left, val);
  else
    return findNode(root->right, val);
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

// Helper function to print the inorder traversal
void printInorder(TreeNode* root) {
  if (root == NULL) return;
  printInorder(root->left);
  cout << root->val << " ";
  printInorder(root->right);
}
