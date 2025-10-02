/*
 * Problem: Maximum Sum BST in Binary Tree (LeetCode #1373)
 * Link:
 * https://leetcode.com/problems/maximum-sum-bst-in-binary-tree/description/
 *
 * Approach: This problem is solved using a post-order traversal. A recursive
 *           helper function is designed to return crucial information about
 *           each subtree it processes. This information is bundled into a
 *           `Details` struct containing:
 *           1.  `min`: The minimum value in the current subtree.
 *           2.  `max`: The maximum value in the current subtree.
 *           3.  `sum`: The sum of all nodes in the current subtree.
 *           4.  `valid`: A boolean indicating if the subtree is a valid BST.
 *
 *           The function gets these details from its left and right children.
 *           It then checks if the current node can form a valid BST with them
 *           (i.e., `root->val > left.max` and `root->val < right.min`). If it
 *           is a valid BST, its sum is calculated and used to update a global
 *           `maxSum`. The function then returns a new `Details` object for the
 *           current subtree to its parent.
 *
 * Time Complexity: O(N), as each node is visited once.
 * Space Complexity: O(H), where H is the height of the tree, for the recursion
 * stack.
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

struct Details {
  int max;
  int min;
  int sum;
  bool valid;
};

int maxSumBST(TreeNode* root);
Details findMaxBST(TreeNode* root, int& maxSum);

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

    cout << "Max BST: " << maxSumBST(root) << endl;
  }

  return 0;
}

int maxSumBST(TreeNode* root) {
  int maxSum = 0;
  findMaxBST(root, maxSum);

  return maxSum;
}

Details findMaxBST(TreeNode* root, int& maxSum) {
  if (root == NULL) {
    return {INT_MIN, INT_MAX, 0, true};
  }

  Details left = findMaxBST(root->left, maxSum);
  Details right = findMaxBST(root->right, maxSum);

  int minVal = min(left.min, right.min);
  int maxVal = max(left.max, right.max);

  Details treeDetails;
  treeDetails.max = max(root->val, maxVal);
  treeDetails.min = min(root->val, minVal);
  treeDetails.sum = root->val + left.sum + right.sum;

  if (left.valid && right.valid && root->val > left.max &&
      root->val < right.min) {
    treeDetails.valid = true;
    maxSum = max(maxSum, treeDetails.sum);
  } else {
    treeDetails.valid = false;
  }

  return treeDetails;
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
