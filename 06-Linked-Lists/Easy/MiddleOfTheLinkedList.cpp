/*
 * Problem: Middle of the Linked List (LeetCode #876)
 * Link: https://leetcode.com/problems/middle-of-the-linked-list/description/
 *
 * Approach: This problem is solved using the optimal 'Tortoise and Hare' or
 *           'slow and fast pointer' algorithm.
 *           - Two pointers, `slow` and `fast`, are initialized to the head.
 *           - The `fast` pointer moves two steps at a time, while the `slow`
 *             pointer moves one step.
 *           - When the `fast` pointer reaches the end of the list, the `slow`
 *             pointer will be at the middle node.
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

ListNode* middleNode(ListNode* head);

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

    ListNode* middle = middleNode(head);

    cout << "Middle of the Linked List: [ ";
    temp = middle;
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

ListNode* middleNode(ListNode* head) {
  ListNode* slow = head;
  ListNode* fast = head;

  while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
  }

  return slow;
}
