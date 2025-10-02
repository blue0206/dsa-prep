/*
 * Problem: Two Sum IV - Input is a BST (LeetCode #653)
 * Link: https://leetcode.com/problems/two-sum-iv-input-is-a-bst/description/
 *
 * Approach: This solution uses a two-pointer approach on the BST, which is
 *           made possible by creating two BST iterators: one for a standard
 *           inorder traversal (smallest to largest) and one for a reverse
 *           inorder traversal (largest to smallest).
 *           1.  **BSTIterator Class:** An iterator class is defined to handle
 *               the traversal logic. It uses a stack to achieve O(H) space. A
 *               boolean flag controls whether it traverses forward (inorder)
 *               or backward (reverse inorder).
 *           2.  **Two Pointers:** In the main function, we initialize one
 *               forward iterator (`l`) and one backward iterator (`r`).
 *           3.  We get the smallest value `i` and the largest value `j`. We
 *               move the pointers inward based on their sum, just like in a
 *               sorted array, until they cross.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(H), where H is the height of the tree.
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
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

class BSTIterator {
 private:
  stack<TreeNode*> st;
  bool isReverse;  // false = next (inorder), true = before (reverse inorder)

  void pushAll(TreeNode* node) {
    while (node != NULL) {
      st.push(node);
      if (isReverse) {
        node = node->right;
      } else {
        node = node->left;
      }
    }
  }

 public:
  BSTIterator(TreeNode* root, bool reverse) {
    isReverse = reverse;
    pushAll(root);
  }

  int next() {
    TreeNode* node = st.top();
    st.pop();
    if (!isReverse) {
      pushAll(node->right);
    } else {
      pushAll(node->left);
    }
    return node->val;
  }
};

bool findTarget(TreeNode* root, int k);

TreeNode* buildTree(const string& str);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character

  while (t--) {
    string line;
    getline(cin, line);

    TreeNode* root = buildTree(line);

    int k;
    cin >> k;
    cin.ignore();  // Consume the newline after reading the integer

    cout << "Result: " << (findTarget(root, k) ? "True" : "False") << endl;
  }

  return 0;
}

bool findTarget(TreeNode* root, int k) {
  if (root == NULL) return false;

  BSTIterator l(root, false);  // Inorder (smallest to largest)
  BSTIterator r(root, true);   // Reverse Inorder (largest to smallest)

  int i = l.next();
  int j = r.next();
  while (i < j) {
    if (i + j == k) {
      return true;
    } else if (i + j < k) {
      i = l.next();
    } else {  // i + j > k
      j = r.next();
    }
  }
  return false;
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
