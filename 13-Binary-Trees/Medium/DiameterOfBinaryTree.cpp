/*
 * Problem: Diameter of Binary Tree (LeetCode #543)
 * Link: https://leetcode.com/problems/diameter-of-binary-tree/description/
 *
 * Approach: The diameter of a binary tree is the length of the longest path
 *           between any two nodes. This path may or may not pass through the
 *           root.
 *
 *           This problem can be solved with a single Depth-First Search (DFS).
 *           We can write a recursive function that does two things for each
 *           node:
 *           1.  **Calculate and return its height:** The height of a node is
 *               `1 + max(height of left child, height of right child)`.
 *           2.  **Update the maximum diameter:** For each node, the longest
 *               path passing through it is `height of left child + height of
 *               right child`. We keep a global maximum variable and update it
 *               at every node.
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

int diameterOfBinaryTree(const TreeNode* root);
int calculateDiameter(const TreeNode* root, int& maxDiameter);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    cout << "Maximum Diameter: " << diameterOfBinaryTree(root) << endl;
  }

  return 0;
}

int diameterOfBinaryTree(const TreeNode* root) {
  int maxDiameter = 0;
  calculateDiameter(root, maxDiameter);

  return maxDiameter;
}

int calculateDiameter(const TreeNode* root, int& maxDiameter) {
  if (root == NULL) return 0;

  // Recursively find the height of the left and right subtrees.
  int leftHeight = calculateDiameter(root->left, maxDiameter);
  int rightHeight = calculateDiameter(root->right, maxDiameter);

  // The diameter at the current node is the sum of the heights of its subtrees.
  // Update the overall maximum diameter found so far.
  maxDiameter = max(maxDiameter, leftHeight + rightHeight);

  // Return the height of the tree rooted at the current node.
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
