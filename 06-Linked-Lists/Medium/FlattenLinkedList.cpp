/*
 * Problem: Flatten a Linked List
 * Link: https://www.geeksforgeeks.org/problems/flattening-a-linked-list/1
 *
 * Approach: This solution uses a divide-and-conquer strategy based on
 *           recursion. It works by treating the flattening process as a series
 *           of merge operations on sorted lists.
 *           1. The base case for the recursion is when the list is empty or
 *              has only one node in the `next` direction.
 *           2. For the recursive step, the function calls itself on
 *              `head->next`.
 *              This effectively flattens the rest of the main list first.
 *           3. The result of this recursive call is a single, fully flattened
 *              and sorted list, which is then merged with the current node's
 *              `bottom` list using a `mergeLists` helper function.
 *
 * Time Complexity: O(T), where T is the total number of nodes.
 * Space Complexity: O(N), where N is the number of horizontal nodes (recursion
 * stack).
 */

#include <algorithm>
#include <iostream>

using namespace std;

struct ListNode {
 public:
  int val;
  ListNode* next;
  ListNode* bottom;
  ListNode(int x) : val(x), next(NULL), bottom(NULL) {}
};

ListNode* flatten(ListNode* head);
ListNode* mergeLists(ListNode* head1, ListNode* head2);

int main() { return 0; }

ListNode* flatten(ListNode* head) {
  if (head == NULL || head->next == NULL) {
    return head;
  }

  ListNode* flattenedHead = flatten(head->next);
  head = mergeLists(head, flattenedHead);
  return head;
}

ListNode* mergeLists(ListNode* head1, ListNode* head2) {
  ListNode* dummy = new ListNode(0);
  ListNode* iter = dummy;

  ListNode* iter1 = head1;
  ListNode* iter2 = head2;

  while (iter1 != NULL && iter2 != NULL) {
    if (iter1->val <= iter2->val) {
      iter->bottom = iter1;
      iter = iter1;
      iter1 = iter1->bottom;
    } else {
      iter->bottom = iter2;
      iter = iter2;
      iter2 = iter2->bottom;
    }
  }

  if (iter1 != NULL) {
    iter->bottom = iter1;
  }
  if (iter2 != NULL) {
    iter->bottom = iter2;
  }

  ListNode* newHead = dummy->bottom;
  delete dummy;
  return newHead;
}
