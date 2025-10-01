/*
 * Problem: Insert into a Binary Search Tree (LeetCode #701)
 * Link:
 * https://leetcode.com/problems/insert-into-a-binary-search-tree/description/
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
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

/**
 * Approach: This iterative solution finds the correct position for the new
 *           node by traversing the tree from the root.
 *           1.  Handle the edge case of an empty tree by returning a new node.
 *           2.  Use a `while` loop to navigate down the tree, keeping track of
 *               the `parent` of the current `iter` node.
 *           3.  The loop terminates when `iter` becomes `NULL`, at which point
 *               `parent` holds the node to which the new node should be
 *               attached.
 *           4.  A final comparison determines whether to attach the new node
 *               as the left or right child of the `parent`.
 *
 * Time Complexity: O(H), where H is the height of the tree.
 * Space Complexity: O(1)
 */
TreeNode* iterativeApproach(TreeNode* root, int val);

/**
 * Approach: This recursive solution leverages the call stack to insert the new
 *           node.
 *           1.  **Base Case:** If the current `root` is `NULL`, we have found
 *               the insertion point. A new node is created and returned, which
 *               will be linked by its parent in the previous call.
 *           2.  **Recursive Step:** If the `val` is greater than the current
 *               node's value, we recursively call on the right subtree.
 *               Otherwise, we call on the left subtree. The return value of
 *               the recursive call (which will eventually be the new node) is
 *               assigned to the appropriate child pointer (`root->right` or
 *               `root->left`).
 *
 * Time Complexity: O(H), where H is the height of the tree.
 * Space Complexity: O(H) for the recursion call stack.
 */
TreeNode* recursiveApproach(TreeNode* root, int val);

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

    int val;
    cin >> val;
    cin.ignore();  // Consume the newline after reading the integer

    // Uncomment the approach to be used.
    TreeNode* newRoot = iterativeApproach(root, val);
    // TreeNode* newRoot = recursiveApproach(root, val);

    cout << "Inorder after insertion: ";
    printInorder(newRoot);
    cout << endl;
  }

  return 0;
}

//-----------------------------ITERATIVE APPROACH-------------------------------
TreeNode* iterativeApproach(TreeNode* root, int val) {
  TreeNode* newNode = new TreeNode(val);
  if (root == NULL) {
    return newNode;
  }

  TreeNode* iter = root;
  TreeNode* parent = NULL;

  while (iter != NULL) {
    parent = iter;
    if (iter->val > val) {
      iter = iter->left;
    } else {
      iter = iter->right;
    }
  }

  if (parent->val > val)
    parent->left = newNode;
  else
    parent->right = newNode;

  return root;
}

//------------------------------RECURSIVE APPROACH------------------------------
TreeNode* recursiveApproach(TreeNode* root, int val) {
  if (root == NULL) {
    TreeNode* newNode = new TreeNode(val);
    return newNode;
  }

  if (val > root->val) {
    root->right = recursiveApproach(root->right, val);
  } else {
    root->left = recursiveApproach(root->left, val);
  }

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

// Helper function to print the traversal result
void printInorder(TreeNode* root) {
  if (root == NULL) return;
  printInorder(root->left);
  cout << root->val << " ";
  printInorder(root->right);
}
