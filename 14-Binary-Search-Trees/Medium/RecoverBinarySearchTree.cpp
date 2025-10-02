/*
 * Problem: Recover Binary Search Tree (LeetCode #99)
 * Link: https://leetcode.com/problems/recover-binary-search-tree/description/
 *
 * Approach: The core idea is that an inorder traversal of a valid BST yields a
 *           sorted sequence of node values. If two nodes are swapped, this
 *           sorted property will be violated at one or two points.
 *
 *           This solution performs a recursive inorder traversal, keeping
 *           track of the previously visited node (`prev`).
 *           - When we find a node whose value is less than `prev`'s value, we
 *             have found a "dip" or violation.
 *           - **Case 1 (Adjacent Swap):** If `[1, 3, 2, 4]`, there's one dip
 *             (3 > 2). The first out-of-place node is `3` (`prev`), and the
 *             second is `2` (`root`).
 *           - **Case 2 (Non-adjacent Swap):** If `[1, 5, 3, 4, 2, 6]`, there
 *             are two dips. The first dip (5 > 3) identifies `5` as the first
 *             node and `3` as the potential second. The second dip (4 > 2)
 *             correctly updates the second node to be `2`.
 *
 *           We use three pointers: `first`, `second`, and `prev`. After the
 *           traversal, `first` and `second` will hold the two swapped nodes,
 *           and we can swap their values to recover the tree.
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

void recoverTree(TreeNode* root);
void fixTree(TreeNode* root, TreeNode*& first, TreeNode*& second,
             TreeNode*& prev);

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

    cout << "Inorder before recovery: ";
    printInorder(root);
    cout << endl;

    recoverTree(root);

    cout << "Inorder after recovery:  ";
    printInorder(root);
    cout << endl;
  }

  return 0;
}

void recoverTree(TreeNode* root) {
  TreeNode* first = NULL;
  TreeNode* second = NULL;
  TreeNode* prev = NULL;
  fixTree(root, first, second, prev);

  swap(first->val, second->val);
}

void fixTree(TreeNode* root, TreeNode*& first, TreeNode*& second,
             TreeNode*& prev) {
  if (root == NULL) return;

  fixTree(root->left, first, second, prev);

  if (prev != NULL && root->val <= prev->val) {  // Found a dip!
    if (first == NULL) {
      // This is the FIRST dip.
      first = prev;   // The first out-of-place node is the larger one.
      second = root;  // The second one is the smaller one (for now).
    } else {
      // This is the SECOND dip.
      second = root;  // The true second node is the smaller one here.
    }
  }
  prev = root;  // Update prev for the next node.

  fixTree(root->right, first, second, prev);
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
