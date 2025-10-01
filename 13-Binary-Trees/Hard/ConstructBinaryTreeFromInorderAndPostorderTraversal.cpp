/*
 * Problem: Construct Binary Tree from Inorder and Postorder Traversal
 *          (LeetCode #106)
 * Link:
 * https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description/
 *
 * Approach: This solution uses a recursive approach that leverages the
 *           properties of inorder and postorder traversals.
 *
 *           1.  **Postorder's Property:** The last element in a postorder
 *               traversal is always the root of the tree/subtree.
 *           2.  **Inorder's Property:** All elements to the left of the root in
 *               an inorder traversal belong to the left subtree, and all
 *               elements to the right belong to the right subtree.
 *
 *           The algorithm works as follows:
 *           -   Create a hash map of inorder values to their indices for O(1)
 *               lookups.
 *           -   Start from the end of the `postorder` array. The current
 *               element is the root of the current subtree.
 *           -   Find this root's index in the `inorder` map to determine the
 *               boundary between the left and right subtrees.
 *           -   Crucially, since we are processing the postorder array from
 *               back to front (which follows a `Root -> Right -> Left` order),
 *               we must recursively build the **right** subtree first, then the
 *               **left** subtree.
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

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder);
TreeNode* build(vector<int>& inorder, vector<int>& postorder,
                const unordered_map<int, int>& inMap, int& postIndex, int inLow,
                int inHigh);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> postorder(n), inorder(n);
    for (int i = 0; i < n; i++) {
      cin >> postorder[i];
    }
    for (int i = 0; i < n; i++) {
      cin >> inorder[i];
    }

    cout << "Post-Order: [ ";
    for (auto i : postorder) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "In-Order: [ ";
    for (auto i : inorder) {
      cout << i << " ";
    }
    cout << "]" << endl;

    TreeNode* root = buildTree(postorder, inorder);
  }

  return 0;
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
  unordered_map<int, int> inMap;  // val -> index
  for (int i = 0; i < inorder.size(); i++) {
    inMap[inorder[i]] = i;
  }

  int postIndex = postorder.size() - 1;
  return build(inorder, postorder, inMap, postIndex, 0, inorder.size() - 1);
}

TreeNode* build(vector<int>& inorder, vector<int>& postorder,
                const unordered_map<int, int>& inMap, int& postIndex, int inLow,
                int inHigh) {
  if (inLow > inHigh) {
    return NULL;
  }

  int rootVal = postorder[postIndex];
  TreeNode* root = new TreeNode(rootVal);
  postIndex--;

  int inorderRoot = inMap.at(rootVal);

  // Build right subtree first, then left subtree.
  root->right =
      build(inorder, postorder, inMap, postIndex, inorderRoot + 1, inHigh);
  root->left =
      build(inorder, postorder, inMap, postIndex, inLow, inorderRoot - 1);

  return root;
}
