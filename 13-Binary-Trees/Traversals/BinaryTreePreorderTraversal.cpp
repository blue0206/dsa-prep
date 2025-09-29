/*
 * Problem: Binary Tree Preorder Traversal (LeetCode #144)
 * Link:
 * https://leetcode.com/problems/binary-tree-preorder-traversal/description/
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
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
 * Approach: This iterative approach uses a stack to mimic the behavior of
 *           recursion.
 *           1. Push the root node onto the stack.
 *           2. While the stack is not empty, pop a node.
 *           3. Process the popped node's value (add it to the result).
 *           4. Push the right child onto the stack (if it exists).
 *           5. Push the left child onto the stack (if it exists).
 *           By pushing the right child before the left, we ensure that the
 *           left child is processed first, adhering to the LIFO (Last-In,
 *           First-Out) nature of the stack and the Root-Left-Right order.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(H), where H is the height of the tree.
 */
vector<int> iterativeApproach(TreeNode* root);

/**
 * Approach: This is the classic recursive solution that directly follows the
 *           definition of preorder traversal (Root -> Left -> Right).
 *           1. If the current node is null, return.
 *           2. Process the current node's value.
 *           3. Make a recursive call on the left child.
 *           4. Make a recursive call on the right child.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(H) for the recursion call stack.
 */
vector<int> recursiveApproach(const TreeNode* root);
void traverse(const TreeNode* root, vector<int>& tree);

TreeNode* buildTree(const string& str);
void printTree(const vector<int>& tree);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    vector<int> iterativeResult = iterativeApproach(root);
    cout << "Iterative Preorder: ";
    printTree(iterativeResult);

    vector<int> recursiveResult = recursiveApproach(root);
    cout << "Recursive Preorder: ";
    printTree(recursiveResult);

    cout << endl;
  }

  return 0;
}

//------------------------------ITERATIVE APPROACH------------------------------
vector<int> iterativeApproach(TreeNode* root) {
  vector<int> tree;
  stack<TreeNode*> st;
  if (root != NULL) st.push(root);

  while (!st.empty()) {
    const TreeNode* node = st.top();
    st.pop();

    tree.emplace_back(node->val);

    // Push right child first so that left child is processed first (LIFO).
    if (node->right != NULL) st.push(node->right);
    if (node->left != NULL) st.push(node->left);
  }

  return tree;
}

//------------------------------RECURSIVE APPROACH------------------------------
vector<int> recursiveApproach(const TreeNode* root) {
  vector<int> tree;
  traverse(root, tree);

  return tree;
}

void traverse(const TreeNode* root, vector<int>& tree) {
  if (root == NULL) return;

  tree.emplace_back(root->val);
  traverse(root->left, tree);
  traverse(root->right, tree);
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
void printTree(const vector<int>& tree) {
  cout << "[ ";
  for (int val : tree) {
    cout << val << " ";
  }
  cout << "]" << endl;
}
