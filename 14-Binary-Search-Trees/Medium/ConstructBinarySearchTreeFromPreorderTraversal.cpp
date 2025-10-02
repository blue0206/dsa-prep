/*
 * Problem: Construct Binary Search Tree from Preorder Traversal
 *          (LeetCode #1008)
 * Link:
 * https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/description/
 *
 * Approach: The key insight is that the inorder traversal of a Binary Search
 *           Tree is simply the sorted version of its elements.
 *           1.  Create a copy of the `preorder` traversal and sort it to
 *               obtain the `inorder` traversal.
 *           2.  With both `preorder` and `inorder` traversals, we can use the
 *               standard algorithm for constructing a binary tree.
 *           3.  A hash map is used to store the indices of elements in the
 *               `inorder` array for O(1) lookups.
 *           4.  A recursive function builds the tree: the current root is the
 *               next element from the `preorder` array, and its position in
 *               the `inorder` map splits the array into left and right
 *               subtrees.
 *
 * Time Complexity: O(N log N), dominated by the initial sort.
 * Space Complexity: O(N) for storing the inorder traversal and the hash map.
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

TreeNode* bstFromPreorder(vector<int>& preorder);
TreeNode* buildBST(vector<int>& preorder, vector<int>& inorder,
                   unordered_map<int, int>& inMap, int& preIndex, int inLow,
                   int inHigh);

TreeNode* buildTree(const string& str);
void printInorder(TreeNode* root);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> preorder(n);
    for (int i = 0; i < n; i++) cin >> preorder[i];

    TreeNode* root = bstFromPreorder(preorder);
    printInorder(root);
    cout << endl;
  }

  return 0;
}

TreeNode* bstFromPreorder(vector<int>& preorder) {
  vector<int> inorder = preorder;
  sort(inorder.begin(), inorder.end());

  unordered_map<int, int> inMap;
  for (int i = 0; i < inorder.size(); i++) {
    inMap[inorder[i]] = i;
  }

  int preIndex = 0;
  return buildBST(preorder, inorder, inMap, preIndex, 0, inorder.size() - 1);
}

TreeNode* buildBST(vector<int>& preorder, vector<int>& inorder,
                   unordered_map<int, int>& inMap, int& preIndex, int inLow,
                   int inHigh) {
  if (inLow > inHigh) {
    return NULL;
  }

  int rootVal = preorder[preIndex];
  TreeNode* root = new TreeNode(rootVal);
  preIndex++;

  root->left =
      buildBST(preorder, inorder, inMap, preIndex, inLow, inMap[rootVal] - 1);
  root->right =
      buildBST(preorder, inorder, inMap, preIndex, inMap[rootVal] + 1, inHigh);

  return root;
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
