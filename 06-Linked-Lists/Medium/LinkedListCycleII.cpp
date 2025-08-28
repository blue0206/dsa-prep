/*
 * Problem: Linked List Cycle II (LeetCode #142)
 * Link: https://leetcode.com/problems/linked-list-cycle-ii/description/
 *
 * Approach: This problem is solved using a two-phase extension of Floyd's
 *           'Tortoise and Hare' algorithm.
 *           Phase 1: Detect the cycle. Use a slow and a fast pointer. If they
 *           meet, a cycle exists. If the fast pointer reaches NULL, there is
 *           no cycle.
 *           Phase 2: Find the start of the cycle. After the pointers meet,
 *           reset one pointer (e.g., `slow`) back to the head of the list.
 *           Keep the other pointer (`fast`) at the meeting point. Now, move
 *           both pointers one step at a time. The node where they meet again
 *           is the starting node of the cycle. This is based on the
 *           mathematical property that the distance from the head to the cycle
 *           start is equal to the distance from the meeting point to the cycle
 *           start.
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

ListNode* detectCycle(ListNode* head);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, pos;
    cin >> n >> pos;

    if (n == 0) {
      ListNode* result = detectCycle(NULL);
      cout << "No cycle detected." << endl;
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

    ListNode* result = detectCycle(head);

    if (result) {
      cout << "Cycle starts at node with value: " << result->val << endl;
    } else {
      cout << "No cycle detected." << endl;
    }

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

ListNode* detectCycle(ListNode* head) {
  if (head == NULL || head->next == NULL) return NULL;

  ListNode* slow = head;
  ListNode* fast = head;

  // Phase 1: Find the meeting point inside the cycle.
  while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) {
      // Phase 2: Find the start of the cycle.
      // Reset one pointer to the head and move both one step at a time.
      slow = head;
      while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
      }
      return slow;
    }
  }

  // No cycle found.
  return NULL;
}
