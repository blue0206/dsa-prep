/*
 * Problem: All Nodes Distance K in Binary Tree (LeetCode #863)
 * Link:
 * https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/description/
 *
 * Approach: This solution uses a two-pass approach. First, it converts the
 *           tree into a graph-like structure by finding the parent of each
 *           node. Then, it performs a Depth-First Search (DFS) from the target
 *           node to find all nodes at distance K.
 *
 *           1.  **Build Parent Pointers:** A BFS traversal is used to iterate
 *               through the tree and populate a hash map (`mp`) where the key
 *               is a child node and the value is its parent node. This allows
 *               for upward traversal.
 *           2.  **DFS from Target:** A recursive DFS function (`traverse`) is
 *               called starting from the `target` node. This function explores
 *               in three directions: left, right, and up (parent). A `visited`
 *               set is used to prevent cycles. The recursion stops when the
 *               distance from the target reaches `k`, and the node's value is
 *               added to the result.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
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

vector<int> distanceK(TreeNode* root, TreeNode* target, int k);
void traverse(TreeNode* root, unordered_set<TreeNode*>& visited,
              unordered_map<TreeNode*, TreeNode*>& mp, vector<int>& ans, int k,
              int distance);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    // Example: Find nodes at distance 2 from node 5 in tree
    // [3,5,1,6,2,0,8,null,null,7,4] This requires a way to get a pointer to the
    // target node. For simplicity, we'll assume the target is root->left.
    if (root && root->left) {
      TreeNode* target = root->left;
      int k = 2;
      vector<int> result = distanceK(root, target, k);
      cout << "Nodes at distance " << k << " from " << target->val << ": ";
      for (int val : result) cout << val << " ";
      cout << endl;
    }
  }

  return 0;
}

vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
  if (root == NULL) return {};

  queue<TreeNode*> q;
  q.push(root);

  unordered_map<TreeNode*, TreeNode*> mp;
  while (!q.empty()) {
    int size = q.size();

    for (int i = 0; i < size; i++) {
      TreeNode* node = q.front();
      q.pop();

      if (node->left != NULL) {
        mp[node->left] = node;
        q.push(node->left);
      }
      if (node->right != NULL) {
        mp[node->right] = node;
        q.push(node->right);
      }
    }
  }

  vector<int> ans;
  unordered_set<TreeNode*> visited;
  traverse(target, visited, mp, ans, k, 0);

  return ans;
}

void traverse(TreeNode* root, unordered_set<TreeNode*>& visited,
              unordered_map<TreeNode*, TreeNode*>& mp, vector<int>& ans, int k,
              int distance) {
  if (root == NULL || distance > k || visited.find(root) != visited.end())
    return;
  if (distance == k) {
    ans.emplace_back(root->val);
    return;
  }

  visited.insert(root);
  // Check up.
  if (mp.find(root) != mp.end()) {
    traverse(mp[root], visited, mp, ans, k, distance + 1);
  }
  // Check left.
  traverse(root->left, visited, mp, ans, k, distance + 1);
  // Check right.
  traverse(root->right, visited, mp, ans, k, distance + 1);
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
