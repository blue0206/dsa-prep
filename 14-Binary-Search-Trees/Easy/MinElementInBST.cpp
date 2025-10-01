/*
 * Problem: Min Element In BST
 * Link:
 * https://www.naukri.com/code360/problems/minimum-element-in-bst_8160462?leftPanelTabValue=PROBLEM
 *
 * Approach: To find the minimum element in a Binary Search Tree (BST), we
 *           leverage its fundamental property: for any given node, all values
 *           in its left subtree are smaller. Therefore, the minimum value in
 *           the entire tree must be the node that is furthest to the left.
 *           This solution iteratively traverses from the root, repeatedly
 *           moving to the left child until a node with no left child is found.
 *           This leftmost node contains the minimum value.
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

int minVal(const TreeNode* root);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    cout << "Min Element: " << minVal(root) << endl;
  }

  return 0;
}

int minVal(const TreeNode* root) {
  if (root == NULL) return -1;  // As per problem statement for empty tree

  const TreeNode* iter = root;
  while (iter->left != NULL) {
    iter = iter->left;
  }

  return iter->val;
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
