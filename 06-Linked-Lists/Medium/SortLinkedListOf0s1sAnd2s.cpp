/*
 * Problem: Sort Linked List Of 0s, 1s, and 2s
 * Link:
 * https://www.naukri.com/code360/problems/sort-linked-list-of-0s-1s-2s_1071937?leftPanelTabValue=PROBLEM
 *
 * Approach: This approach sorts the list by partitioning it into three
 *           separate lists: one for 0s, one for 1s, and one for 2s.
 *           1. Three dummy nodes are created to act as heads for the 0, 1, and
 *              2 lists, with corresponding pointers to track the tail of each.
 *           2. The original list is traversed once. Each node is appended to
 *              the end of the appropriate sub-list.
 *           3. After the traversal, the three sub-lists are concatenated in
 *              the correct order (0s -> 1s -> 2s).
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

ListNode* sortList(ListNode* head);

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
  if (head == NULL || head->next == NULL) return head;

  ListNode* dummy0 = new ListNode(0);
  ListNode* dummy1 = new ListNode(0);
  ListNode* dummy2 = new ListNode(0);

  ListNode* iter0 = dummy0;
  ListNode* iter1 = dummy1;
  ListNode* iter2 = dummy2;
  ListNode* iter = head;
  while (iter != NULL) {
    if (iter->val == 0) {
      iter0->next = iter;
      iter0 = iter;
    } else if (iter->val == 1) {
      iter1->next = iter;
      iter1 = iter;
    } else {
      iter2->next = iter;
      iter2 = iter;
    }
    iter = iter->next;
  }

  iter0->next = dummy1->next;  // Link tail of 0s list to head of 1s list
  iter1->next = dummy2->next;  // Link tail of 1s list to head of 2s list
  iter2->next = NULL;          // Terminate the final list
  iter0 = dummy0->next;
  delete dummy0;
  delete dummy1;
  delete dummy2;
  return iter0;
}
