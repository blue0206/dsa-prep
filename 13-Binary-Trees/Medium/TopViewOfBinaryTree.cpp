/*
 * Problem: Top View Of Binary Tree
 * Link:
 * https://www.naukri.com/code360/problems/top-view-of-binary-tree_799401?leftPanelTabValue=PROBLEM
 *
 * Approach: This problem is solved using a level-order traversal (BFS). We need
 *           to find the first node visible from the top at each vertical line
 *           (or horizontal distance).
 *
 *           1.  Use a queue to store pairs of
 *               `(TreeNode*, horizontal_distance)`.
 *           2.  Use a map to store the first node's value encountered for each
 *               horizontal distance. The map's key is the distance, and the
 *               value is the node's value.
 *           3.  During the BFS, for each node, if its horizontal distance is
 *               not already in the map, it means this is the first
 *               (and thus highest) node we've seen at this distance, so we add
 *               it to the map.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
#include <algorithm>
#include <iostream>
#include <map>
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

vector<int> getTopView(TreeNode* root);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    vector<int> ans = getTopView(root);

    cout << "Top View of Binary Tree: [ ";
    for (int i : ans) {
      cout << i << " ";
    }
    cout << "]" << endl;
  }

  return 0;
}

vector<int> getTopView(TreeNode* root) {
  if (root == NULL) return {};

  map<int, int> mp;
  queue<pair<TreeNode*, int>> q;
  q.push({root, 0});

  while (!q.empty()) {
    int size = q.size();

    for (int i = 0; i < size; i++) {
      auto [node, col] = q.front();
      q.pop();

      if (mp.find(col) == mp.end()) {
        mp[col] = node->val;
      }

      if (node->left != NULL) q.push({node->left, col - 1});
      if (node->right != NULL) q.push({node->right, col + 1});
    }
  }

  vector<int> ans;
  for (auto it : mp) {
    ans.emplace_back(it.second);
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
