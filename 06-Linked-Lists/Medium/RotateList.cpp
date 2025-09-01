/*
 * Problem: Rotate List (LeetCode #61)
 * Link: https://leetcode.com/problems/rotate-list/description/
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
 * Approach: This method calculates the effective number of rotations, finds the
 *           new tail of the list, and then re-links the segments.
 *           1. Calculate the list length `len` and the effective rotations
 *              `k = k % len`.
 *           2. If `k` is 0, no rotation is needed.
 *           3. Traverse `len - k - 1` nodes to find the node that will become
 *              the new tail of the rotated list.
 *           4. The node after this new tail is the new head.
 *           5. Split the list by setting the new tail's `next` to `NULL`.
 *           6. Traverse the second part to its end (the original tail) and
 *              link it to the original head.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
ListNode* splitAndRelinkApproach(ListNode* head, int k);
ListNode* reverseList(ListNode* head);
int getLen(ListNode* head);

/**
 * Approach: This elegant approach temporarily makes the list circular.
 *           1. Find the length `len` and the tail node in one pass.
 *           2. Connect the tail to the head, forming a circular list.
 *           3. Calculate the effective rotations `k = k % len`.
 *           4. Traverse `len - k` steps from the head to find the new tail.
 *           5. The node after the new tail becomes the new head.
 *           6. Break the circle by setting the new tail's `next` to `NULL`.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
ListNode* circularApproach(ListNode* head, int k);

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
    head = splitAndRelinkApproach(head, k);
    // head = circularApproach(head, k);

    cout << "Rotated Linked List: [ ";
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

//-------------------------SPLIT AND RELINK APPROACH----------------------------
ListNode* splitAndRelinkApproach(ListNode* head, int k) {
  if (head == NULL || head->next == NULL || k == 0) {
    return head;
  }

  // Get total length of list and calculate the
  // actual number of rotations.
  int len = getLen(head);
  int rotations = k % len;

  if (rotations == 0) {
    return head;
  }

  // 1. Find the pivot node, i.e., the tail of first half.
  ListNode* firstTail = head;
  for (int i = 1; i < len - rotations; i++) {
    firstTail = firstTail->next;
  }

  // 2. Store the head of next half.
  ListNode* secondHead = firstTail->next;
  // 3. Isolate the two halves.
  firstTail->next = NULL;

  // 4. Find the tail of second half.
  ListNode* secondTail = secondHead;
  while (secondTail->next != NULL) {
    secondTail = secondTail->next;
  }

  // 5. Connect tail of next half to head of first half
  //    Now, the new head is the head of next half.
  secondTail->next = head;
  return secondHead;
}

//-----------------------------CIRCULAR LL APPROACH-----------------------------
ListNode* circularApproach(ListNode* head, int k) {
  if (head == NULL || head->next == NULL || k == 0) {
    return head;
  }

  // Find the length and tail.
  ListNode* tail = head;
  int len = 1;
  while (tail->next != NULL) {
    len++;
    tail = tail->next;
  }
  // Find actual rotations.
  int rotations = k % len;
  if (rotations == 0) {
    return head;
  }

  // Connect tail to head and make LL circular.
  tail->next = head;

  // Find the tail of rotated LL.
  for (int i = 0; i < len - rotations; i++) {
    tail = tail->next;
  }

  // The new head is the node following the new tail
  // in circular LL.
  ListNode* newHead = tail->next;
  tail->next = NULL;

  return newHead;
}

//-----------------------------HELPER FUNCTIONS---------------------------------
int getLen(ListNode* head) {
  int len = 0;
  ListNode* iter = head;
  while (iter != NULL) {
    len++;
    iter = iter->next;
  }

  return len;
}

ListNode* reverseList(ListNode* head) {
  if (head == NULL || head->next == NULL) {
    return head;
  }

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
