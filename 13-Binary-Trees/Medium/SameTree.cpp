/*
 * Problem: Same Tree (LeetCode #100)
 * Link: https://leetcode.com/problems/same-tree/description/
 *
 * Approach: This problem can be solved with a simple recursive Depth-First
 *           Search (DFS). We compare two trees, `p` and `q`, from the root
 *           down. For any given pair of nodes:
 *           1.  **Base Cases:**
 *               - If both nodes are `NULL`, they are the same. Return `true`.
 *               - If one node is `NULL` or their values are different, they are
 *                 not the same. Return `false`.
 *           2.  **Recursive Step:** If the base cases don't apply, the current
 *               nodes are a match. We then recursively check if the left
 *               subtrees are the same AND the right subtrees are the same.
 *
 * Time Complexity: O(N), where N is the number of nodes in the smaller tree.
 * Space Complexity: O(H), where H is the height of the smaller tree.
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

bool isSameTree(const TreeNode* p, const TreeNode* q);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);
    cin.ignore();

    string line2;
    getline(cin, line2);

    TreeNode* root2 = buildTree(line2);

    cout << "Result: " << (isSameTree(root, root2) ? "True" : "False") << endl;
  }

  return 0;
}

bool isSameTree(TreeNode* p, TreeNode* q) {
  if (p == NULL || q == NULL) return p == q;

  bool left = isSameTree(p->left, q->left);
  bool right = isSameTree(p->right, q->right);

  return (p->val == q->val && left && right);
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
