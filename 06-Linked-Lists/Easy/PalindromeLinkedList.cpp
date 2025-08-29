/*
 * Problem: Palindrome Linked List (LeetCode #234)
 * Link: https://leetcode.com/problems/palindrome-linked-list/description/
 *
 * Approach: This approach finds if a list is a palindrome in O(1) space by
 *           manipulating the list in-place.
 *           1. A helper function `getNodeBeforeMid` uses a slow and fast
 *              pointer to find the last node of the first half.
 *           2. The list is explicitly split into two halves by setting the
 *              `next` pointer of this "pre-middle" node to `NULL`.
 *           3. The second half of the list is reversed using an iterative
 *              approach.
 *           4. The first half and the reversed second half are then compared
 *              node by node.
 *           5. Finally, the list is restored to its original state by reversing
 *              the second half again and re-linking it.
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

bool isPalindrome(ListNode* head);
ListNode* getNodeBeforeMid(ListNode* head);
ListNode* reverseList(ListNode* head);

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

    cout << "Result: " << (isPalindrome(head) ? "True" : "False") << endl;

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

bool isPalindrome(ListNode* head) {
  if (head->next == NULL) {
    return true;
  }

  // Get node right before mid and set its next
  // to NULL to clearly divide the list.
  ListNode* firstTail = getNodeBeforeMid(head);
  ListNode* mid = firstTail->next;
  firstTail->next = NULL;

  // Get head after reversing the second half.
  ListNode* newHead = reverseList(mid);

  // Check palindrome.
  ListNode* first = head;
  ListNode* second = newHead;
  // We only need to check upto the size of second half.
  while (second != NULL) {
    if (first->val != second->val) {
      // Reverse the second half again to get original list.
      mid = reverseList(newHead);
      // Reconnect the two halves of lists.
      firstTail->next = mid;
      return false;
    }
    first = first->next;
    second = second->next;
  }

  // Reverse the second half again to get original list.
  mid = reverseList(newHead);
  // Reconnect the two halves of lists.
  firstTail->next = mid;

  return true;
}

ListNode* getNodeBeforeMid(ListNode* head) {
  ListNode* slow = head;
  ListNode* fast = head->next;

  while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
  }

  return slow;
}

ListNode* reverseList(ListNode* head) {
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
