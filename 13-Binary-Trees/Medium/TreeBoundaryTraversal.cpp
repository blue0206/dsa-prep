/*
 * Problem: Boundary Traversal of Binary Tree
 * Link:
 * https://www.naukri.com/code360/problems/boundary-traversal_790725?leftPanelTabValue=PROBLEM
 *
 * Approach: The boundary traversal is performed in three parts in an
 *           anti-clockwise direction:
 *           1.  **Left Boundary:** Traverse the left boundary from top to
 *               bottom, excluding any leaf nodes. This is done by always
 *               preferring the left child, and if not available, the right
 *               child.
 *           2.  **Leaf Nodes:** Traverse all leaf nodes from left to right.
 *               This is achieved with a standard preorder traversal that only
 *               adds leaf nodes to the result.
 *           3.  **Right Boundary (Reversed):** Traverse the right boundary from
 *               bottom to top, excluding any leaf nodes. This is done
 *               recursively, adding the node's value after the recursive call
 *               to achieve the reverse order.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(H), where H is the height of the tree.
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

vector<int> traverseBoundary(const TreeNode* root);
void traverseLeft(const TreeNode* root, vector<int>& ans);
void traverseRight(const TreeNode* root, vector<int>& ans);
void processLeaves(const TreeNode* root, vector<int>& ans);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    vector<int> ans = traverseBoundary(root);

    cout << "Boundary Traversal: [ ";
    for (int i : ans) {
      cout << i << " ";
    }
    cout << "]" << endl;
  }

  return 0;
}

vector<int> traverseBoundary(const TreeNode* root) {
  if (root == NULL) return {};

  vector<int> ans;
  ans.emplace_back(root->val);

  // If the root is a leaf, we are done.
  if (root->left == NULL && root->right == NULL) return ans;

  traverseLeft(root->left, ans);
  processLeaves(root->left, ans);
  processLeaves(root->right, ans);
  traverseRight(root->right, ans);

  return ans;
}

void traverseLeft(const TreeNode* root, vector<int>& ans) {
  if (root == NULL) return;
  // Do not add leaf nodes.
  if (root->left == NULL && root->right == NULL) return;

  ans.emplace_back(root->val);
  if (root->left != NULL) {
    traverseLeft(root->left, ans);
  } else {
    traverseLeft(root->right, ans);
  }
}

void traverseRight(const TreeNode* root, vector<int>& ans) {
  if (root == NULL) return;
  // Do not add leaf nodes.
  if (root->left == NULL && root->right == NULL) return;

  if (root->right != NULL) {
    traverseRight(root->right, ans);
  } else {
    traverseRight(root->left, ans);
  }

  // Add after the recursive call to get bottom-up order.
  ans.emplace_back(root->val);
}

void processLeaves(const TreeNode* root, vector<int>& ans) {
  if (root == NULL) return;

  // This is a standard preorder traversal to find leaves.
  if (root->left == NULL && root->right == NULL) {
    ans.emplace_back(root->val);
    return;
  }

  processLeaves(root->left, ans);
  processLeaves(root->right, ans);
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
