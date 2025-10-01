/*
 * Problem: Construct Binary Tree from Preorder and Inorder Traversal
 *          (LeetCode #105)
 * Link:
 * https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/
 *
 * Approach: This solution uses a recursive approach that leverages the
 *           properties of preorder and inorder traversals.
 *
 *           1.  **Preorder's Property:** The first element in a preorder
 *               traversal is always the root of the tree/subtree.
 *           2.  **Inorder's Property:** All elements to the left of the root in
 *               an inorder traversal belong to the left subtree, and all
 *               elements to the right belong to the right subtree.
 *
 *           The algorithm works as follows:
 *           -   Create a hash map of inorder values to their indices for O(1)
 *               lookups.
 *           -   Use a recursive helper function `build`. The current root is
 *               determined by the current index in the `preorder` array.
 *           -   Find this root's index in the `inorder` map. This splits the
 *               inorder array into left and right subtrees.
 *           -   Recursively call `build` for the left subtree and the right
 *               subtree with their corresponding inorder segments.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_map>
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

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder);
TreeNode* build(vector<int>& preorder, vector<int>& inorder,
                unordered_map<int, int>& inMap, int& preIndex, int inLow,
                int inHigh);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> preorder(n), inorder(n);
    for (int i = 0; i < n; i++) {
      cin >> preorder[i];
    }
    for (int i = 0; i < n; i++) {
      cin >> inorder[i];
    }

    cout << "Pre-Order: [ ";
    for (auto i : preorder) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "In-Order: [ ";
    for (auto i : inorder) {
      cout << i << " ";
    }
    cout << "]" << endl;

    TreeNode* root = buildTree(preorder, inorder);
  }

  return 0;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
  unordered_map<int, int> inMap;  // val -> index
  for (int i = 0; i < inorder.size(); i++) {
    inMap[inorder[i]] = i;
  }

  int preIndex = 0;
  return build(preorder, inorder, inMap, preIndex, 0, inorder.size() - 1);
}

TreeNode* build(vector<int>& preorder, vector<int>& inorder,
                unordered_map<int, int>& inMap, int& preIndex, int inLow,
                int inHigh) {
  if (inLow > inHigh) {
    return NULL;
  }

  int rootVal = preorder[preIndex];
  TreeNode* root = new TreeNode(rootVal);
  preIndex++;

  int inorderRoot = inMap[rootVal];

  root->left =
      build(preorder, inorder, inMap, preIndex, inLow, inorderRoot - 1);
  root->right =
      build(preorder, inorder, inMap, preIndex, inorderRoot + 1, inHigh);

  return root;
}
