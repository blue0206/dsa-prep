/*
 * Problem: Vertical Order Traversal of a Binary Tree (LeetCode #987)
 * Link:
 * https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/description/
 */

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;
using pii = pair<int, int>;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

/**
 * Approach: This solution uses Breadth-First Search (BFS) to traverse the
 *           tree. A queue stores pairs of `(TreeNode*, col)`. A map is
 *           used to group nodes by their vertical column. The map's key is the
 *           column, and the value is a vector of `(row, value)` pairs.
 *           After the BFS traversal, we iterate through the map. For each
 *           column, we sort the corresponding vector. The default pair sorting
 *           in C++ correctly handles the problem's requirements: sort by row,
 *           then by value for ties.
 *
 * Time Complexity: O(N * log N) due to sorting.
 * Space Complexity: O(N) for the map and queue.
 */
vector<vector<int>> bfsApproach(TreeNode* root);

/**
 * Approach: This solution uses a Depth-First Search (DFS) traversal (preorder)
 *           to visit every node. A recursive helper function passes the
 *           current `row` and `col` for each node. A map is used to group
 *           nodes by their vertical column, storing `(row, value)` pairs.
 *           After the DFS traversal, the process is the same as the BFS
 *           approach: iterate through the map, sort each column's vector, and
 *           construct the final result.
 *
 * Time Complexity: O(N * log N) due to sorting.
 * Space Complexity: O(N) for the map and recursion stack.
 */
vector<vector<int>> dfsApproach(TreeNode* root);
void traverse(TreeNode* root, map<int, vector<pii>>& mp, int row, int col);

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

    vector<vector<int>> dfsResult = dfsApproach(root);
    vector<vector<int>> bfsResult = bfsApproach(root);

    cout << "DFS Traversal: [ ";
    for (auto level : dfsResult) {
      cout << "[ ";
      for (auto i : level) {
        cout << i << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "BFS Traversal: [ ";
    for (auto level : bfsResult) {
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

//------------------------------DFS APPROACH------------------------------------
vector<vector<int>> dfsApproach(TreeNode* root) {
  vector<vector<int>> ans;
  map<int, vector<pii>> mp;

  traverse(root, mp, 0, 0);

  for (auto it : mp) {
    ans.push_back({});
    int index = ans.size() - 1;

    vector<pii> temp = it.second;
    sort(temp.begin(), temp.end());
    for (int i = 0; i < temp.size(); i++) {
      ans[index].emplace_back(temp[i].second);
    }
  }

  return ans;
}

void traverse(TreeNode* root, map<int, vector<pii>>& mp, int row, int col) {
  if (root == NULL) return;

  mp[col].push_back({row, root->val});

  traverse(root->left, mp, row + 1, col - 1);
  traverse(root->right, mp, row + 1, col + 1);
}

//------------------------------BFS APPROACH------------------------------------
vector<vector<int>> bfsApproach(TreeNode* root) {
  if (root == NULL) return {};

  queue<pair<TreeNode*, int>> q;
  q.push({root, 0});

  map<int, vector<pii>> mp;
  int row = 0;

  while (!q.empty()) {
    int size = q.size();

    for (int i = 0; i < size; i++) {
      auto [node, col] = q.front();
      q.pop();
      mp[col].push_back({row, node->val});

      if (node->left != NULL) q.push({node->left, col - 1});
      if (node->right != NULL) q.push({node->right, col + 1});
    }
    row++;
  }

  vector<vector<int>> ans(mp.size());
  int index = 0;
  for (auto it : mp) {
    vector<pii> temp = it.second;
    sort(temp.begin(), temp.end());

    for (int i = 0; i < temp.size(); i++) {
      ans[index].emplace_back(temp[i].second);
    }
    index++;
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
