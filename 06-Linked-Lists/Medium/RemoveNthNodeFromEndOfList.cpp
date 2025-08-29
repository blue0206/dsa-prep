/*
 * Problem: Remove Nth Node From End of List (LeetCode #19)
 * Link:
 * https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/
 *
 * Approach: This problem is solved efficiently using a two-pointer approach
 *           with a dummy head node.
 *           1. A `dummy` node is created and linked to the head. This
 *              simplifies edge cases, such as removing the first node of the
 *              list.
 *           2. Two pointers, `slow` and `fast`, are initialized to the `dummy`
 *              node.
 *           3. The `fast` pointer is advanced `n` steps ahead.
 *           4. Then, both `slow` and `fast` pointers are moved one step at a
 *              time until `fast` reaches the last node of the list.
 *           5. At this point, the `slow` pointer will be at the node just
 *              before the one to be deleted. We can then bypass and delete the
 *              target node.
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

ListNode* removeNthFromEnd(ListNode* head, int n);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;

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

    head = removeNthFromEnd(head, k);

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

ListNode* removeNthFromEnd(ListNode* head, int n) {
  ListNode* dummy = new ListNode(0);
  dummy->next = head;

  ListNode* slow = dummy;
  ListNode* fast = dummy;
  for (int i = 1; i <= n; i++) {
    fast = fast->next;
  }

  while (fast->next != NULL) {
    slow = slow->next;
    fast = fast->next;
  }

  ListNode* nodeToDelete = slow->next;
  slow->next = nodeToDelete->next;
  ListNode* newHead = dummy->next;

  delete nodeToDelete;
  delete dummy;
  return newHead;
}
