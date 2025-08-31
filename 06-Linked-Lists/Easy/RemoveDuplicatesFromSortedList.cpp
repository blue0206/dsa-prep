/*
 * Problem: Remove Duplicates from Sorted List (LeetCode #83)
 * Link:
 * https://leetcode.com/problems/remove-duplicates-from-sorted-list/description/
 *
 * Approach: This approach uses a single pointer, `curr`, to iterate through the
 *           sorted list. Since the list is sorted, all duplicate nodes will be
 *           adjacent.
 *           1. Initialize a `curr` pointer to the `head` of the list.
 *           2. Traverse the list as long as `curr` is not `NULL`.
 *           3. At each node, check if `curr->next` exists and has the same
 *              value as `curr`.
 *           4. If it's a duplicate, we bypass `curr->next` by pointing
 *              `curr->next` to `curr->next->next` and then delete the old
 *              `curr->next`. The `curr` pointer is not advanced, to handle
 *              sequences of more than two duplicates.
 *           5. If it's not a duplicate, we simply advance `curr` to the next
 *              node.
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

ListNode* deleteDuplicates(ListNode* head);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    ListNode* dummy = new ListNode(0);
    ListNode* temp = dummy;
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      temp->next = new ListNode(x);
      temp = temp->next;
    }
    ListNode* head = dummy->next;
    delete dummy;

    cout << "Linked List: [ ";
    temp = head;
    while (temp != NULL) {
      cout << temp->val << " ";
      temp = temp->next;
    }
    cout << "]" << endl;

    head = deleteDuplicates(head);

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

ListNode* deleteDuplicates(ListNode* head) {
  ListNode* curr = head;
  while (curr != NULL) {
    if (curr->next && curr->next->val == curr->val) {
      ListNode* nodeToDelete = curr->next;
      curr->next = curr->next->next;
      delete nodeToDelete;
    } else {
      curr = curr->next;
    }
  }

  return head;
}
