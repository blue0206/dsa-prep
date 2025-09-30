/*
 * Problem: Binary Tree Paths (LeetCode #257)
 * Link: https://leetcode.com/problems/binary-tree-paths/description/
 *
 * Approach: This solution uses a recursive Depth-First Search (DFS) with
 *           backtracking to find all root-to-leaf paths.
 *           A helper function `traverse` is used, which takes the current node,
 *           a reference to the result vector, and a reference to the current
 *           path string.
 *           1.  As the function descends the tree, it appends the current
 *               node's value and "->" to the path string.
 *           2.  If a leaf node is reached, the final path is constructed and
 *               added to the result vector.
 *           3.  After the recursive calls for a node's children return, the
 *               function backtracks by erasing the part of the string that was
 *               just added. This allows the correct path to be formed for
 *               sibling nodes.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(H), where H is the height of the tree.
 */
#include <algorithm>
#include <iostream>
#include <map>
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

vector<string> binaryTreePaths(TreeNode* root);
void traverse(TreeNode* root, vector<string>& ans, string& s);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    vector<string> ans = binaryTreePaths(root);

    cout << "Binary Tree Paths: " << endl;
    for (auto s : ans) {
      cout << s << endl;
    }

    cout << endl;
  }

  return 0;
}

vector<string> binaryTreePaths(TreeNode* root) {
  vector<string> ans;
  string s = "";

  traverse(root, ans, s);

  return ans;
}

void traverse(TreeNode* root, vector<string>& ans, string& s) {
  if (root == NULL) return;
  if (root->left == NULL && root->right == NULL) {
    ans.emplace_back(s + to_string(root->val));
    return;
  }

  int index = s.length();
  string temp = to_string(root->val) + "->";
  s += temp;

  traverse(root->left, ans, s);
  traverse(root->right, ans, s);

  s.erase(index, temp.length());
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
