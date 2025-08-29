/*
 * Problem: Odd Even Linked List (LeetCode #328)
 * Link: https://leetcode.com/problems/odd-even-linked-list/description/
 *
 * Approach: This is an in-place algorithm that uses two pointers to separate
 *           the list into odd and even indexed nodes.
 *           1. Initialize an `odd` pointer to `head` and an `even` pointer to
 *              `head->next`. Also, store the head of the even list in
 *              `evenHead`.
 *           2. Iterate through the list. In each step, the `odd` node's `next`
 *              is set to skip the following `even` node, and the `even` node's
 *              `next` is set to skip the following `odd` node.
 *           3. After the loop, the tail of the odd list (`odd`) is connected to
 *              the head of the even list (`evenHead`).
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

ListNode* oddEvenList(ListNode* head);

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

    head = oddEvenList(head);

    cout << "Odd Even Linked List: [ ";
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

ListNode* oddEvenList(ListNode* head) {
  if (head == NULL) return head;

  ListNode* odd = head;
  ListNode* even = head->next;
  ListNode* evenHead = even;

  while (even != NULL && even->next != NULL) {
    odd->next = even->next;
    odd = odd->next;

    even->next = odd->next;
    even = even->next;
  }

  odd->next = evenHead;
  return head;
}
