/*
 * Problem: Add Two Numbers (LeetCode #2)
 * Link: https://leetcode.com/problems/add-two-numbers/description/
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
 * Approach: This iterative approach simulates elementary school addition.
 *           1. A `dummy` head node is created to simplify building the result
 *              list.
 *           2. A `carry` variable is initialized to 0.
 *           3. We loop as long as either list has nodes or there's a remaining
 *              carry.
 *           4. In each iteration, we sum the values of the current nodes (if
 *              they exist) and the carry, create a new node with the unit
 *              digit of the sum, and update the carry with the tens digit.
 *
 * Time Complexity: O(max(N, M)) where N and M are lengths of the lists.
 * Space Complexity: O(max(N, M)) for the new result list.
 */
ListNode* iterativeApproach(ListNode* l1, ListNode* l2);

/**
 * Approach: This approach uses recursion to perform the addition.
 *           1. The base case for the recursion is when both lists are NULL and
 *              there is no carry.
 *           2. In each call, we sum the values of the current nodes and the
 *              carry.
 *           3. A new node is created with the unit digit of the sum.
 *           4. The `next` pointer of this new node is set to the result of a
 *              recursive call on the next nodes with the new carry.
 *
 * Time Complexity: O(max(N, M))
 * Space Complexity: O(max(N, M)) for the result list and recursion stack.
 */
ListNode* recursiveApproach(ListNode* l1, ListNode* l2);
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2, int carry);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n1, n2;
    cin >> n1 >> n2;

    // Build list 1
    ListNode* dummy1 = new ListNode(0);
    ListNode* temp = dummy1;
    for (int i = 0; i < n1; i++) {
      int x;
      cin >> x;
      temp->next = new ListNode(x);
      temp = temp->next;
    }
    ListNode* l1 = dummy1->next;
    delete dummy1;

    // Build list 2
    ListNode* dummy2 = new ListNode(0);
    temp = dummy2;
    for (int i = 0; i < n2; i++) {
      int x;
      cin >> x;
      temp->next = new ListNode(x);
      temp = temp->next;
    }
    ListNode* l2 = dummy2->next;
    delete dummy2;

    cout << "List 1: [ ";
    temp = l1;
    while (temp != NULL) {
      cout << temp->val << " ";
      temp = temp->next;
    }
    cout << "]" << endl;

    cout << "List 2: [ ";
    temp = l2;
    while (temp != NULL) {
      cout << temp->val << " ";
      temp = temp->next;
    }
    cout << "]" << endl;

    // Uncomment the approach to be used.
    ListNode* result = iterativeApproach(l1, l2);
    // ListNode* result = recursiveApproach(l1, l2);

    cout << "Sum List: [ ";
    temp = result;
    while (temp != NULL) {
      cout << temp->val << " ";
      temp = temp->next;
    }
    cout << "]" << endl;

    // Clean up memory for all lists.
    auto deleteList = [](ListNode* head) {
      while (head) {
        ListNode* toDelete = head;
        head = head->next;
        delete toDelete;
      }
    };
    deleteList(l1);
    deleteList(l2);
    deleteList(result);

    cout << endl;
  }

  return 0;
}

//----------------------------ITERATIVE APPROACH--------------------------------
ListNode* iterativeApproach(ListNode* l1, ListNode* l2) {
  ListNode* head = new ListNode(0);
  ListNode* iter = head;

  ListNode* iter1 = l1;
  ListNode* iter2 = l2;
  int carry = 0;
  while (iter1 != NULL || iter2 != NULL || carry > 0) {
    int val1 = (iter1 == NULL) ? 0 : iter1->val;
    int val2 = (iter2 == NULL) ? 0 : iter2->val;
    int total = val1 + val2 + carry;
    carry = total / 10;

    ListNode* newNode = new ListNode(total % 10);
    iter->next = newNode;
    iter = newNode;

    iter1 = (iter1 == NULL) ? NULL : iter1->next;
    iter2 = (iter2 == NULL) ? NULL : iter2->next;
  }

  iter = head->next;
  delete head;
  return iter;
}

//----------------------------RECURSIVE APPROACH--------------------------------
ListNode* recursiveApproach(ListNode* l1, ListNode* l2) {
  return addTwoNumbers(l1, l2, 0);
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2, int carry) {
  if (l1 == NULL && l2 == NULL && carry <= 0) {
    return NULL;
  }

  int val1 = (l1 == NULL) ? 0 : l1->val;
  int val2 = (l2 == NULL) ? 0 : l2->val;
  int total = val1 + val2 + carry;

  ListNode* nextNode = new ListNode(total % 10);

  l1 = (l1 == NULL) ? NULL : l1->next;
  l2 = (l2 == NULL) ? NULL : l2->next;

  nextNode->next = addTwoNumbers(l1, l2, total / 10);
  return nextNode;
}
