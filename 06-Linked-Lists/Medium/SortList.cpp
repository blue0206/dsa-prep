/*
 * Problem: Sort List (LeetCode #148)
 * Link: https://leetcode.com/problems/sort-list/description/
 *
 * Approach: This solution implements the Merge Sort algorithm, which is highly
 *           efficient for linked lists as it doesn't rely on random access.
 *           1.  **Divide**: The list is recursively split into two halves. A
 *               `getMid` helper function uses the slow/fast pointer technique
 *               to find the middle, and the list is broken at that point.
 *           2.  **Conquer**: The `sortList` function is called recursively on
 *               both halves until the base case (a list with 0 or 1 nodes) is
 *               reached.
 *           3.  **Combine**: A `merge` helper function takes two sorted lists
 *               and combines them into a single, larger sorted list.
 *
 * Time Complexity: O(N log(N))
 * Space Complexity: O(log(N))
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

ListNode* sortList(ListNode* head);
ListNode* getMid(ListNode* head);
ListNode* merge(ListNode* list1, ListNode* list2);

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

    head = sortList(head);

    cout << "Sorted Linked List: [ ";
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

ListNode* sortList(ListNode* head) {
  if (head == NULL || head->next == NULL) {
    return head;
  }

  ListNode* mid = getMid(head);
  ListNode* rightHead = mid->next;
  mid->next = NULL;

  ListNode* list1 = sortList(head);
  ListNode* list2 = sortList(rightHead);
  return merge(list1, list2);
}

ListNode* getMid(ListNode* head) {
  if (head == NULL || head->next == NULL) return head;

  ListNode* slow = head;
  ListNode* fast = head->next->next;

  while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
  }

  return slow;
}

ListNode* merge(ListNode* list1, ListNode* list2) {
  ListNode* dummy = new ListNode(0);

  ListNode* iter1 = list1;
  ListNode* iter2 = list2;
  ListNode* iter = dummy;

  while (iter1 != NULL && iter2 != NULL) {
    if (iter1->val <= iter2->val) {
      iter->next = iter1;
      iter = iter1;
      iter1 = iter1->next;
    } else {
      iter->next = iter2;
      iter = iter2;
      iter2 = iter2->next;
    }
  }

  if (iter1 != NULL) {
    iter->next = iter1;
  }
  if (iter2 != NULL) {
    iter->next = iter2;
  }

  iter = dummy->next;
  delete dummy;
  return iter;
}
