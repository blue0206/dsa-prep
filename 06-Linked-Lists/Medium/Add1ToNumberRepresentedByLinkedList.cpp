/*
 * Problem: Add 1 To A Number Represented By Linked List
 * Link:
 * https://www.naukri.com/code360/problems/add-one-to-a-number-represented-as-linked-list_920557?leftPanelTabValue=PROBLEM
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
 * Approach: This approach first reverses the linked list to make addition
 *           easier (from least significant to most significant digit). It then
 *           iterates through the reversed list, adding 1 and handling any
 *           carry. If a carry remains after traversing the entire list (e.g.,
 *           for 999 + 1), a new head node is created. Finally, the list is
 *           reversed back to its original order.
 *
 * Time Complexity: O(3N)
 * Space Complexity: O(1)
 */
ListNode* reverseApproach(ListNode* head);
ListNode* reverseList(ListNode* head);

/**
 * Approach: This approach uses recursion to traverse to the end of the list
 *           first. The addition starts from the last node. The function returns
 *           a `carry` value back up the call stack. Each node adds the incoming
 *           carry to its value, updates itself, and passes a new carry to its
 *           predecessor. If a carry propagates all the way to the head, a new
 *           head node is created.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N) due to recursion call stack
 */
ListNode* recursiveApproach(ListNode* head);
int addOne(ListNode* head);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

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
    head = reverseApproach(head);
    // head = recursiveApproach(head);

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

//-----------------------------REVERSE APPROACH---------------------------------
ListNode* reverseApproach(ListNode* head) {
  if (head == NULL) return NULL;

  ListNode* reverseHead = reverseList(head);

  int carry = 1;
  ListNode* iter = reverseHead;

  while (iter != NULL && carry > 0) {
    int newVal = iter->val + carry;
    iter->val = newVal % 10;
    carry = newVal / 10;
    iter = iter->next;
  }

  if (carry > 0) {
    ListNode* newHead = new ListNode(carry);
    newHead->next = reverseHead;
    return newHead;
  }

  return reverseList(reverseHead);
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

//------------------------------RECURSIVE APPROACH------------------------------
ListNode* recursiveApproach(ListNode* head) {
  if (head == NULL) return NULL;

  int carry = addOne(head);
  if (carry > 0) {
    ListNode* newHead = new ListNode(carry);
    newHead->next = head;
    return newHead;
  }

  return head;
}

int addOne(ListNode* head) {
  if (head->next == NULL) {
    int newVal = head->val + 1;
    head->val = newVal % 10;
    return newVal / 10;
  }

  int carry = addOne(head->next);
  int newVal = head->val + carry;
  head->val = newVal % 10;
  return newVal / 10;
}
