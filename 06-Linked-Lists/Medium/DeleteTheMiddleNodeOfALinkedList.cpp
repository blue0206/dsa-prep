/*
 * Problem: Delete the Middle Node of a Linked List (LeetCode #2095)
 * Link:
 * https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/description/
 *
 * Approach: This problem is solved using a modified 'slow and fast pointer'
 *           algorithm to find the node just before the middle.
 *           1. Handle the edge case of a list with 0 or 1 nodes, where the
 *              result is an empty list (NULL).
 *           2. Initialize a `slow` pointer to `head` and a `fast` pointer to
 *              `head->next->next`.
 *           3. Move `slow` one step and `fast` two steps at a time. This
 *              specific initialization ensures that when `fast` reaches the
 *              end, `slow` will be pointing to the node right before the
 *              middle node.
 *           4. Bypass and delete the middle node (`slow->next`).
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>

using namespace std;

struct ListNode {
 public:
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

ListNode* deleteMiddle(ListNode* head);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    ListNode* head = new ListNode(0);
    ListNode* temp = head;
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      temp->next = new ListNode(x);
      temp = temp->next;
    }
    head = head->next;

    cout << "Linked List: [ ";
    temp = head;
    while (temp != NULL) {
      cout << temp->val << " ";
      temp = temp->next;
    }
    cout << "]" << endl;

    head = deleteMiddle(head);

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
    cout << endl;
  }

  return 0;
}

ListNode* deleteMiddle(ListNode* head) {
  if (head == NULL || head->next == NULL) return NULL;

  ListNode* slow = head;
  ListNode* fast = head->next->next;
  while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
  }

  ListNode* nodeToDelete = slow->next;
  slow->next = nodeToDelete->next;
  delete nodeToDelete;
  return head;
}
