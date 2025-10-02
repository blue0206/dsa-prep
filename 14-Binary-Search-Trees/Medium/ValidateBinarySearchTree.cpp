/*
 * Problem: Validate Binary Search Tree (LeetCode #98)
 * Link: https://leetcode.com/problems/validate-binary-search-tree/description/
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
 * Approach: This solution leverages the property that an inorder traversal of a
 *           valid BST will produce a sequence of values in strictly ascending
 *           order.
 *           The algorithm performs a recursive inorder traversal, keeping
 *           track of the value of the previously visited node (`prev`). For
 *           each node, it checks if its value is greater than `prev`. If this
 *           condition is ever violated, the tree is not a valid BST.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(H), where H is the height of the tree.
 */
bool traversalApproach(TreeNode* root);
bool checkValid(TreeNode* root, long long& prev);

/**
 * Approach: This recursive solution validates the BST by ensuring that every
 *           node falls within a valid range `[minVal, maxVal]`.
 *           - The root node can be any value.
 *           - For a left child, its value must be less than its parent's
 *             value. So, the valid range for the left subtree is updated to
 *             `[minVal, parent.val]`.
 *           - For a right child, its value must be greater than its parent's
 *             value. The valid range for the right subtree is updated to
 *             `[parent.val, maxVal]`.
 *           If any node's value falls outside its designated range, the tree is
 *           invalid.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(H), where H is the height of the tree.
 */
bool rangeApproach(TreeNode* root);
bool isValid(TreeNode* root, long long minVal, long long maxVal);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    cout << "Result (Range Approach): " << rangeApproach(root) << endl;
    cout << "Result (Traversal Approach): " << traversalApproach(root) << endl;
  }

  return 0;
}

//-------------------------------RANGE APPROACH---------------------------------
bool rangeApproach(TreeNode* root) {
  return isValid(root, LLONG_MIN, LLONG_MAX);
}

bool isValid(TreeNode* root, long long minVal, long long maxVal) {
  if (root == NULL) return true;

  if (root->val <= minVal || root->val >= maxVal) {
    return false;
  }

  return (isValid(root->left, minVal, root->val) &&
          isValid(root->right, root->val, maxVal));
}

//-----------------------------TRAVERSAL APPROACH-------------------------------
bool traversalApproach(TreeNode* root) {
  long long prev = LLONG_MIN;
  return checkValid(root, prev);
}

bool checkValid(TreeNode* root, long long& prev) {
  if (root == NULL) return true;

  if (!checkValid(root->left, prev)) {
    return false;
  }
  if (root->val <= prev) {
    return false;
  }
  prev = root->val;
  if (!checkValid(root->right, prev)) {
    return false;
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
