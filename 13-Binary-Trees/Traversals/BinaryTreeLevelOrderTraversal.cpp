/*
 * Problem: Binary Tree Level Order Traversal (LeetCode #102)
 * Link:
 * https://leetcode.com/problems/binary-tree-level-order-traversal/description/
 *
 * Approach: This problem is solved using Breadth-First Search (BFS), which is
 *           perfect for level-by-level traversal. A queue is used to keep
 *           track of nodes to visit.
 *           1.  Initialize a queue and add the root node to it.
 *           2.  Loop as long as the queue is not empty.
 *           3.  In each iteration of the loop, which corresponds to one level,
 *               first get the number of nodes currently in the queue (`size`).
 *           4.  Create a new vector to store the values for the current level.
 *           5.  Loop `size` times: dequeue a node, add its value to the level
 *               vector, and enqueue its left and right children if they exist.
 *           6.  After the inner loop finishes, add the level vector to the
 *               final result.
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

vector<vector<int>> levelOrder(TreeNode* root);

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

    vector<vector<int>> result = levelOrder(root);
    cout << "Level Order: [ ";
    for (auto level : result) {
      cout << "[ ";
      for (auto i : level) {
        cout << i << " ";
      }
      cout << "] ";
    }
    cout << "] " << endl;

    cout << endl;
  }

  return 0;
}

vector<vector<int>> levelOrder(TreeNode* root) {
  vector<vector<int>> tree;
  if (root == NULL) return tree;

  queue<TreeNode*> q;
  q.push(root);

  while (!q.empty()) {
    int size = q.size();
    vector<int> level;

    for (int i = 0; i < size; i++) {
      const TreeNode* node = q.front();
      q.pop();

      level.emplace_back(node->val);

      if (node->left != NULL) q.push(node->left);
      if (node->right != NULL) q.push(node->right);
    }
    tree.emplace_back(level);
  }

  return tree;
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
