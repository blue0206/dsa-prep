/*
 * Problem: Binary Tree Postorder Traversal (LeetCode #145)
 * Link:
 * https://leetcode.com/problems/binary-tree-postorder-traversal/description/
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
 * Approach: Perform the same operations as the stack-based approach of Preorder
 *           traversal but instead of storing right first, store left first,
 *           i.e., process right before left as right will now be at top. This
 *           traversal is effectively NRL. If you take the output of this
 *           traversal and reverse it, you get the correct LRN post-order
 *           traversal!
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N) for the two stacks.
 */
vector<int> twoStacksApproach(const TreeNode* root);

/**
 * Approach: This approach uses a single stack and is more complex. It keeps
 *           track of the last visited node to decide when to process a parent.
 *           1. Go as far left as possible, pushing nodes onto the stack.
 *           2. When at a null node, peek at the stack's top.
 *           3. If the top node has a right child that has not been visited yet,
 *              move to that right child and repeat step 1.
 *           4. Otherwise, it's time to process the node at the top of the
 *              stack. Pop it, add its value to the result, and mark it as the
 *              last visited node.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(H), where H is the height of the tree.
 */
vector<int> singleStackApproach(const TreeNode* root);

/**
 * Approach: This is the classic recursive solution that directly follows the
 *           definition of postorder traversal (Left -> Right -> Root).
 *           1. If the current node is null, return.
 *           2. Make a recursive call on the left child.
 *           3. Make a recursive call on the right child.
 *           4. Process the current node's value.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(H) for the recursion call stack.
 */
vector<int> recursiveApproach(const TreeNode* root);
void traverse(const TreeNode* root, vector<int>& tree);

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

    vector<int> twoStackResult = twoStacksApproach(root);
    cout << "Iterative Postorder (2 Stacks): ";
    printTree(twoStackResult);

    vector<int> singleStackResult = singleStackApproach(root);
    cout << "Iterative Postorder (1 Stack): ";
    printTree(singleStackResult);

    vector<int> recursiveResult = recursiveApproach(root);
    cout << "Recursive Postorder: ";
    printTree(recursiveResult);

    cout << endl;
  }

  return 0;
}

//------------------------ITERATIVE APPROACH (2-Stacks)-------------------------
vector<int> twoStacksApproach(TreeNode* root) {
  vector<int> tree;
  stack<TreeNode*> st;
  stack<int> res;
  if (root != NULL) st.push(root);

  while (!st.empty()) {
    TreeNode* node = st.top();
    st.pop();

    res.push(node->val);
    if (node->left != NULL) st.push(node->left);
    if (node->right != NULL) st.push(node->right);
  }

  while (!res.empty()) {
    tree.emplace_back(res.top());
    res.pop();
  }

  return tree;
}

//------------------------ITERATIVE APPROACH (1-Stack)--------------------------
vector<int> singleStackApproach(const TreeNode* root) {
  vector<int> tree;
  stack<const TreeNode*> st;
  const TreeNode* current = root;
  const TreeNode* lastVisited = NULL;

  while (!st.empty() || current != NULL) {
    while (current != NULL) {
      st.push(current);
      current = current->left;
    }

    current = st.top();
    if (current->right != NULL && current->right != lastVisited) {
      current = current->right;
    } else {
      st.pop();
      tree.emplace_back(current->val);
      lastVisited = current;
      current = NULL;
    }
  }

  return tree;
}

//------------------------------RECURSIVE APPROACH------------------------------
vector<int> recursiveApproach(const TreeNode* root) {
  vector<int> tree;
  traverse(root, tree);

  return tree;
}

void traverse(const TreeNode* root, vector<int>& tree) {
  if (root == NULL) return;

  traverse(root->left, tree);
  traverse(root->right, tree);
  tree.emplace_back(root->val);
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
