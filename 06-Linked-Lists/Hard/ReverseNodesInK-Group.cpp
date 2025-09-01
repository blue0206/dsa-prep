/*
 * Problem: Reverse Nodes in k-Group (LeetCode #25)
 * Link: https://leetcode.com/problems/reverse-nodes-in-k-group/description/
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
 * Approach: This approach uses a `dummy` node to simplify linking and a `prev`
 *           pointer to track the tail of the previously reversed group. It
 *           first calculates the total number of full k-groups. Then, it
 *           iterates that many times. In each iteration, it:
 *           1. Isolates the next k-group.
 *           2. Reverses the detached group using a helper function.
 *           3. Reconnects the `prev` tail to the new head of the reversed
 *              group, and the new tail of the reversed group to the start of
 *              the next segment.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
ListNode* iterativeApproach(ListNode* head, int k);
ListNode* reverseList(ListNode* head);
int getLen(ListNode* head);

/**
 * Approach: This approach uses recursion to solve the problem.
 *           1. The base case is when the remaining list has fewer than `k`
 *              nodes; in this case, the list is returned as is.
 *           2. For the recursive step, it first reverses the initial `k` nodes
 *              of the current list. The original head of this group becomes
 *              the new tail.
 *           3. It then recursively calls the function on the rest of the list.
 *           4. Finally, it links the new tail's `next` pointer to the result
 *              of the recursive call and returns the new head of the reversed
 *              k-group.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N/k) for recursive call stack
 */
ListNode* recursiveApproach(ListNode* head, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;

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
    head = iterativeApproach(head, k);
    // head = recursiveApproach(head, k);

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

//-----------------------------ITERATIVE APPROACH-------------------------------
ListNode* iterativeApproach(ListNode* head, int k) {
  int len = getLen(head);

  int possibleGroups = len / k;

  ListNode* dummy = new ListNode(0);
  dummy->next = head;

  ListNode* prev = dummy;
  for (int i = 0; i < possibleGroups; i++) {
    // 1. Find the end of the current group.
    ListNode* curr = prev->next;
    for (int j = 1; j < k; j++) {
      curr = curr->next;
    }

    // 2. Save the start of the next group.
    ListNode* nextHalf = curr->next;
    // 3. Separate the current group by cutting the link.
    curr->next = NULL;

    // 4. Save the head of the current group
    //    as it will be the new tail.
    ListNode* newTail = prev->next;
    // 5. Reverse the separated group.
    prev->next = reverseList(prev->next);
    // 6. Link the new tail to the rest of the list
    newTail->next = nextHalf;
    // 7. Update `prev` for the next iteration
    prev = newTail;
  }

  ListNode* newHead = dummy->next;
  delete dummy;
  return newHead;
}

//-----------------------------RECURSIVE APPROACH-------------------------------
ListNode* recursiveApproach(ListNode* head, int k) {
  // Feasibility Check (Base Case: There must be at least k nodes).
  ListNode* iter = head;
  for (int i = 0; i < k; i++) {
    if (iter == NULL) return head;
    iter = iter->next;
  }

  // 1. Reverse the first k nodes (iterative reversal is efficient)
  ListNode* tail = head;
  for (int i = 1; i < k; i++) {
    tail = tail->next;
  }
  ListNode* nextHalf = tail->next;
  // 2. Separate the current group by cutting the link.
  tail->next = NULL;
  // 3. Save the original head, which will be the new tail.
  tail = head;

  // 4. Reverse the isolated group.
  ListNode* newHead = reverseList(head);
  // 5. Link the new tail to the result of the recursion.
  tail->next = recursiveApproach(nextHalf, k);
  return newHead;
}

//---------------------------HELPER FUNCTIONS-----------------------------------
ListNode* reverseList(ListNode* head) {
  if (head == NULL || head->next == NULL) return head;

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

int getLen(ListNode* head) {
  int len = 0;
  ListNode* iter = head;
  while (iter != NULL) {
    len++;
    iter = iter->next;
  }
  return len;
}
