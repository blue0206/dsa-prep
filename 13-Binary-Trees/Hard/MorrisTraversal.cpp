/*
 * Problem: Morris Traversal (In-Order, Pre-Order, and Post-Order)
 *
 * Link (In-Order LC#94):
 * https://leetcode.com/problems/binary-tree-inorder-traversal/description/
 * Link (Pre-Order LC#144):
 * https://leetcode.com/problems/binary-tree-preorder-traversal/description/
 * Link (Post-Order LC#145):
 * https://leetcode.com/problems/binary-tree-postorder-traversal/description/
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
 * Approach: Morris Traversal for Preorder (Root -> Left -> Right).
 *           The core idea is to create temporary "threaded" links to avoid
 *           using a stack or recursion.
 *           - If the current node has no left child, process it and move to
 *             the right child.
 *           - If it has a left child, find the inorder predecessor (the
 *             rightmost node in the left subtree).
 *             - If the predecessor's right child is NULL, it's our first visit.
 *               Process the current node's value, create the thread from the
 *               predecessor to the current node, and move to the left child.
 *             - If the predecessor's right child points to the current node,
 *               it means we've finished the left subtree. Remove the thread
 *               and move to the right child.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
vector<int> preorderTraversal(TreeNode* root);

/**
 * Approach: Morris Traversal for Inorder (Left -> Root -> Right).
 *           This is the canonical Morris Traversal.
 *           - If the current node has no left child, process it and move to
 *             the right child.
 *           - If it has a left child, find the inorder predecessor.
 *             - If the predecessor's right child is NULL, create the thread
 *               from the predecessor to the current node and move to the left
 *               child.
 *             - If the predecessor's right child points to the current node,
 *               it means we've finished the left subtree. Remove the thread,
 *               process the current node's value, and move to the right child.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
vector<int> inorderTraversal(TreeNode* root);

/**
 * Approach: Morris Traversal for Postorder (Left -> Right -> Root).
 *           This is a clever modification. Instead of a direct postorder, we
 *           perform a traversal in the order `Root -> Right -> Left` and then
 *           reverse the result.
 *           The `Root -> Right -> Left` traversal is implemented similarly to
 *           the preorder Morris traversal, but with `left` and `right` roles
 *           swapped.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
vector<int> postorderTraversal(TreeNode* root);

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

    vector<int> inorderTraversalResult = inorderTraversal(root);
    cout << "In-Order: ";
    printTree(inorderTraversalResult);

    vector<int> preorderTraversalResult = preorderTraversal(root);
    cout << "Pre-Order: ";
    printTree(preorderTraversalResult);

    vector<int> postorderTraversalResult = postorderTraversal(root);
    cout << "Post-Order: ";
    printTree(postorderTraversalResult);

    cout << endl;
  }

  return 0;
}

vector<int> preorderTraversal(TreeNode* root) {
  vector<int> ans;
  TreeNode* iter = root;

  while (iter != NULL) {
    if (iter->left == NULL) {
      ans.emplace_back(iter->val);
      iter = iter->right;
    } else {
      TreeNode* prev = iter->left;
      while (prev->right != NULL && prev->right != iter) {
        prev = prev->right;
      }

      if (prev->right == NULL) {
        ans.emplace_back(iter->val);
        prev->right = iter;
        iter = iter->left;
      } else {
        prev->right = NULL;
        iter = iter->right;
      }
    }
  }

  return ans;
}

vector<int> inorderTraversal(TreeNode* root) {
  vector<int> ans;
  TreeNode* iter = root;

  while (iter != NULL) {
    if (iter->left == NULL) {
      ans.emplace_back(iter->val);
      iter = iter->right;
    } else {
      TreeNode* prev = iter->left;
      while (prev->right != NULL && prev->right != iter) {
        prev = prev->right;
      }

      if (prev->right == NULL) {
        prev->right = iter;
        iter = iter->left;
      } else {
        prev->right = NULL;
        ans.emplace_back(iter->val);
        iter = iter->right;
      }
    }
  }

  return ans;
}

vector<int> postorderTraversal(TreeNode* root) {
  vector<int> ans;
  TreeNode* iter = root;

  while (iter != NULL) {
    if (iter->right == NULL) {
      ans.emplace_back(iter->val);
      iter = iter->left;
    } else {
      TreeNode* prev = iter->right;
      while (prev->left != NULL && prev->left != iter) {
        prev = prev->left;
      }

      if (prev->left == NULL) {
        ans.emplace_back(iter->val);
        prev->left = iter;
        iter = iter->right;
      } else {
        prev->left = NULL;
        iter = iter->left;
      }
    }
  }

  reverse(ans.begin(), ans.end());
  return ans;
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
