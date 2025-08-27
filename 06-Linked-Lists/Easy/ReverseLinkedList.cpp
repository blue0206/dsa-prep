/*
 * Problem: Reverse Linked List (LeetCode #206)
 * Link: https://leetcode.com/problems/reverse-linked-list/description/
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

/**
 * Approach: This method uses three pointers: `prev`, `curr`, and `nextNode`.
 *           - `prev` points to the previous node (initially NULL).
 *           - `curr` points to the current node (initially head).
 *           - `nextNode` temporarily stores the next node before we change
 *             the pointer.
 *           The list is traversed, and at each node, `curr->next` is pointed
 *           to `prev`. Then, all pointers are moved one step forward.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
ListNode* iterativeApproach(ListNode* head);

/**
 * Approach: This method uses the call stack to reverse the list.
 *           The base case is an empty list or a single-node list.
 *           Otherwise, we recursively call the function on the rest of the
 *           list (`head->next`). When the recursion returns, we have the head
 *           of the reversed "tail". We then make the original next node point
 *           back to the current head and set the current head's next to NULL.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N) due to the recursion call stack.
 */
ListNode* recursiveApproach(ListNode* head);

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

    ListNode* iterativeResult = iterativeApproach(head);

    cout << "Reversed Linked List: [ ";
    temp = iterativeResult;
    while (temp != NULL) {
      cout << temp->val << " ";
      temp = temp->next;
    }
    cout << "]" << endl;

    // Uncomment to use recursive approach.
    // ListNode* recursiveResult = recursiveApproach(head);

    // cout << "Reversed Linked List: [ ";
    // temp = recursiveResult;
    // while (temp != NULL) {
    //   cout << temp->val << " ";
    //   temp = temp->next;
    // }
    // cout << "]" << endl;

    // Clean up the reversed list to prevent memory leaks.
    temp = iterativeResult;  // Change to `recursiveResult` when using recursion
    while (temp != NULL) {
      ListNode* toDelete = temp;
      temp = temp->next;
      delete toDelete;
    }
  }

  return 0;
}

ListNode* iterativeApproach(ListNode* head) {
  ListNode* prev = NULL;
  ListNode* curr = head;

  while (curr != NULL) {
    ListNode* nextNode = curr->next;
    curr->next = prev;
    prev = curr;
    curr = nextNode;
  }

  return prev;
}

ListNode* recursiveApproach(ListNode* head) {
  if (head == NULL || head->next == NULL) {
    return head;
  }

  // 1. Recursively reverse the rest of the list.
  // For a list 1 -> 2 -> 3 -> 4, this call will return the node 4,
  // which is the head of the reversed list 4 -> 3 -> 2.
  ListNode* newHead = recursiveApproach(head->next);

  // 2. Now, `head` is node 1. `head->next` is node 2.
  // The reversed list looks like: 4 -> 3 -> 2.
  // Node 2's `next` pointer still points to NULL.
  // We need to make node 2 point back to node 1.
  head->next->next = head;

  // 3. Node 1 is now the last node in the reversed list.
  // Its `next` must point to NULL.
  head->next = NULL;

  // 4. `newHead` (node 4) is still the head of the fully reversed list.
  // We return it all the way up the call stack.
  return newHead;
}
