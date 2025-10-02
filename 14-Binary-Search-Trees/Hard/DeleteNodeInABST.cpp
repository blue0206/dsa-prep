/*
 * Problem: Delete Node in a BST (LeetCode #450)
 * Link: https://leetcode.com/problems/delete-node-in-a-bst/description/
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

/**
 * Approach: This iterative solution first finds the target node and its parent.
 *           It then handles deletion based on three cases:
 *           1.  **Node not found:** The tree is returned unchanged.
 *           2.  **Node has 0 or 1 child:** The target node is bypassed by
 *               linking its parent directly to its single child (or NULL). If
 *               the target is the root, the child becomes the new root.
 *           3.  **Node has 2 children:** The inorder predecessor (the rightmost
 *               node in the left subtree) is found. The target's right subtree
 *               is attached to the predecessor's right. Then, the target's
 *               parent is linked to the target's left child. This effectively
 *               replaces the target with its left subtree, with the right
 *               subtree correctly re-attached.
 *
 * Time Complexity: O(H), where H is the height of the tree.
 * Space Complexity: O(1)
 */
TreeNode* iterativeApproach(TreeNode* root, int key);

/**
 * Approach: This recursive solution finds the node to delete by traversing the
 *           tree. Once the node is found, it handles the deletion:
 *           1.  **Base Case:** If `root` is `NULL`, we've reached the end
 *               without finding the key, so we return `NULL`.
 *           2.  **Recursive Step:** Traverse left or right based on the key.
 *           3.  **Node Found:**
 *               - If the node has 0 or 1 child, it returns the existing child
 *                 (or NULL) to its parent, effectively deleting the current
 *                 node.
 *               - If the node has 2 children, it finds the inorder predecessor
 *                 (rightmost node of the left subtree), attaches the current
 *                 node's right subtree to it, and then promotes the left
 *                 subtree to replace the current node.
 *
 * Time Complexity: O(H), where H is the height of the tree.
 * Space Complexity: O(H) for the recursion call stack.
 */
TreeNode* recursiveApproach(TreeNode* root, int key);

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

    int val;
    cin >> val;
    cin.ignore();  // Consume the newline after reading the integer

    // Uncomment the approach to be used.
    TreeNode* newRoot = iterativeApproach(root, val);
    // TreeNode* newRoot = recursiveApproach(root, val);

    cout << "Inorder after deletion: ";
    printInorder(newRoot);
    cout << endl;
  }

  return 0;
}

//-----------------------------ITERATIVE APPROACH-------------------------------
TreeNode* iterativeApproach(TreeNode* root, int key) {
  TreeNode* target = root;
  TreeNode* parent = NULL;

  while (target != NULL && target->val != key) {
    parent = target;
    if (target->val > key) {
      target = target->left;
    } else {
      target = target->right;
    }
  }

  // Case 1: No Target.
  if (target == NULL) return root;

  TreeNode* nodeToDelete = target;
  TreeNode* leftChild = target->left;
  TreeNode* rightChild = target->right;
  // Case 2: 0 or 1 Child.
  if (leftChild == NULL || rightChild == NULL) {
    if (parent == NULL) {
      delete nodeToDelete;
      return (leftChild == NULL) ? rightChild : leftChild;
    }

    if (parent->val > key) {
      parent->left = (leftChild == NULL) ? rightChild : leftChild;
    } else {
      parent->right = (leftChild == NULL) ? rightChild : leftChild;
    }
    delete nodeToDelete;
    return root;
  }

  // Case 3: Both children present.
  // In this case, we simply find the in-order predecessor of target and link
  // its right with the target's right and link the parent's ptr with the
  // target's left and delete target. This maintains BST property and gets the
  // job done.
  TreeNode* pred = target->left;
  while (pred->right != NULL) {
    pred = pred->right;
  }

  pred->right = target->right;
  if (parent != NULL) {
    if (parent->val > key) {
      parent->left = target->left;
    } else {
      parent->right = target->left;
    }
  } else {
    root = target->left;
  }
  delete nodeToDelete;
  return root;
}

//------------------------------RECURSIVE APPROACH------------------------------
TreeNode* recursiveApproach(TreeNode* root, int key) {
  if (root == NULL) return root;

  if (root->val < key) {
    root->right = recursiveApproach(root->right, key);
  } else if (root->val > key) {
    root->left = recursiveApproach(root->left, key);
  } else {
    TreeNode* nodeToDelete = root;
    // Case 1 & 2: 0 or 1 child.
    if (root->left == NULL) {
      root = root->right;
    } else if (root->right == NULL) {
      root = root->left;
    } else {
      // Case 3: 2 children.
      // Find the inorder predecessor (rightmost node of the left subtree).
      TreeNode* pred = root->left;
      while (pred->right != NULL) {
        pred = pred->right;
      }
      // Attach the right subtree to the predecessor and promote the left
      // subtree.
      pred->right = root->right;
      root = root->left;
    }
    delete nodeToDelete;
  }

  return root;
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
void printInorder(TreeNode* root) {
  if (root == NULL) return;
  printInorder(root->left);
  cout << root->val << " ";
  printInorder(root->right);
}
