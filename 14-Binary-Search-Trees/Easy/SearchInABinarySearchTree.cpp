/*
 * Problem: Search in a Binary Search Tree (LeetCode #700)
 * Link:
 * https://leetcode.com/problems/search-in-a-binary-search-tree/description/
 *
 * Approach: This is a classic iterative solution that leverages the properties
 *           of a Binary Search Tree (BST).
 *           Starting from the root, we compare the target `val` with the
 *           current node's value:
 *           - If `val` is greater, we move to the right child.
 *           - If `val` is smaller, we move to the left child.
 *           This process continues until we either find the node with the
 *           matching value or we reach a `NULL` pointer (meaning the value is
 *           not in the tree).
 *
 * Time Complexity: O(H), where H is the height of the tree. O(log N) on
 *                  average.
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

TreeNode* searchBST(const TreeNode* root, int val);

TreeNode* buildTree(const string& str);

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
    cin.ignore();  // Consume the newline after reading the integer

    TreeNode* target = searchBST(root, val);

    if (target) {
      cout << "Found node with value: " << target->val << endl;
    } else {
      cout << "Node with value " << val << " not found." << endl;
    }
  }

  return 0;
}

TreeNode* searchBST(const TreeNode* root, int val) {
  const TreeNode* iter = root;

  while (iter != NULL && iter->val != val) {
    if (val > iter->val) {
      iter = iter->right;
    } else {
      iter = iter->left;
    }
  }

  return const_cast<TreeNode*>(iter);
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
