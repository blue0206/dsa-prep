/*
 * Problem: Children Sum Property
 * Link:
 * https://www.naukri.com/code360/problems/childrensumproperty_790723?leftPanelTabValue=PROBLEM
 *
 * Approach: This solution uses a two-pass recursive approach to modify the
 *           tree. The goal is to make every node's value equal to the sum of
 *           its children's values, by only incrementing values.
 *
 *           1.  **First Pass (Top-Down):** Before the recursive calls for the
 *               left and right children, the function ensures that the sum of
 *               the immediate children is at least as large as the parent. If
 *               not, it increases one of the children's values to satisfy this.
 *               This propagates larger values from the top of the tree
 *               downwards.
 *           2.  **Second Pass (Bottom-Up):** After the recursive calls return,
 *               the children's subtrees are already compliant. The function
 *               then updates the parent's value to be the exact sum of its now
 *               updated children. This ensures the property holds as the
 *               recursion unwinds.
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

void changeTree(TreeNode* root);
void updateSum(TreeNode* root, TreeNode* left, TreeNode* right);

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

    changeTree(root);

    cout << "Inorder of modified tree: ";
    printInorder(root);
    cout << endl;
  }

  return 0;
}

void changeTree(TreeNode* root) {
  if (root == NULL) return;
  if (root->left == NULL && root->right == NULL) return;

  updateSum(root, root->left, root->right);

  changeTree(root->left);
  changeTree(root->right);

  updateSum(root, root->left, root->right);
}

void updateSum(TreeNode* root, TreeNode* left, TreeNode* right) {
  int leftVal = (left == NULL) ? 0 : left->val;
  int rightVal = (right == NULL) ? 0 : right->val;

  long long sum = (long long)leftVal + rightVal;

  if (sum < root->val) {
    if (left != NULL) {
      left->val = root->val;
    } else if (right != NULL) {
      right->val += root->val - sum;
    }
  } else if (sum > root->val) {
    root->val = sum;
  }
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

void printInorder(TreeNode* root) {
  if (root == NULL) return;
  printInorder(root->left);
  cout << root->val << " ";
  printInorder(root->right);
}
