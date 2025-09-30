/*
 * Problem: Amount of Time for Binary Tree to Be Infected (LeetCode #2385)
 * Link:
 * https://leetcode.com/problems/amount-of-time-for-binary-tree-to-be-infected/description/
 *
 * Approach: The problem asks for the time to infect the whole tree, which is
 *           equivalent to finding the maximum distance from the `start` node
 *           to any other node in the tree. This can be solved by treating the
 *           tree as an undirected graph and finding the longest path from the
 *           start node.
 *
 *           1.  **Build Parent Pointers & Find Target:** First, traverse the
 *               tree (using BFS) to create a map of child-to-parent pointers.
 *               This allows us to traverse upwards. During this traversal, we
 *               also find the pointer to the `start` node.
 *           2.  **BFS from Target:** Start a second BFS from the `target` node.
 *               This BFS will explore in three directions: left, right, and up
 *               (parent). We use a `visited` set to avoid cycles and keep
 *               track of the distance at each step. The maximum distance found
 *               is the time required to infect the entire tree.
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

int infectionTime(const TreeNode* target,
                  unordered_map<const TreeNode*, const TreeNode*>& mp);
int amountOfTime(TreeNode* root, int start);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    int start;
    cin >> start;
    cin.ignore();  // Consume the newline after reading the integer

    TreeNode* root = buildTree(line);

    cout << "Minimum Time to Infect Entire Tree: " << amountOfTime(root, start)
         << endl;
  }

  return 0;
}

int amountOfTime(TreeNode* root, int start) {
  if (root == NULL) return 0;

  queue<TreeNode*> q;
  q.push(root);

  unordered_map<const TreeNode*, const TreeNode*> mp;
  TreeNode* target = NULL;

  // 1. Build parent map and find the target node
  while (!q.empty()) {
    TreeNode* node = q.front();
    q.pop();

    if (node->val == start) target = node;

    if (node->left != NULL) {
      mp[node->left] = node;
      q.push(node->left);
    }
    if (node->right != NULL) {
      mp[node->right] = node;
      q.push(node->right);
    }
  }

  return infectionTime(target, mp);
}

int infectionTime(const TreeNode* target,
                  unordered_map<const TreeNode*, const TreeNode*>& mp) {
  queue<pair<const TreeNode*, int>> infect;
  infect.push({target, 0});

  int maxDistance = 0;
  unordered_set<const TreeNode*> visited;
  visited.insert(target);

  // 2. BFS from the target to find the max distance
  while (!infect.empty()) {
    auto [node, distance] = infect.front();
    infect.pop();

    maxDistance = max(maxDistance, distance);

    // Explore neighbors: parent, left, and right
    if (mp.count(node) && !visited.count(mp.at(node))) {
      infect.push({mp[node], distance + 1});
      visited.insert(mp.at(node));
    }
    if (node->left != NULL && !visited.count(node->left)) {
      infect.push({node->left, distance + 1});
      visited.insert(node->left);
    }
    if (node->right != NULL && !visited.count(node->right)) {
      infect.push({node->right, distance + 1});
      visited.insert(node->right);
    }
  }

  return maxDistance;
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
