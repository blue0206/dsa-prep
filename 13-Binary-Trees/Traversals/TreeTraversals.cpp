/*
 * Problem: Tree Traversals
 * Link:
 * https://www.naukri.com/code360/problems/tree-traversal_981269?leftPanelTabValue=PROBLEM
 *
 * Approach: This solution performs all three DFS traversals (inorder, preorder,
 *           postorder) in a single iteration using a stack. The stack stores
 *           pairs of `(TreeNode*, int)`, where the integer represents the
 *           state of processing for that node.
 *
 *           -   **State 1:** The first time we encounter a node. We add it to
 *               the `preorder` traversal, then push it back onto the stack
 *               with state 2, and finally push its left child with state 1.
 *           -   **State 2:** The second time we encounter a node (after
 *               visiting its left subtree). We add it to the `inorder`
 *               traversal, push it back with state 3, and then push its right
 *               child with state 1.
 *           -   **State 3:** The third and final time we encounter a node
 *               (after visiting its right subtree). We add it to the
 *               `postorder` traversal and do not push it back.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(H), where H is the height of the tree.
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

vector<vector<int>> getTreeTraversal(const TreeNode* root);

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

    vector<vector<int>> result = getTreeTraversal(root);
    cout << "Traversals (Inorder, Preorder, Postorder):" << endl;
    for (auto traversals : result) {
      cout << "[ ";
      for (auto i : traversals) {
        cout << i << " ";
      }
      cout << "]" << endl;
    }

    cout << endl;
  }

  return 0;
}

vector<vector<int>> getTreeTraversal(const TreeNode* root) {
  vector<int> pre, post, inorder;
  if (root == NULL) return {inorder, pre, post};

  stack<pair<const TreeNode*, int>> st;
  st.push({root, 1});

  while (!st.empty()) {
    auto [node, state] = st.top();
    st.pop();

    // State 1: Preorder processing. Go left.
    if (state == 1) {
      pre.emplace_back(node->val);
      st.push({node, 2});
      st.push({node->left, 1});
    }
    // State 2: Inorder processing. Go right.
    else if (state == 2) {
      inorder.emplace_back(node->val);
      st.push({node, 3});
      st.push({node->right, 1});
    }
    // State 3: Postorder processing.
    else {
      post.emplace_back(node->val);
    }
  }

  return {inorder, pre, post};
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
