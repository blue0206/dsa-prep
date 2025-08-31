/*
 * Problem: Remove Linked List Elements (LeetCode #203)
 * Link: https://leetcode.com/problems/remove-linked-list-elements/description/
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
 * Approach: This approach uses a `dummy` head node to simplify edge cases,
 *           particularly when the head of the list itself needs to be removed.
 *           1. A `dummy` node is created and its `next` points to the original
 *              `head`.
 *           2. Two pointers, `prev` and `curr`, are used to traverse the list,
 *              starting at `dummy` and `head` respectively.
 *           3. When a node with the target value is found (`curr->val == val`),
 *              it is removed by linking `prev` to `curr->next`. The `curr`
 *              pointer is advanced, and the old node is deleted.
 *           4. If the current node's value does not match, both `prev` and
 *              `curr` are simply advanced one step.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
ListNode* iterativeApproach(ListNode* head, int val);

/**
 * Approach: This approach uses post-order recursion. The function calls itself
 *           on the rest of the list (`head->next`) first.
 *           1. The base case is an empty list, which returns `NULL`.
 *           2. The recursive call on `head->next` returns the correct head of
 *              the rest of the list (after potential deletions), which we link
 *              to `head->next`.
 *           3. After the recursive call returns, we check the current `head`.
 *              If its value matches the target, we delete it and return its
 *              `next` pointer up the call stack. Otherwise, we return `head`.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N) due to recursion call stack
 */
ListNode* recursiveApproach(ListNode* head, int val);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, val;
    cin >> n >> val;

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

    // Uncomment the approach to be used.
    head = iterativeApproach(head, val);
    // head = recursiveApproach(head, val);

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

//---------------------------ITERATIVE APPROACH---------------------------------
ListNode* iterativeApproach(ListNode* head, int val) {
  if (head == NULL) return NULL;

  ListNode* dummy = new ListNode(0);
  dummy->next = head;

  ListNode* prev = dummy;
  ListNode* curr = head;
  while (curr != NULL) {
    ListNode* nextNode = curr->next;
    if (curr->val == val) {
      ListNode* deleteNode = curr;
      curr = nextNode;
      prev->next = nextNode;
      delete deleteNode;
    } else {
      prev = curr;
      curr = nextNode;
    }
  }

  ListNode* newHead = dummy->next;
  delete dummy;
  return newHead;
}

//------------------------------RECURSIVE APPROACH------------------------------
ListNode* recursiveApproach(ListNode* head, int val) {
  if (head == NULL) return NULL;

  head->next = recursiveApproach(head->next, val);

  if (head->val == val) {
    ListNode* nodeToDelete = head;
    ListNode* newHead = head->next;
    delete nodeToDelete;
    return newHead;
  }

  return head;
}
