/*
 * Problem: Floor In BST
 * Link: https://www.geeksforgeeks.org/problems/floor-in-bst/0
 *
 * Approach: To find the floor of a value `x` in a BST, we need to find the
 *           largest value in the tree that is less than or equal to `x`.
 *           This iterative solution leverages the BST properties:
 *           - Start at the root.
 *           - If the current node's value is equal to `x`, we've found the
 *             exact value, which is the floor. Return it.
 *           - If the current node's value is less than `x`, it's a potential
 *             candidate for the floor. We store its value and move right to
 *             search for a potentially larger value that still meets the
 *             condition.
 *           - If the current node's value is greater than `x`, we must move
 *             left to find a smaller value.
 *
 * Time Complexity: O(H), where H is the height of the tree.
 * Space Complexity: O(1)
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

int floor(const TreeNode* root, int x);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    int x;
    cin >> x;
    cin.ignore();  // Consume the newline after reading the integer

    cout << "Floor(" << x << "): " << floor(root, x) << endl;
  }

  return 0;
}

int floor(const TreeNode* root, int x) {
  const TreeNode* iter = root;
  int ans = -1;

  while (iter != NULL) {
    if (x == iter->val) {
      return x;
    } else if (x > iter->val) {
      ans = iter->val;
      iter = iter->right;
    } else {
      iter = iter->left;
    }
  }

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
