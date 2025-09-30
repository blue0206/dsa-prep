/*
 * Problem: Lowest Common Ancestor of a Binary Tree (LeetCode #236)
 * Link:
 * https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/
 *
 * Approach: This problem is solved with a classic recursive Depth-First Search
 *           (DFS). The function has three key states for any given `root`:
 *
 *           1.  **Base Case:** If the `root` is `NULL`, or if it matches `p` or
 *               `q`, we return the `root`. This is because if we find one of
 *               the nodes, it could be the LCA itself (if the other node is in
 *               its subtree).
 *           2.  **Recursive Step:** We recursively call the function on the
 *               left and right subtrees.
 *           3.  **Combine Results:**
 *               - If the left call returns `NULL`, it means `p` and `q` are in
 *                 the right subtree, so we return the result from the right.
 *               - If the right call returns `NULL`, it means `p` and `q` are in
 *                 the left subtree, so we return the result from the left.
 *               - If neither call returns `NULL`, it means `p` and `q` were
 *                 found in different subtrees, making the current `root` the
 *                 LCA.
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

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    // Example: Find LCA of nodes 5 and 1 in a tree like
    // [3,5,1,6,2,0,8,null,null,7,4] This requires a way to get pointers to
    // nodes with value 5 and 1. For simplicity, we'll assume p and q are
    // root->left and root->right.
    if (root && root->left && root->right) {
      TreeNode* p = root->left;
      TreeNode* q = root->right;
      TreeNode* lca = lowestCommonAncestor(root, p, q);
      if (lca) {
        cout << "LCA of " << p->val << " and " << q->val << " is: " << lca->val
             << endl;
      }
    }
  }

  return 0;
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
  // Base case: if root is null, or we found p or q, return the root.
  if (root == NULL || root == p || root == q) return root;

  TreeNode* left = lowestCommonAncestor(root->left, p, q);
  TreeNode* right = lowestCommonAncestor(root->right, p, q);

  if (left != right) {
    // If both not null and unequal, they're definitely p and q,
    // hence current node is ancestor.
    if (left != NULL && right != NULL) return root;

    // left is NULL, right is a valid node (p or q or ancestor), return right.
    if (left == NULL) return right;
  }
  // If left and right are same, the current node is definitely not the LCA.
  return left;
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
