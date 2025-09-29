/*
 * Problem: Binary Tree Zigzag Level Order Traversal (LeetCode #103)
 * Link:
 * https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/description/
 *
 * Approach: This solution is a modification of the standard level-order
 *           traversal (BFS). It uses a queue to process nodes level by level.
 *           The "zigzag" effect is achieved by using a boolean flag
 *           `reverseOrder` that toggles after each level.
 *
 *           Instead of reversing the level vector after populating it, this
 *           approach cleverly calculates the correct insertion index directly.
 *           - For left-to-right levels, the index is `i`.
 *           - For right-to-left levels, the index is `size - 1 - i`.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(W), where W is the maximum width of the tree.
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

vector<vector<int>> zigzagLevelOrder(TreeNode* root);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    vector<vector<int>> result = zigzagLevelOrder(root);

    cout << "Zigzag Level Order: [ ";
    for (auto level : result) {
      cout << "[ ";
      for (auto i : level) {
        cout << i << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;
  }

  return 0;
}

vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
  if (root == NULL) return {};

  vector<vector<int>> ans;
  queue<TreeNode*> q;
  q.push(root);

  bool reverseOrder = false;
  while (!q.empty()) {
    int size = q.size();
    vector<int> level(size);

    for (int i = 0; i < size; i++) {
      const TreeNode* node = q.front();
      q.pop();

      // Calculate index based on the current level's direction.
      int index = (reverseOrder) ? (size - 1 - i) : i;
      level[index] = node->val;

      if (node->left != NULL) q.push(node->left);
      if (node->right != NULL) q.push(node->right);
    }

    ans.emplace_back(level);
    reverseOrder = !reverseOrder;
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
