/*
 * Problem: Binary Tree Inorder Traversal (LeetCode #94)
 * Link:
 * https://leetcode.com/problems/binary-tree-inorder-traversal/description/
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
 * Approach: This iterative approach uses a stack to simulate the recursive
 *           inorder traversal.
 *           1. Create a stack and initialize a `current` node pointer to the
 *              root.
 *           2. In a loop, first go as far left as possible from the `current`
 *              node, pushing each node onto the stack along the way.
 *           3. When `current` becomes NULL, it means we've reached the
 *              leftmost node. Pop a node from the stack.
 *           4. Process the popped node's value (add it to the result).
 *           5. Move to the right child of the popped node (`current =
 *              current->right`) and repeat the process.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(H), where H is the height of the tree.
 */
vector<int> iterativeApproach(TreeNode* root);

/**
 * Approach: This is the classic recursive solution that directly follows the
 *           definition of inorder traversal (Left -> Root -> Right).
 *           1. If the current node is null, return.
 *           2. Make a recursive call on the left child.
 *           3. Process the current node's value.
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
    cout << "Iterative Inorder: ";
    printTree(iterativeResult);

    vector<int> recursiveResult = recursiveApproach(root);
    cout << "Recursive Inorder: ";
    printTree(recursiveResult);

    cout << endl;
  }

  return 0;
}

//------------------------------ITERATIVE APPROACH------------------------------
vector<int> iterativeApproach(TreeNode* root) {
  vector<int> tree;

  stack<TreeNode*> st;
  TreeNode* current = root;
  while (!st.empty() || current != NULL) {
    // Go as far left as possible.
    while (current != NULL) {
      st.push(current);
      current = current->left;
    }

    // Process the node.
    current = st.top();
    st.pop();
    tree.emplace_back(current->val);
    // Move to the right subtree.
    current = current->right;
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

  traverse(root->left, tree);
  tree.emplace_back(root->val);
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
