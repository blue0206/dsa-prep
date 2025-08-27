/*
 * Problem: Linked List Cycle (LeetCode #141)
 * Link: https://leetcode.com/problems/linked-list-cycle/description/
 *
 * Approach: This problem is solved using the optimal 'Tortoise and Hare' or
 *           'slow and fast pointer' algorithm.
 *           - Two pointers, `slow` and `fast`, are initialized to the head.
 *           - The `fast` pointer moves two steps at a time, while the `slow`
 *             pointer moves one step.
 *           - If there is a cycle, the `fast` pointer will eventually lap the
 *             `slow` pointer, and they will meet. If there is no cycle, the
 *             `fast` pointer will reach the end of the list (NULL).
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

bool hasCycle(ListNode* head);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, pos;
    cin >> n >> pos;

    if (n == 0) {
      cout << "Result: " << (hasCycle(NULL) ? "True" : "False") << endl;
      cout << endl;
      continue;
    }

    ListNode* head = new ListNode(0);
    ListNode* temp = head;
    ListNode* cycleNode = NULL;
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      temp->next = new ListNode(x);
      temp = temp->next;
      if (i == pos) {
        cycleNode = temp;
      }
    }
    head = head->next;

    // Create the cycle if pos is valid
    if (pos != -1) {
      temp->next = cycleNode;
    }

    cout << "Result: " << (hasCycle(head) ? "True" : "False") << endl;

    // Clean up memory
    if (pos != -1) {
      temp->next = NULL;  // Break the cycle to allow for proper deletion
    }
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

bool hasCycle(ListNode* head) {
  ListNode* slow = head;
  ListNode* fast = head;

  while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) return true;
  }

  return false;
}
