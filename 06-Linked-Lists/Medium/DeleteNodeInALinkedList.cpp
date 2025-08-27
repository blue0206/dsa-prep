/*
 * Problem: Delete Node in a Linked List (LeetCode #237)
 * Link: https://leetcode.com/problems/delete-node-in-a-linked-list/description/
 *
 * Approach: Since we do not have access to the head of the list or the node
 *           before the one to be deleted, we cannot perform a standard
 *           deletion. The trick is to realize that we don't need to delete the
 *           given `node` itself. Instead, we can copy the data from the next
 *           node into the current node and then delete the next node. This
 *           effectively removes the value from the list.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

struct ListNode {
 public:
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

void deleteNode(ListNode* node);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;

    ListNode* head = new ListNode(0);
    ListNode* temp = head;
    ListNode* node = NULL;
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      temp->next = new ListNode(x);
      temp = temp->next;
      if (temp->val == k) {
        node = temp;
      }
    }
    head = head->next;

    cout << "Linked List: [ ";
    temp = head;
    while (temp != NULL) {
      cout << temp->val << " ";
      temp = temp->next;
    }
    cout << "]" << endl;

    deleteNode(node);

    cout << "Updated Linked List: [ ";
    temp = head;
    while (temp != NULL) {
      cout << temp->val << " ";
      temp = temp->next;
    }
    cout << "]" << endl;

    // Clean up.
    temp = head;
    while (temp != NULL) {
      ListNode* toDelete = temp;
      temp = temp->next;
      delete toDelete;
    }
  }

  return 0;
}

void deleteNode(ListNode* node) {
  ListNode* temp = node->next;
  node->val = temp->val;
  node->next = temp->next;
  delete temp;
}
