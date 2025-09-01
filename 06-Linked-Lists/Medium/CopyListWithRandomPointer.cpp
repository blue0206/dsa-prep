/*
 * Problem: Copy List with Random Pointer (LeetCode #138)
 * Link:
 * https://leetcode.com/problems/copy-list-with-random-pointer/description/
 *
 * Approach: This is an elegant, in-place solution that avoids using extra space
 *           like a hash map. It works in three passes:
 *           1.  **Weaving Nodes**: Iterate through the original list. For each
 *               node, create its copy and insert it immediately after the
 *               original node. The list becomes `A -> A' -> B -> B' -> ...`.
 *           2.  **Copying Random Pointers**: Iterate through the woven list.
 *               For each original node `iter`, its copy's random pointer
 *               (`iter->next->random`) is set to the copy of the original's
 *               random pointer (`iter->random->next`).
 *           3.  **Unweaving Lists**: Separate the woven list back into two
 *               distinct lists: the original and the deep copy.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>

using namespace std;

struct Node {
 public:
  int val;
  Node* next;
  Node* random;
  Node(int x) : val(x), next(NULL), random(NULL) {}
};

Node* copyRandomList(Node* head);

// A main function is not provided, but would be necessary for testing.
int main() { return 0; }

Node* copyRandomList(Node* head) {
  if (head == NULL) return NULL;

  // 1. Create and weave the new nodes.
  Node* iter = head;
  while (iter != NULL) {
    Node* newNode = new Node(iter->val);
    newNode->next = iter->next;
    iter->next = newNode;
    iter = newNode->next;
  }

  // Store the head of new list.
  Node* newHead = head->next;

  // 2. Set the random pointers
  Node* newIter = newHead;
  iter = head;
  while (newIter != NULL && iter != NULL) {
    Node* randomNode = iter->random;
    newIter->random = (randomNode == NULL) ? NULL : randomNode->next;

    iter = newIter->next;
    newIter = (iter == NULL) ? NULL : iter->next;
  }

  // 3. Set next pointer of both list to their correct place.
  iter = head;
  newIter = newHead;
  while (iter != NULL && newIter != NULL) {
    iter->next = newIter->next;
    iter = iter->next;
    newIter->next = (iter == NULL) ? NULL : iter->next;
    newIter = newIter->next;
  }

  return newHead;
}
