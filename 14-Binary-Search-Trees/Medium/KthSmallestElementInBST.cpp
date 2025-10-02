/*
 * Problem: Kth Smallest Element in a BST (LeetCode #230)
 * Link:
 * https://leetcode.com/problems/kth-smallest-element-in-a-bst/description/
 *
 * Approach: The key property of a Binary Search Tree (BST) is that an inorder
 *           traversal (Left -> Root -> Right) visits the nodes in ascending
 *           sorted order. Therefore, the k-th smallest element is simply the
 *           k-th element encountered during an inorder traversal.
 *           This solution uses a recursive helper function to perform the
 *           inorder traversal. A counter `k` is passed by reference and
 *           decremented each time a node is "visited" (after its left subtree
 *           has been processed). When `k` becomes 0, the current node is the
 *           k-th smallest, and its value is stored.
 *
 * Time Complexity: O(H + k), where H is the height of the tree.
 * Space Complexity: O(H) for the recursion call stack.
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

int kthSmallest(TreeNode* root, int k);
void findKthElement(TreeNode* root, int& ans, int& k);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    int x;
    cin >> x;
    cin.ignore();  // Consume the newline after reading the integer

    cout << x << "th smallest element: " << kthSmallest(root, x) << endl;
  }

  return 0;
}

int kthSmallest(TreeNode* root, int k) {
  int ans = -1;
  findKthElement(root, ans, k);
  return ans;
}

void findKthElement(TreeNode* root, int& ans, int& k) {
  if (root == NULL || k <= 0) {
    return;
  }

  // Go left.
  findKthElement(root->left, ans, k);

  // Process current node.
  k--;
  if (k == 0) {
    ans = root->val;
    return;  // Found the element, no need to go right.
  }

  // Go right.
  findKthElement(root->right, ans, k);
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
